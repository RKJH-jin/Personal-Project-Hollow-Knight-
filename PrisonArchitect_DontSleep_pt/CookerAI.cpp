#include "stdafx.h"
#include "CookerAI.h"
#include "MoveToTarget.h"
#include "AssignTarget.h"
#include "Character.h"
#include "MapToolScene.h"
#include "StuffObject.h"
#include "AssignTargetOnce.h"
#include "AssignRNDGoalOnce.h"
#include "BTCook.h"
#include "BTCreateStuff.h"

CookerAI::CookerAI()
{
	//��Ʈ: ����
	_ROOT = new Selector;
	//�丮������?
	_CONIsMeterial = new VoidCondition(bind(&CookerAI::checkIsNotMeterial, this));
	_SELIsNotMeterial = new Selector;
	//�ֹ�����?
	_CONIsKitchen = new StrCondition(bind(&CookerAI::checkIsSpot, this, std::placeholders::_1), "�ξ�");
	//�ֹ濡 ��� ����
	_SEQCreateMeterial = new Sequence;
	//�����ֹ漼����?
	_CONIsSetGoalRNDKitchen = new VoidCondition(bind(&CookerAI::checkSetNotPos, this));
	_ATRNDKitchen = new AssignTargetOnce;
	//�̵��� ������
	_SEQMoveAfter = new Sequence;
	_ATCreateMeterial = new BTCreateStuff;
	//������ġ���
	_SELRND = new Selector;
	_CONIsSetGoalRND = new VoidCondition(bind(&CookerAI::checkSetNotPos, this));
	_ATRND = new AssignRNDGoalOnce;
	//��������?
	_CONIsNotReachGoal = new VoidCondition(bind(&CookerAI::checkNotReach, this));
	_CONIsReackKitchen = new VoidCondition(bind(&CookerAI::checkReach, this));
	//�̵�����
	_ATMoveToTarget = new MoveToTarget;
	//�丮��?
	_CONIsCooking = new VoidCondition(bind(&CookerAI::checkIsCooking, this));
	_ATCook = new BTCook();
	//�Ļ�ð�?
	_CONIsMealTime = new VoidCondition(bind(&CookerAI::checkMealTime, this));
	//�Ļ�ð��ƴ�

	//��Ʈ: �ֹ�����?
	_ROOTCONIsnotMealTime = new VoidCondition(bind(&CookerAI::checkNotMealTime, this));
	_ROOTCONIsKitchen = new StrCondition(bind(&CookerAI::checkIsSpot, this, std::placeholders::_1), "�ξ�");
	_SELFindKitchen = new Selector;
	//�ֹ������?
	_CONIsSetGoalKtRND = new VoidCondition(bind(&CookerAI::checkSetNotPos, this));
}

HRESULT CookerAI::init(Character * character)
{
	//�ʱ�ȭ
	_character = character;
	_ATMoveToTarget->init(_character);
	_ATRND->init(_character);
	_ATCreateMeterial->init(_character);
	_ATCook->init(_character);

	//��� ����
	{
		//��Ʈ: ����
		_ROOT->AddChild(_CONIsMeterial);
		//�� �丮������?
		_CONIsMeterial->AddChild(_SELIsNotMeterial);
		//�ֹ�����?
		_SELIsNotMeterial->AddChild(_CONIsKitchen);
		//�ֹ濡������
		_CONIsKitchen->AddChild(_SEQCreateMeterial);

		//�ֹ���ġ������?
		_SEQCreateMeterial->AddChild(_CONIsSetGoalRNDKitchen);
		_CONIsSetGoalRNDKitchen->AddChild(_ATRNDKitchen);
		//�̵����������� _SEQCreateMeterial
		_SEQCreateMeterial->AddChild(_SEQMoveAfter);
		_SEQMoveAfter->AddChild(_CONIsNotReachGoal);
		_SEQMoveAfter->AddChild(_ATMoveToTarget);
		_SEQMoveAfter->AddChild(_CONIsReackKitchen);
		_CONIsReackKitchen->AddChild(_ATCreateMeterial);

		//������ġ���
		_SELIsNotMeterial->AddChild(_SELRND);
		_SELRND->AddChild(_CONIsSetGoalRND);
		_CONIsSetGoalRND->AddChild(_ATRND);
		_SELRND->AddChild(_CONIsNotReachGoal);
		_CONIsNotReachGoal->AddChild(_ATMoveToTarget);

		//�� �丮 �ȳ�����?
		_ROOT->AddChild(_CONIsCooking);
		_CONIsCooking->AddChild(_ATCook);

		//�� �Ļ�ð��ΰ�?
		_ROOT->AddChild(_CONIsMealTime);
		_CONIsMealTime->AddChild(_ATCook);

		//�ֹ�Ȯ��
		_ROOT->AddChild(_ROOTCONIsnotMealTime);
		_ROOTCONIsnotMealTime->AddChild(_ROOTCONIsKitchen);
		_ROOTCONIsKitchen->AddChild(_SELFindKitchen);
		//�ֹ���ġ����
		_SELFindKitchen->AddChild(_CONIsSetGoalKtRND);
		_CONIsSetGoalKtRND->AddChild(_ATRNDKitchen);
		//�ֹ��̵�
		_SELFindKitchen->AddChild(_CONIsNotReachGoal);
		_CONIsNotReachGoal->AddChild(_ATMoveToTarget);

		//�������ƴٴϴ� ��Ʈ ����
		_ROOT->AddChild(_SELRND);


	}
	return S_OK;
}

void CookerAI::Update()
{
	_ROOT->invoke();
}

//�Ļ�ð����� üũ
bool CookerAI::checkMealTime()
{
	if (DATAMANAGER->GetInfo().schedule == TIMESCHEDULE::MEAL)return true;
	if (DATAMANAGER->GetInfo().schedule != TIMESCHEDULE::MEAL)return false;
}

//�Ļ�ð��ƴ���üũ
bool CookerAI::checkNotMealTime()
{
	if (DATAMANAGER->GetInfo().schedule != TIMESCHEDULE::MEAL)
	{
		_character->GetInfo().toolObject->SetToolType(TOOLTYPE::NONE);
		_character->initHands();
		return true;
	}

	if (DATAMANAGER->GetInfo().schedule == TIMESCHEDULE::MEAL)return false;
}

//�丮������ üũ
bool CookerAI::checkIsCooking()
{
	if (_character->GetInfo().btState == BTSTATE::COOKING)return true;
	return false;
}

//���� ��� �ִ��� üũ
bool CookerAI::checkHasTool(TOOLTYPE tool)
{
	if (_character->GetInfo().toolObject->getToolType() == tool)
		return true;
	return false;
}



//���� ���� �ϴ��� üũ
bool CookerAI::checkHasStuff(string stuff)
{
	StuffObject* obj = DATAMANAGER->GetMapToolScene()->GetMapM()->FindStuffObject(stuff);

	if (obj == nullptr)return false;
	else if (obj != nullptr)
	{

		return true;
	}

}


bool CookerAI::checkHasMeterial()
{
	if (_character->GetInfo().toolObject != nullptr)
	{
		if (_character->GetInfo().toolObject->getToolType() == TOOLTYPE::BACON
			|| _character->GetInfo().toolObject->getToolType() == TOOLTYPE::CABBAGE
			|| _character->GetInfo().toolObject->getToolType() == TOOLTYPE::POTATO
			)return true;

	}
	return false;
}



//������ �ȵǾ����Ȯ��
bool CookerAI::checkSetNotPos()
{

	if (_character->GetInfo().goalState != GOALSTATE::GOALSET)
	{
		_character->GetInfo().goalState = GOALSTATE::NONE;
		return true;
	}


	return false;
}
//�������ߴ��� Ȯ��
bool CookerAI::checkNotReach()
{

	if (_character->GetInfo().goalState != GOALSTATE::GOALREACH)
	{
		return true;
	}
	return false;
}

//�����ߴ���
bool CookerAI::checkReach()
{
	if (_character->GetInfo().goalState == GOALSTATE::GOALREACH)
	{
		return true;
	}

	return false;
}

//�丮��ᰡ �����ϴ��� Ȯ��
bool CookerAI::checkIsNotMeterial()
{

	MapManager* mapM = DATAMANAGER->GetMapToolScene()->GetMapM();

	if (!mapM->FindStuffObject("������ �ٷ���"))
	{
		_ATCreateMeterial->setStuff(STUFFTTYPE::BACONS);
		return true;
	}

	if (!mapM->FindStuffObject("����� �ٷ���"))
	{
		_ATCreateMeterial->setStuff(STUFFTTYPE::CABBAGES);
		return true;
	}

	if (!mapM->FindStuffObject("���� �ٷ���"))
	{
		_ATCreateMeterial->setStuff(STUFFTTYPE::POTATOS);
		return true;
	}



	return false;
}

bool CookerAI::checkIsSpot(string name)
{
	TileAttribute* obj = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->FindTileObject(name);

	if (obj == nullptr)		//null �̸� ����.
		return false;
	else if (obj != nullptr)	//�ƴϸ� �ִ�.
	{
		Vector2 temp = obj->GetRandomIndex();
		_ATRNDKitchen->init(_character, temp);
		return true;
	}
	return false;
}
