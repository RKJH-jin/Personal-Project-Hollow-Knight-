#include "stdafx.h"
#include "Image.h"
#include "CameraManager.h"

/********************************************************************************
## Image ## 
@@ ID2D1Bitmap* bitmap : ImageManager���� ������ ��Ʈ��
@@ TagLoadImageInfo loadinfo : �̹��� ����(Ű��,���� ���) 

�������̹����� �ƴ� �̹��� Ŭ���� ����
*********************************************************************************/
Image::Image(ID2D1Bitmap * const bitmap, const TagLoadedImageInfo & loadinfo)
	:mBitmap(bitmap),mLoadInfo(loadinfo),mScale(1.f),mAlpha(1.f),mAngle(0.f),mMaxFrameX(1),mMaxFrameY(1)
{
	this->mSize.x = (float)this->mBitmap->GetPixelSize().width;
	this->mSize.y = (float)this->mBitmap->GetPixelSize().height;

	FrameRect rc;
	rc.x = 0;
	rc.y = 0;
	rc.width = mSize.x;
	rc.height = mSize.y;
	this->mFrameInfo.push_back(rc);
	this->ResetRenderOption();
}
/********************************************************************************
## Image ##
@@ ID2D1Bitmap* bitmap : ImageManager���� ������ ��Ʈ��
@@ TagLoadImageInfo loadinfo : �̹��� ����(Ű��,���� ���)
@@ int maxFrameX : ���� ������ �� 
@@ int maxFrameY : ���� ������ �� 

������ �̹��� Ŭ���� ����
*********************************************************************************/
Image::Image( ID2D1Bitmap *const bitmap, const TagLoadedImageInfo & loadinfo, const int  maxFrameX, const int  maxFrameY)
	:mBitmap(bitmap),mLoadInfo(loadinfo),mMaxFrameX(maxFrameX),mMaxFrameY(maxFrameY), mScale(1.f), mAlpha(1.f), mAngle(0.f)
{
	this->mSize.x = (float)mBitmap->GetPixelSize().width;
	this->mSize.y = (float)mBitmap->GetPixelSize().height;

	float frameX = mSize.x / (float)this->mMaxFrameX;
	float frameY = mSize.y / (float)this->mMaxFrameY;

	FrameRect rc;
	for (int j = 0; j < maxFrameY; ++j)
	{
	for (int i = 0; i < maxFrameX; ++i)
	{
		rc.x = (float)i * (frameX);
		rc.y = (float)j * (frameY);
		rc.width = frameX;
		rc.height = frameY;
		this->mFrameInfo.push_back(rc);
	}
	}

	this->ResetRenderOption();
}
/********************************************************************************
## ~Image ##
��Ʈ�� ����
*********************************************************************************/
Image::~Image()
{
	NEW_SAFE_RELEASE(mBitmap);
}
/********************************************************************************
## PerfeactRender ##
*********************************************************************************/
void Image::Render(const Vector2& position)
{
	Vector2 size = mSize * mScale;

	//������ ����� ������ش�
	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(mScale, mScale, D2D1::Point2F(size.x / 2.f, size.y / 2.f));
	//ȸ�� ����� ������ش�. 
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, D2D1::Point2F(size.x / 2.f, size.y / 2.f));
	//�̵� ����� ������ش�.
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(position.x - size.x / 2.f, position.y - size.y / 2.f);

	D2D1_RECT_F dxArea = D2D1::RectF(0.f, 0.f, size.x, size.y);

	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha);
	ResetRenderOption();
}

/********************************************************************************
## PerfeactFrameRender ##
*********************************************************************************/
void Image::FrameRender(const Vector2& position, const int frameX, const int frameY)
{
	//�������� �ִ� �������� ����ٸ� �׸��� �ʴ´�. 
	if (frameX >= this->mMaxFrameX || frameY >= this->mMaxFrameY || frameX < 0 || frameY < 0)
	{
		ResetRenderOption();
		return;
	}

	//���� �������ε��� 
	int frame = frameY * mMaxFrameX + frameX;

	//������ = ������ * ������
	Vector2 size = mSize * mScale;

	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(mScale, mScale, D2D1::Point2F(size.x / 2.f, size.y / 2.f));
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, D2D1::Point2F(size.x / 2.f, size.y / 2.f));
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(position.x - size.x / 2.f, position.y - size.y / 2.f);

	//�׸� ���� ���� 
	D2D1_RECT_F dxArea = D2D1::RectF(0.0f, 0.0f, size.x, size.y);
	D2D1_RECT_F dxSrc = D2D1::RectF((float)mFrameInfo[frame].x, (float)mFrameInfo[frame].y,
		(float)(mFrameInfo[frame].x + mFrameInfo[frame].width),
		(float)(mFrameInfo[frame].y + mFrameInfo[frame].height));
	//������� ����
	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	//������ ��û
	D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, &dxSrc);

	this->ResetRenderOption();
}
/********************************************************************************
## SourceRender ##
*********************************************************************************/
void Image::SourceRender(const Vector2 & position, Vector2 InputSize, Vector2 frameIndex) //CenterBottom
{
	//���� �������ε��� 
	int frame = frameIndex.y* mMaxFrameX + frameIndex.x;

	//������ = ������ * ������
	Vector2 size = mSize * mScale;

	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(mScale, mScale, D2D1::Point2F(size.x / 2.f, size.y / 2.f));
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, D2D1::Point2F(size.x / 2.f, size.y / 2.f));
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(position.x - size.x / 2.f, position.y - size.y / 2.f);

	//�׸� ���� ���� 
	D2D1_RECT_F dxArea = D2D1::RectF(0.0f, 0.0f, size.x, size.y);
	D2D1_RECT_F dxSrc = D2D1::RectF((float)mFrameInfo[frame].x+ mFrameInfo[frame].width/2 - InputSize.x/2,
		(float)mFrameInfo[frame].y + mFrameInfo[frame].height- InputSize.y,
		(float)(mFrameInfo[frame].x + mFrameInfo[frame].width/2 + InputSize.x/2),
		(float)(mFrameInfo[frame].y + mFrameInfo[frame].height));
	//������� ����
	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	//������ ��û
	D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, &dxSrc);

	this->ResetRenderOption();
}


/********************************************************************************
## Camera Render Function ##
*********************************************************************************/
void Image::Render(const Vector2 & position, Camera* camera)
{
	//������ ��ǥ, ũ��, ����, ������
	Vector2 renderPos = position;				//�׸� ��ġ
	Vector2 renderSize = mSize * mScale;		//�׸� ũ��
	float renderScale = mScale;					//�׸� ����
	float renderAngle = mAngle;					//�׸� ����
	float renderAlpha = mAlpha;					//�׸� ������

	mRect = FloatRect(renderPos, renderSize, Pivot::Center);

	//ī�޶� ���� ����
	if (camera)
	{
		//ī�޶� ��� ��ǥ
		renderPos = camera->GetRelativePos(renderPos);

		//ī�޶� ����
		renderSize = renderSize * camera->_zoom;
		//renderScale *= camera->_zoom;

		//ī�޶� ����
		renderAngle += camera->_angle;

		//ī�޶� ������
		renderAlpha *= camera->_alpha;
	}


	renderSize = renderSize * renderScale;

	//������ �̹��� ��Ʈ ����
	mRenderRect = FloatRect(renderPos, renderSize, Pivot::Center);

	//ī�޶� ����Ʈ ��Ʈ ����
	FloatRect viewRc = camera->_viewRc;


	//������ ����� ������ش�.
	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(renderScale, renderScale, D2D1::Point2F(renderSize.x / 2.f, renderSize.y / 2.f));
	Vector2 offset(0, 0);

	//���η� ������ ���ΰ�
	if (mIsReverseAxisX)
	{
		scaleMatrix = D2D1::Matrix3x2F::Scale(-renderScale, renderScale);
		offset.x = renderSize.x;
	}

	//���η� ������ ���ΰ�
	if (mIsReverseAxisY)
	{
		scaleMatrix = D2D1::Matrix3x2F::Scale(renderScale, -renderScale);
		offset.y = renderSize.y;
	}

	//ȸ�� ����� ������ش�. 
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(renderAngle, D2D1::Point2F(renderSize.x / 2.f, renderSize.y / 2.f));
	//�̵� ����� ������ش�.
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(renderPos.x - renderSize.x / 2.f + offset.x, renderPos.y - renderSize.y / 2.f + offset.y);
	//�׸� ������ �����Ѵ�.
	D2D1_RECT_F dxArea = D2D1::RectF(0.f, 0.f, renderSize.x, renderSize.y);

	_D2DRenderer->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);

	//������ ��û
	_D2DRenderer->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, renderAlpha);
#if true // Debug

	//������ ��Ʈ ����
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		D2DRenderer::GetInstance()->DrawRectangle(mRenderRect, D2DRenderer::DefaultBrush::Blue, 1.0f);
	}

#endif // Debug

	ResetRenderOption();

}

/********************************************************************************
## Camera Frame Render Function ##
*********************************************************************************/
void Image::FrameRender(const Vector2 & position, const int frameX, const int frameY, Camera * camera)
{
	//�������� �ִ� �������� ����ٸ� �׸��� �ʴ´�. 
	if (frameX >= this->mMaxFrameX || frameY >= this->mMaxFrameY || frameX < 0 || frameY < 0)
	{
		ResetRenderOption();
		return;
	}
	
	//���� ������ �ε��� 
	int frame = frameY * mMaxFrameX + frameX;

	//������ ��ǥ, ũ��, ����, ������
	Vector2 renderPos = position;				//�׸� ��ġ
	Vector2 renderSize = mSize;					//�׸� ũ��
	float renderScale = mScale;					//�׸� ����
	float renderAngle = mAngle;					//�׸� ����
	float renderAlpha = mAlpha;					//�׸� ������

	mRect = FloatRect(renderPos, renderSize, Pivot::Center);

	//ī�޶� ���� ����
	
	if (camera)
	{
		//ī�޶� ��� ��ǥ
		renderPos = camera->GetRelativePos(renderPos);

		//ī�޶� ������ ���� ũ��
		renderSize = renderSize * camera->_zoom;
		//renderScale *= camera->_zoom;

		//ī�޶� ����
		renderAngle += camera->_angle;

		//ī�޶� ������
		renderAlpha *= camera->_alpha;
	}

	renderSize = renderSize * renderScale;

	//������ �̹��� ��Ʈ ����
	mRenderRect = FloatRect(renderPos, renderSize, Pivot::Center);

	//ī�޶� ����Ʈ ��Ʈ ����
	FloatRect viewRc = camera->_viewRc;

#pragma region Ŭ����
	

	//Ŭ���� ���� - ������ â
	if (mRenderRect.left > WINSIZEX || mRenderRect.right < 0.f ||
		mRenderRect.top > WINSIZEY || mRenderRect.bottom < 0.f)
	{
		ResetRenderOption();
		return;
	}

	//Ŭ���� ���� - ī�޶� ����Ʈ
	if (camera)
	{
		if (mRenderRect.left > viewRc.right || mRenderRect.right < viewRc.left ||
			mRenderRect.top > viewRc.bottom || mRenderRect.bottom < viewRc.top)
		{
			ResetRenderOption();
			return;
		}
	}
#pragma endregion

	//������ ����� ������ش�.
	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(renderScale, renderScale, D2D1::Point2F(renderSize.x / 2.f, renderSize.y / 2.f));
	Vector2 offset(0, 0);

	//���η� ������ ���ΰ�
	if (mIsReverseAxisX)
	{
		scaleMatrix = D2D1::Matrix3x2F::Scale(-renderScale, renderScale);
		offset.x = renderSize.x;
	}

	//���η� ������ ���ΰ�
	if (mIsReverseAxisY)
	{
		scaleMatrix = D2D1::Matrix3x2F::Scale(renderScale, -renderScale);
		offset.y = renderSize.y;
	}

	//ȸ�� ����� ������ش�. 
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(renderAngle, D2D1::Point2F(renderSize.x / 2.f, renderSize.y / 2.f));
	//�̵� ����� ������ش�.
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(renderPos.x - renderSize.x / 2.f + offset.x, renderPos.y - renderSize.y / 2.f + offset.y);

	//�׸� ���� ����
	D2D1_RECT_F dxArea = D2D1::RectF(0.f, 0.f, renderSize.x, renderSize.y);

	//�ҽ����� ������ ���� ����
	D2D1_RECT_F dxSrc = D2D1::RectF((float)mFrameInfo[frame].x, (float)mFrameInfo[frame].y,
		(float)(mFrameInfo[frame].x + mFrameInfo[frame].width),
		(float)(mFrameInfo[frame].y + mFrameInfo[frame].height));

	_D2DRenderer->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	//������ ��û
	_D2DRenderer->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, renderAlpha,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, &dxSrc);


#if true // Debug

	//������ ��Ʈ ����
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		D2DRenderer::GetInstance()->DrawRectangle(mRenderRect, D2DRenderer::DefaultBrush::Blue, 1.0f);
	}

#endif // Debug

	ResetRenderOption();

}

/********************************************************************************
## ResetRenderOption ##
�̹��� Ŭ���� ���� ���� �ɼǵ� ���� �ʱ�ȭ
*********************************************************************************/
void Image::ResetRenderOption()
{
	this->mAlpha = 1.0f;
	this->mScale = 1.0f;
	this->mAngle = 0.f;
	if (mFrameInfo.size() <= 1)
	{
		this->mSize.x = (float)mBitmap->GetPixelSize().width;
		this->mSize.y = (float)mBitmap->GetPixelSize().height;
	}
	else
	{
		this->mSize.x = mFrameInfo[0].width;
		this->mSize.y = mFrameInfo[0].height;
	}
	this->mIsReverseAxisX = this->mIsReverseAxisY = false;
}
