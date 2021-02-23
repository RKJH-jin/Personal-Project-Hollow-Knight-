#pragma once
#include "Character.h"

//�˼�
class Prisoner : public Character
{
private:
	GameObject* _head;	//��ü����
	int _bodNum;		//��������
public:
	Prisoner();
	~Prisoner();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void SetNaked(bool isNaked);
};


