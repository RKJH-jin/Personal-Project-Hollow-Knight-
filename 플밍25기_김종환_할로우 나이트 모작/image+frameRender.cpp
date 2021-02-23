#include "stdafx.h"
#include "image.h"

#pragma comment(lib, "msimg32.lib")

void image::frameRender(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,						//����� ������  DC
			destX,						//����� ��ǥ X
			destY,						//����� ��ǥ Y
			_imageInfo->frameWidth,		//����� ũ�� (����)
			_imageInfo->frameHeight,	//����� ũ�� (����)
			_imageInfo->hMemDC,			//�����ؿ� DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,		//������ ����ũ��
			_imageInfo->frameHeight,	//������ ����ũ��
			_transColor
		);
	}
	else
	{
		//�갡 �װ��Դϴ� DC���� ���� ��Ӻ��縦 ���ִ� �Լ�
		BitBlt(hdc,						//������ DC
			destX,						//������ ��ǥ X (left)
			destY,						//������ ��ǥ Y (top)
			_imageInfo->frameWidth,			//������ ũ��
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,			//����� DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//����� ������ (left, top)
			SRCCOPY);					//�������� �����Ұ���
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_trans)
	{
		GdiTransparentBlt(
			hdc,						//����� ������  DC
			destX,						//����� ��ǥ X
			destY,						//����� ��ǥ Y
			_imageInfo->frameWidth,		//����� ũ�� (����)
			_imageInfo->frameHeight,	//����� ũ�� (����)
			_imageInfo->hMemDC,			//�����ؿ� DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,		//������ ����ũ��
			_imageInfo->frameHeight,	//������ ����ũ��
			_transColor
		);
	}
	else
	{
		//�갡 �װ��Դϴ� DC���� ���� ��Ӻ��縦 ���ִ� �Լ�
		BitBlt(hdc,						//������ DC
			destX,						//������ ��ǥ X (left)
			destY,						//������ ��ǥ Y (top)
			_imageInfo->frameWidth,		//������ ũ��
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,			//����� DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//����� ������ (left, top)
			SRCCOPY);					//�������� �����Ұ���
	}
}