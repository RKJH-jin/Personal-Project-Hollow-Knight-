#include "stdafx.h"
#include "MapToolScene.h"
#include "UpperUI.h"
#include "Character.h"
#include "HelperUI.h"
void MapToolScene::AddUI()
{
	_vUI.push_back(new HelperUI);
	_vUI.push_back(new UpperUI);

	_descriptionUI = new DescriptionUI;
	_infoUI = new InfoUI;
	_infoUI->SetActive(false);

	addUnderBarUI("����", Vector2(50, WINSIZEY - 45), 0.7f, IMAGEMANAGER->FindImage("buttonBlue"), 0, 0);
	addUnderBarUI("��", Vector2(110, WINSIZEY - 45), 0.7f, IMAGEMANAGER->FindImage("buttonBlue"), 1, 0);
	addUnderBarUI("��ǰ", Vector2(170, WINSIZEY - 45), 0.7f, IMAGEMANAGER->FindImage("buttonGreen"), 3, 0);
	addUnderBarUI("����", Vector2(230, WINSIZEY - 45), 0.7f, IMAGEMANAGER->FindImage("buttonGray"), 0, 0);

	addUnderBarUI("�ο�", Vector2(1140, WINSIZEY - 45), 0.7f, IMAGEMANAGER->FindImage("buttonBlue"), 6, 0);
	addUnderBarUI("�ذ�", Vector2(1200, WINSIZEY - 45), 0.7f, IMAGEMANAGER->FindImage("buttonOrange"), 1, 0);

	addUnderBarWindowUI(Vector2(10 + 100, WINSIZEY - 275), Vector2(200, 400), 0.7f);		//����
	addUnderBarWindowUI(Vector2(10 + 100, WINSIZEY - 275), Vector2(200, 400), 0.7f);		//��
	addUnderBarWindowUI(Vector2(10 + 100, WINSIZEY - 275), Vector2(200, 400), 0.7f);		//��ǰ
	addUnderBarWindowUI(Vector2(10 + 100, WINSIZEY - 275), Vector2(200, 400), 0.7f);		//����

	addUnderBarWindowUI(Vector2(1140, WINSIZEY - 275), Vector2(200, 400), 0.7f);	//�ο�
	addUnderBarWindowUI(Vector2(1140, WINSIZEY - 275), Vector2(0, 0), 0.7f);		//�ذ�

	for (int i = 0; i < 6; ++i) setLinkUnderBarUI(i, i);

	// ������Ʈ ��ư ������ �߰�
	map<string, TileAttribute*>::iterator miTileObject;
	miTileObject = DATAMANAGER->GetMTileObject()->begin();

	int count = 0;
	for (; miTileObject != DATAMANAGER->GetMTileObject()->end(); )
	{
		if (miTileObject->second->GetInfo()._attribute == TILEATTRIBUTE::TERRAIN)
		{
			addObjectButtonUIInWindowUI(
				0,                                          // ���� �ε���
				miTileObject->second->GetName(),
				miTileObject->second->GetKey(),
				Vector2(10 + 25 + 50 * (count % 4), WINSIZEY / 2 - 90 + 50 * (count / 4)),
				Vector2(48, 48),
				Vector2(72, 72),
				IMAGEMANAGER->FindImage("terrain"),
				miTileObject->second->GetInfo()._frame
			);
			count++;
		}
		++miTileObject;
	}

	miTileObject = DATAMANAGER->GetMTileObject()->begin();
	count = 0;
	for (; miTileObject != DATAMANAGER->GetMTileObject()->end(); )
	{
		if (miTileObject->second->GetInfo()._attribute == TILEATTRIBUTE::WALL)
		{
			addObjectButtonUIInWindowUI(
				1,                                          // �� ������â �ε���
				miTileObject->second->GetName(),
				miTileObject->second->GetKey(),
				Vector2(10 + 25 + 50 * (count % 4), WINSIZEY / 2 - 90 + 50 * (count / 4)),
				Vector2(48, 48),
				Vector2(72, 72),
				IMAGEMANAGER->FindImage(miTileObject->second->GetKey()),
				Vector2(1, 3)
			);
			count++;
		}
		++miTileObject;
	}


	miTileObject = DATAMANAGER->GetMTileObject()->begin();
	count = 0;
	for (; miTileObject != DATAMANAGER->GetMTileObject()->end(); )
	{
		if (miTileObject->second->GetInfo()._attribute == TILEATTRIBUTE::OBJECT)
		{
			addObjectButtonUIInWindowUI(
				2,                                          // ��ǰ ������â �ε���
				miTileObject->second->GetName(),
				miTileObject->second->GetKey(),
				Vector2(10 + 25 + 50 * (count % 4), WINSIZEY / 2 - 90 + 50 * (count / 4)),
				Vector2(48, 48),
				Vector2(72, 72),
				IMAGEMANAGER->FindImage(miTileObject->second->GetKey()),
				Vector2(0, 0)
			);
			count++;
		}
		++miTileObject;
	}

	miTileObject = DATAMANAGER->GetMTileObject()->begin();
	count = 0;
	for (; miTileObject != DATAMANAGER->GetMTileObject()->end(); )
	{
		if (miTileObject->second->GetInfo()._attribute == TILEATTRIBUTE::AREA)
		{
			addObjectButtonUIInWindowUI(
				3,                                          // ���� ������â �ε���
				miTileObject->second->GetName(),
				miTileObject->second->GetKey(),
				Vector2(10 + 25 + 50 * (count % 4), WINSIZEY / 2 - 90 + 50 * (count / 4)),
				Vector2(48, 48),
				Vector2(72, 72),
				IMAGEMANAGER->FindImage("buttonGray"),
				Vector2(0, 0)
			);
			count++;
		}
		++miTileObject;
	}

	//������ư
	map<string, Character*>::iterator miChar;
	miChar = DATAMANAGER->GetMCharacter()->begin();
	count = 0;
	for (; miChar != DATAMANAGER->GetMCharacter()->end(); ++miChar)
	{
		addObjectButtonUIInWindowUI(
			4,                                          // ���� ������â �ε���
			miChar->second->GetName(),
			miChar->second->GetKey(),
			Vector2(1065 + 50 * (count % 4), WINSIZEY / 2 - 90 + 50 * (count / 4)),
			Vector2(48, 48),
			Vector2(72, 72),
			IMAGEMANAGER->FindImage(miChar->second->GetKey()),
			Vector2(0, 0)
		);
		count++;
	}

	// �ð� �߰�
	_clockUI = new ClockUI(Vector2(WINSIZEX / 2 + 550, WINSIZEY / 2 - 250), 0.8f, Vector2(200, 250));

	// �ӵ� ���� ��ư �߰�
	for (int i = 0; i < 5; ++i)
	{
		string name = "time_play" + to_string(i);
		addPlayButtonUI(name, Vector2(WINSIZEX / 2 + 475 + 35 * i, WINSIZEY / 2 - 150), Vector2(35, 24), 1.0f, IMAGEMANAGER->FindImage(name));
	}

	//�ϴ�
	_sky = FloatRect(Vector2(WINSIZEX / 2, WINSIZEY / 2), Vector2(WINSIZEX, WINSIZEY), Pivot::Center);
}


void MapToolScene::renderUI()
{
	//�ϴ�
	if (19 <= DATAMANAGER->GetInfo().time.hour && DATAMANAGER->GetInfo().time.hour < 21)
	{
		D2DRenderer::GetInstance()->FillRectangle(_sky, D2D1::ColorF::DarkOrange, DATAMANAGER->GetInfo().skyAlpha);
	}
	else
	{
		D2DRenderer::GetInstance()->FillRectangle(_sky, D2D1::ColorF::DarkBlue, DATAMANAGER->GetInfo().skyAlpha);
	}

	//UI
	for (int i = 0; i < _vUI.size(); i++)
	{
		_vUI[i]->render();
	}

	//�ð�
	_clockUI->render();
	Vector2 vTemp = Vector2(WINSIZEX / 2, WINSIZEY - 10);
	IMAGEMANAGER->FindImage("screenEdge")->SetScale(0.7f);
	IMAGEMANAGER->FindImage("screenEdge")->SetAlpha(0.8f);
	IMAGEMANAGER->FindImage("screenEdge")->Render(vTemp);

	for (BarButtonUI* u : _vUnderBarUI)
	{
		u->render();
	}

	for (WindowUI* u : _vUnderBarWindowUI)
	{
		u->render();
	}

	for (PlayButtonUI* u : _vPlayButtonUI)
	{
		u->render();
	}

	_infoUI->render();
	_descriptionUI->render();
}

void MapToolScene::addUnderBarUI(string strName, Vector2 pos, float scale, Image * img)
{
	BarButtonUI* temp = new BarButtonUI(strName, pos, scale, img);
	temp->setIsRender(true);
	_vUnderBarUI.push_back(temp);
}

void MapToolScene::addUnderBarUI(string strName, Vector2 pos, float scale, Image * img, int frameX, int frameY)
{
	BarButtonUI* temp = new BarButtonUI(strName, pos, scale, img, frameX, frameY);
	temp->setIsRender(true);
	_vUnderBarUI.push_back(temp);
}

void MapToolScene::addUnderBarWindowUI(Vector2 pos, Vector2 size, float scale)
{
	WindowUI* temp = new WindowUI(pos, size, scale);
	_vUnderBarWindowUI.push_back(temp);
}

void MapToolScene::addObjectButtonUIInWindowUI(int arrNum, string strName, string key, Vector2 pos, Vector2 rcSize, Vector2 imgSize, Image* img, Vector2 frame = Vector2(0, 0))
{
	_vUnderBarWindowUI[arrNum]->addObjectButtonUI(strName, key, pos, rcSize, imgSize, img, frame);
}

void MapToolScene::setLinkUnderBarUI(int arrNum, int arrNum2)
{
	_vUnderBarUI[arrNum]->setLinkWindowUI(_vUnderBarWindowUI[arrNum2]);
}

void MapToolScene::addSingleUI(string strName, Vector2 pos, float scale, Image * img)
{

}

void MapToolScene::addPlayButtonUI(string strName, Vector2 pos, Vector2 size, float scale, Image* img)
{
	PlayButtonUI* temp = new PlayButtonUI(strName, pos, size, scale, img);
	_vPlayButtonUI.push_back(temp);
}