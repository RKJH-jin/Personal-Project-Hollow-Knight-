#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ�� ����� �ϼ���
HRESULT playGround::init()
{
	gameNode::init(true, 7100, WINSIZEY);	// managerInit check, maxScreenWidth, maxScreenHeight
	//===========================ī�޶� ��ġ ������Ʈ(�ʼ�)============================//
	_mainCamera = CAMERAMANAGER->getMainCamera();							// ����ī�޶� ��������
	SCENEMANAGER->addScene("startScene", new startScene);

	hornetImageInit();
	hornetAnimationInit();
	aspidImageInit();
	aspidAnimationInit();
	xeroImageInit();
	xeroAnimationInit();
	_cMapManager = new mapManager;
	_cMapManager->init();

	_cProjectile = new projectile;
	_cProjectile->init();

	_cPlayer = new player;
	_cPlayer->init();
	
	_cEnemyManager = new enemyManager;
	_cEnemyManager->init();

	_cUIManager = new UIManager;
	_cUIManager->init(200, 100);

	_cMapManager->setLinkPlayer(_cPlayer);
	_cProjectile->setLinkPlayer(_cPlayer);
	_cProjectile->setLinkEnemyManager(_cEnemyManager);
	_cEnemyManager->setLinkPlayer(_cPlayer);
	_cEnemyManager->setLinkProjectile(_cProjectile);
	_cPlayer->setLinkMapManager(_cMapManager);
	_cPlayer->setLinkProjectile(_cProjectile);
	_cPlayer->setLinkEnemyManager(_cEnemyManager);
	_cUIManager->setLinkPlayer(_cPlayer);

	return S_OK;
}

//�޸� ������ ����� �ϼ���
void playGround::release()
{
	gameNode::release();
	_cMapManager->release();
	_cPlayer->release();
	_cEnemyManager->release();
	_cProjectile->release();
}

//����(���)�� ����� �ϼ���
void playGround::update()
{
	gameNode::update();
	_cMapManager->update();
	_cPlayer->update();
	_cEnemyManager->update();
	_cProjectile->update();
	_cUIManager->update();

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene("startScene");
	}
	
	SCENEMANAGER->update();
	//===========================ī�޶� ��ġ ������Ʈ(�ʼ�)============================//
	CAMERAMANAGER->mainCameraUpdate(_cPlayer->getPlayer().x, _cPlayer->getPlayer().y);			// ����ī�޶� ��ġ ������Ʈ! �ʼ�!! (centerX, centerY)
}

//���� ����� �׷��� ��...
void playGround::render()
{
	PatBlt(getMemDC(), _mainCamera->getLTX(), _mainCamera->getLTY(), WINSIZEX, WINSIZEY, WHITENESS); // getMemDC() == _backBuffer�� hMemDC�� ��� �Լ�
	//================ ���� �ǵ��� ���� ==============================
	IMAGEMANAGER->findImage("town_background")->render(getMemDC(), _mainCamera->getLTX(), _mainCamera->getLTY());
	_cMapManager->render();
	_cPlayer->render();
	_cEnemyManager->render();
	_cProjectile->render();
	_cUIManager->render(_mainCamera->getLTX() + 20, _mainCamera->getLTY() + 10);
	
	SCENEMANAGER->render();
	//TIMEMANAGER->render(getMemDC());
	//================= �Ʒ��� �ǵ��� ���� ==============================
	//_backBuffer->render(getHDC());
	
	//============================ī�޶� ����============================//
	// * ī�޶� �Ⱦ����� ���� _backBuffer->render�� �ּ�ó���� ����� ���ø� �˴ϴ�
	_backBuffer->render(getHDC(), 0, 0, _mainCamera->getLTX(), _mainCamera->getLTY(),
		_mainCamera->getWidth(), _mainCamera->getHeight());

}





