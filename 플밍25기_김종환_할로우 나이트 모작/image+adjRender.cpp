#include "stdafx.h"
#include "image.h"

#pragma comment(lib, "msimg32.lib")

void image::adjRender(HDC hdc, int destX, int destY, int adjWidth, int adjHeight)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//����� ������  DC
			destX,					//����� ��ǥ X
			destY,					//����� ��ǥ Y
			adjWidth,				//����� ũ�� (����)
			adjHeight,				//����� ũ�� (����)
			_imageInfo->hMemDC,		//�����ؿ� DC
			0, 0,					//�����ؿ� ��ǥ X, Y
			_imageInfo->width,		//������ ����ũ��
			_imageInfo->height,		//������ ����ũ��
			_transColor
		);
	}
	else
	{
		SetStretchBltMode(hdc, HALFTONE);
		StretchBlt(
			hdc,					//������ DC
			destX,					//������ ��ǥ X (left)
			destY,					//������ ��ǥ Y (top)
			adjWidth,				//������ width
			adjHeight,				//������ height
			_imageInfo->hMemDC,		//����� DC
			0, 0,					//����� ������ (left, top)
			_imageInfo->width,		//�̹��� ũ��
			_imageInfo->height,
			SRCCOPY);				//�������� �����Ұ���
	}
}

void image::adjFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, int adjWidth, int adjHeight)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_trans)
	{
		GdiTransparentBlt(
			hdc,						//����� ������  DC
			destX,						//����� ��ǥ X
			destY,						//����� ��ǥ Y
			adjWidth,					//����� ũ�� (����)
			adjHeight,					//����� ũ�� (����)
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
		SetStretchBltMode(hdc, HALFTONE);
		StretchBlt(hdc,
			destX,
			destY,
			adjWidth,
			adjHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,		//������ ����ũ��
			_imageInfo->frameHeight,	//������ ����ũ��
			SRCCOPY
		);
	}
}



