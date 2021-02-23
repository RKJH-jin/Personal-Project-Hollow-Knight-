#pragma once

class TileAttribute;

class Tile
{
public:
    struct tagCost
    {
        int totalCost;              //�� ���
        int costFromStart;          //����������κ����� ���
        int costToGoal;             //������������ ���
        tagCost()
        {
            totalCost = 0;
            costFromStart = 0;
            costToGoal = 0;
        }
    };
public:
	Vector2 _index;				//�ε���
	RECT _rc;					//��Ʈ

	TileAttribute* _terrain;		//����
	
	TileAttribute* _wall;			//��

	TileAttribute* _tileObj;		//Ÿ�� ������Ʈ
	
	TileAttribute* _area;			//����

    //��ã�⿡�� ���� ������
    SEARCHDIRECTION _sDir;        //Ž���ϴ� ����
    Tile* _parentTile;           //�θ� Ÿ�� 
    tagCost _cost;               //���

public:
    //GETTER
	Vector2 GetIndex() { return _index; }
    
    //SETTER
    void SetIndex(Vector2 index) { _index = index; }

    //��ã�⿡�� ���� �Լ���
    bool GetTileEmpty();
    Tile* GetParentTile() { return _parentTile; }
    tagCost& GetCost() { return _cost; }
    SEARCHDIRECTION& GetDirection() { return _sDir; }

    void SetParentTile(Tile* tile) { _parentTile = tile; }

    void ResetInfo();


    //���콺 �Լ�
	virtual TileAttribute* MouseEnter();
	virtual TileAttribute* MouseStay();
	virtual TileAttribute* MouseExit();

private:
    //boost
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        if (Archive::is_saving::value)
        {
            ar& _index;
            ar& _terrain;
            ar& _wall;
            ar& _tileObj;
            ar& _area;
        }

        if (Archive::is_loading::value)
        {
            ar& _index;
            ar& _terrain;
            ar& _wall;
            ar& _tileObj;
            ar& _area;
        }
    }
};

