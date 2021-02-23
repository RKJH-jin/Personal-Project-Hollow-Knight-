#include "stdafx.h"
#include "HelperUI.h"
#include "Button.h"

HelperUI::HelperUI()
{
	_name = "��� ��";
	_description = "���� ������ Ȯ���� �� �ִ� ��� ���Դϴ�.";
	
	_helperImg = IMAGEMANAGER->FindImage("buttonRed");
	AddComponent<ImageC>()->SetImage(_helperImg);

	_transform->SetPosition(Vector2(50, 50));
	_transform->SetRect();

	_helper = new Button;
	_helper->SetParent(this);
	_helper->SetName("����");
	_helper->SetDescription("��Ŭ������ ��ȣ �ۿ�, ��Ŭ������ ���.\nRŰ�� ������Ʈ ȸ��, ���콺 �Ǵ� WASD�� ī�޶� �̵�.\n�����̽��� �Ǵ� �ð� ��ư���� �Ͻ� ����.");

	_helper->GetTransform()->SetPosition(Vector2(50, 50));
	_helper->GetTransform()->SetSize(Vector2(50, 50));
	_helper->GetTransform()->SetRect();

	_vButton.push_back(_helper);

}

void HelperUI::update()
{
	Update();
}

void HelperUI::render()
{
	Render();
	_helperImg->SetSize(Vector2(50, 50));
}
