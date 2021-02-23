#include "stdafx.h"
#include "TileObject.h"

TileObject::TileObject(TILEOBJECT type)
{
	_info._type = (int)type;
	_info._attribute = TILEATTRIBUTE::OBJECT;
	_type = type;
	_info._direction = DIRECTION::FRONT;

	_frame[0] = 0;		//��
	_frame[1] = 2;		//��
	_frame[2] = 1;		//��
	_frame[3] = 2;		//��

	_key = DATAMANAGER->_vStr_buf[(int)type * 10 + 0];
	_name = DATAMANAGER->_vStr_buf[(int)type * 10 + 1];
	_description = DATAMANAGER->_vStr_buf[(int)type * 10 + 5];

	_info._count = Vector2(stoi(DATAMANAGER->_vStr_buf[(int)type * 10 + 2]), stoi(DATAMANAGER->_vStr_buf[(int)type * 10 + 3]));
	_info._price = stoi(DATAMANAGER->_vStr_buf[(int)type * 10 + 4]);

	_description = _description + "\n������ " + to_string(_info._price) + "���Դϴ�.";

	switch (type)
	{
	case TILEOBJECT::����������:
		_vUsable.push_back(Vector2(0, 0));
		_vUsable.push_back(Vector2(1, 0));
		break;
	case TILEOBJECT::��Ĵ�:
		_vUsable.push_back(Vector2(0, 0));
		_vUsable.push_back(Vector2(1, 0));
		_vUsable.push_back(Vector2(2, 0));
		break;
	case TILEOBJECT::��ġ:
		_vUsable.push_back(Vector2(0, 0));
		_vUsable.push_back(Vector2(1, 0));
		_vUsable.push_back(Vector2(2, 0));
		_vUsable.push_back(Vector2(3, 0));
		break;
	case TILEOBJECT::����:
		_vUsable.push_back(Vector2(0, 0));
		break;
	case TILEOBJECT::�繫��å��:
		_vUsable.push_back(Vector2(0, 0));
		break;
	case TILEOBJECT::������:
		_vUsable.push_back(Vector2(0, 0));
		break;
	case TILEOBJECT::����������:
		break;
	case TILEOBJECT::����:
		_vUsable.push_back(Vector2(0, 0));
		_vUsable.push_back(Vector2(1, 0));
		break;
	case TILEOBJECT::��Ź:
		_vUsable.push_back(Vector2(0, 0));
		_vUsable.push_back(Vector2(1, 0));
		_vUsable.push_back(Vector2(2, 0));
		break;
	case TILEOBJECT::��ũ��:
		_vUsable.push_back(Vector2(0, 0));
		break;
	case TILEOBJECT::����:
		_vUsable.push_back(Vector2(0, 0));
		break;
	case TILEOBJECT::����öâ��:
		_vUsable.push_back(Vector2(0, 0));
		break;
	case TILEOBJECT::���Ǳ�:
		_vUsable.push_back(Vector2(0, 0));
		break;
	case TILEOBJECT::������:
		_vUsable.push_back(Vector2(0, 0));
		break;
	case TILEOBJECT::öâ��:
		_vUsable.push_back(Vector2(0, 0));
		break;
	case TILEOBJECT::ħ��:
		_vUsable.push_back(Vector2(0, 0));
		break;
	}

	_info._img = ImageManager::GetInstance()->FindImage(_key);
}

HRESULT TileObject::init()
{
	return E_NOTIMPL;
}

void TileObject::release()
{
}

void TileObject::update()
{
}

void TileObject::render()
{
	//���� �����̸� ���η� ������ �ش�.
	if (_info._direction == DIRECTION::LEFT) _info._img->SetReverseX(true);

	_info._img->FrameRender(_info._renderPos, _frame[(int)_info._direction], 0, CAMERAMANAGER->GetMainCamera());
}

void TileObject::Build(Vector2 index)
{
	TileAttribute::Build(index);


	_info._renderPos = Vector2(_info._pos.x + (GetCount().x*TILESIZE) / 2,
		_info._pos.y + (GetCount().y*TILESIZE) - _info._img->GetFrameSize().y / 2);

	if (_info._direction == DIRECTION::FRONT || _info._direction == DIRECTION::BACK)
	{

	}
	else if (_info._direction == DIRECTION::RIGHT || _info._direction == DIRECTION::LEFT)
	{
		//������̶�� �����´�.
		for (int i = 0; i < _vUsable.size(); i++)
		{
			_vUsable[i].Swap();
			_vUsable[i].Swap();
		}
	}

	for (int i = 0; i < _vUsable.size(); i++)
	{
		_vUsable[i].x += index.x;
		_vUsable[i].y += index.y;
	}
}

void TileObject::Destroy()
{
}

bool TileObject::CheckVoidIndex()
{
    if (!_vUsable.empty()) return true;
    return false;
}

Vector2* TileObject::GetVoidIndexfromVector()
{
	//���Ͱ� ��� ������ null�� ��ȯ�Ѵ�.
	if (_vUsable.empty()) return nullptr;

	//���Ͱ� ������� �ʴٸ� �ε����� �����Ѵ�.
	Vector2* index = &_vUsable[0];
	_vUsable.erase(_vUsable.begin());
	return index;
}

void TileObject::PutIndexToVector(Vector2* index)
{
	_vUsable.push_back(*index);
}
BOOST_CLASS_EXPORT(TileObject)