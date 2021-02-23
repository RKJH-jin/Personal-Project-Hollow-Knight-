#pragma once
#include "TileAttribute.h"
class TileObject : public TileAttribute
{
private:
	TILEOBJECT		_type;		//������Ʈ Ÿ��

	int				_frame[4];		//������ �ε���
	vector<Vector2> _vUsable;		//��� ������ �ε���

public:
    TileObject() {};
	TileObject(TILEOBJECT type);

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//FUNCTION
	virtual void Build(Vector2 index);
	virtual void Destroy();

	//GETTER
	TILEOBJECT GetType() { return _type; }

	virtual vector<Vector2>* GetvUsable() { return &_vUsable; };	//��� ������ �ε���

    virtual bool CheckVoidIndex();
	virtual Vector2* GetVoidIndexfromVector();
	virtual void PutIndexToVector(Vector2* index);

private:
    //boost
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& boost::serialization::base_object<TileAttribute>(*this);
        if (Archive::is_saving::value)
        {
            ar& _type;
            ar& _frame;
            ar& _vUsable;
        }

        if (Archive::is_loading::value)
        {
            ar& _type;
            ar& _frame;
            ar& _vUsable;
        }
    }
};

