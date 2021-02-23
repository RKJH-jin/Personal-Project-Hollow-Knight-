#pragma once
#include "GameObject.h"
class Mouse : public GameObject
{
protected:
	MOUSESTATE _state;			//���콺 ������Ʈ
	bool _isOnUI;				//UI���� �ִ���
	float _speed;

public:
	Mouse() { _speed = 2.0f; };
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	void SetState(MOUSESTATE state) { _state = state; };
	float GetSpeed() { return _speed; }

};

