#pragma once
#include "TileMap.h"

class MapManager
{
private:
	typedef vector<Character*> vCharacter;
	typedef vector<StuffObject*> vStuffObj;

private:
	TileMap* _tileMap;			//Ÿ�� ��

	vCharacter _vCharacter;		//ĳ���� ����
	vStuffObj _vStuffObj;		//������ ����

	//Y-Order ����
	vector<GameObject*> _vYOrderObject;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	/*====================================================
							GETTER
	====================================================*/
	TileMap* GetTileMap() { return _tileMap; }
	vCharacter& GetVCharacter() { return _vCharacter; }
	vStuffObj& GetVStuffObj() { return _vStuffObj; }

	/*====================================================
							������
	====================================================*/
	//������ ������Ʈ�� ã�� ��
	StuffObject* FindStuffObject(string key);

	/*====================================================
							ĳ����
	====================================================*/
	//ĳ���͸� ���� ��
	void CreateCharacter(Vector2 pos, Character* obj);
	
	//ĳ���͸� ���� ��
	void DeleteCharacter(int i);

	/*====================================================
							Y-Order
	====================================================*/
	void SortYOrder(int s, int e);
	void RenderYOrder();

private:
    //boost
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        if (Archive::is_saving::value)
        {
            ar& _tileMap;
        }

        if (Archive::is_loading::value)
        {
            ar& _tileMap;
        }
    }
};

