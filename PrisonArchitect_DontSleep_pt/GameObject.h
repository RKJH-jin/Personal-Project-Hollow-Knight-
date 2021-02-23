#pragma once
#include <vector>

class Component;
class TransformC;

struct Color
{
	float r; float g; float b; float a;
};

class GameObject
{
protected:
	/* ==================================================
		������Ʈ ���
	================================================== */
	string _name;				//�̸�
	string _key;				//Ű
	string _tag;				//�±�
	string _description;		//����
	vector<string> _vDescription;	//������
	bool _isActive;				//Ȱ��ȭ ����
	bool _isRender;				//���� ����

	/* ==================================================
		������Ʈ
	================================================== */
	vector<Component*> _vComponent;		//������Ʈ ����
	TransformC* _transform;				//Ʈ������

	/* ==================================================
		�θ� �ڽ� ������Ʈ
	================================================== */
	GameObject* _parent;				//�θ�
	vector<GameObject*> _vChild;		//�ڽ� ����

public:
	GameObject();
	~GameObject() {}

	/* ==================================================
		������Ʈ�� Ŭ�� ����
	================================================== */

	//������Ʈ �����
	static GameObject* CreateObject(GameObject* parent = NULL);

	//Ŭ�� �����
	template<typename T>
	T* GetClone();

	/* ==================================================
		�θ� �ڽ� ����
	================================================== */

	//�θ� ����
	void SetParent(GameObject* parent);
	
	//�ڽ� �߰�
	void AddChild(GameObject* child);
	
	//�ڽ� ����
	void RemoveChild(GameObject* child);



	/* ==================================================
		������Ʈ ���� ����
	================================================== */

	//������Ʈ ���� ����
	template<typename T>
	vector<T*> GetvComponent();

	//������Ʈ ����
	template<typename T>
	T * GetComponent();

	//������Ʈ �߰�
	template<typename T>
	T * AddComponent();

	//������Ʈ ����
	void RemoveComponent(Component* component);

	//Ʈ������ ����
	TransformC* GetTransform() { return _transform; };

	
	/* ==================================================
		����
	================================================== */
	GameObject* GetParent() { return _parent; };
	vector<GameObject*> GetvChild() { return _vChild; };
	//GameObject* GetChildByName(string name);

	string GetName() { return _name; };						//�̸�
	string GetTag() { return _tag; };						//�±�
	string GetKey() { return _key; }						//Ű
	string GetDescription() { return _description; };		//����

	bool GetActive() { return _isActive; }

	/* ==================================================
		����
	================================================== */
	void SetName(string name) { _name = name; }
	void SetKey(string key) { _key = key; }
	void SetTag(string tag) { _tag = tag; }
	void SetDescription(string des) { _description = des; }
	void AddDescription(string des) { _vDescription.push_back(des); }

	void SetActive(bool active);
	void SetRender(bool render);
	/* ==================================================
		�Լ�
	================================================== */
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

};

template<typename T>
inline vector<T*> GameObject::GetvComponent()
{
	vector<T*> componentVector;
	for (auto c : _vComponent)
	{
		if (dynamic_cast<T*>(c)) componentVector.push_back((T*)c);
	}
	return componentVector;
}

//������Ʈ ����
template<typename T>
inline T * GameObject::GetComponent()
{
	for (Component* c : _vComponent)
	{
		if (dynamic_cast<T*>(c)) return (T*)c;
	}
	return NULL;
}

//������Ʈ �߰�
template<typename T>
inline T * GameObject::AddComponent()
{
	Component* component = new T();
	component->LinkGameObject(this);
	_vComponent.push_back(component);
	component->Awake();
	return (T*)component;
}

//Ŭ�� �����
template<typename T>
inline T * GameObject::GetClone()
{
	T* object = new T();
	memmove(object, this, sizeof(T*));
	return object;
}
