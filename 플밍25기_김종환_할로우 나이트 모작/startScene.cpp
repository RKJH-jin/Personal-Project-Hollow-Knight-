#include "stdafx.h"
#include "startScene.h"

HRESULT startScene::init()
{
    IMAGEMANAGER->addImage("����", "image/����.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
    _mainCamera = CAMERAMANAGER->getMainCamera();
    x = WINSIZEX / 2;
    y = WINSIZEY / 2;
    return S_OK;
}

void startScene::release()
{
}

void startScene::update()
{
    if (KEYMANAGER->isStayKeyDown(VK_LEFT))
    {
        x -= 5;
    }

    if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
    {
        x += 5;
    }
    //===========================ī�޶� ��ġ ������Ʈ(�ʼ�)============================//
    CAMERAMANAGER->mainCameraUpdate(x, y);			// ����ī�޶� ��ġ ������Ʈ! �ʼ�!! (centerX, centerY)
}

void startScene::render()
{
    IMAGEMANAGER->findImage("����")->render(getMemDC());
}
