#pragma once
#include "gameNode.h"

/*====================================================================
====================================================================*/

/*====================================================================

	(���� �� ���� �⺻ �ּ� ��Ÿ���Դϴ�.)
	��ü���� ������ ���̽��� �Ǵ� playGround�Դϴ�.
	map�� �׷����� �ϴ� �͵��� �⺻������ mapDC�� �׷��ּ���.

====================================================================*/

class playGround : public gameNode
{
private:

public:
	playGround() {}
	~playGround() {}

	virtual HRESULT init();		//�ʱ�ȭ ���� �Լ�
	virtual void release();		//�޸� ���� �Լ�
	virtual void update();		//���� ����
	virtual void render();		//�׸��� ����

	void addScene();	//���� �� ��� �� �߰�

	void addSource();	//���� �� ��� �ҽ� �߰�
	void addImage();	//���� �� ��� �̹��� �߰�
	void addSound();	//���� �� ��� �Ҹ� �߰�

};
