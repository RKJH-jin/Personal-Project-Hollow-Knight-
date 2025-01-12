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
	//루트
	_root = new Selector();
	_hasPlace = new Sequence();
	_noPlace = new Sequence();
	_hang = new Sequence();

	//컨디션
	_isPlace = new StrCondition(bind(&AccountantAI::IsTileObject, this, std::placeholders::_1), "사무실");
	_isReached = new StrCondition(bind(&AccountantAI::IsReached, this, std::placeholders::_1), "사무실");

	//액션 노드
	_home = new AssignTargetOnce;
	_moveToHome = new MoveToTarget2;
	
	_rndgoal = new AssignRNDGoalOnce;
	_hangAround = new MoveToTarget2;

	_getWork = new AssignTargetOnce;
	_working = new MoveToTarget2;

	//오브젝트	
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

	_root->AddChild(_isPlace);				//컨디션
	_isPlace->AddChild(_hasPlace);			//시퀀스
	_hasPlace->AddChild(_home);				//액션노드
	_hasPlace->AddChild(_moveToHome);		//액션노드
	_hasPlace->AddChild(_isReached);		//컨디션	
	_isReached->AddChild(_hang);			//시퀀스
	_hang->AddChild(_getWork);	
	//_hang->AddChild(_isReached);        //액션노드
	_hang->AddChild(_working);				//액션노드	

	_root->AddChild(_noPlace);				//시퀀스
	_noPlace->AddChild(_rndgoal);			//시퀀스
	_noPlace->AddChild(_hangAround);		//시퀀스

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

