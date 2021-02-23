#include "stdafx.h"
#include "TileMap.h"
#include "JumpPointSearch.h"

#include "TileAttribute.h"
#include "TileTerrain.h"

HRESULT TileMap::init()
{
	return S_OK;
}

void TileMap::release()
{
}

void TileMap::update()
{
}

void TileMap::render()
{
	//�ٴ� ����
	for (int i = 0; i < _tileCount; i++)
	{
		if (_vTile[i]->_terrain && _vTile[i]->_terrain->GetInfo()._startIndex == Vector2(i % (int)_count.x, i / (int)_count.x)) _vTile[i]->_terrain->render();
	}

	//���� ����
	for (int i = 0; i < _tileCount; i++)
	{
		if (_vTile[i]->_area && _vTile[i]->_area->GetInfo()._startIndex == Vector2(i % (int)_count.x, i / (int)_count.x)) _vTile[i]->_area->render();
	}
	
	//�� ����
	for (int i = 0; i < _tileCount; i++)
	{
		if (_vTile[i]->_wall && _vTile[i]->_wall->GetInfo()._startIndex == Vector2(i % (int)_count.x, i / (int)_count.x)) _vTile[i]->_wall->render();
	}

	
	//������Ʈ ����
	for (int i = 0; i < _tileCount; i++)
	{
		if (_vTile[i]->_tileObj && _vTile[i]->_tileObj->GetInfo()._startIndex == Vector2(i % (int)_count.x, i / (int)_count.x)) _vTile[i]->_tileObj->render();
	}
	
}
void TileMap::SetTileMap(Vector2 count)
{
	//x, y �ε��� ������ ���Ѵ�.
	_count = count;

	//Ÿ�� �� ������ ���Ѵ�.
	_tileCount = _count.x * _count.y;

	for (int i = 0; i < _tileCount; i++)
	{
		Tile* tile = new Tile;

		tile->_index = Vector2(i % (int)_count.x, i / (int)_count.x);

		_vTile.push_back(tile);

		BuildTileObject(tile->_index, DATAMANAGER->CreateTileObject("GRASS1"));
		tile->_wall = NULL;
		tile->_tileObj = NULL;
	}

}

void TileMap::BuildTileObject(Vector2 index, TileAttribute * tileObj)
{
	//���ܿ� �ش��ϸ� ������ ����.
	if (!CanBuildTile(index, tileObj)) return;

	tileObj->GetInfo()._startIndex = index;

	switch (tileObj->GetInfo()._attribute)
	{
	case TILEATTRIBUTE::END:

		break;
	case TILEATTRIBUTE::TERRAIN:
	{
		_vTile[index.y * _count.x + index.x]->_terrain = tileObj;
		tileObj->Build(index);
	}
	break;
	case TILEATTRIBUTE::WALL:
	{
		//�̹� ���� �ִµ�
		if (_vTile[index.y * _count.x + index.x]->_wall)
		{
			//Ÿ���� �ٸ��ٸ� ���� Ÿ���� �޸𸮸� �����Ѵ�.
			delete _vTile[index.y * _count.x + index.x]->_wall;
			_vTile[index.y * _count.x + index.x]->_wall = NULL;
		}

		//Ÿ���� ���� �� �ش�.
		tileObj->Build(index);

		_vTile[index.y * _count.x + index.x]->_wall = tileObj;
		_vTile[index.y * _count.x + index.x]->_wall->GetInfo()._startIndex = index;

		//�ֺ� �� Ÿ���� �˻��ϰ� �������� �ٲ� �ش�.
		_vTile[index.y * _count.x + index.x]->_wall->GetInfo()._frame = (GetWallFrame(index, tileObj));

		//��
		if(index.y - 1 >= 0 && _vTile[(index.y - 1) * _count.x + index.x]->_wall)
		{
			_vTile[(index.y - 1) * _count.x + index.x]->_wall->GetInfo()._frame = GetWallFrame(Vector2(index.x, index.y - 1), tileObj);
		}
		//��
		if (index.y + 1 < _count.y && _vTile[(index.y + 1) * _count.x + index.x]->_wall)
		{
			_vTile[(index.y + 1) * _count.x + index.x]->_wall->GetInfo()._frame = GetWallFrame(Vector2(index.x, index.y + 1), tileObj);
		}
		//��
		if (index.x - 1 >= 0 && _vTile[index.y * _count.x + index.x - 1]->_wall)
		{
			_vTile[index.y * _count.x + index.x - 1]->_wall->GetInfo()._frame = GetWallFrame(Vector2(index.x - 1, index.y), tileObj);
		}
		//��
		if (index.x + 1 < _count.x &&_vTile[index.y * _count.x + index.x + 1]->_wall)
		{
			_vTile[index.y * _count.x + index.x + 1]->_wall->GetInfo()._frame = GetWallFrame(Vector2(index.x + 1, index.y), tileObj);
		}

	}
	break;
	case TILEATTRIBUTE::OBJECT:
	{
		//������ ������ �Ǵ� �����̶�� �����ϴ� x, y ĭ�� ������ ������ �˻� �� �ش�.
		Vector2 count = tileObj->GetInfo()._count;
		if (tileObj->GetInfo()._direction == DIRECTION::RIGHT || tileObj->GetInfo()._direction == DIRECTION::LEFT)
		{
			count.x = tileObj->GetInfo()._count.y;
			count.y = tileObj->GetInfo()._count.x;
		}

		//���ܿ� �ش��ϸ� ������ ����.
		if (!CanBuildTile(index, tileObj)) return;
		

		//�ش� Ÿ�Ͽ� �ε����� �����, ������Ʈ�� ���� �ε����� �����Ѵ�.
		tileObj->Build(index);

		for (int i = 0; i < count.x; i++)
		{
			for (int j = 0; j < count.y; j++)
			{
				//ī��Ʈ �ε����� ���� �ش� ������Ʈ�� ��ũ ���� �ش�.
				_vTile[(index.y + j) * _count.x + index.x + i]->_tileObj = tileObj;
			}
		}
	}
	break;
	case TILEATTRIBUTE::AREA:
	{
		tileObj->GetInfo()._startIndex = index;
		Vector2 count = tileObj->GetInfo()._count;

		for (int i = 0; i < count.x; i++)
		{
			for (int j = 0; j < count.y; j++)
			{
				if (!CanBuildTile(Vector2(index.x+i,index.y+j), tileObj)) return;
			}
		}

		tileObj->Build(index);

		for (int i = 0; i < count.x; i++)
		{
			for (int j = 0; j < count.y; j++)
			{
				//ī��Ʈ �ε����� ���� �ش� ������Ʈ�� ��ũ ���� �ش�.
				_vTile[(index.y + j) * _count.x + index.x + i]->_area = tileObj;
			}
		}
	}
	break;
	}
	DATAMANAGER->GetInfo().money -= tileObj->GetInfo()._price;
}

void TileMap::DestroyTileObject(TileAttribute * tileObj)
{
	switch (tileObj->GetInfo()._attribute)
	{
		case TILEATTRIBUTE::TERRAIN:
		{
		}
		break;
		case TILEATTRIBUTE::WALL:
		{
			Vector2 index = tileObj->GetInfo()._startIndex;
			delete tileObj;

			_vTile[index.x + index.y * _count.x]->_wall = NULL;

			//��
			if (index.y - 1 >= 0 && _vTile[(index.y - 1) * _count.x + index.x]->_wall)
			{
				_vTile[(index.y - 1) * _count.x + index.x]->_wall->GetInfo()._frame = GetWallFrame(Vector2(index.x, index.y - 1), tileObj);
			}
			//��
			if (index.y + 1 < _count.y && _vTile[(index.y + 1) * _count.x + index.x]->_wall)
			{
				_vTile[(index.y + 1) * _count.x + index.x]->_wall->GetInfo()._frame = GetWallFrame(Vector2(index.x, index.y + 1), tileObj);
			}
			//��
			if (index.x - 1 >= 0 && _vTile[index.y * _count.x + index.x - 1]->_wall)
			{
				_vTile[index.y * _count.x + index.x - 1]->_wall->GetInfo()._frame = GetWallFrame(Vector2(index.x - 1, index.y), tileObj);
			}
			//��
			if (index.x + 1 < _count.x &&_vTile[index.y * _count.x + index.x + 1]->_wall)
			{
				_vTile[index.y * _count.x + index.x + 1]->_wall->GetInfo()._frame = GetWallFrame(Vector2(index.x + 1, index.y), tileObj);
			}
		}
		break;
		case TILEATTRIBUTE::OBJECT:
		{
			//������ ������ �Ǵ� �����̶�� �����ϴ� x, y ĭ�� ������ ������ �˻� �� �ش�.
			Vector2 count = tileObj->GetInfo()._count;
			if (tileObj->GetInfo()._direction == DIRECTION::RIGHT || tileObj->GetInfo()._direction == DIRECTION::LEFT)
			{
				count.x = tileObj->GetInfo()._count.y;
				count.y = tileObj->GetInfo()._count.x;
			}

			//���� �ε����������� ���������� Ÿ�Ͽ��� ������.
			for (int i = tileObj->GetInfo()._startIndex.x; i < tileObj->GetInfo()._startIndex.x + count.x; i++)
			{
				for (int j = tileObj->GetInfo()._startIndex.y; j < tileObj->GetInfo()._startIndex.y + count.y; j++)
				{
					//�ش� �ε����� Ÿ���� ������Ʈ�� ���� �ش�.
					_vTile[j * _count.x + i]->_tileObj = NULL;
				}
			}

			delete tileObj;

		}
		break;
		case TILEATTRIBUTE::AREA:
		{
			Vector2 count = tileObj->GetInfo()._count;
			Vector2 start = tileObj->GetInfo()._startIndex;

			for (int i = start.x; i < start.x + count.x; i++)
			{
				for (int j = start.y; j < start.y + count.y; j++)
				{
					//�ش� �ε����� Ÿ���� ������Ʈ�� ���� �ش�.
					_vTile[j * _count.x + i]->_area = NULL;
				}
			}
			delete tileObj;
		}
		break;
	}
}

Vector2 TileMap::GetWallFrame(Vector2 index, TileAttribute * tileObj)
{
	//�ֺ� �� Ÿ���� �˻��ϰ� �������� �ٲ� ��.
	int wall = 0;

	//��
	if ((index.y - 1) * _count.x + index.x >= 0				&& _vTile[(index.y - 1) * _count.x + index.x]->_wall) wall += 1;
	//��
	if ((index.y + 1) * _count.x + index.x < _tileCount		&& _vTile[(index.y + 1) * _count.x + index.x]->_wall) wall += 2;
	//��
	if (index.y * _count.x + index.x - 1 >= 0				&& _vTile[index.y * _count.x + index.x - 1]->_wall) wall += 4;
	//��
	if (index.y * _count.x + index.x + 1 < _tileCount		&& _vTile[index.y * _count.x + index.x + 1]->_wall) wall += 8;

	int wallIndex;
	Vector2 realIndex;

	switch (wall)
	{
		case 0:	 wallIndex = 22;	break;		//��
		case 1:	 wallIndex = 14;	break;		//��
		case 2:	 wallIndex = 7;		break;		//��
		case 3:	 wallIndex = 0;		break;		//����
		case 4:	 wallIndex = 15;	break;		//��
		case 5:	 wallIndex = 10;	break;		//����
		case 6:	 wallIndex = 3;		break;		//����
		case 7:	 wallIndex = 19;	break;		//������
		case 8:	 wallIndex = 8;		break;		//��
		case 9:	 wallIndex = 9;		break;		//���
		case 10: wallIndex = 2;		break;		//�Ͽ�
		case 11: wallIndex = 18;	break;		//���Ͽ�
		case 12: wallIndex = 1;		break;		//�¿�
		case 13: wallIndex = 11;	break;		//���¿�
		case 14: wallIndex = 4;		break;		//���¿�
		case 15: wallIndex = 20;	break;		//�����¿�
		default:
		break;
	}
	realIndex.x = wallIndex % 7;
	realIndex.y = wallIndex / 7;
	return realIndex;
}

bool TileMap::CanBuildTile(Vector2 index, TileAttribute * tileObj)
{
	//�������� ���ݺ��� ���� ��� ������ ����.
	if(DATAMANAGER->GetInfo().money < tileObj->GetInfo()._price) return false;

	//������ Ÿ�ϸ��� �Ѿ�� ������ ����.
	if (index.x >= _count.x - 1 || index.y >= _count.y - 1) return false;

	switch (tileObj->GetInfo()._attribute)
	{
		case TILEATTRIBUTE::TERRAIN:
		{
			//�̹� ���� Ÿ���� �ٴ��� �ִٸ� ������ �� ��.
			if (_vTile[index.y * _count.x + index.x]->_terrain && _vTile[index.y * _count.x + index.x]->_terrain->GetInfo()._type == tileObj->GetInfo()._type) return false;
		}
		break;
		case TILEATTRIBUTE::WALL:
		{
			//�̹� ������Ʈ�� �ִٸ� ������ �� ��.
			if (_vTile[(index.y) * _count.x + index.x]->_tileObj) return false;

			//�̹� ���� Ÿ���� ���� �ִٸ� ������ �� ��.
			 if (_vTile[index.y * _count.x + index.x]->_wall && _vTile[index.y * _count.x + index.x]->_wall->GetInfo()._type == tileObj->GetInfo()._type) return false;
		}
		break;
		case TILEATTRIBUTE::OBJECT:
		{
			//������ ������ �Ǵ� �����̶�� �����ϴ� x, y ĭ�� ������ ������ �˻� �� �ش�.
			Vector2 count = tileObj->GetInfo()._count;
			if (tileObj->GetInfo()._direction == DIRECTION::RIGHT || tileObj->GetInfo()._direction == DIRECTION::LEFT)
			{
				count.x = tileObj->GetInfo()._count.y;
				count.y = tileObj->GetInfo()._count.x;
			}

			//�̹� ���̳� ������Ʈ�� ������ ������ ����.
			for (int i = index.x; i < index.x + count.x; i++)
			{
				for (int j = index.y; j < index.y + count.y; j++)
				{
					if (_vTile[j * _count.x + i]->_wall || _vTile[j * _count.x + i]->_tileObj) return false;
				}
			}
		}
		break;
		case TILEATTRIBUTE::AREA:
		{
			Vector2 count = tileObj->GetInfo()._count;

			//���� ���� �ٸ� ������ ������ �����Ѵ�.
			if (_vTile[index.y * _count.x + index.x]->_area) DestroyTileObject(_vTile[index.y * _count.x + index.x]->_area);
			
		}

		break;
	}
	return true;
}

TileAttribute * TileMap::FindTileObject(string key)
{
	for (int i = 0; i < _tileCount; i++)
	{
		if (_vTile[i]->_area && _vTile[i]->_area->GetKey() == key)
		{
			return _vTile[i]->_area;
		}

		if (_vTile[i]->_tileObj && _vTile[i]->_tileObj->GetKey() == key)
		{
			return _vTile[i]->_tileObj;
		}
	}
	return nullptr;
}
