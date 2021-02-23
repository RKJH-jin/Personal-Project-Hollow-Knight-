#include "stdafx.h"
#include "Prisoner.h"
#include "PrisonerAI.h"
//������
Prisoner::Prisoner()
{
	_info.type = CHARACTERTYPE::PRISONER;
	int random = RND->getInt(10);
	_name = "�˼�";
	SetDescription("��Ȥ�� �˸� ������ \n�����ҿ� �� �˼��Դϴ�.");

	//��ü ����
	_bodNum = RND->getInt(4);

	//���� �ʱ�ȭ
	char bodImgName[20];
	sprintf_s(bodImgName, "bodCloth%d", _bodNum);
	_torso = CreateObject(this);
	_torso->AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage(bodImgName));
	_torso->GetComponent<ImageC>()->SetCamera(CAMERAMANAGER->GetVCamera()[0]);
	_torso->GetTransform()->SetPivot(Vector2(0, 0));

	//�Ӹ� �ʱ�ȭ
	int headNum = RND->getInt(10);
	char headImgName[20];
	sprintf_s(headImgName, "head%d", headNum);
	_head = CreateObject(this);
	_head->AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage(headImgName));
	_head->GetTransform()->SetPivot(Vector2(0, - HEADOFFSET));
	_head->GetComponent<ImageC>()->SetCamera(CAMERAMANAGER->GetVCamera()[0]);

	//���߰�
	CreateHands();

	_key = headImgName;
    AddComponent<PrisonerAI>();
    GetComponent<PrisonerAI>()->init(this);
}
//�Ҹ���
Prisoner::~Prisoner()
{
}

HRESULT Prisoner::init()
{
   
	return S_OK;
}

void Prisoner::release()
{
}

void Prisoner::update()
{
	Character::update();
	//���⿡ ���� ����
	if (_torso->GetTransform()->GetDirection() == DIRECTION::RIGHT) _torso->GetComponent<ImageC>()->SetReverese(true, false);
	_torso->GetComponent<ImageC>()->SetFrame(Vector2(_info.frameX[(int)_transform->GetDirection()], 0));

	if (_head->GetTransform()->GetDirection() == DIRECTION::RIGHT) _head->GetComponent<ImageC>()->SetReverese(true, false);
	_head->GetComponent<ImageC>()->SetFrame(Vector2(_info.frameX[(int)_transform->GetDirection()], 0));


}

void Prisoner::render()
{
	Character::render();


}

void Prisoner::SetNaked(bool isNaked)
{
	char bodImgName[20];

	if(isNaked) sprintf_s(bodImgName, "bod%d", _bodNum);

	if(!isNaked) sprintf_s(bodImgName, "bodCloth%d", _bodNum);

	_torso->GetComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage(bodImgName));
}

