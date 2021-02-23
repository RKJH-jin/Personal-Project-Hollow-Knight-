#include "stdafx.h"
#include "TitleScene.h"
#include "MapToolScene.h"

#include "VolumeUI.h"

HRESULT TitleScene::init()
{
	Scene::init();
	DATAMANAGER->init();

	SOUNDMANAGER->play("title");

	//���콺 ���� �� �ʱ�ȭ
	_mouse = new Mouse;
	_mouse->Init();

	//Ÿ�� ������Ʈ ����� ����� �ش�.
	
	//�ΰ� �̹����� �����Ѵ�.
	_logoImg = IMAGEMANAGER->FindImage("PAlogo");
	
	_background = IMAGEMANAGER->FindImage("titleBackground");

	_volume = new VolumeUI;
	_text = L"Press Enter Or Click To Start";
	return S_OK;
}

void TitleScene::release()
{
	Scene::release();

}

void TitleScene::update()
{
	Scene::update();
	
	_volume->update();

	if(KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) SOUNDMANAGER->play("click8");

	if (_volume->GetTransform()->GetFloatRect().PtInRect(_ptMouse))
	{

	}
	else
	{
		//���͸� ġ�ų� ���� �ܸ� Ŭ���ϸ� ���� ����
		if (KEYMANAGER->isOnceKeyUp(VK_RETURN) || KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			SOUNDMANAGER->play("click3", DATAMANAGER->GetInfo().soundVolume * DATAMANAGER->GetInfo().sfxVolume);
			SCENEMANAGER->ReplaceScene(new MapToolScene);
		}
	}

}

void TitleScene::render()
{
	Scene::render();

	_background->Render(Vector2(WINSIZEX / 2, WINSIZEY / 2));

	_logoImg->SetScale(0.4f);
	_logoImg->Render(Vector2(WINSIZEX / 8, WINSIZEY/8));

	_volume->render();

	if (!_volume->GetTransform()->GetFloatRect().PtInRect(_ptMouse))
	{
		D2DRenderer::GetInstance()->RenderText(_ptMouse.x, _ptMouse.y, _text, 30, D2DRenderer::DefaultBrush::Red, DWRITE_TEXT_ALIGNMENT_LEADING);
	}

}
