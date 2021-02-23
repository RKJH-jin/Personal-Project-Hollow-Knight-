#include "stdafx.h"
#include "CameraManager.h"
#include "image.h"

Camera::Camera()
{
	//�⺻ ����
	_minZoom = 0.01f;
	_maxZoom = 10.0f;

	//ī�޶� ����
	_zoom = 1.0f;
	_alpha = 1.0f;
	_angle = 0;
}

HRESULT Camera::Init()
{
	

	return S_OK;
}

void Camera::Release()
{
}

void Camera::Update()
{
	//��ũ�� ��Ʈ ����
	_screenRc = FloatRect(GetRelativePos(_pos), _size*_zoom, Pivot::Center);
}

void Camera::Render(Image * img, Vector2 pos)
{
	if (!_isActive) return;

	img->Render(pos, this);
}


//����Ʈ ��Ʈ ����
void Camera::SetViewRect(FloatRect rc)
{
	//����Ʈ ��Ʈ ����
	_viewRc = rc;

	_size.x = _viewRc.right - _viewRc.left;
	_size.y = _viewRc.bottom - _viewRc.top;

}

//ī�޶� ���� ����
void Camera::SetPos(Vector2 pos)
{
	_pos = pos;
	Update();
}

//���� ����
void Camera::SetZoom(float scale)
{
	_zoom = scale;

	if (_zoom < _minZoom) _zoom = _minZoom;
	if (_zoom > _maxZoom) _zoom = _maxZoom;

}

void Camera::SetAlpha(float alpha)
{
	_alpha = alpha;
}

void Camera::SetAngle(float angle)
{
	_angle = angle;
}

void Camera::SetActive(bool active)
{
	_isActive = active;
}

//ī�޶��� ��� ��ǥ�� ���� �޵��� ��ġ�� ����
Vector2 Camera::GetRelativePos(Vector2 pos)
{
	Vector2 result = pos;
	result -= Vector2(_pos.x, _pos.y);
	result.x *= _zoom;
	result.y *= _zoom;
	result += _viewRc.GetCenter();

	return result;
}

FloatRect Camera::GetRelativePos(FloatRect & rc)
{
	FloatRect result = rc;

	result.left = GetRelativePos(Vector2(result.left, result.top)).x;
	result.top = GetRelativePos(Vector2(result.left, result.top)).y;

	result.right = GetRelativePos(Vector2(result.right, result.bottom)).x;
	result.bottom = GetRelativePos(Vector2(result.right, result.bottom)).y;

	return result;
}

Vector2 Camera::GetAbsolutePos(Vector2 pos)
{
	Vector2 result = pos;
	result -= _viewRc.GetCenter();
	result.x /= _zoom;
	result.y /= _zoom;
	result += Vector2(_pos.x, _pos.y);

	return result;
}

FloatRect Camera::GetAbsolutePos(FloatRect& rc)
{
	FloatRect result = rc;

	result.left = GetAbsolutePos(Vector2(result.left, result.top)).x;
	result.top = GetAbsolutePos(Vector2(result.left, result.top)).y;

	result.right = GetAbsolutePos(Vector2(result.right, result.bottom)).x;
	result.bottom = GetAbsolutePos(Vector2(result.right, result.bottom)).y;

	return result;
}

void Camera::FillRectangle(FloatRect & rect, ID2D1Brush * brush)
{
	FloatRect rc = GetRelativePos(rect);

}

void CameraManager::CreateCamera(FloatRect rc)
{
	Camera* camera = new Camera();

	camera->Init();
	camera->SetViewRect(rc);

	_vCamera.push_back(camera);

}
