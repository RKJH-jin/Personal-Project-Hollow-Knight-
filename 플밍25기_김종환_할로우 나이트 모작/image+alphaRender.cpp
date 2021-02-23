#include "stdafx.h"
#include "image.h"

#pragma comment(lib, "msimg32.lib")

void image::alphaRender(HDC hdc, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(
			_blendImage->hMemDC,					//����� ������  DC
			0,						//����� ��ǥ X
			0,						//����� ��ǥ Y
			_imageInfo->width,		//����� ũ�� (����)
			_imageInfo->height,		//����� ũ�� (����)
			hdc,		//�����ؿ� DC
			_imageInfo->x,
			_imageInfo->y,
			SRCCOPY
		);

		GdiTransparentBlt(
			_blendImage->hMemDC,					//����� ������  DC
			0,						//����� ��ǥ X
			0,						//����� ��ǥ Y
			_imageInfo->width,		//����� ũ�� (����)
			_imageInfo->height,		//����� ũ�� (����)
			_imageInfo->hMemDC,		//�����ؿ� DC
			0,
			0,
			_imageInfo->width,		//������ ����ũ��
			_imageInfo->height,		//������ ����ũ��
			_transColor
		);

		AlphaBlend(
			hdc,					//����� ������  DC
			_imageInfo->x,			//����� ��ǥ X
			_imageInfo->y,			//����� ��ǥ Y
			_imageInfo->width,		//����� ũ�� (����)
			_imageInfo->height,		//����� ũ�� (����)
			_blendImage->hMemDC,		//�����ؿ� DC
			0,
			0,
			_imageInfo->width,		//������ ����ũ��
			_imageInfo->height,		//������ ����ũ��
			_blendFunc
		);
	}
	else
	{
		AlphaBlend(
			hdc,					//����� ������  DC
			_imageInfo->x,			//����� ��ǥ X
			_imageInfo->y,			//����� ��ǥ Y
			_imageInfo->width,		//����� ũ�� (����)
			_imageInfo->height,		//����� ũ�� (����)
			_imageInfo->hMemDC,		//�����ؿ� DC
			0,
			0,
			_imageInfo->width,		//������ ����ũ��
			_imageInfo->height,		//������ ����ũ��
			_blendFunc
		);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(
			_blendImage->hMemDC,		//����� ������  DC
			0,							//����� ��ǥ X
			0,							//����� ��ǥ Y
			_imageInfo->width,			//����� ũ�� (����)
			_imageInfo->height,			//����� ũ�� (����)
			hdc,						//�����ؿ� DC
			destX,
			destY,
			SRCCOPY
		);

		GdiTransparentBlt(
			_blendImage->hMemDC,		//����� ������  DC
			0,							//����� ��ǥ X
			0,							//����� ��ǥ Y
			_imageInfo->width,			//����� ũ�� (����)
			_imageInfo->height,			//����� ũ�� (����)
			_imageInfo->hMemDC,			//�����ؿ� DC
			0,
			0,
			_imageInfo->width,			//������ ����ũ��
			_imageInfo->height,			//������ ����ũ��
			_transColor
		);

		AlphaBlend(
			hdc,						//����� ������  DC
			destX,						//����� ��ǥ X
			destY,						//����� ��ǥ Y
			_imageInfo->width,			//����� ũ�� (����)
			_imageInfo->height,			//����� ũ�� (����)
			_blendImage->hMemDC,		//�����ؿ� DC
			0,
			0,
			_imageInfo->width,			//������ ����ũ��
			_imageInfo->height,			//������ ����ũ��
			_blendFunc
		);
	}
	else
	{
		AlphaBlend(
			hdc,					//����� ������  DC
			destX,					//����� ��ǥ X
			destY,					//����� ��ǥ Y
			_imageInfo->width,		//����� ũ�� (����)
			_imageInfo->height,		//����� ũ�� (����)
			_imageInfo->hMemDC,		//�����ؿ� DC
			0,
			0,
			_imageInfo->width,		//������ ����ũ��
			_imageInfo->height,		//������ ����ũ��
			_blendFunc
		);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(
			_blendImage->hMemDC,						//����� ������  DC
			destX,						//����� ��ǥ X
			destY,						//����� ��ǥ Y
			sourWidth,					//����� ũ�� (����)
			sourHeight,					//����� ũ�� (����)
			hdc,						//�����ؿ� DC
			sourX,
			sourY,
			SRCCOPY
		);

		GdiTransparentBlt(
			_blendImage->hMemDC,						//����� ������  DC
			destX,						//����� ��ǥ X
			destY,						//����� ��ǥ Y
			sourWidth,					//����� ũ�� (����)
			sourHeight,					//����� ũ�� (����)
			_imageInfo->hMemDC,			//�����ؿ� DC
			sourX,
			sourY,
			sourWidth,					//������ ����ũ��
			sourHeight,					//������ ����ũ��
			_transColor
		);

		AlphaBlend(
			hdc,						//����� ������  DC
			destX,						//����� ��ǥ X
			destY,						//����� ��ǥ Y
			sourWidth,					//����� ũ�� (����)
			sourHeight,					//����� ũ�� (����)
			_blendImage->hMemDC,			//�����ؿ� DC
			sourX,
			sourY,
			sourWidth,					//������ ����ũ��
			sourHeight,					//������ ����ũ��
			_blendFunc
		);
	}
	else
	{
		AlphaBlend(
			hdc,						//����� ������  DC
			destX,						//����� ��ǥ X
			destY,						//����� ��ǥ Y
			sourWidth,					//����� ũ�� (����)
			sourHeight,					//����� ũ�� (����)
			_imageInfo->hMemDC,			//�����ؿ� DC
			sourX,
			sourY,
			sourWidth,					//������ ����ũ��
			sourHeight,					//������ ����ũ��
			_blendFunc
		);
	}
}

void image::alphaFrameRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(
			_blendImage->hMemDC,						//����� ������  DC
			0,						//����� ��ǥ X
			0,						//����� ��ǥ Y
			_imageInfo->frameWidth,		//����� ũ�� (����)
			_imageInfo->frameHeight,	//����� ũ�� (����)
			hdc,						//�����ؿ� DC
			destX,
			destY,
			SRCCOPY
		);

		GdiTransparentBlt(
			_blendImage->hMemDC,						//����� ������  DC
			0,						//����� ��ǥ X
			0,						//����� ��ǥ Y
			_imageInfo->frameWidth,		//����� ũ�� (����)
			_imageInfo->frameHeight,	//����� ũ�� (����)
			_imageInfo->hMemDC,			//�����ؿ� DC
			_imageInfo->frameWidth * _imageInfo->currentFrameX,
			_imageInfo->frameHeight * _imageInfo->currentFrameY,
			_imageInfo->frameWidth,		//������ ����ũ��
			_imageInfo->frameHeight,	//������ ����ũ��
			_transColor
		);

		AlphaBlend(
			hdc,						//����� ������  DC
			destX,						//����� ��ǥ X
			destY,						//����� ��ǥ Y
			_imageInfo->frameWidth,		//����� ũ�� (����)
			_imageInfo->frameHeight,	//����� ũ�� (����)
			_blendImage->hMemDC,		//�����ؿ� DC
			0,
			0,
			_imageInfo->frameWidth,		//������ ����ũ��
			_imageInfo->frameHeight,	//������ ����ũ��
			_blendFunc
		);
	}
	else
	{
		AlphaBlend(
			hdc,						//����� ������  DC
			destX,						//����� ��ǥ X
			destY,						//����� ��ǥ Y
			_imageInfo->frameWidth,		//����� ũ�� (����)
			_imageInfo->frameHeight,	//����� ũ�� (����)
			_imageInfo->hMemDC,			//�����ؿ� DC
			_imageInfo->frameWidth * _imageInfo->currentFrameX,
			_imageInfo->frameHeight * _imageInfo->currentFrameY,
			_imageInfo->frameWidth,		//������ ����ũ��
			_imageInfo->frameHeight,	//������ ����ũ��
			_blendFunc
		);
	}
}

void image::alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(
			_blendImage->hMemDC,		//����� ������  DC
			0,							//����� ��ǥ X
			0,							//����� ��ǥ Y
			_imageInfo->frameWidth,		//����� ũ�� (����)
			_imageInfo->frameHeight,	//����� ũ�� (����)
			hdc,						//�����ؿ� DC
			destX,
			destY,
			SRCCOPY
		);

		GdiTransparentBlt(
			_blendImage->hMemDC,		//����� ������  DC
			0,						//����� ��ǥ X
			0,						//����� ��ǥ Y
			_imageInfo->frameWidth,		//����� ũ�� (����)
			_imageInfo->frameHeight,	//����� ũ�� (����)
			_imageInfo->hMemDC,			//�����ؿ� DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,		//������ ����ũ��
			_imageInfo->frameHeight,	//������ ����ũ��
			_transColor
		);

		AlphaBlend(
			hdc,						//����� ������  DC
			destX,						//����� ��ǥ X
			destY,						//����� ��ǥ Y
			_imageInfo->frameWidth,		//����� ũ�� (����)
			_imageInfo->frameHeight,	//����� ũ�� (����)
			_blendImage->hMemDC,		//�����ؿ� DC
			0,
			0,
			_imageInfo->frameWidth,		//������ ����ũ��
			_imageInfo->frameHeight,	//������ ����ũ��
			_blendFunc
		);
	}
	else
	{
		AlphaBlend(
			hdc,						//����� ������  DC
			destX,						//����� ��ǥ X
			destY,						//����� ��ǥ Y
			_imageInfo->frameWidth,		//����� ũ�� (����)
			_imageInfo->frameHeight,	//����� ũ�� (����)
			_imageInfo->hMemDC,			//�����ؿ� DC
			_imageInfo->frameWidth * _imageInfo->currentFrameX,
			_imageInfo->frameHeight * _imageInfo->currentFrameY,
			_imageInfo->frameWidth,		//������ ����ũ��
			_imageInfo->frameHeight,	//������ ����ũ��
			_blendFunc
		);
	}
}