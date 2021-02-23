#pragma once
#include "gameNode.h"
#include "pixelCollision.h"
#include "player.h"
#include "mapManager.h"
#include "enemyManager.h"
#include "projectile.h"
#include "UIManager.h"
#include "startScene.h"


class playGround : public gameNode
{
private:
	camera* _mainCamera;	// ����ī�޶�
	player* _cPlayer;
	mapManager* _cMapManager;
	enemyManager* _cEnemyManager;
	projectile* _cProjectile;
	UIManager* _cUIManager;
	float angle = PI;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render();			//�׸��� ����

	void hornetImageInit();
	void hornetAnimationInit();
	void aspidImageInit();
	void aspidAnimationInit();
	void xeroImageInit();
	void xeroAnimationInit();
};

