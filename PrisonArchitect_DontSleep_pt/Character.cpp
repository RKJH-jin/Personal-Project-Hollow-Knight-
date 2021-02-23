#include "stdafx.h"
#include "Character.h"
#include "MapToolScene.h"
#include "MapManager.h"
Character::Character()
{
	//�����ʱ�ȭ
	_info.goalState = GOALSTATE::NONE;
	_info.btState = BTSTATE::NONE;

	//���⿡ ���� ������ ����
	_info.frameX[0] = 0;	//��
	_info.frameX[1] = 2;	//��
	_info.frameX[2] = 1;	//��
	_info.frameX[4] = 3;	//��

	//Ʈ���� �� ������Ʈ�� �⺻ ����
	{
		_transform = AddComponent<TransformC>();
		_transform->SetPosition(Vector2(WINSIZEX / 2, WINSIZEY / 2)); // 640 360 10, 5.?
		_transform->SetDirection(DIRECTION::FRONT);

		_transform->SetSize(Vector2(50, 60));
		_transform->SetCamera(CAMERAMANAGER->GetVCamera()[0]);

		_info.moveSpeed = 4.f * DATAMANAGER->GetInfo().gameSpeed;
		_info.actSpeed = 1.f * DATAMANAGER->GetInfo().gameSpeed;
	}
	GameObject::SetActive(true);

	_info.toolObject = new ToolObject();


}

HRESULT Character::init()
{
	return S_OK;
}

void Character::release()
{
}

void Character::update()
{
	GameObject::Update();

	_info.moveSpeed = 4.f * DATAMANAGER->GetInfo().gameSpeed;	//*��ü�ӵ� �� �����༭ �̵��ӵ��� �׼Ǽӵ��� �ٲ�Ű���. 
	_info.actSpeed = 1.f * DATAMANAGER->GetInfo().gameSpeed;	//*��ü�ӵ� �׼Ǽӵ��� �ȿ����̰� �׷��� ����������.. �׻� ��ü�ӵ� �����ִ°� �ſ� �߿�!!

	_transform->Update();

	if (KEYMANAGER->isStayKeyDown(VK_SPACE)) _transform->Translate(Vector2(RND->getFromFloatTo(-_info.moveSpeed, _info.moveSpeed), RND->getFromFloatTo(-_info.moveSpeed, _info.moveSpeed)));


	//���⿡���� ��������
	if (_info.toolObject != NULL && _transform->GetDirection() == DIRECTION::BACK)_info.toolObject->SetRender(false);
	if (_info.toolObject != NULL && _transform->GetDirection() != DIRECTION::BACK)_info.toolObject->SetRender(true);

	if (_torso->GetTransform()->GetDirection() == DIRECTION::RIGHT) _torso->GetComponent<ImageC>()->SetReverese(true, false);
	_torso->GetComponent<ImageC>()->SetFrame(Vector2(_info.frameX[(int)_transform->GetDirection()], 0));

	if (_info.toolObject != nullptr)
		_info.toolObject->GetTransform()->SetPosition(Vector2(_info.leftHand->GetTransform()->GetPosition().x, _info.leftHand->GetTransform()->GetPosition().y));

}

void Character::render()
{

}

Character * Character::MouseEnter()
{
	return this;
}

Character * Character::MouseStay()
{
	return this;
}

Character * Character::MouseExit()
{
	return this;
}

void Character::CreateHands()
{
	//��ü ���� - ��

	//������ �ʱ�ȭ
	_info.rightHand = CreateObject(this);
	_info.rightHand->AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("hand"));
	_info.rightHand->GetComponent<ImageC>()->SetCamera(CAMERAMANAGER->GetVCamera()[0]);
	_info.rightHand->GetTransform()->SetPivot(Vector2(-HANDOFFSETX, -HANDOFFSETY));

	//�޼� �ʱ�ȭ
	_info.leftHand = CreateObject(this);
	_info.leftHand->AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("hand"));
	_info.leftHand->GetComponent<ImageC>()->SetCamera(CAMERAMANAGER->GetVCamera()[0]);
	_info.leftHand->GetTransform()->SetPivot(Vector2(HANDOFFSETX, -HANDOFFSETY));

	_info.toolObject->SetParent(_info.leftHand);
	_info.toolObject->GetTransform()->SetPosition(Vector2(_transform->GetPosition().x, _transform->GetPosition().y));
}
void Character::initHands()
{
	_info.rightHand->GetTransform()->SetPosition(Vector2(_transform->GetPosition().x - HANDOFFSETX, _transform->GetPosition().y - HANDOFFSETY));
	_info.leftHand->GetTransform()->SetPosition(Vector2(_transform->GetPosition().x + HANDOFFSETX, _transform->GetPosition().y - HANDOFFSETY));
	_info.toolObject->GetTransform()->SetPosition(Vector2(_transform->GetPosition().x, _transform->GetPosition().y));
}


void Character::SetPrisonerRandomName()
{
	string temp = " ";
	int random = RND->getInt(25);
	//int random = 0;
	switch (random)
	{
	case 0:		temp += "�� ��";
		_description = _description + "\n�ڵ� �������� ������\n�л����� ���� �긮�� �� ��ǹ�.";
		break;
	case 1:		temp += "���� ��";
		_description = _description + "\n���� ������ ���ּ�����\n������� �ʾҴ� ���...";
		break;
	case 2:		temp += "�褷��";
		_description = _description + "\n��� Ż�ֹ� �̵����� �Ŀ�.\n������ ������ ��ġ...";
		break;
	case 3:		temp += "�褷ȣ";
		_description = _description + "\n���ݸ��� ���� �� �شٰ� �ߴ�...\n����ɲ�����!!!!!";
		break;
	case 4:		temp += "�褷��";		break;
	case 5:		temp += "�褷��";		break;
	case 6:		temp += "�褷��";		break;
	case 7:		temp += "�褷��";		break;
	case 8:		temp += "�ڤ���";
		_description = _description + "\n��ũ����!\n�εε���!";
		break;
	case 9:		temp += "�ڤ���";		break;
	case 10:	temp += "�ڤ���";		break;
	case 11:	temp += "�ڤ���";		break;
	case 12:	temp += "�ڤ�ȣ";
		_description = _description + "\n���� �� ������ �׷���...\n���� �� ì�� �༭ ���� �ɾҴ�.";
		break;
	case 13:	temp += "������";
		_description = _description + "\n�����غ��� ������ �߸��� ����.\n���� ���� ���� ��...";
		break;
	case 14:	temp += "�ۤ���";		break;
	case 15:	temp += "�ɤ���";		break;
	case 16:	temp += "�̤���";		break;
	case 17:	temp += "�̤���";		break;
	case 18:	temp += "�̤���";		break;
	case 19:	temp += "�̤���";		break;
	case 20:	temp += "�夷��";		break;
	case 21:	temp += "�夷��";		break;
	case 22:	temp += "������";		break;
	case 23:	temp += "������";
		_description = _description + "\n�׽��ǹٴ�\n������...";
		break;
	case 24:	temp += "�Ϥ�ȣ";		break;
	default: break;
	}

	_name = _name + temp;

}

void Character::SetPeopleRandomName()
{
	string temp = " ";
	int random = RND->getInt(5);
	switch (random)
	{
	case 0:		temp += "�褷ȯ";
		_description = _description + "\n������ ���� �����ؼ�\n������ ������ �� ����̴�.";
		break;
	case 1:		temp += "�Ť���";
		_description = _description + "\n����Ʈ ����̹���.\n�ӵ����̱� �ѵ� ������ �� �Ѵ�.";
		break;
	case 2:		temp += "�Ť���";
		_description = _description + "\n���� ���� �� ����.\n�ٴٿ� ���� ������ ������.";
		break;
	case 3:		temp += "������";
		_description = _description + "\n�׻� ���� �Ͻð� �����Ͻô�.\n������ �� ���� �ſ�ť�Ф�";
		break;
	case 4:		temp += "�֤�ȣ";
		_description = _description + "\n�ֱٿ� �̿�ǿ� �ٳ�Դ�.\n��� �ڱ� ������ �� �Ѵ�.";
		break;
	default: break;
	}
	_name = _name + temp;
}

bool Character::GetIsInArea(string name)
{
	TileAttribute* area = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->FindTileObject(name);

	if (area)	//������ �ִٸ�
	{
		if (area->GetIsInArea(_transform->GetIndex())) return true;
		else return false;
	}
	return false;	//���� ��ü�� ����.
}
