#pragma once
#include "AllComponents.h"

class MoveToTarget;
class AssignTarget;
class StuffObject;
class AssignTargetOnce;

class WorkerAI : public AI
{
private:

	//��Ʈ
	Selector* _root;

	//â��
	Condition* _conIsStorage;		//â�� �ִ���
	Sequence* _seqIsTree;
	AssignTargetOnce* _assGoToStorage;
	MoveToTarget* _actMoveToStorage;

	//�޽�
	Condition* _conIsBreakTime;		//�޽Ľð�
	Condition* _conIsLounge;		//�ްԽ� �ִ���

	//����




public:
	WorkerAI();

	HRESULT init(Character* character);
	void Update();

	bool IsTileObject(string name);
	bool IsStuffObject(string name);


};

