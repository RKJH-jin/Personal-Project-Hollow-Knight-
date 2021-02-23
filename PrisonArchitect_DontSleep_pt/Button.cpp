#include "stdafx.h"
#include "Button.h"

Button::Button(string strName, Vector2 pos, Vector2 size, float scale, Image* img)
{
    _name = strName;
    _img = img;
    _scale = scale;
    _img->SetScale(_scale);
    _pos = pos;
    _rcSize = size;
    _imgSize = size;
    _rc = FloatRect(_pos, _rcSize, Pivot::Center);

	SetDescription(_name + "�Դϴ�");

    _frameX = 0;
    _frameY = 0;
}

Button::Button(string strName, string key, Vector2 pos, Vector2 rcSize, Vector2 imgSize, Image* img, Vector2 frame)
{
	_name = strName;
	_key = key;
	_img = img;
	_scale = 0.6f;
	_img->SetScale(_scale);
	_pos = pos;
    _rcSize = rcSize;
	_imgSize = imgSize;
	_rc = FloatRect(_pos, _rcSize, Pivot::Center);

	SetDescription(_name + " ���� ��ư�Դϴ�.\nŬ���ϰ� ��ġ�� �����ϸ� ��ġ�˴ϴ�.");

	_frameX = frame.x;
	_frameY = frame.y;
}

Button::Button(string strName, Vector2 pos, float scale, Image * img)
{
	_name = strName;
	_img = img;
	_scale = scale;
	_img->SetScale(_scale);
	_pos = pos;
	_imgSize = _img->GetFrameSize();
	_rc = FloatRect(_pos, _imgSize * _scale * _scale, Pivot::Center);

	SetDescription(_name + " ��ư�Դϴ�./nŬ�� �� ��ġ īŻ�α׸� Ȯ���� �� �ֽ��ϴ�.");

	_frameX = 0;
	_frameY = 0;
}

Button::Button(string strName, Vector2 pos, float scale, Image* img, int frameX, int frameY)
{
	_name = strName;
	_img = img;
	_scale = scale;
	_img->SetScale(_scale);
	_pos = pos;
	_imgSize = _img->GetFrameSize();
	_rc = FloatRect(_pos, _imgSize * _scale * _scale, Pivot::Center);

	SetName(_name);
	SetDescription(_name + "��ư�Դϴ�");

	_frameX = frameX;
	_frameY = frameY;
}

Button::~Button()
{
}

void Button::update()
{
	if (!_isActive) return;

	if (_rc.PtInRect(_ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if(fn) invokeFunction();
		}
	}
}

void Button::render()
{
	if (!_isRender) return;

#if true // Debug

	//������ ��Ʈ ����
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		D2DRenderer::GetInstance()->DrawRectangle(_rc, D2DRenderer::DefaultBrush::Blue, 1.0f);
	}

#endif // Debug
	_img->SetScale(_scale);
	_img->SetSize(_imgSize);
	_img->SourceRender(_pos, _imgSize, Vector2(_frameX, _frameY));
}

Button * Button::MouseEnter()
{
	return nullptr;
}

Button * Button::MouseStay()
{
	return nullptr;
}

Button * Button::MouseExit()
{
	return nullptr;
}
