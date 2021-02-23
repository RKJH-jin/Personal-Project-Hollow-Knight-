#include "stdafx.h"
#include "MapManager.h"
#include "StuffObject.h"
#include "Character.h"

HRESULT MapManager::init()
{
	//Ÿ�� ���� �����Ѵ�.
	_tileMap = new TileMap;
	_tileMap->init();
	_tileMap->SetTileMap(Vector2(TILECOUNTX, TILECOUNTY));
    JPSMANAGER->SetLinkTileMap(_tileMap);
    JPSMANAGER->init();


	

	return S_OK;
}

void MapManager::release()
{
	_tileMap->release();

	delete _tileMap;

}

void MapManager::update()
{
	_tileMap->update();


	//ĳ����
	for (int i = 0; i != _vCharacter.size(); i++)
	{
		_vCharacter[i]->update();
	}
}

void MapManager::render()
{
	_tileMap->render();

	//�����
	for (int i = 0; i != _vCharacter.size(); i++)
	{
		_vYOrderObject.push_back(_vCharacter[i]);
	}

	// �� ������Ʈ ����
	for (int i = 0; i != _vStuffObj.size(); i++)
	{
		_vStuffObj[i]->render();
	}

	//Y_ORDER�� ���� �����Ѵ�.
	RenderYOrder();
}

StuffObject * MapManager::FindStuffObject(string key)
{
	for (int i = 0; i < _vStuffObj.size(); i++)
	{
		if (_vStuffObj[i]->GetName() == key)
		{
			return _vStuffObj[i];
		}
	}
	return nullptr;
}

void MapManager::CreateCharacter(Vector2 pos, Character * obj)
{
	obj->GetTransform()->SetPosition(pos);
	_vCharacter.push_back(obj);
}

void MapManager::DeleteCharacter(int index)
{
	delete _vCharacter[index];
	_vCharacter.erase(_vCharacter.begin() + index);
}

void MapManager::SortYOrder(int s, int e)
{
	if (s >= e) return;
	float pivot = _vYOrderObject[s]->GetTransform()->GetPosition().y;
	int left = s;
	int right = e;

	while (left <= right)
	{
		//left�� pivot�� ��, left�� ������ ++
		while (_vYOrderObject[left]->GetTransform()->GetPosition().y < pivot) ++left;

		//right�� pivot�� ��, left�� ũ�� --
		while (_vYOrderObject[right]->GetTransform()->GetPosition().y > pivot) --right;

		//left�� right ���� ������ ������ ������.
		if (left <= right)
		{
			swap(_vYOrderObject[left], _vYOrderObject[right]);
			++left; --right;
		}
	}

	//����Լ��� �¿츦 ������ �� �����Ѵ�.
	SortYOrder(s, right);
	SortYOrder(left, e);
}

void MapManager::RenderYOrder()
{

	// ���Ͱ� ������� return�Ѵ�.
	if (_vYOrderObject.empty()) return;

	//������ ���Ҹ� ó������ ������ �����Ѵ�.
	SortYOrder(0, _vYOrderObject.size() - 1);


	//�̹����� �����Ѵ�.
	for (int i = 0; i < _vYOrderObject.size(); i++)
	{
		_vYOrderObject[i]->Render();
	}

	//ĳ����
	for (int i = 0; i != _vCharacter.size(); i++)
	{
		_vCharacter[i]->render();
	}
	//���͸� ����.
	_vYOrderObject.clear();
}
