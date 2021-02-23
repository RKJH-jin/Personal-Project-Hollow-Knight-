#include "stdafx.h"
#include "UpperUI.h"
#include "Button.h"
#include "AllComponents.h"
#include "MapToolScene.h"

UpperUI::UpperUI()
{
	_name = "��� ��";
	_description = "���� ������ Ȯ���� �� �ִ� ��� ���Դϴ�.";
	_transform->SetPosition(Vector2(WINSIZEX / 2, 50));
	_transform->SetSize(Vector2(500, 50));
	_transform->SetRect();

	_schedule = new Button;
	_schedule->SetParent(this);
	_schedule->SetName("�ð�ǥ");
	_schedule->SetDescription("���� ������ �������� Ȯ���� �� �ֽ��ϴ�.");
	_schedule->GetTransform()->SetPosition(Vector2(200, 50));
	_schedule->GetTransform()->SetSize(Vector2(200, 30));
	_schedule->GetTransform()->SetRect();

	_schedule->AddComponent<RectC>()->SetAlpha(0.7f);
	_schedule->GetComponent<RectC>()->SetColor(D2D1::ColorF::DarkSlateBlue);

	_schedule->AddComponent<TextC>()->ChangeText("������ : ");
	_schedule->GetComponent<TextC>()->SetText(20);

	_vButton.push_back(_schedule);


	_manageDay = new Button;
	_manageDay->SetParent(this);
	_manageDay->SetName("���");
	_manageDay->SetDescription("�����Ҹ� �󸶳� �������� ��ߴ��� �����ݴϴ�. \n�� �÷��� �ð� : " + to_string(DATAMANAGER->GetInfo().time.day) + "�� " + to_string(DATAMANAGER->GetInfo().time.hour) + "�� " + to_string(DATAMANAGER->GetInfo().time.minute) + "�� " + to_string(DATAMANAGER->GetInfo().time.second) + "��");

	_manageDay->GetTransform()->SetPosition(Vector2(450, 50));
	_manageDay->GetTransform()->SetSize(Vector2(200, 30));
	_manageDay->GetTransform()->SetRect();

	_manageDay->AddComponent<RectC>()->SetAlpha(0.7f);
	_manageDay->GetComponent<RectC>()->SetColor(D2D1::ColorF::DarkGoldenrod);

	_manageDay->AddComponent<TextC>()->ChangeText("��¥ : " + to_string(DATAMANAGER->GetInfo().time.day) + "��");
	_manageDay->GetComponent<TextC>()->SetText(20);

	_vButton.push_back(_manageDay);

	_money = new Button;
	_money->SetParent(this);
	_money->SetName("���� �ܰ�");
	_money->SetDescription("���࿡ ������ ������ �󸶳� �ִ��� �����ݴϴ�.");

	_money->GetTransform()->SetPosition(Vector2(700, 50));
	_money->GetTransform()->SetSize(Vector2(200, 30));
	_money->GetTransform()->SetRect();

	_money->AddComponent<RectC>()->SetAlpha(0.7f);
	_money->GetComponent<RectC>()->SetColor(D2D1::ColorF::DarkOrchid);

	_money->AddComponent<TextC>()->ChangeText("������ : " + to_string(DATAMANAGER->GetInfo().money) + "��");
	_money->GetComponent<TextC>()->SetText(20);

	_vButton.push_back(_money);

	_prisoner = new Button;
	_prisoner->SetParent(this);
	_prisoner->SetName("�ο�");
	_prisoner->SetDescription("���� �����ҿ� �����ϰ� �ִ� �ο��� ���� �����ݴϴ�.");
	_prisoner->GetTransform()->SetPosition(Vector2(950, 50));
	_prisoner->GetTransform()->SetSize(Vector2(200, 30));
	_prisoner->GetTransform()->SetRect();
	_prisoner->AddComponent<RectC>()->SetAlpha(0.7f);
	_prisoner->GetComponent<RectC>()->SetColor(D2D1::ColorF::DarkTurquoise);
	_prisoner->AddComponent<TextC>()->ChangeText("�ο� : " + to_string(DATAMANAGER->GetMapToolScene()->GetMapM()->GetVCharacter().size()) + "��");
	_prisoner->GetComponent<TextC>()->SetText(20);

	_vButton.push_back(_prisoner);

}

void UpperUI::release()
{
	delete _manageDay;
}

void UpperUI::update()
{
	GameObject::Update();
	_manageDay->GetComponent<TextC>()->ChangeText("��¥ : " + to_string(DATAMANAGER->GetInfo().time.day) + "��");
	_manageDay->SetDescription("�����Ҹ� �󸶳� �������� ��ߴ��� �����ݴϴ�. \n�� �÷��� �ð� : " + to_string(DATAMANAGER->GetInfo().time.day) + "�� " + to_string(DATAMANAGER->GetInfo().time.hour) + "�� " + to_string(DATAMANAGER->GetInfo().time.minute) + "�� " + to_string(DATAMANAGER->GetInfo().time.second) + "��");
	_money->GetComponent<TextC>()->ChangeText("������ : " + to_string(DATAMANAGER->GetInfo().money) + "��");
	_prisoner->GetComponent<TextC>()->ChangeText("�ο� : " + to_string(DATAMANAGER->GetMapToolScene()->GetMapM()->GetVCharacter().size()) + "��");


	switch (DATAMANAGER->GetInfo().schedule)
	{
	case TIMESCHEDULE::SLEEP:
		_schedule->GetComponent<TextC>()->ChangeText("�ð�ǥ : ��ħ");
		break;
	case TIMESCHEDULE::MEAL:
		_schedule->GetComponent<TextC>()->ChangeText("�ð�ǥ : �Ļ�");
		break;
	case TIMESCHEDULE::WASH:
		_schedule->GetComponent<TextC>()->ChangeText("�ð�ǥ : ����");
		break;
	case TIMESCHEDULE::GROUND:
		_schedule->GetComponent<TextC>()->ChangeText("�ð�ǥ : �");
		break;
	case TIMESCHEDULE::REST:
		_schedule->GetComponent<TextC>()->ChangeText("�ð�ǥ : �޽�");
		break;
	case TIMESCHEDULE::IMPRISON:
		_schedule->GetComponent<TextC>()->ChangeText("�ð�ǥ : ����");
		break;
	default:
		break;
	}
}

void UpperUI::render()
{
	GameObject::Render();
}
