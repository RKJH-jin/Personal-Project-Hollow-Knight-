#include "stdafx.h"
#include "image.h"

#pragma comment(lib, "msimg32.lib")

void image::rotateRender(HDC hdc, float centerX, float centerY, float angle)
{
	//size = getDistance(0, 0, _imageInfo->width, _imageInfo->height); // 0, 0����(�̹����� �׷����� �����ϴ� ��ġ)���� �̹��� ���������� �Ÿ�

	HDC hWDC = GetDC(_hWnd);

	HDC destDC = CreateCompatibleDC(hWDC);
	HBITMAP hBitResult = CreateCompatibleBitmap(hWDC, size, size);
	HBITMAP destHOBit = (HBITMAP)SelectObject(destDC, hBitResult);

	HBRUSH backBrush = CreateSolidBrush(RGB(255, 0, 255));
	HBRUSH oldBackBrush = (HBRUSH)SelectObject(destDC, backBrush);
	PatBlt(destDC, 0, 0, size, size, PATCOPY);
	DeleteObject(SelectObject(destDC, oldBackBrush));

	float cosine = cosf(angle);
	float sine = sinf(angle);

	SetGraphicsMode(destDC, GM_ADVANCED);

	XFORM xform;
	xform.eM11 = cosine;
	xform.eM12 = sine;
	xform.eM21 = -sine;
	xform.eM22 = cosine;
	xform.eDx = size / 2;
	xform.eDy = size / 2;

	SetWorldTransform(destDC, &xform);

	cosf(angle)* (-size / 2) + sinf(angle) * (-size / 2);
	-sinf(angle) * (-size / 2) + cosf(angle) * (-size / 2);

	BitBlt(destDC, -_imageInfo->width / 2, -_imageInfo->height / 2, size, size, _imageInfo->hMemDC, 0, 0, SRCCOPY);

	SelectObject(destDC, destHOBit);
	DeleteObject(destDC);


	static HDC hTempMemDC; // ȸ���� ��Ʈ���� ������ �޸�DC
	HBITMAP hTempBitmap, hOldBitmap; // ȸ���� ��Ʈ���� ������, ��Ʈ�� �ڵ�

	if (!hTempMemDC) hTempMemDC = CreateCompatibleDC(hdc);

	hOldBitmap = (HBITMAP)SelectObject(hTempMemDC, hBitResult);

	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//����� ������  DC
			centerX - size / 2,						//����� ��ǥ X
			centerY - size / 2,						//����� ��ǥ Y
			size,					//����� ũ�� (����)
			size,					//����� ũ�� (����)
			hTempMemDC,		//�����ؿ� DC
			0, 0,					//�����ؿ� ��ǥ X, Y
			size,		//������ ����ũ��
			size,		//������ ����ũ��
			_transColor
		);
	}
	else
	{
		//�갡 �װ��Դϴ� DC���� ���� ��Ӻ��縦 ���ִ� �Լ�
		BitBlt(hdc,					//������ DC
			centerX - size / 2,					//������ ��ǥ X (left)
			centerY - size / 2,					//������ ��ǥ Y (top)
			size,					//������ ũ��
			size,
			hTempMemDC,				//����� DC
			0, 0,					//����� ������ (left, top)
			SRCCOPY);				//�������� �����Ұ���
	}

	SelectObject(hTempMemDC, hOldBitmap);
	DeleteObject(hBitResult);
}

void image::rotateRender2(HDC hdc, float centerX, float centerY, float angle)
{
	HDC hWDC = GetDC(_hWnd);

	HDC destDC = CreateCompatibleDC(hWDC);
	HBITMAP hBitResult = CreateCompatibleBitmap(hWDC, size, size);
	HBITMAP destHOBit = (HBITMAP)SelectObject(destDC, hBitResult);

	POINT pt[3];
	float dist = getDistance(0, 0, _imageInfo->width / 2, _imageInfo->height / 2);
	float baseAngle[3];
	float temp = atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));
	baseAngle[0] = PI - temp;
	baseAngle[1] = temp;
	baseAngle[2] = PI + temp;

	for (int i = 0; i < 3; ++i)
	{
		pt[i].x = (size / 2 + cosf(baseAngle[i] + angle) * dist);
		pt[i].y = (size / 2 + -sinf(baseAngle[i] + angle) * dist);
	}

	if (_trans)
	{
		BitBlt(destDC, 0, 0, size, size, hdc, 0, 0, BLACKNESS);
		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(destDC, hBrush);
		ExtFloodFill(destDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);

		PlgBlt(destDC, pt, _imageInfo->hMemDC,
			0,
			0,
			_imageInfo->width,
			_imageInfo->height,
			NULL, 0, 0);
		GdiTransparentBlt(hdc,
			centerX - size / 2,
			centerY - size / 2,
			size,
			size,
			destDC,
			0,
			0,
			size,
			size,
			_transColor);
	}
	else
	{
		PlgBlt(hdc, pt, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, NULL, 0, 0);
	}

}
