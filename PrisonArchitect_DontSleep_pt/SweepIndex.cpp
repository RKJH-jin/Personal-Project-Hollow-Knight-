#include "stdafx.h"
#include "SweepIndex.h"
#include "Character.h"

HRESULT SweepIndex::init(Character * character)
{
	_character = character;
	
	return S_OK;
}

STATE SweepIndex::invoke()
{
	_character->GetInfo().toolObject->SetToolType(TOOLTYPE::MOP);
	

	//������ ��ġ
   float centerX = _character->GetTransform()->GetPosition().GetIntX() + HANDOFFSETX;
   GameObject* leftHand = _character->GetInfo().leftHand;
   
   //�����ʱ��غ��� ������
   if (centerX + 10 <= leftHand->GetTransform()->GetPosition().GetIntX())
      _handEnd = false;
      //���ʱ��غ��� ũ��
   if (centerX - 10 >= leftHand->GetTransform()->GetPosition().GetIntX())
      _handEnd = true;

   if(_handEnd)leftHand->GetTransform()->Translate(Vector2(1, 0));
   if(!_handEnd)leftHand->GetTransform()->Translate(Vector2(-1, 0));

   _count++;

	if (_count > 200)
	{
		_character->GetInfo().toolObject->SetToolType(TOOLTYPE::NONE);
		_character->GetInfo().isSweep = true;
		_count = 0;

	}
	
	return STATE::SUCCESS;
}
