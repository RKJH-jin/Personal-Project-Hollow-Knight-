#pragma once
#include "GameObject.h"
#include "AllComponents.h"
#include "AllEnums.h"

/*
�ٴڿ� �ִ� �� ������Ʈ : ������ �÷��̾� ������ �����ȴ�. ���Ƚ���� ���� �̹����� �ٲ��.
*/
class StuffObject : public GameObject
{
private:
	int _useCount;		//���Ƚ��
	STUFFTTYPE _stuffType;
public:
	StuffObject(STUFFTTYPE stuffType);
	~StuffObject() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void MouseEnter();
	virtual void MouseStay();
	virtual void MouseExit();

	//����
	virtual int getUseCount() { return _useCount; }
	STUFFTTYPE getStuffType() { return _stuffType; }

	//����
	virtual void setUseCount(int useCount) { _useCount = useCount; }

};
