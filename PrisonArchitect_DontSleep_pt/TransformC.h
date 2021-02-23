#pragma once
#include "Component.h"
#include "JumpPointSearch.h"

class TransformC : public Component
{
private:
	Vector2 _pivot;			//�ǹ�
	Vector2 _pos;			//��ġ
	Vector2 _index;         //�ε���
	DIRECTION _direction;	//����

	Vector2 _size;		//ũ��
	FloatRect _rc;	//��Ʈ

	Camera* _camera;

	bool haveTarget = false;
	Vector2 _target;		//��ǥ����
	stack<Vector2> _path;	//��ǥ������ ���
	Vector2 _endIndex;		//�� �ε���
	bool arriveEndIndex = false;
public:
	TransformC() {};
	~TransformC() {};

	//����
	Vector2 GetPosition() { return _pos; }
	Vector2 GetPivot() { return _pivot; }
	DIRECTION GetDirection() { return _direction; }

	RECT GetRect();
	FloatRect GetFloatRect() { return _rc; }

	Vector2 GetIndex() { return _index; }
	Vector2 GetTarget() { return _target; }
	stack<Vector2>& GetPath() { return _path; }
	bool GetHaveTarget() { return haveTarget; }
	Vector2 GetEndIndex() { return _endIndex; }
	bool GetArriveEndIndex() { return arriveEndIndex; }

	//����
	void SetPosition(Vector2 pos);
	void SetPivot(Vector2 pivot) { _pivot = pivot; _pos = pivot; };
	void SetDirection(DIRECTION direction) { _direction = direction; }
	void SetSize(Vector2 size) { _size = size; }

	void SetCamera(Camera* camera) { _camera = camera; }

	void SetIndex(Vector2 idx) { _index = idx; }
	void SetTarget(Vector2 target) { _target = target; }
	void SetPath(Vector2 endIndex)
	{
		_endIndex = endIndex;
		_index = Vector2((int)(_pos.x / TILESIZE), (int)(_pos.y / TILESIZE));
		_path = JumpPointSearch::GetInstance()->PathFinding(_index, _endIndex);
	}
	void SetHaveTarget(bool boolValue) { haveTarget = boolValue; }
	void SetArriveEndIndex(bool boolValue) { arriveEndIndex = boolValue; }

	//�Լ�
	virtual void Init();
	virtual void Update();
	virtual void Render();

	void Translate(Vector2 delta);
	void SetRect();

};

