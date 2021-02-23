#pragma once

#include "Tile.h"
#include "TileObject.h"

class TileMap
{
public:
	static TileMap* GetInstance()
	{
		static TileMap istance;
		return &istance;
	}

protected:
	vector<Tile*> _vTile;				//Ÿ�� ����

	Vector2 _count;						//Ÿ�� x, y ����
	int _tileCount;						//��ü Ÿ�� ����

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	Vector2 GetCount() { return _count; }

	//Ÿ�ϸ��� ������
	void SetTileMap(Vector2 count);

	//Ÿ�� ������Ʈ�� ����
	void BuildTileObject(Vector2 index, TileAttribute* tileObj);

	//Ÿ�� ������Ʈ �ı�
	void DestroyTileObject(TileAttribute* tileObj);

	//���� ����Ÿ�� �������� ���� ��
	Vector2 GetWallFrame(Vector2 index, TileAttribute* tileObj);
	
	//Ÿ�Ͽ� ���� �� �ִ��� Ȯ�� �� ��
	bool CanBuildTile(Vector2 index, TileAttribute* tileObj);

	//Ÿ�� ������Ʈ�� ã�� ��
	TileAttribute* FindTileObject(string key);

	//GETTER
	vector<Tile*> GetvTile() { return _vTile; }

private:
    //boost
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        if (Archive::is_saving::value)
        {
            ar& _vTile;
            ar& _tileCount;
            ar& _count;
        }

        if (Archive::is_loading::value)
        {
            ar& _vTile;
            ar& _tileCount;
            ar& _count;
        }
    }
};

