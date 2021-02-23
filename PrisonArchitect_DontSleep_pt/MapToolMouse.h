#pragma once
#include "Mouse.h"

enum class TILEATTRIBUTE;
enum class MOUSEDRAG;
enum class MOUSESTATE;

class TileMap;
class MapToolScene;

class MapToolMouse : public Mouse
{
private:
	float _zoom;						//��
	float _prevZoom;					//���� ��

	GameObject* _cameraPivot;			//ī�޶� �Ǻ�
	GameObject* _cameraGoal;			//ī�޶� ��

	Vector2 _startPoint;				//���� ��
	Vector2 _startIndex;				//���� �ε���

	Vector2 _endPoint;					//�� ��
	Vector2 _endIndex;					//�� �ε���

	bool _isDragging;					//�巡�� ������
	MOUSEDRAG _drag;					//�巡�� ����

	vector<Vector2> _vSelectIndex;		//���� Ÿ�� �ε���

	TileAttribute* _rollOverObj;			//�ѿ��� ������Ʈ

	TileAttribute* _selectObj;				//���� ������Ʈ
	Character* _selectChar;					//���� ĳ����
	int _charNum;

	TileMap* _tileMap;						//Ÿ�� ��
	MapToolScene* _scene;					//��

	//���콺 ����
	FloatRect _mouseArea[4];

public:
	MapToolMouse(MapToolScene* scene);
	~MapToolMouse() {};

	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	//���콺 ����
	void BuildRender();

	//���콺 ��Ʈ��
	void Control();
	void Move();
	void OnUICheck();			//������ ���� �ִ� �� üũ

    void UIControl();           //������
	void BuildControl();		//����
	void DestroyControl();		//�ı�
	void SelectControl();		//����
	void DeleteControl();		//����

	template<typename T>
	void OnCollisionEnter(T* obj);

	template<typename T>
	void OnCollisionExit(T* obj);

	template<typename T>
	void OnCollisionStay(T* obj);

	void DeleteMouseObject();

};

template<typename T>
inline void MapToolMouse::OnCollisionEnter(T * obj)
{
	SOUNDMANAGER->play("click4", DATAMANAGER->GetInfo().soundVolume);

	obj->MouseEnter();
}

template<typename T>
inline void MapToolMouse::OnCollisionExit(T * obj)
{
	obj->MouseExit();
}

template<typename T>
inline void MapToolMouse::OnCollisionStay(T * obj)
{
	obj->MouseStay();
}