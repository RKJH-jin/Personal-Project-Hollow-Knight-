#pragma once
#include "IPlayerState.h"


class playerDashAttack: public IPlayerState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

