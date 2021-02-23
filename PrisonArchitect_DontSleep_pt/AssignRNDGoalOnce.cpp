#include "stdafx.h"
#include "AssignRNDGoalOnce.h"
#include "Character.h"
#include "MapToolScene.h"
HRESULT AssignRNDGoalOnce::init(Character * character)
{
	_character = character;
	return S_OK;
}

STATE AssignRNDGoalOnce::invoke()
{
	//��Ÿ�����ѻ��°ų� �����ߴٸ� Ÿ���������ʰ� ����
	if (_character->GetInfo().goalState == GOALSTATE::GOALSET || _character->GetInfo().goalState == GOALSTATE::GOALREACH) return STATE::SUCCESS;
	_character->GetTransform()->SetPath(Vector2(RND->getInt(TILECOUNTX), RND->getInt(TILECOUNTY)));
	_character->GetTransform()->SetArriveEndIndex(false);
	//��Ÿ�����ѻ��·� ����
	_character->GetInfo().goalState = GOALSTATE::GOALSET;
	return STATE::SUCCESS;
}
