#include "stdafx.h"
#include "BTCook.h"
#include "Character.h"

HRESULT BTCook::init(Character * character)
{
	_character = character;
	//�̰� �丮������ �ٲٴ� ������ ������ҵ�!
	_handEnd = true;
	return S_OK;
}

STATE BTCook::invoke()
{
	_character->GetTransform()->SetDirection(DIRECTION::FRONT);
	_character->GetInfo().toolObject->SetToolType(TOOLTYPE::SPATULA);
	//������ ��ġ
	float centerY = _character->GetTransform()->GetPosition().GetIntY() + HANDOFFSETY;
	GameObject* leftHand = _character->GetInfo().leftHand;

	//�����ʱ��غ��� ������
	if (centerY + 5 <= leftHand->GetTransform()->GetPosition().GetIntY())
		_handEnd = false;
	//���ʱ��غ��� ũ��
	if (centerY - 5 >= leftHand->GetTransform()->GetPosition().GetIntY())
		_handEnd = true;

	if (_handEnd)leftHand->GetTransform()->Translate(Vector2(0, 1));
	if (!_handEnd)leftHand->GetTransform()->Translate(Vector2(0, -1));

	return STATE::SUCCESS;
}
