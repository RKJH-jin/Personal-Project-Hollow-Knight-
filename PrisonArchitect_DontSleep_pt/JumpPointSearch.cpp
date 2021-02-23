#include "stdafx.h"
#include "JumpPointSearch.h"

#include "Tile.h"
#include "TileObject.h"
#include "TileMap.h"

JumpPointSearch::JumpPointSearch()
{
}

JumpPointSearch::~JumpPointSearch()
{
}

HRESULT JumpPointSearch::init()
{
	TILENUMX = _tileMap->GetCount().x;
	TILENUMY = _tileMap->GetCount().y;

	return S_OK;
}

void JumpPointSearch::release()
{
}

void JumpPointSearch::update()
{

}

void JumpPointSearch::render()
{

}


void JumpPointSearch::addOpenList(Tile* currentTile)
{

	linearLeft(currentTile);
	linearRight(currentTile);
	linearUp(currentTile);
	linearDown(currentTile);

	linearLU(currentTile);
	linearRU(currentTile);
	linearLD(currentTile);
	linearRD(currentTile);

}

void JumpPointSearch::pathFinder(Tile* currentTile)
{
	if (_vOpenList.empty()) return;

	Tile* temp = _vOpenList.top(); // ���� �տ��ִ°� �Ҵ�
	_vOpenList.pop();

	for (int i = 0; i < _vCloseList.size(); ++i) // Ž���ߴ� Ÿ������ Ȯ��
	{
		if (temp->GetIndex() == _vCloseList[i]->GetIndex()) // Ž���ߴ� Ÿ���̸� ����?
		{
			return;
		}
	}

	_vCloseList.push_back(temp); // ���� ��带 ���� ��Ͽ� �ִ´�(Ž���� ���� ���� ���)

	if (temp->GetIndex() == _endTile->GetIndex()) // ���� ��尡 ���������
	{
		while (!_vOpenList.empty())
		{
			_vCloseList.push_back(_vOpenList.top());
			_vOpenList.pop();
		}

		_vResultList.push(_endTile->GetIndex());
		Tile* saveTile = _endTile->GetParentTile();

		while (true)
		{
			if (saveTile->GetParentTile() == nullptr) break;
			_vResultList.push(saveTile->GetIndex());
			saveTile = saveTile->GetParentTile();
		}

		return; // ���������� ����
	}


	switch (temp->GetDirection())
	{
	case SEARCHDIRECTION::LEFT:
		if (temp->GetIndex().y == 0)
		{
			linearLeft(temp);
			linearLD(temp);
		}
		else if (temp->GetIndex().y == TILENUMY - 1)
		{
			linearLeft(temp);
			linearLU(temp);
		}
		else
		{
			if (_tileMap->GetvTile()[(temp->GetIndex().y - 1) * TILENUMX + temp->GetIndex().x]->GetTileEmpty() == false &&
				_tileMap->GetvTile()[(temp->GetIndex().y + 1) * TILENUMX + temp->GetIndex().x]->GetTileEmpty() == false)
			{
				linearLU(temp);
				linearLeft(temp);
				linearLD(temp);
			}
			else if (_tileMap->GetvTile()[(temp->GetIndex().y - 1) * TILENUMX + temp->GetIndex().x]->GetTileEmpty() == false &&
				_tileMap->GetvTile()[(temp->GetIndex().y + 1) * TILENUMX + temp->GetIndex().x]->GetTileEmpty() == true)
			{
				linearLU(temp);
				linearLeft(temp);
			}
			else if (_tileMap->GetvTile()[(temp->GetIndex().y - 1) * TILENUMX + temp->GetIndex().x]->GetTileEmpty() == true &&
				_tileMap->GetvTile()[(temp->GetIndex().y + 1) * TILENUMX + temp->GetIndex().x]->GetTileEmpty() == false)
			{
				linearLeft(temp);
				linearLD(temp);
			}
		}
		break;
	case SEARCHDIRECTION::RIGHT:
		if (temp->GetIndex().y == 0)
		{
			linearRight(temp);
			linearRD(temp);
		}
		else if (temp->GetIndex().y == TILENUMY - 1)
		{
			linearRight(temp);
			linearRU(temp);
		}
		else
		{
			if (_tileMap->GetvTile()[(temp->GetIndex().y - 1) * TILENUMX + temp->GetIndex().x]->GetTileEmpty() == false &&
				_tileMap->GetvTile()[(temp->GetIndex().y + 1) * TILENUMX + temp->GetIndex().x]->GetTileEmpty() == false)
			{
				linearRU(temp);
				linearRight(temp);
				linearRD(temp);
			}
			else if (_tileMap->GetvTile()[(temp->GetIndex().y - 1) * TILENUMX + temp->GetIndex().x]->GetTileEmpty() == false &&
				_tileMap->GetvTile()[(temp->GetIndex().y + 1) * TILENUMX + temp->GetIndex().x]->GetTileEmpty() == true)
			{
				linearRU(temp);
				linearRight(temp);
			}
			else if (_tileMap->GetvTile()[(temp->GetIndex().y - 1) * TILENUMX + temp->GetIndex().x]->GetTileEmpty() == true &&
				_tileMap->GetvTile()[(temp->GetIndex().y + 1) * TILENUMX + temp->GetIndex().x]->GetTileEmpty() == false)
			{
				linearRight(temp);
				linearRD(temp);
			}
		}
		break;
	case SEARCHDIRECTION::UP:
		if (temp->GetIndex().x == 0)
		{
			linearUp(temp);
			linearRU(temp);
		}
		else if (temp->GetIndex().x == TILENUMX - 1)
		{
			linearLU(temp);
			linearUp(temp);
		}
		else
		{
			if (_tileMap->GetvTile()[(temp->GetIndex().y) * TILENUMX + temp->GetIndex().x - 1]->GetTileEmpty() == false &&
				_tileMap->GetvTile()[(temp->GetIndex().y) * TILENUMX + temp->GetIndex().x + 1]->GetTileEmpty() == false)
			{
				linearLU(temp);
				linearUp(temp);
				linearRU(temp);
			}
			else if (_tileMap->GetvTile()[(temp->GetIndex().y) * TILENUMX + temp->GetIndex().x - 1]->GetTileEmpty() == false &&
				_tileMap->GetvTile()[(temp->GetIndex().y) * TILENUMX + temp->GetIndex().x + 1]->GetTileEmpty() == true)
			{
				linearLU(temp);
				linearUp(temp);
			}
			else if (_tileMap->GetvTile()[(temp->GetIndex().y) * TILENUMX + temp->GetIndex().x - 1]->GetTileEmpty() == true &&
				_tileMap->GetvTile()[(temp->GetIndex().y) * TILENUMX + temp->GetIndex().x + 1]->GetTileEmpty() == false)
			{
				linearUp(temp);
				linearRU(temp);
			}
		}
		break;
	case SEARCHDIRECTION::DOWN:
		if (temp->GetIndex().x == 0)
		{
			linearDown(temp);
			linearRD(temp);
		}
		else if (temp->GetIndex().x == TILENUMX - 1)
		{
			linearDown(temp);
			linearLD(temp);
		}
		else
		{
			if (_tileMap->GetvTile()[(temp->GetIndex().y) * TILENUMX + temp->GetIndex().x - 1]->GetTileEmpty() == false &&
				_tileMap->GetvTile()[(temp->GetIndex().y) * TILENUMX + temp->GetIndex().x + 1]->GetTileEmpty() == false)
			{
				linearLD(temp);
				linearDown(temp);
				linearRD(temp);
			}
			else if (_tileMap->GetvTile()[(temp->GetIndex().y) * TILENUMX + temp->GetIndex().x - 1]->GetTileEmpty() == false &&
				_tileMap->GetvTile()[(temp->GetIndex().y) * TILENUMX + temp->GetIndex().x + 1]->GetTileEmpty() == true)
			{
				linearLD(temp);
				linearDown(temp);
			}
			else if (_tileMap->GetvTile()[(temp->GetIndex().y) * TILENUMX + temp->GetIndex().x - 1]->GetTileEmpty() == true &&
				_tileMap->GetvTile()[(temp->GetIndex().y) * TILENUMX + temp->GetIndex().x + 1]->GetTileEmpty() == false)
			{
				linearDown(temp);
				linearRD(temp);
			}
		}
		break;
	case SEARCHDIRECTION::UPPERLEFT:
		linearLU(temp);
		linearLeft(temp);
		linearUp(temp);
		linearRU(temp);
		linearLD(temp);
		break;
	case SEARCHDIRECTION::UPPERRIGHT:
		linearRU(temp);
		linearRight(temp);
		linearUp(temp);
		linearLU(temp);
		linearRD(temp);
		break;
	case SEARCHDIRECTION::LOWERLEFT:
		linearLD(temp);
		linearLeft(temp);
		linearDown(temp);
		linearRD(temp);
		linearLU(temp);
		break;
	case SEARCHDIRECTION::LOWERRIGHT:
		linearRD(temp);
		linearRight(temp);
		linearDown(temp);
		linearLD(temp);
		linearRU(temp);
		break;
	}

	_currentTile = temp; // ���� ��带 �ٲ��ݴϴ�
}


stack<Vector2> JumpPointSearch::PathFinding(Vector2 start, Vector2 end)
{
	_startTile = _tileMap->GetvTile()[start.y * TILENUMX + start.x];
	_currentTile = _startTile;
	_endTile = _tileMap->GetvTile()[end.y * TILENUMX + end.x];

	addOpenList(_currentTile);


	//��ã��
	while (!_vOpenList.empty())
	{
		pathFinder(_currentTile);
	}

	//Ÿ�� ���� ����
	for (int i = 0; i < _vCloseList.size(); ++i)
	{
		_vCloseList[i]->ResetInfo();
	}
	_vCloseList.clear();

	//swap���� �޸� ����
	vector<Tile*> swapTemp;
	swapTemp.swap(_vCloseList);

	priority_queue<Tile*, vector<Tile*>, compare> swapPriTemp;
	swapPriTemp.swap(_vOpenList);

	stack<Vector2> resTemp;
	resTemp.swap(_vResultList);

	return resTemp;
}


/*=============================================================

						�����¿� �Լ�

==============================================================*/
void JumpPointSearch::linearLeft(Tile* currentTile)
{
	int startX = currentTile->GetIndex().x;
	int startY = currentTile->GetIndex().y;

	int count = 1;
	while (true)
	{
		if (startX - count < 0) break; // �ε��� ����ó��

		Tile* node = _tileMap->GetvTile()[(startY)* TILENUMX + (startX - count)];
		if (node->GetTileEmpty() == false) break; // Ž�� ���� - �� (������� ������)

		// Ž�� ���� - �б�
		if (node->GetIndex().x - 1 >= 0)
		{
			// �ݽð� ���� Ȯ��
			if (node->GetIndex().y + 1 < TILENUMY)
			{
				if (_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + node->GetIndex().x]->GetTileEmpty() == false &&
					_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + node->GetIndex().x - 1]->GetTileEmpty() == true)
				{
					node->SetParentTile(currentTile);
					node->GetDirection() = SEARCHDIRECTION::LEFT;
					node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 10;
					node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
					node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
					_vOpenList.push(node);
					break;
				}
			}

			// �ð� ���� Ȯ��
			if (node->GetIndex().y - 1 >= 0)
			{
				if (_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + node->GetIndex().x]->GetTileEmpty() == false &&
					_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + node->GetIndex().x - 1]->GetTileEmpty() == true)
				{
					node->SetParentTile(currentTile);
					node->GetDirection() = SEARCHDIRECTION::LEFT;
					node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 10;
					node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
					node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
					_vOpenList.push(node);
					break;
				}
			}
		}

		// Ž�� ���� - ����
		if (node->GetIndex() == _endTile->GetIndex())
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::LEFT;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 10;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}
		count++;
	}
}

void JumpPointSearch::linearRight(Tile* currentTile)
{
	int startX = currentTile->GetIndex().x;
	int startY = currentTile->GetIndex().y;

	int count = 1;
	while (true)
	{
		if (startX + count >= TILENUMX) break;

		Tile* node = _tileMap->GetvTile()[(startY)* TILENUMX + (startX + count)];
		if (node->GetTileEmpty() == false) break; // // Ž�� ���� - �� (������� ������)

		// Ž�� ���� - �б�
		if (node->GetIndex().x + 1 < TILENUMX)
		{
			// �ݽð� ���� Ȯ��
			if (node->GetIndex().y - 1 >= 0)
			{
				if (_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + node->GetIndex().x]->GetTileEmpty() == false &&
					_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + node->GetIndex().x + 1]->GetTileEmpty() == true)
				{
					node->SetParentTile(currentTile);
					node->GetDirection() = SEARCHDIRECTION::RIGHT;
					node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 10;
					node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
					node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
					_vOpenList.push(node);
					break;
				}
			}

			// �ð� ���� Ȯ��
			if (node->GetIndex().y + 1 < TILENUMY)
			{
				if (_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + node->GetIndex().x]->GetTileEmpty() == false &&
					_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + node->GetIndex().x + 1]->GetTileEmpty() == true)
				{
					node->SetParentTile(currentTile);
					node->GetDirection() = SEARCHDIRECTION::RIGHT;
					node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 10;
					node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
					node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
					_vOpenList.push(node);
					break;
				}
			}
		}

		// Ž�� ���� - ����
		if (node->GetIndex() == _endTile->GetIndex())
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::RIGHT;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 10;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}
		count++;
	}
}

void JumpPointSearch::linearUp(Tile* currentTile)
{
	int startX = currentTile->GetIndex().x;
	int startY = currentTile->GetIndex().y;

	int count = 1;
	while (true)
	{
		if (startY - count < 0) break;

		Tile* node = _tileMap->GetvTile()[(startY - count) * TILENUMX + startX];
		if (node->GetTileEmpty() == false) break; // // Ž�� ���� - ��

		// Ž�� ���� - �б�
		if (node->GetIndex().y - 1 >= 0)
		{
			// �ݽð� ���� Ȯ��
			if (node->GetIndex().x - 1 > 0)
			{
				if (_tileMap->GetvTile()[(node->GetIndex().y) * TILENUMX + node->GetIndex().x - 1]->GetTileEmpty() == false &&
					_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + node->GetIndex().x - 1]->GetTileEmpty() == true)
				{
					node->SetParentTile(currentTile);
					node->GetDirection() = SEARCHDIRECTION::UP;
					node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 10;
					node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
					node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
					_vOpenList.push(node);
					break;
				}
			}

			// �ð� ���� Ȯ��
			if (node->GetIndex().x + 1 <= TILENUMX)
			{
				if (_tileMap->GetvTile()[(node->GetIndex().y) * TILENUMX + node->GetIndex().x + 1]->GetTileEmpty() == false &&
					_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + node->GetIndex().x + 1]->GetTileEmpty() == true)
				{
					node->SetParentTile(currentTile);
					node->GetDirection() = SEARCHDIRECTION::UP;
					node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 10;
					node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
					node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
					_vOpenList.push(node);
					break;
				}
			}
		}

		// Ž�� ���� - ����
		if (node->GetIndex() == _endTile->GetIndex())
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::UP;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 10;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}
		count++;
	}
}

void JumpPointSearch::linearDown(Tile* currentTile)
{
	int startX = currentTile->GetIndex().x;
	int startY = currentTile->GetIndex().y;

	int count = 1;
	while (true)
	{
		if (startY + count >= TILENUMY) break;

		Tile* node = _tileMap->GetvTile()[(startY + count) * TILENUMX + startX]; // Ȯ���� ��� ����
		if (node->GetTileEmpty() == false) break; // Ž�� ���� - ��

		// Ž�� ���� - �б�
		if (node->GetIndex().y + 1 < TILENUMY)
		{
			// �ݽð� ���� Ȯ��
			if (node->GetIndex().x + 1 < TILENUMX)
			{
				if (_tileMap->GetvTile()[(node->GetIndex().y) * TILENUMX + node->GetIndex().x + 1]->GetTileEmpty() == false &&
					_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + node->GetIndex().x + 1]->GetTileEmpty() == true)
				{
					node->SetParentTile(currentTile);
					node->GetDirection() = SEARCHDIRECTION::DOWN;
					node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 10;
					node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
					node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
					_vOpenList.push(node);
					break;
				}
			}

			// �ð� ���� Ȯ��
			if (node->GetIndex().x - 1 >= 0)
			{
				if (_tileMap->GetvTile()[(node->GetIndex().y) * TILENUMX + node->GetIndex().x - 1]->GetTileEmpty() == false &&
					_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + node->GetIndex().x - 1]->GetTileEmpty() == true)
				{
					node->SetParentTile(currentTile);
					node->GetDirection() = SEARCHDIRECTION::DOWN;
					node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 10;
					node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
					node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
					_vOpenList.push(node);
					break;
				}
			}
		}

		// Ž�� ���� - ����
		if (node->GetIndex() == _endTile->GetIndex())
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::DOWN;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 10;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}
		count++;
	}
}

/*=============================================================

						�밢�� �Լ�

==============================================================*/
void JumpPointSearch::linearLU(Tile* currentTile)
{
	int startX = currentTile->GetIndex().x;
	int startY = currentTile->GetIndex().y;

	int count = 1;
	while (true)
	{
		if (startX - count < 0 || startY - count < 0) break;                                                        // �̵��� ��ġ�� �ε����� �����

		Tile* node = _tileMap->GetvTile()[(startY - count) * TILENUMX + (startX - count)];           // �̵��ϰ�
		if (node->GetTileEmpty() == false) break;                                                                   // �̵��� ��ġ�� ���� ���̸�
		if (_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + (node->GetIndex().x)]->GetTileEmpty() == false &&
			_tileMap->GetvTile()[(node->GetIndex().y) * TILENUMX + (node->GetIndex().x + 1)]->GetTileEmpty() == false) break; // �밢���� �����־� �����δ� �̵��� �Ұ��� ���

		// Ž�� ���� - �б�
		bool counterClockwise = false;
		bool clockwise = false;

		// �ݽð� ���� Ž��
		if (node->GetIndex().x - 1 >= 0)
		{
			if (_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + (node->GetIndex().x)]->GetTileEmpty() == false &&
				_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + (node->GetIndex().x - 1)]->GetTileEmpty() == true)
			{
				counterClockwise = true;
			}
		}

		// �ð� ���� Ž��
		if (node->GetIndex().y - 1 >= 0)
		{
			if (_tileMap->GetvTile()[(node->GetIndex().y) * TILENUMX + (node->GetIndex().x + 1)]->GetTileEmpty() == false &&
				_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + (node->GetIndex().x + 1)]->GetTileEmpty() == true)
			{
				clockwise = true;
			}
		}

		if ((counterClockwise && !clockwise) || (!counterClockwise && clockwise)) // �бⰡ ������
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::UPPERLEFT;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 14;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}
		else if (counterClockwise && clockwise) break; // �� �� ����������

		CHECKDIVERGENT checkValue1 = subLinearLeft(node);
		CHECKDIVERGENT checkValue2 = subLinearUp(node);

		// Ž�� ���� - �밢�� ���� �б�
		if (checkValue1 == CHECKDIVERGENT::DIVERGENT || checkValue2 == CHECKDIVERGENT::DIVERGENT)       //�б⸦ ��������
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::UPPERLEFT;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 14;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}
		else if (checkValue1 == CHECKDIVERGENT::END || checkValue2 == CHECKDIVERGENT::END)              //�������� �����ߴٸ�
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::UPPERLEFT;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 14;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}

		// Ž�� ���� - ����
		if (node->GetIndex() == _endTile->GetIndex())
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::UPPERLEFT;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 14;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}
		count++;
	}
}

void JumpPointSearch::linearRU(Tile* currentTile)
{
	int startX = currentTile->GetIndex().x;
	int startY = currentTile->GetIndex().y;

	int count = 1;
	while (true)
	{
		if (startX + count >= TILENUMX || startY - count < 0) break;                                                // �̵��� ��ġ�� �ε����� �����

		Tile* node = _tileMap->GetvTile()[(startY - count) * TILENUMX + (startX + count)];                                    // �̵��ϰ�
		if (node->GetTileEmpty() == false) break;                                                                   // �̵��� ��ġ�� ���� ���̸�
		if (_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + (node->GetIndex().x)]->GetTileEmpty() == false &&
			_tileMap->GetvTile()[(node->GetIndex().y) * TILENUMX + (node->GetIndex().x - 1)]->GetTileEmpty() == false) break; // �밢���� �����־� �����δ� �̵��� �Ұ��� ���

		// Ž�� ���� - �б�
		bool counterClockwise = false;
		bool clockwise = false;

		// �ݽð� ���� Ž��
		if (node->GetIndex().y - 1 >= 0)
		{
			if (_tileMap->GetvTile()[(node->GetIndex().y) * TILENUMX + (node->GetIndex().x - 1)]->GetTileEmpty() == false &&
				_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + (node->GetIndex().x - 1)]->GetTileEmpty() == true)
			{
				counterClockwise = true;
			}
		}

		// �ð� ���� Ž��
		if (node->GetIndex().x + 1 < TILENUMX)
		{
			if (_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + (node->GetIndex().x)]->GetTileEmpty() == false &&
				_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + (node->GetIndex().x + 1)]->GetTileEmpty() == true)
			{
				clockwise = true;
			}
		}

		if ((counterClockwise && !clockwise) || (!counterClockwise && clockwise)) // �бⰡ ������
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::UPPERRIGHT;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 14;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}
		else if (counterClockwise && clockwise) break; // �� �� ����������

		// Ž�� ���� - �밢�� ���� �б�
		CHECKDIVERGENT checkValue1 = subLinearRight(node);
		CHECKDIVERGENT checkValue2 = subLinearUp(node);

		if (checkValue1 == CHECKDIVERGENT::DIVERGENT || checkValue2 == CHECKDIVERGENT::DIVERGENT)           // �б⸦ �����ٸ�
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::UPPERRIGHT;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 14;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}
		else if (checkValue1 == CHECKDIVERGENT::END || checkValue2 == CHECKDIVERGENT::END)                  // �������� �����ߴٸ�
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::UPPERRIGHT;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 14;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}

		// Ž�� ���� - ����
		if (node->GetIndex() == _endTile->GetIndex())
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::UPPERRIGHT;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 14;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}
		count++;
	}
}

void JumpPointSearch::linearLD(Tile* currentTile)
{
	int startX = currentTile->GetIndex().x;
	int startY = currentTile->GetIndex().y;

	int count = 1;
	while (true)
	{
		if (startX - count < 0 || startY + count >= TILENUMY) break;                                                    // �̵��� ��ġ�� �ε����� �����

		Tile* node = _tileMap->GetvTile()[(startY + count) * TILENUMX + (startX - count)];                                        // �̵��ϰ�
		if (node->GetTileEmpty() == false) break;                                                                       // �̵��� ��ġ�� ���� ���̸�
		if (_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + (node->GetIndex().x)]->GetTileEmpty() == false &&
			_tileMap->GetvTile()[(node->GetIndex().y) * TILENUMX + (node->GetIndex().x + 1)]->GetTileEmpty() == false) break;     // �밢���� �����־� �����δ� �̵��� �Ұ��� ���

		// Ž�� ���� - �б�
		bool counterClockwise = false;
		bool clockwise = false;

		// �ݽð� ���� Ž��
		if (node->GetIndex().y + 1 < TILENUMY)
		{
			if (_tileMap->GetvTile()[(node->GetIndex().y) * TILENUMX + (node->GetIndex().x + 1)]->GetTileEmpty() == false &&
				_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + (node->GetIndex().x + 1)]->GetTileEmpty() == true)
			{
				counterClockwise = true;
			}
		}

		// �ð� ���� Ž��
		if (node->GetIndex().x - 1 >= 0)
		{
			if (_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + (node->GetIndex().x)]->GetTileEmpty() == false &&
				_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + (node->GetIndex().x - 1)]->GetTileEmpty() == true)
			{
				clockwise = true;
			}
		}

		if ((counterClockwise && !clockwise) || (!counterClockwise && clockwise)) // �бⰡ ������
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::LOWERLEFT;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 14;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}
		else if (counterClockwise && clockwise) break; // �� �� ����������

		// Ž�� ���� - �밢�� ���� �б�
		CHECKDIVERGENT checkValue1 = subLinearLeft(node);
		CHECKDIVERGENT checkValue2 = subLinearDown(node);

		if (checkValue1 == CHECKDIVERGENT::DIVERGENT || checkValue2 == CHECKDIVERGENT::DIVERGENT)
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::LOWERLEFT;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 14;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}
		else if (checkValue1 == CHECKDIVERGENT::END || checkValue2 == CHECKDIVERGENT::END)
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::LOWERLEFT;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 14;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}

		// Ž�� ���� - ����
		if (node->GetIndex() == _endTile->GetIndex())
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::LOWERLEFT;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 14;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}
		count++;
	}
}

void JumpPointSearch::linearRD(Tile* currentTile)
{
	int startX = currentTile->GetIndex().x;
	int startY = currentTile->GetIndex().y;


	int count = 1;
	while (true)
	{
		if (startX + count >= TILENUMX || startY + count >= TILENUMY) break;                                          // �̵��� ��ġ�� �ε����� �����

		Tile* node = _tileMap->GetvTile()[(startY + count) * TILENUMX + (startX + count)];                           // �̵��ϰ�
		if (node->GetTileEmpty() == false) break;                                                                     // �̵��� ��ġ�� ���� ���̸�
		if (_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + (node->GetIndex().x)]->GetTileEmpty() == false &&
			_tileMap->GetvTile()[(node->GetIndex().y) * TILENUMX + (node->GetIndex().x - 1)]->GetTileEmpty() == false) break;   // �밢���� �����־� �����δ� �̵��� �Ұ��� ���

		// Ž�� ���� - �б�
		bool counterClockwise = false;
		bool clockwise = false;

		// �ݽð� ���� Ž��
		if (node->GetIndex().x + 1 < TILENUMX)
		{
			if (_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + (node->GetIndex().x)]->GetTileEmpty() == false &&
				_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + (node->GetIndex().x + 1)]->GetTileEmpty() == true)
			{
				counterClockwise = true;
			}
		}

		// �ð� ���� Ž��
		if (node->GetIndex().y + 1 < TILENUMY)
		{
			if (_tileMap->GetvTile()[(node->GetIndex().y) * TILENUMX + (node->GetIndex().x - 1)]->GetTileEmpty() == false &&
				_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + (node->GetIndex().x - 1)]->GetTileEmpty() == true)
			{
				clockwise = true;
			}
		}

		if ((counterClockwise && !clockwise) || (!counterClockwise && clockwise)) // �бⰡ ������
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::LOWERRIGHT;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 14;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}
		else if (counterClockwise && clockwise) break; // �� �� ����������

		// Ž�� ���� - �밢�� ���� �б�
		CHECKDIVERGENT checkValue1 = subLinearRight(node);
		CHECKDIVERGENT checkValue2 = subLinearDown(node);

		if (checkValue1 == CHECKDIVERGENT::DIVERGENT || checkValue2 == CHECKDIVERGENT::DIVERGENT)
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::LOWERRIGHT;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 14;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}
		else if (checkValue1 == CHECKDIVERGENT::END || checkValue2 == CHECKDIVERGENT::END)
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::LOWERRIGHT;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 14;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}

		// Ž�� ���� - ����
		if (node->GetIndex() == _endTile->GetIndex())
		{
			node->SetParentTile(currentTile);
			node->GetDirection() = SEARCHDIRECTION::LOWERRIGHT;
			node->GetCost().costFromStart = currentTile->GetCost().costFromStart + count * 14;
			node->GetCost().costToGoal = (abs(_endTile->GetIndex().x - node->GetIndex().x) + abs(_endTile->GetIndex().y - node->GetIndex().y)) * 10;
			node->GetCost().totalCost = node->GetCost().costFromStart + node->GetCost().costToGoal;
			_vOpenList.push(node);
			break;
		}
		count++;
	}
}

/*=============================================================

					�밢�� ���� Ž�� �Լ�

==============================================================*/
CHECKDIVERGENT JumpPointSearch::subLinearLeft(Tile* currentTile)
{
	int startX = currentTile->GetIndex().x;
	int startY = currentTile->GetIndex().y;

	int count = 1;
	while (true)
	{
		if (startX - count < 0) break;

		Tile* node = _tileMap->GetvTile()[(startY)* TILENUMX + (startX - count)];
		if (node->GetTileEmpty() == false) break;

		// Ž�� ���� - �б�
		if (node->GetIndex().x - 1 >= 0)
		{
			// �ݽð� ���� Ȯ��
			if (node->GetIndex().y + 1 < TILENUMY)
			{
				if (_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + node->GetIndex().x]->GetTileEmpty() == false &&
					_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + node->GetIndex().x - 1]->GetTileEmpty() == true)
				{
					return CHECKDIVERGENT::DIVERGENT;
				}
			}

			// �ð� ���� Ȯ��
			if (node->GetIndex().y - 1 >= 0)
			{
				if (_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + node->GetIndex().x]->GetTileEmpty() == false &&
					_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + node->GetIndex().x - 1]->GetTileEmpty() == true)
				{
					return CHECKDIVERGENT::DIVERGENT;
				}
			}
		}

		// Ž�� ���� - ����
		if (node->GetIndex() == _endTile->GetIndex())
		{
			return CHECKDIVERGENT::END;
		}
		count++;
	}
	return CHECKDIVERGENT::NONE;
}

CHECKDIVERGENT JumpPointSearch::subLinearRight(Tile* currentTile)
{
	int startX = currentTile->GetIndex().x;
	int startY = currentTile->GetIndex().y;

	int count = 1;
	while (true)
	{
		if (startX + count >= TILENUMX) break;

		Tile* node = _tileMap->GetvTile()[(startY)* TILENUMX + (startX + count)];
		if (node->GetTileEmpty() == false) break;

		// Ž�� ���� - �б�
		if (node->GetIndex().x + 1 < TILENUMX)
		{
			// �ݽð� ���� Ȯ��
			if (node->GetIndex().y - 1 >= 0)
			{
				if (_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + node->GetIndex().x]->GetTileEmpty() == false &&
					_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + node->GetIndex().x + 1]->GetTileEmpty() == true)
				{
					return CHECKDIVERGENT::DIVERGENT;
				}
			}

			// �ð� ���� Ȯ��
			if (node->GetIndex().y + 1 < TILENUMY)
			{
				if (_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + node->GetIndex().x]->GetTileEmpty() == false &&
					_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + node->GetIndex().x + 1]->GetTileEmpty() == true)
				{
					return CHECKDIVERGENT::DIVERGENT;
				}
			}
		}

		// Ž�� ���� - ����
		if (node->GetIndex() == _endTile->GetIndex())
		{
			return CHECKDIVERGENT::END;
		}
		count++;
	}
	return CHECKDIVERGENT::NONE;
}

CHECKDIVERGENT JumpPointSearch::subLinearUp(Tile* currentTile)
{
	int startX = currentTile->GetIndex().x;
	int startY = currentTile->GetIndex().y;

	int count = 1;
	while (true)
	{
		if (startY - count < 0) break;

		Tile* node = _tileMap->GetvTile()[(startY - count)* TILENUMX + (startX)];
		if (node->GetTileEmpty() == false) break;

		// Ž�� ���� - �б�
		if (node->GetIndex().y - 1 >= 0)
		{
			// �ݽð� ���� Ȯ��
			if (node->GetIndex().x - 1 >= 0)
			{
				if (_tileMap->GetvTile()[(node->GetIndex().y) * TILENUMX + node->GetIndex().x - 1]->GetTileEmpty() == false &&
					_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + node->GetIndex().x - 1]->GetTileEmpty() == true)
				{
					return CHECKDIVERGENT::DIVERGENT;
				}
			}

			// �ð� ���� Ȯ��
			if (node->GetIndex().x + 1 < TILENUMX)
			{
				if (_tileMap->GetvTile()[(node->GetIndex().y) * TILENUMX + node->GetIndex().x + 1]->GetTileEmpty() == false &&
					_tileMap->GetvTile()[(node->GetIndex().y - 1) * TILENUMX + node->GetIndex().x + 1]->GetTileEmpty() == true)
				{
					return CHECKDIVERGENT::DIVERGENT;
				}
			}
		}

		// Ž�� ���� - ����
		if (node->GetIndex() == _endTile->GetIndex())
		{
			return CHECKDIVERGENT::END;
		}
		count++;
	}
	return CHECKDIVERGENT::NONE;
}

CHECKDIVERGENT JumpPointSearch::subLinearDown(Tile* currentTile)
{
	int startX = currentTile->GetIndex().x;
	int startY = currentTile->GetIndex().y;

	int count = 1;
	while (true)
	{
		if (startY + count >= TILENUMY) break;

		Tile* node = _tileMap->GetvTile()[(startY + count)* TILENUMX + (startX)];
		if (node->GetTileEmpty() == false) break;

		// Ž�� ���� - �б�
		if (node->GetIndex().y + 1 < TILENUMY)
		{
			// �ݽð� ���� Ȯ��
			if (node->GetIndex().x + 1 < TILENUMX)
			{
				if (_tileMap->GetvTile()[(node->GetIndex().y) * TILENUMX + node->GetIndex().x + 1]->GetTileEmpty() == false &&
					_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + node->GetIndex().x + 1]->GetTileEmpty() == true)
				{
					return CHECKDIVERGENT::DIVERGENT;
				}
			}

			// �ð� ���� Ȯ��
			if (node->GetIndex().x - 1 >= 0)
			{
				if (_tileMap->GetvTile()[(node->GetIndex().y) * TILENUMX + node->GetIndex().x - 1]->GetTileEmpty() == false &&
					_tileMap->GetvTile()[(node->GetIndex().y + 1) * TILENUMX + node->GetIndex().x - 1]->GetTileEmpty() == true)
				{
					return CHECKDIVERGENT::DIVERGENT;
				}
			}
		}

		// Ž�� ���� - ����
		if (node->GetIndex() == _endTile->GetIndex())
		{
			return CHECKDIVERGENT::END;
		}
		count++;
	}
	return CHECKDIVERGENT::NONE;
}

