#pragma once
#include "IEnemyState.h"
class enemyHeldRelease : public IEnemyState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

