#include "stdafx.h"
#include "Staff.h"
#include "WorkerAI.h"
#include "AccountantAI.h"
#include "DoctorAI.h"
#include "TeacherAI.h"
#include "WardenAI.h"

Staff::Staff(STAFFROLE role)
{
	_info.type = CHARACTERTYPE::STAFF;
    _role = role;
	_info.role = (int)role;
    _torso = CreateObject(this);

    switch (role)
    {
    case STAFFROLE::ACCOUNTANT:
	{
		_name = "ȸ���";
		_key = "accountant";
		AddComponent<AccountantAI>()->init(this);
	}
	break;
    case STAFFROLE::CLEANER:
    {
		_name = "û�Һ�";
		_key = "cleaner" + to_string(RND->getInt(4));
        AddComponent<CleanerAI>()->init(this);
        
    }
	break;

    case STAFFROLE::COOKER:
    {
		_name = "�丮��";
		_key = "cooker" + to_string(RND->getInt(4));
        AddComponent<CookerAI>()->init(this);
    }
	break;

    case STAFFROLE::DOCTER:
    {
		 _name = "�ǻ�";
		 _key = "docter" + to_string(RND->getInt(4));
		 AddComponent<DoctorAI>()->init(this);
    }
    break;
	case STAFFROLE::TEACHER:
	{
		_name = "������";
		_key = "teacher";
		AddComponent<TeacherAI>()->init(this);
	}
	break;
	case STAFFROLE::WARDEN:
	{
	_name = "��������";
	_key = "warden";
	AddComponent<WardenAI>()->init(this);
	}
	break;
	case STAFFROLE::WARDER:
	{
		_name = "����";
		_key = "warder" + to_string(RND->getInt(4));
	}
	break;
	case STAFFROLE::WORKER:
	{
		_name = "�κ�";
		_key = "worker" + to_string(RND->getInt(4));
		AddComponent<WorkerAI>()->init(this);
	}
	break;
    }
	_description = _name + "�Դϴ�.";

	_torso->AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage(_key));
    _torso->GetComponent<ImageC>()->SetCamera(CAMERAMANAGER->GetMainCamera());
	_torso->GetTransform()->SetPivot(Vector2(0, 0));

    //���߰�
    CreateHands();

}

HRESULT Staff::init()
{
    return S_OK;
}

void Staff::release()
{
}

void Staff::update()
{
	Character::update();
    if (_torso->GetTransform()->GetDirection() == DIRECTION::RIGHT) _torso->GetComponent<ImageC>()->SetReverese(true, false);
    _torso->GetComponent<ImageC>()->SetFrame(Vector2(_info.frameX[(int)_transform->GetDirection()], 0));


}

void Staff::render()
{
    Character::render();

}
