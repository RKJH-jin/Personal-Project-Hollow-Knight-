#include "stdafx.h"
#include "StuffObject.h"
#include "stdafx.h"
#include "StuffObject.h"

StuffObject::StuffObject(STUFFTTYPE stuffType)
{
	_useCount = 3;

	//Ʈ���� �� ������Ʈ�� �⺻ ����
	{
		_transform = AddComponent<TransformC>();
		_transform->SetPosition(Vector2(WINSIZEX / 2 + RND->getInt(500), WINSIZEY / 2));

		_transform->SetCamera(CAMERAMANAGER->GetVCamera()[0]);
	}

	//�̹�������
	_stuffType = stuffType;
	CreateObject(this);


	switch (_stuffType)
	{
	case STUFFTTYPE::COOKBACON:
		_name = "�丮 ���� ������";
		_description = "�丮 ���� ������.";
		AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("baconCook")); break;

		break;
	case STUFFTTYPE::FOODBACON:
		_name = "�丮 �� ������";
		_description = "���ִ� ������ ���� ������.";
		AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("baconFood")); break;
		break;
	case STUFFTTYPE::BACONS:
		_name = "������ �ٷ���";
		_description = "�ż��� ������";
		AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("bacons")); break;
		break;
	case STUFFTTYPE::BOX:
		_name = "����";
		_description = "��ᰡ �� ����";
		AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("box")); break;
		break;
	case STUFFTTYPE::GRAYBRICKS:
		_name = "ȸ����";
		_description = "ȸ�� ������";
		AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("bricks")); break;
		break;
	case STUFFTTYPE::REDBRICKS:
		_name = "������";
		_description = "���� ������";
		AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("brickReds")); break;
		break;
	case STUFFTTYPE::CABBAGES:
		_name = "����� �ٷ���";
		_description = "�ż��� �����";
		AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("cabbages")); break;
		break;
	case STUFFTTYPE::REBARS:
		_name = "ö�ٵ�";
		_description = "���翡 ���̴� ö��";
		AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("rebars")); break;
		break;
	case STUFFTTYPE::SOUPGREENS:
		_name = "�丮�� ����� ����";
		_description = "���ִ� ����� ����";
		AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("soupGreens")); break;
		break;
	case STUFFTTYPE::SOUPS:
		_name = "�丮�� ���� ����";
		_description = "���ִ� ���� ����";
		AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("soups")); break;
		break;
	case STUFFTTYPE::TRAYS:
		_name = "������ ����";
		_description = "�����ϰ� ���� ���ǵ�";
		AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("trays")); break;
		break;
	case STUFFTTYPE::TRAYDIRTYS:
		_name = "������ ����";
		_description = "����ϰ� �� ������ ���ǵ�";
		AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("trayDirtys")); break;
		break;
	case STUFFTTYPE::WOODCUTS:
		_name = "�����";
		_description = "��ģ �����";
		AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("woodCuts")); break;
		break;
	case STUFFTTYPE::CAR:
		_name = "��";
		_description = "�̵� ����";
		AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("car")); break;
		break;
	case STUFFTTYPE::TRASH:
		_name = "������";
		_description = "������";
		AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("trash")); break;
		break;
	case STUFFTTYPE::POTATOS:
		_name = "���� �ٷ���";
		_description = "�ż��� ���ڵ�";
		AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("patatos")); break;
		break;
	case STUFFTTYPE::END:
		break;
	default:
		break;
	}

	GetComponent<ImageC>()->SetCamera(CAMERAMANAGER->GetVCamera()[0]);
	GetTransform()->SetPosition(_transform->GetPosition());
}

HRESULT StuffObject::init()
{
	return S_OK;
}

void StuffObject::release()
{
}

void StuffObject::update()
{
}

void StuffObject::render()
{
	GameObject::Render();
	//������ŭ ����
	GetComponent<ImageC>()->SetFrame(Vector2(_useCount - 1, 0));
	//�ִ�ġ�� �Ѿ�� �ִ�ġ�̹����� ����
	if (_useCount >= 3)
		GetComponent<ImageC>()->SetFrame(Vector2(GetComponent<ImageC>()->GetImage()->GetMaxFrameX() - 1, 0));

}

void StuffObject::MouseEnter()
{
}

void StuffObject::MouseStay()
{
}

void StuffObject::MouseExit()
{
}
