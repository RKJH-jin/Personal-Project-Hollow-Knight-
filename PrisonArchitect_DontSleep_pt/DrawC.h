#pragma once
#include "Component.h"

class TransformC;

class DrawC : public Component
{
protected:
	TransformC* _transform;		//Ʈ������
	Camera* _camera;			//ī�޶�
	float _alpha;

public:
	DrawC() {}
	~DrawC() {}

	virtual void Awake() override;

	void SetCamera(Camera* camera) { _camera = camera; }

	void SetAlpha(float alpha) { _alpha = alpha; }
};

