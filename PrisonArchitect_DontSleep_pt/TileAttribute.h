#pragma once
#include "GameObject.h"
class TileAttribute : public GameObject
{
protected:
	struct tagTileObjectInfo
	{
		Vector2 _pos;
		Vector2 _renderPos;

		TILEATTRIBUTE	_attribute;		//�Ӽ�
		int _type;						//Ÿ��

		int				_price;			//����
		Image*			_img;			//�̹���
		Vector2			_frame;			//������

		Vector2			_startIndex;	//���� �ε���
		Vector2			_count;			//x, y�� �����ϴ� ĭ
		DIRECTION		_direction;		//����
	};
	
	tagTileObjectInfo _info;

public:
    TileAttribute() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//FUNCTION
	virtual void Build(Vector2 index);
	virtual void Destroy();

	//GETTER
	tagTileObjectInfo & GetInfo() { return _info; }
	Vector2 GetCount();

	Vector2 GetLeftTopIndex();
	Vector2 GetCenterIndex();
	Vector2 GetRandomIndex();

	virtual vector<Vector2>* GetvUsable() { return nullptr; };		//��� ������ �ε���

	virtual Vector2* GetVoidIndexfromVector() {	return nullptr; }
	virtual void PutIndexToVector(Vector2* index) { };

	bool GetIsInArea(Vector2 index);

private:
    //boost
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        if (Archive::is_saving::value)
        {
            ar& _info._pos;
            ar& _info._renderPos;

            ar& _info._attribute;	
            ar& _info._type;		
            ar& _key;
            ar& _info._price;		
            ar& _info._frame;		
            ar& _info._startIndex;
            ar& _info._count;		
            ar& _info._direction;	
        }

        if (Archive::is_loading::value)
        {
            ar& _info._pos;
            ar& _info._renderPos;

            ar& _info._attribute;
            ar& _info._type;
            ar& _key;
            ar& _info._price;
            ar& _info._frame;
            ar& _info._startIndex;
            ar& _info._count;
            ar& _info._direction;

            if (_info._attribute == TILEATTRIBUTE::OBJECT)
            {
                _info._img = ImageManager::GetInstance()->FindImage(_key);
            }
            else if (_info._attribute == TILEATTRIBUTE::WALL)
            {
                _info._img = ImageManager::GetInstance()->FindImage(_key);
            }
        }
    }
};
