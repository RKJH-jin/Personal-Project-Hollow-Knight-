#include "stdafx.h"
#include "MapToolScene.h"
#include "MapToolMouse.h"
#include "StuffObject.h"

HRESULT MapToolScene::init()
{
	Scene::init();
	SOUNDMANAGER->stop("title");
	SOUNDMANAGER->play("map");

	_camera = CAMERAMANAGER->GetMainCamera();

	//�� ���� �� �ʱ�ȭ
	_mapM = new MapManager;
	_mapM->init();

	//���콺 ���� �� �ʱ�ȭ
	_mouse = new MapToolMouse(this);
	_mouse->Init();


	//�����͸Ŵ����� ����
	DATAMANAGER->SetLinkMapToolScene(this);

	//UI ����
	AddUI();
	return S_OK;
}

void MapToolScene::release()
{
	Scene::release();

	_mapM->release();
	delete _mapM;
}

void MapToolScene::update()
{
	Scene::update();

    if (KEYMANAGER->isOnceKeyDown(VK_F1)) Save();
    if (KEYMANAGER->isOnceKeyDown(VK_F2)) Load();

    DATAMANAGER->UpdateTime();

	_mouse->Update();

	_mapM->update();

	for (int i = 0; i < _vUI.size(); i++)
	{
		_vUI[i]->update();
	}
}

void MapToolScene::render()
{
	//�� ����
	_mapM->render();

	//���콺 ����
	_mouse->Render();

	//������ ����
	renderUI();
}


void MapToolScene::MouseEnter()
{

}

void MapToolScene::MouseStay()
{
}

void MapToolScene::MouseExit()
{
}

void MapToolScene::Save()
{
    ofstream output("SaveData.txt");

    boost::archive::text_oarchive oa(output);
    oa << _mapM;
    DATAMANAGER->Save();
}

void MapToolScene::Load()
{
    MapManager* temp;
    temp = new MapManager();

    ifstream input("SaveData.txt");
    boost::archive::text_iarchive ia(input);

    ia >> temp;
    *(_mapM->GetTileMap()) = *(temp->GetTileMap());

    delete temp;

    DATAMANAGER->Load();
}