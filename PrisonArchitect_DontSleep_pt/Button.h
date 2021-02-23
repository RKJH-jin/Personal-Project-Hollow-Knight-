#pragma once
#include "GameObject.h"

class Button : public GameObject
{
protected:
	FloatRect _rc;
	Vector2 _pos;
	Vector2 _imgSize;
    Vector2 _rcSize;

	Image* _img; // ���콺 �����Ͱ� ������ ��¦ �Ͼ��� + ���� �ѱ�� ���� �Ҹ��� ��
	float _scale;
	int _frameX, _frameY;

	function<void()> fn;
public:
	Button() {};
    Button(string strName, Vector2 pos, Vector2 size, float scale, Image* img);
	Button(string strName, string key, Vector2 pos, Vector2 rcSize, Vector2 imgSize, Image* img, Vector2 frame = Vector2(0,0));
	Button(string strName, Vector2 pos, float scale, Image* img);
	Button(string strName, Vector2 pos, float scale, Image* img, int frameX, int frameY);
	~Button();

	virtual void update();
	virtual void render();

	//GETTER
	FloatRect* getRect() { return &_rc; }
	Vector2 getPos() { return _pos; }
	Vector2 getImageSize() { return _imgSize; }
	Image* getImage() { return _img; }
	int getFrameX() { return _frameX; }
	int getFrameY() { return _frameY; }

	//�ݹ� �Լ�
	void setFunction(function<void()> fn) { this->fn = fn; }
	void invokeFunction() { fn(); }

	//���콺 �Լ�
	virtual Button* MouseEnter();
	virtual Button* MouseStay();
	virtual Button* MouseExit();
};

