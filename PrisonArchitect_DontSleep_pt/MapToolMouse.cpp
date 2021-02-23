#include "stdafx.h"
#include "MapToolMouse.h"
#include "MapToolScene.h"
#include "AllComponents.h"
#include "Character.h"
#include "StuffObject.h"

MapToolMouse::MapToolMouse(MapToolScene* scene)
{
	_scene = scene;
	_tileMap = _scene->GetMapM()->GetTileMap();
}

void MapToolMouse::Init()
{
	_cameraPivot = GameObject::CreateObject();
	_cameraPivot->GetTransform()->SetPosition(Vector2(WINSIZEX / 2, WINSIZEY / 2));

	_cameraGoal = GameObject::CreateObject();
	_cameraGoal->GetTransform()->SetPosition(Vector2(WINSIZEX / 2, WINSIZEY / 2));

	_state = MOUSESTATE::SELECT;

	// ���콺 ����
	_mouseArea[0] = RectMakePivot(Vector2(0, 0), Vector2(WINSIZEX, 40), Pivot::LeftTop);
	_mouseArea[1] = RectMakePivot(Vector2(0, 0), Vector2(40, WINSIZEY), Pivot::LeftTop);
	_mouseArea[2] = RectMakePivot(Vector2(WINSIZEX - 40, 0), Vector2(40, WINSIZEY), Pivot::LeftTop);
	_mouseArea[3] = RectMakePivot(Vector2(0, WINSIZEY - 40), Vector2(WINSIZEX, 40), Pivot::LeftTop);
}

void MapToolMouse::Release()
{
}

void MapToolMouse::Update()
{
	Control();
	Move();
}

void MapToolMouse::Render()
{
	CAMERAMANAGER->GetMainCamera()->SetPos(Vector2(_cameraPivot->GetTransform()->GetPosition()));

	if (_isDragging)
	{
		if (_drag == MOUSEDRAG::LINE)
		{
			//�巡�� ���� �����Ѵ�.
			FloatRect dragRc = FloatRect(_startPoint.x, _startPoint.y, _endPoint.x + TILESIZE, _endPoint.y + TILESIZE);
			dragRc = CAMERAMANAGER->GetVCamera()[0]->GetRelativePos(dragRc);
			_D2DRenderer->DrawRectangle(dragRc, D2D1::ColorF::ForestGreen, 0.5f, 10.0f);
		}
		else
		{
			//�巡�� ��Ʈ�� �����Ѵ�.
			FloatRect dragRc = FloatRect(_startPoint.x, _startPoint.y, _endPoint.x + TILESIZE, _endPoint.y + TILESIZE);
			dragRc = CAMERAMANAGER->GetMainCamera()->GetRelativePos(dragRc);
			_D2DRenderer->FillRectangle(dragRc, D2D1::ColorF::ForestGreen, 0.5f);
		}
	}

	switch (_state)
	{
		case MOUSESTATE::BUILD:
			BuildRender();
		break;
		case MOUSESTATE::DESTROY:

		break;
		case MOUSESTATE::SELECT:
			if (_selectObj)
			{
				FloatRect objRc = FloatRect(_selectObj->GetInfo()._pos.x, _selectObj->GetInfo()._pos.y, _selectObj->GetInfo()._pos.x + _selectObj->GetCount().x*TILESIZE, _selectObj->GetInfo()._pos.y + _selectObj->GetCount().y*TILESIZE);
				objRc = CAMERAMANAGER->GetMainCamera()->GetRelativePos(objRc);
				_D2DRenderer->FillRectangle(objRc, D2D1::ColorF::Yellow, 0.7f);
			}
		break;
		case MOUSESTATE::DELETECHAR:
			{
				wstring text = L"�ذ�";
				_D2DRenderer->RenderText(_ptMouse.x, _ptMouse.y, text, 20 * CAMERAMANAGER->GetVCamera()[0]->_zoom, D2DRenderer::DefaultBrush::Red, DWRITE_TEXT_ALIGNMENT_LEADING);

			}
		break;
	}
}

void MapToolMouse::BuildRender()
{
	if (_selectChar)
	{
		_selectChar->GetTransform()->SetPosition(CAMERAMANAGER->GetMainCamera()->GetAbsolutePos(_ptMouse));
		_selectChar->Render();
	}

	if (!_isOnUI && _selectObj)
	{
		switch (_selectObj->GetInfo()._attribute)
		{
		case TILEATTRIBUTE::TERRAIN:
		{
			_selectObj->GetInfo()._renderPos = Vector2(_endPoint.x + TILESIZE / 2, _endPoint.y + TILESIZE / 2);
			_selectObj->render();
		}
		break;
		case TILEATTRIBUTE::WALL:
		{
			_selectObj->GetInfo()._img->FrameRender(Vector2(_endPoint.x + (_selectObj->GetInfo()._count.y * TILESIZE) - TILESIZE / 2,
				_endPoint.y + (_selectObj->GetInfo()._count.x*TILESIZE) - _selectObj->GetInfo()._img->GetFrameSize().y / 2)
				, 1, 3, CAMERAMANAGER->GetVCamera()[0]);
		}
		break;
		case TILEATTRIBUTE::OBJECT:
		{
			//������Ʈ�� �����ϴ� �ε��� ��Ʈ�� �����Ѵ�.
			FloatRect objRc;

			objRc = FloatRect(_endPoint.x, _endPoint.y, _endPoint.x + _selectObj->GetCount().x*TILESIZE, _endPoint.y + _selectObj->GetCount().y*TILESIZE);
			objRc = CAMERAMANAGER->GetVCamera()[0]->GetRelativePos(objRc);

			if (_tileMap->CanBuildTile(_endIndex, _selectObj)) _D2DRenderer->FillRectangle(objRc, D2D1::ColorF::ForestGreen, 0.7f);
			else _D2DRenderer->FillRectangle(objRc, D2D1::ColorF::HotPink, 0.7f);

			//�����̶�� �̹����� ���η� �����´�.
			if (_selectObj->GetInfo()._direction == DIRECTION::LEFT) _selectObj->GetInfo()._img->SetReverseX(true);

			//���콺�� ������Ʈ�� �����Ѵ�.
			_selectObj->GetInfo()._img->SetAlpha(0.5f);
			_selectObj->GetInfo()._renderPos = Vector2(_endPoint.x + (_selectObj->GetCount().x * TILESIZE) / 2,
				_endPoint.y + (_selectObj->GetCount().y*TILESIZE) - _selectObj->GetInfo()._img->GetFrameSize().y / 2);

			_selectObj->render();

		}
		break;
		case TILEATTRIBUTE::AREA:
		{
			wstring text = TextC::ConvertStringToWstring(_selectObj->GetName());
			_D2DRenderer->RenderText(_ptMouse.x, _ptMouse.y, text, 20 * CAMERAMANAGER->GetVCamera()[0]->_zoom, D2DRenderer::DefaultBrush::Blue, DWRITE_TEXT_ALIGNMENT_LEADING);
		}
		break;
		}
	}

}

void MapToolMouse::Control()
{
	//UI�� �����ϴ� ���
	OnUICheck();
	UIControl();

	if (_isOnUI)
	{
		UIControl();
		return;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (DATAMANAGER->GetInfo().gameSpeed == 0) { DATAMANAGER->GetInfo().gameSpeed = 1; }
		else DATAMANAGER->GetInfo().gameSpeed = 0;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		SOUNDMANAGER->play("click2");
		DeleteMouseObject();
	}

	switch (_state)
	{
	case MOUSESTATE::BUILD:		BuildControl();		break;
	case MOUSESTATE::DESTROY:	DestroyControl();	break;
	case MOUSESTATE::SELECT:	SelectControl();	break;
	case MOUSESTATE::DELETECHAR: DeleteControl(); break;
	}
}

void MapToolMouse::Move()
{

	if (_wheelMouse < -10) _wheelMouse = -10;
	if (_wheelMouse > 20) _wheelMouse = 20;

	//���콺 �ӵ�
	_speed = 3.0f / _scene->GetCamera()->_zoom;

	_zoom = ((float)(_wheelMouse)+10.0f) / 10.0f;

	if (_zoom < 0.1f) _zoom = 0.1f;
	if (_zoom > 3.0f) _zoom = 3.0f;

	//ī�޶� �Ǻ�
	if (_prevZoom < _zoom)	//���� �ٲ� �� ���� �ٲ۴�.
	{
		_prevZoom = _zoom;
		CAMERAMANAGER->GetMainCamera()->SetZoom(_zoom);
		_cameraGoal->GetTransform()->SetPosition(CAMERAMANAGER->GetMainCamera()->GetAbsolutePos(_ptMouse));
	}
	if (_prevZoom > _zoom)	//���� �ٲ� �� ���� �ٲ۴�.
	{
		_prevZoom = _zoom;
		CAMERAMANAGER->GetMainCamera()->SetZoom(_zoom);
	}

	//�ǹ��� �� ������ ������ ���Ѵ�.
	float angle = Math::GetAngle(_cameraPivot->GetTransform()->GetPosition().x, _cameraPivot->GetTransform()->GetPosition().y,
		_cameraGoal->GetTransform()->GetPosition().x, _cameraGoal->GetTransform()->GetPosition().y);

	//�ǹ��� �������� �̵� ��Ų��.
	if (Math::GetDistance(_cameraPivot->GetTransform()->GetPosition().x, _cameraPivot->GetTransform()->GetPosition().y,
		_cameraGoal->GetTransform()->GetPosition().x, _cameraGoal->GetTransform()->GetPosition().y) > 50.0f / _scene->GetCamera()->_zoom)
		_cameraPivot->GetTransform()->Translate(Vector2(cosf(angle) * _speed, -sinf(angle)*_speed));

	if (_isOnUI) return;

	//ȭ���� �����¿쿡 ������ ���콺 �̵�
	if (PtInRect(&_mouseArea[0].GetRect(), { (LONG)_ptMouse.x, (LONG)_ptMouse.y })
		|| KEYMANAGER->isStayKeyDown(VK_UP)
		|| KEYMANAGER->isStayKeyDown('W'))
		_cameraGoal->GetTransform()->Translate(Vector2(0.0f, -_speed*2));

	if (PtInRect(&_mouseArea[1].GetRect(), { (LONG)_ptMouse.x, (LONG)_ptMouse.y })
		|| KEYMANAGER->isStayKeyDown(VK_LEFT)
		|| KEYMANAGER->isStayKeyDown('A'))
		_cameraGoal->GetTransform()->Translate(Vector2(-_speed * 2, 0.0f));

	if (PtInRect(&_mouseArea[2].GetRect(), { (LONG)_ptMouse.x, (LONG)_ptMouse.y })
		|| KEYMANAGER->isStayKeyDown(VK_RIGHT)
		|| KEYMANAGER->isStayKeyDown('D'))
		_cameraGoal->GetTransform()->Translate(Vector2(_speed * 2, 0.0f));

	if (PtInRect(&_mouseArea[3].GetRect(), { (LONG)_ptMouse.x, (LONG)_ptMouse.y })
		|| KEYMANAGER->isStayKeyDown(VK_DOWN)
		|| KEYMANAGER->isStayKeyDown('S'))
		_cameraGoal->GetTransform()->Translate(Vector2(0.0f, _speed * 2));
}

void MapToolMouse::OnUICheck()
{
	// UI ���� ���� ���, ���콺 ���¸� UI�� �����Ѵ�.

	//UI
	for (UI* u : _scene->GetvUI())
	{
		for (int i = 0; i < u->GetvButton().size(); i++)
		{
			if (u->GetvButton()[i]->GetTransform()->GetFloatRect().PtInRect(_ptMouse))
			{
				_isOnUI = true;
				return;
			}
			else _isOnUI = false;
		}
	}
	for (BarButtonUI* u : _scene->GetvUnderBarUI())
	{
		if (u->getButton()->getRect()->PtInRect(_ptMouse))
		{
			_isOnUI = true;
			return;
		}
		else _isOnUI = false;
	}

	for (WindowUI* w : _scene->GetvUnderBarWindowUI())
	{
		if (w->getIsActive() && w->getRect()->PtInRect(_ptMouse))
		{
			_isOnUI = true;
			return;
		}
		else _isOnUI = false;
	}

	if (_scene->GetInfoUI()->GetActive() && _scene->GetInfoUI()->GetTransform()->GetFloatRect().PtInRect(_ptMouse))
	{
		_isOnUI = true;
		return;
	}
	else _isOnUI = false;

}

void MapToolMouse::UIControl()
{
	// UI ���� ���� ���, ���콺 ���¸� UI�� �����Ѵ�.
	for (BarButtonUI* u : _scene->GetvUnderBarUI())
	{
		u->update();
		if (u->getButton()->getRect()->PtInRect(_ptMouse))
		{
			_scene->GetDescriptionUI()->SetGameObject(u);

			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				SOUNDMANAGER->play("click1");
				if (u->GetName() == "�ذ�") _state = MOUSESTATE::DELETECHAR;
				if (_scene->GetCurrentUnderBarActive() == u) // â�� �����ִµ� �ش� â ��ư�� ������ �ش� â�� ����
				{
					u->setIsActive(false);
					u->getWindowUI()->setIsActive(false);
					_scene->SetCurrentUnderBarActive(nullptr);

					if (_selectObj != nullptr) DeleteMouseObject();
					break;
				}
				else if (_scene->GetCurrentUnderBarActive() != nullptr) // ���� �����ִ� â�� ������ 
				{
					_scene->GetCurrentUnderBarActive()->setIsActive(false); // ���� â�� ����
					_scene->GetCurrentUnderBarActive()->getWindowUI()->setIsActive(false);
					if (_selectObj != nullptr) DeleteMouseObject();
				}
				// ���� ���� â�� Ų��
				u->setIsActive(true);
				_scene->SetCurrentUnderBarActive(u);
				u->getWindowUI()->setIsActive(true);
				break;
			}
		}
		else if (u->getIsActive())
		{
			_scene->GetDescriptionUI()->SetGameObject(NULL);
		}
	}

	for (WindowUI* w : _scene->GetvUnderBarWindowUI())
	{
		if (!w->getIsActive()) continue;
		if (w->getRect()->PtInRect(_ptMouse))
		{
			for (Button* b : w->getVButton())
			{
				if (b->getRect()->PtInRect(_ptMouse))
				{
					_scene->GetDescriptionUI()->SetGameObject(b);

					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						SOUNDMANAGER->play("click2");
						DeleteMouseObject();
						_selectObj = DATAMANAGER->FindTileObject(b->GetKey());
						_selectChar = DATAMANAGER->FindCharacter(b->GetName());
						_state = MOUSESTATE::BUILD;
						break;
					}
				}
			}
		}
	}

	for (PlayButtonUI* u : _scene->GetvPlayButtonUI())
	{
		if (u->GetButton()->getRect()->PtInRect(_ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				SOUNDMANAGER->play("click3");
				char temp = u->GetButton()->GetName().back();
				DATAMANAGER->GetInfo().gameSpeed = temp - '0';
			}
		}
	}

	//UI
	for (UI* u : _scene->GetvUI())
	{
		for (int i = 0; i < u->GetvButton().size(); i++)
		{
			if (u->GetvButton()[i]->GetTransform()->GetFloatRect().PtInRect(_ptMouse))
			{
				_scene->GetDescriptionUI()->SetGameObject(u->GetvButton()[i]);
			}
		}
	}

	if (_scene->GetInfoUI()->GetTransform()->GetFloatRect().PtInRect(_ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) OnCollisionEnter(_scene->GetInfoUI());
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) OnCollisionStay(_scene->GetInfoUI());
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) OnCollisionExit(_scene->GetInfoUI());
	}

}

void MapToolMouse::BuildControl()
{

	// ���콺 ������Ʈ�� Ÿ�Կ� ���� �巡�׸� ����
	if (_selectObj)
	{
		switch (_selectObj->GetInfo()._attribute)
		{
		case TILEATTRIBUTE::TERRAIN:
			_drag = MOUSEDRAG::RECT;
			break;
		case TILEATTRIBUTE::WALL:
			_drag = MOUSEDRAG::LINE;
			break;
		case TILEATTRIBUTE::OBJECT:
			_drag = MOUSEDRAG::POINT;
			break;
		case TILEATTRIBUTE::AREA:
			_drag = MOUSEDRAG::RECT;
			break;
		}

		//R��ư�� ������ ȸ���Ѵ�.
		if (KEYMANAGER->isOnceKeyDown('R'))
		{
			int num = (int)_selectObj->GetInfo()._direction;
			if (num == (int)DIRECTION::RIGHT) num = -1;
			_selectObj->GetInfo()._direction = (DIRECTION)(num + 1);
		}

	}
	else if (_selectChar)
	{
		_drag = MOUSEDRAG::POINT;
	}
	else
	{
		_drag = MOUSEDRAG::POINT;

	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{

		//������ ������
		_startIndex.x = (int)CAMERAMANAGER->GetMainCamera()->GetAbsolutePos(_ptMouse).x / TILESIZE;
		_startIndex.y = (int)CAMERAMANAGER->GetMainCamera()->GetAbsolutePos(_ptMouse).y / TILESIZE;

		if (_startIndex.x < 0) _startIndex.x = 0;
		if (_startIndex.y < 0) _startIndex.y = 0;
		if (_startIndex.x >= _tileMap->GetCount().x) _startIndex.x = _tileMap->GetCount().x - 1;
		if (_startIndex.y >= _tileMap->GetCount().y) _startIndex.y = _tileMap->GetCount().y - 1;

		_startPoint.x = _startIndex.x * TILESIZE;
		_startPoint.y = _startIndex.y * TILESIZE;

		if (_drag != MOUSEDRAG::POINT) _isDragging = true;

		if (_selectObj && _drag == MOUSEDRAG::POINT)
		{
			SOUNDMANAGER->play("click5");

			TileAttribute* obj = DATAMANAGER->CreateTileObject(_selectObj->GetKey());
			obj->GetInfo()._direction = _selectObj->GetInfo()._direction;
			_tileMap->BuildTileObject(Vector2(_endIndex.x, _endIndex.y), obj);
		}

		if (_selectChar)
		{
			SOUNDMANAGER->play("click5");

			Character* charObj = DATAMANAGER->CreateCharacter(_selectChar->GetName());
			_scene->GetMapM()->CreateCharacter(Vector2(_endPoint.x + TILESIZE / 2, _endPoint.y + TILESIZE / 2), charObj);
		}
	}

	//������ ����
	_endIndex.x = (int)CAMERAMANAGER->GetVCamera()[0]->GetAbsolutePos(_ptMouse).x / TILESIZE;
	_endIndex.y = (int)CAMERAMANAGER->GetVCamera()[0]->GetAbsolutePos(_ptMouse).y / TILESIZE;

	if (_endIndex.x < 0) _endIndex.x = 0;
	if (_endIndex.y < 0) _endIndex.y = 0;
	if (_endIndex.x >= _tileMap->GetCount().x) _endIndex.x = _tileMap->GetCount().x - 1;
	if (_endIndex.y >= _tileMap->GetCount().y) _endIndex.y = _tileMap->GetCount().y - 1;

	_endPoint.x = _endIndex.x * TILESIZE;
	_endPoint.y = _endIndex.y * TILESIZE;

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		SOUNDMANAGER->play("click6");

		Vector2 tempPoint;
		if (_startPoint.x > _endPoint.x)
		{
			tempPoint.x = _startPoint.x;
			_startPoint.x = _endPoint.x;
			_endPoint.x = tempPoint.x;
		}

		if (_startPoint.y > _endPoint.y)
		{
			tempPoint.y = _startPoint.y;
			_startPoint.y = _endPoint.y;
			_endPoint.y = tempPoint.y;
		}

		if (_isDragging)
		{
			_vSelectIndex.clear();

			//���� ���� �ε������� ���� ���Ϳ� �ִ´�.
			for (int i = _startIndex.x; i < _endIndex.x + 1; i++)
			{
				for (int j = _startIndex.y; j < _endIndex.y + 1; j++)
				{
					_vSelectIndex.push_back(Vector2(i, j));
				}
			}
		}

		//�巡�׸� ����.
		_isDragging = false;

		switch (_drag)
		{
		case MOUSEDRAG::POINT:	//����Ʈ�� KeyDown���� �ٷ� �׸���.
			break;
		case MOUSEDRAG::LINE:
		{
			for (int i = 0; i < _vSelectIndex.size(); i++)
			{
				if (_vSelectIndex[i].x > _vSelectIndex[0].x && _vSelectIndex[i].x < _vSelectIndex[_vSelectIndex.size() - 1].x
					&&_vSelectIndex[i].y != _vSelectIndex[0].y&& _vSelectIndex[i].y < _vSelectIndex[_vSelectIndex.size() - 1].y) continue;
				_tileMap->BuildTileObject(Vector2(_vSelectIndex[i].x, _vSelectIndex[i].y), DATAMANAGER->CreateTileObject(_selectObj->GetKey()));
			}
		}
		break;
		case MOUSEDRAG::RECT:
		{
			if (_selectObj->GetInfo()._attribute == TILEATTRIBUTE::AREA)
			{
				TileAttribute* area = DATAMANAGER->CreateTileObject(_selectObj->GetKey());
				area->GetInfo()._count = Vector2(_endIndex.x - _startIndex.x + 1, _endIndex.y - _startIndex.y + 1);
				_tileMap->BuildTileObject(_startIndex, area);
			}
			else if (_selectObj->GetInfo()._attribute == TILEATTRIBUTE::TERRAIN)
			{
				for (int i = 0; i < _vSelectIndex.size(); i++)
				{
					_tileMap->BuildTileObject(Vector2(_vSelectIndex[i].x, _vSelectIndex[i].y), DATAMANAGER->CreateTileObject(_selectObj->GetKey()));
				}
			}
		}
		break;

		}
	}
}

void MapToolMouse::DestroyControl()
{
	if(_selectObj) _tileMap->DestroyTileObject(_selectObj);
	if (_selectChar) _scene->GetMapM()->DeleteCharacter(_charNum);
	DeleteMouseObject();
}

void MapToolMouse::SelectControl()
{
	//����
	if (_selectObj)
	{
		TileAttribute* tempObj = _tileMap->GetvTile()[_endIndex.y * _tileMap->GetCount().x + _endIndex.x]->MouseEnter();
		if (_selectObj == tempObj && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			SOUNDMANAGER->play("click7");
			DestroyControl();
			tempObj = NULL;
			return;
		}
	}

	//��� ����
	for (int i = 0; i < _scene->GetMapM()->GetVCharacter().size(); i++)
	{
		if (PtInRect(&(_scene->GetMapM()->GetVCharacter()[i]->GetTransform()->GetRect()), { (LONG)_ptMouse.x, (LONG)_ptMouse.y }))
		{
			Character* obj = _scene->GetMapM()->GetVCharacter()[i];
			_scene->GetDescriptionUI()->SetGameObject(obj);

			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_selectChar = obj;
				OnCollisionEnter(obj);

				_scene->GetInfoUI()->SetUI(new PrisonInfoUI(obj));
				_scene->GetInfoUI()->SetActive(true);
				_selectChar = NULL;
			}
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) OnCollisionStay(obj);
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) OnCollisionExit(obj);

			return;
		}
	}
	//���� ����
	for (int i = 0; i < _scene->GetMapM()->GetVStuffObj().size(); i++)
	{
		if (PtInRect(&(_scene->GetMapM()->GetVStuffObj()[i]->GetTransform()->GetRect()), { (LONG)_ptMouse.x, (LONG)_ptMouse.y }))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				SOUNDMANAGER->play("click2");
			}
			_scene->GetDescriptionUI()->SetGameObject(_scene->GetMapM()->GetVStuffObj()[i]);
			return;
		}
	}

	//Ÿ�� ����

	//������ ����
	_endIndex.x = (int)CAMERAMANAGER->GetVCamera()[0]->GetAbsolutePos(_ptMouse).x / TILESIZE;
	_endIndex.y = (int)CAMERAMANAGER->GetVCamera()[0]->GetAbsolutePos(_ptMouse).y / TILESIZE;

	if (_endIndex.x < 0) _endIndex.x = 0;
	if (_endIndex.y < 0) _endIndex.y = 0;
	if (_endIndex.x >= _tileMap->GetCount().x) _endIndex.x = _tileMap->GetCount().x - 1;
	if (_endIndex.y >= _tileMap->GetCount().y) _endIndex.y = _tileMap->GetCount().y - 1;

	_endPoint.x = _endIndex.x * TILESIZE;
	_endPoint.y = _endIndex.y * TILESIZE;

	_rollOverObj = _tileMap->GetvTile()[_endIndex.y * _tileMap->GetCount().x + _endIndex.x]->MouseEnter();
	_scene->GetDescriptionUI()->SetGameObject(_rollOverObj);

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		SOUNDMANAGER->play("click8");
		_selectObj = _tileMap->GetvTile()[_endIndex.y * _tileMap->GetCount().x + _endIndex.x]->MouseEnter();

	};
	//if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) OnCollisionEnter(_tileMap->GetvTile()[_ptMouse.y / TILESIZE * _tileMap->GetCount().x + _ptMouse.x / TILESIZE]);
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) OnCollisionStay(_tileMap->GetvTile()[_ptMouse.y / TILESIZE * _tileMap->GetCount().x + _ptMouse.x / TILESIZE]);
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))   OnCollisionExit(_tileMap->GetvTile()[_ptMouse.y / TILESIZE * _tileMap->GetCount().x + _ptMouse.x / TILESIZE]);

}

void MapToolMouse::DeleteControl()
{
	_scene->GetInfoUI()->SetActive(false);

	//����
	if (_selectChar)
	{
		for (int i = 0; i < _scene->GetMapM()->GetVCharacter().size(); i++)
		{
			if (PtInRect(&(_scene->GetMapM()->GetVCharacter()[i]->GetTransform()->GetRect()), { (LONG)_ptMouse.x, (LONG)_ptMouse.y }))
			{
				Character* tempObj = _scene->GetMapM()->GetVCharacter()[i];
				if (tempObj == _selectChar)
				{
					SOUNDMANAGER->play("click7");
					_charNum = i;
					DestroyControl();
					tempObj = NULL;

					_state = MOUSESTATE::DELETECHAR;
				}
			}
		}
	}
	else
	{
		//��� ����
		for (int i = 0; i < _scene->GetMapM()->GetVCharacter().size(); i++)
		{
			if (PtInRect(&(_scene->GetMapM()->GetVCharacter()[i]->GetTransform()->GetRect()), { (LONG)_ptMouse.x, (LONG)_ptMouse.y }))
			{
				Character* obj = _scene->GetMapM()->GetVCharacter()[i];

				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) _selectChar = obj;
			}
		}
	}
}

void MapToolMouse::DeleteMouseObject()
{
	_scene->GetInfoUI()->SetActive(false);

	_rollOverObj = NULL;

	_selectObj = NULL;
	_selectObj = NULL;

	_selectChar = NULL;
	_selectChar = NULL;
	
	_state = MOUSESTATE::SELECT;
	_scene->GetDescriptionUI()->SetGameObject(NULL);
	_isDragging = false;
}

