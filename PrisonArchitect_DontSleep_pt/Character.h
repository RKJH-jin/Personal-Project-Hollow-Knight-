#pragma once
#include "ToolObject.h"

//�������κ��� ��ġ������� ������ġ
#define HEADOFFSET 10
#define HANDOFFSETY -10
#define HANDOFFSETX 20

//����⺻����
struct tagCharacterInfo
{
public:
	int role;					//����
    int frameX[4];		        //������ ��ȣ
    float moveSpeed;	        //�̵� �ӵ� 
    float actSpeed;		        //�ൿ �ӵ�
    bool isSleep;		        //��ħ ����
	bool isSweep;               //û�� ����
	bool isStart;               //ó���� ����� ����������
	bool isDumping;             //������������ ��ǥ ������ �ƴ���
    ToolObject* toolObject;     //����
	CHARACTERTYPE type;			//Ÿ��
	GOALSTATE goalState;		//�� ����
	BTSTATE btState;			//�ൿ ����
	float countTime;				//�ൿ ����ð�

	GameObject* rightHand;
	GameObject* leftHand;
};

//���
class Character : public GameObject
{
protected:
	//��ü ����
	GameObject* _torso;
	//����
	tagCharacterInfo _info;
   
public:
	Character();
	~Character() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	//�ڷ����Լ��� �� �������� �� �ϴ� �Ⱦ��µ� ������ ���� ����
	virtual void render();

	virtual Character* MouseEnter();
	virtual Character* MouseStay();
	virtual Character* MouseExit();

	//����
	tagCharacterInfo& GetInfo() { return _info; }
    TransformC* GetTransform() { return _transform; }

	//�ջ���
	virtual void CreateHands();
	//����ġ�ʱ�ȭ
	virtual void initHands();
	//�ʻ��º���
	virtual void SetNaked(bool isNaked) {  }

	void SetPrisonerRandomName();
	void SetPeopleRandomName();

	bool GetIsInArea(string name);

};