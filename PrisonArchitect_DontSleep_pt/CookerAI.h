#pragma once
#include "AllComponents.h"

class MoveToTarget;
class AssignTarget;
class Character;
class AssignTargetOnce;
class AssignRNDGoalOnce;
class BTCreateStuff;
class BTCook;
class CookerAI : public AI
{
private:

	//�������Ÿ��
	STUFFTTYPE _meterial;
	//��Ʈ: ����
	Selector* _ROOT;
	//�丮������?
	Condition* _CONIsMeterial;
	Selector* _SELIsNotMeterial;

	//�ֹ�����?
	Condition* _CONIsKitchen;
	//�ֹ濡 ������
	Sequence* _SEQCreateMeterial;
	//�����ֹ漼����?
	Condition* _CONIsSetGoalRNDKitchen; //����
	AssignTargetOnce* _ATRNDKitchen;
	//�̵��� ������
	Sequence* _SEQMoveAfter;
	Condition* _CONIsReackKitchen; //����
	BTCreateStuff* _ATCreateMeterial;

	//������ġ���
	Selector* _SELRND;//��������
	Condition* _CONIsSetGoalRND; //����
	AssignRNDGoalOnce* _ATRND;
	//��������?
	Condition* _CONIsNotReachGoal;//��������
	//�̵�
	MoveToTarget* _ATMoveToTarget;
	//��Ʈ: �Ļ�ð��ΰ�
	Condition* _CONIsMealTime;
	//�丮���ΰ�
	Condition* _CONIsCooking;
	BTCook* _ATCook;
	//=========================================
	//�Ļ�ð��ƴ�
	Condition* _ROOTCONIsnotMealTime;
	Condition* _ROOTCONIsKitchen;
	//�ֹ���ġã��
	Selector* _SELFindKitchen;
	//��ġ������?
	Condition* _CONIsSetGoalKtRND; //����





public:
	CookerAI();
	~CookerAI() {};

	HRESULT init(Character* character);
	void Update();

	bool checkMealTime();
	bool checkNotMealTime();
	bool checkIsCooking();
	bool checkHasTool(TOOLTYPE tool);
	bool checkHasStuff(string stuff);
	bool checkHasMeterial();
	bool checkSetNotPos();
	bool checkNotReach();
	bool checkReach();
	bool checkIsNotMeterial();
	bool checkIsSpot(string name);
};




