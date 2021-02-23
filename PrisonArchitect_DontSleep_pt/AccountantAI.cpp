#include "stdafx.h"
#include "AccountantAI.h"
#include "MoveToTarget2.h"
#include "AssignTargetOnce.h"
#include "AssignRNDGoalOnce.h"
#include "Character.h"
#include "MapToolScene.h"
#include "ToolObject.h"



AccountantAI::AccountantAI()
{
	//��Ʈ
	_root = new Selector();
	_hasPlace = new Sequence();
	_noPlace = new Sequence();
	_hang = new Sequence();

	//�����
	_isPlace = new StrCondition(bind(&AccountantAI::IsTileObject, this, std::placeholders::_1), "�繫��");
	_isReached = new StrCondition(bind(&AccountantAI::IsReached, this, std::placeholders::_1), "�繫��");

	//�׼� ���
	_home = new AssignTargetOnce;
	_moveToHome = new MoveToTarget2;
	
	_rndgoal = new AssignRNDGoalOnce;
	_hangAround = new MoveToTarget2;

	_getWork = new AssignTargetOnce;
	_working = new MoveToTarget2;

	//������Ʈ	
	//_object = new ToolObject(TOOLTYPE::DOCUMENT);

	

}

HRESULT AccountantAI::init(Character * character)
{
	_character = character;
	

	_home->init(_character, Vector2(14, 27));
	_rndgoal->init(_character);
	_getWork->init(_character, Vector2(15, 25));

	_moveToHome->init(_character);
	_hangAround->init(_character);
	_working->init(_character);

	_root->AddChild(_isPlace);				//�����
	_isPlace->AddChild(_hasPlace);			//������
	_hasPlace->AddChild(_home);				//�׼ǳ��
	_hasPlace->AddChild(_moveToHome);		//�׼ǳ��
	_hasPlace->AddChild(_isReached);		//�����	
	_isReached->AddChild(_hang);			//������
	_hang->AddChild(_getWork);	
	//_hang->AddChild(_isReached);        //�׼ǳ��
	_hang->AddChild(_working);				//�׼ǳ��	

	_root->AddChild(_noPlace);				//������
	_noPlace->AddChild(_rndgoal);			//������
	_noPlace->AddChild(_hangAround);		//������

	return S_OK;
}

void AccountantAI::Update()
{
	_root->invoke();
}

bool AccountantAI::IsTileObject(string name)	
{
	TileAttribute* obj = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->FindTileObject(name);

	if (obj == nullptr)		
	{		
		return false;		
	}
	else if (obj != nullptr)	
	{		
		Vector2 temp = obj->GetCenterIndex();
		_home->init(_character, temp);
		return true;	
	}
	return false;
}

bool AccountantAI::IsReached(string name)
{	
	TileAttribute* area = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->FindTileObject(name);
	if (_character->GetTransform()->GetIndex() == _character->GetTransform()->GetEndIndex())
	{
		Vector2 temp = area->GetRandomIndex();
			_getWork->init(_character, temp);

			//_object->GetTransform()->SetPosition(_character->GetTransform()->GetPosition());	
			//_character->GetInfo().goalState = GOALSTATE::NONE;
			_character->GetInfo().toolObject->SetToolType(TOOLTYPE::DOCUMENT);
			//_createstuff->setStuff(TOOLTYPE::DOCUMENT)
			//_ATCreateMeterial->setStuff(STUFFTTYPE::BACONS);
			//_character->GetInfo().toolObject->GetTransform()->SetPosition(Vector2 (10,0));
		return true;
	}
	else 
		return false;
}

