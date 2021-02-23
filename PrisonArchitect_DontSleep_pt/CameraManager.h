#pragma once
class Image;

class Camera
{
public:	//�� ¥�� ���� private���� �ٲ� ����

	FloatRect _screenRc;	//ī�޶� ��ũ�� ����
	FloatRect _viewRc;		//ī�޶� ����Ʈ ����

	Vector2 _pos;			//ī�޶� ���� ��ġ
	Vector2 _size;			//ī�޶� ũ��

	float _zoom;			//���� (scale)
	float _alpha;			//����
	float _angle;			//���� (rotation)

	bool _isActive;			//Ȱ��ȭ ����

	float _minZoom;			//�ּ� ����
	float _maxZoom;			//�ִ� ����

public:

	Camera();
	~Camera() {}

	HRESULT Init();
	void Release();
	void Update();
	void Render(Image* img, Vector2 pos); //�� �ᵵ ��

	//����
	float GetScale() { return _zoom; }
	float GetAlpha() { return _alpha; }
	FloatRect GetViewRect() { return _viewRc; }

	//����
	void SetViewRect(FloatRect rc);
	void SetPos(Vector2 pos);
	void SetZoom(float scale);
	void SetAlpha(float alpha);
	void SetAngle(float angle);
	void SetActive(bool active);

	Vector2 GetRelativePos(Vector2 pos);
	FloatRect GetRelativePos(FloatRect & rc);
	Vector2 GetAbsolutePos(Vector2 pos);
	FloatRect GetAbsolutePos(FloatRect & rc);

	//�Լ�

	void FillRectangle(FloatRect &rect, _In_ ID2D1Brush *brush);
	
};

class CameraManager
{

public:
	static CameraManager* GetInstance()
	{
		static CameraManager istance;
		return &istance;
	}

private:
	typedef vector<Camera*> vCamera;

	vCamera _vCamera;

public:
	
	vCamera& GetVCamera() { return _vCamera; }

	Camera* GetMainCamera() { return _vCamera[0]; }

	//�Լ�
	void CreateCamera(FloatRect rc);
	
};

