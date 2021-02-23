#include "stdafx.h"
#include "playGround.h"
#include "TitleScene.h"
playGround::playGround()
{
}

playGround::~playGround()
{
}

//�ʱ�ȭ �Լ�
HRESULT playGround::init()
{
	gameNode::init(true);

	// ============================ ����� �� ============================
	#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
	using namespace std;
	// ==================================================================
	
	//�ҽ� �߰�
	AddSource();

	//csv�� �о� �´�.
	_csv.read();

	//���� ī�޶�
	CAMERAMANAGER->CreateCamera(FloatRect(0, 0, WINSIZEX, WINSIZEY));

	//Ÿ��Ʋ �� �߰�
	SCENEMANAGER->PushScene(new TitleScene);

	return S_OK;
}

//�޸� ����
void playGround::release()
{

}

//����
void playGround::update()
{
	gameNode::update();
	
	//�� ������Ʈ
	SCENEMANAGER->Update();
}

//�׸��� ����
void playGround::render()
{	
	//����� ������ �����Ѵ�.
	D2DRenderer::GetInstance()->BeginRender(D2D1::ColorF::Black);

	//���� �����Ѵ�.
	SCENEMANAGER->Render();

	//����� ������ ������.
	D2DRenderer::GetInstance()->EndRender();
}
