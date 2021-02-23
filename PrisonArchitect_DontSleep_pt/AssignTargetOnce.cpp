#include "stdafx.h"
#include "AssignTargetOnce.h"
#include "Character.h"

HRESULT AssignTargetOnce::init(Character* character, Vector2 target)
{
	_character = character;
	_target = target;
	return S_OK;
}

STATE AssignTargetOnce::invoke()
{
	//��Ÿ�����ѻ��°ų� �����ߴٸ� Ÿ���������ʰ� ����
	if (_character->GetInfo().goalState == GOALSTATE::GOALSET || _character->GetInfo().goalState == GOALSTATE::GOALREACH) return STATE::SUCCESS;
	_character->GetTransform()->SetPath(_target);
	_character->GetTransform()->SetArriveEndIndex(false);
	//��Ÿ�����ѻ��·� ����
	_character->GetInfo().goalState = GOALSTATE::GOALSET;
	return STATE::SUCCESS;
}
