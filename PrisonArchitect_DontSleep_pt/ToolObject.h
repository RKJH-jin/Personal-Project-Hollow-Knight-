#pragma once
#include "GameObject.h"
#include "AllComponents.h"
#include "AllEnums.h"

/*
ĳ���Ͱ� ��� ���� ������Ʈ : ������ �÷��̾� ���� �����ȴ�.
*/
class Character;
class ToolObject : public GameObject
{
private:
	int _useCount;		//���Ƚ��
	TOOLTYPE _toolType;

	Character* _charecter;
public:
	ToolObject();
	~ToolObject() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void MouseEnter();
	virtual void MouseStay();
	virtual void MouseExit();

	//����
	virtual int getUseCount() { return _useCount; }
	virtual TOOLTYPE& getToolType() { return _toolType; }
	virtual void SetToolType(TOOLTYPE type);
	//����
	virtual void setUseCount(int useCount) { _useCount = useCount; }
	//��Ŀ
	virtual void setLinkCharacter(Character* character);
};