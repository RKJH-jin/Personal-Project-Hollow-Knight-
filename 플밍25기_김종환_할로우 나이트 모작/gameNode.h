#pragma once
#include "image.h"

static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);
static image* _pixelBuffer = IMAGEMANAGER->addImage("pixelBuffer", WINSIZEX, WINSIZEY);

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;
	

public:
	gameNode();
	virtual ~gameNode();

	//HRESULT�� ���� ���� ����� ��ȯ�� ��
	//S_OK, E_FAIL, SUCCEDED ������ return���� ����
	//����� �ʱ�ȭ �ƴ��� �ȵƴ��� ȣ������

	virtual HRESULT init();
	virtual HRESULT init(bool managerInit, int width, int height);	//�ʱ�ȭ ���� �Լ�				
	virtual void release();									//�޸� ���� �Լ�
	virtual void update();									//���� ����
	virtual void render();							//�׸��� ����

	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getPixelMemDC() { return _pixelBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

};

