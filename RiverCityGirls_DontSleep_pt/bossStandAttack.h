#pragma once
#include"IBossState.h"


class bossStandAttack :public IBossState
{
private:	
	float _enterTime;
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};
