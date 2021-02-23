#pragma once

class TileAttribute;
class Character;
class MapToolScene;

class DataManager
{
public:
	static DataManager* GetInstance()
	{
		static DataManager istance;
		return &istance;
	}

private:
    struct tagTime
    {
        int day;
        int hour;
        int minute;
        int second;
        float milliSeconds;

        tagTime()
        {
            day = 0;
            hour = 19;
            minute = 0;
            second = 0;
            milliSeconds = 0;
        }
    };

	struct tagDataInfo
	{
		int         money;
		float       gameSpeed = 1.0f;			//���� ���� (�ӽ÷� 1�� �ʱ�ȭ�ص�)
        tagTime     time;
        float       skyAlpha;                //�ϴ� ���İ�
        TIMESCHEDULE schedule;
		
		float		soundVolume;			//�Ҹ� ũ��
		float		sfxVolume;			//ȿ���� ũ��
		float		bgmVolume;				//����� ũ��

    private:
        //boost
        friend class boost::serialization::access;

        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            if (Archive::is_saving::value)
            {
                ar& gameSpeed;
                ar& money;
                ar& skyAlpha;
                ar& time.day;
                ar& time.hour;
                ar& time.minute;
                ar& time.second;
                ar& time.milliSeconds;
            }

            if (Archive::is_loading::value)
            {
                ar& gameSpeed;
                ar& money;
                ar& skyAlpha;
                ar& time.day;
                ar& time.hour;
                ar& time.minute;
                ar& time.second;
                ar& time.milliSeconds;
            }
        }
	};

	typedef map<string, TileAttribute*> mTileAttribute;
	typedef map<string, TileAttribute*>::iterator miTileAttribute;

	typedef map<string, Character*> mCharacter;
	typedef map<string, Character*>::iterator miCharacter;

	tagDataInfo _info;
	Image* _terrainImg;				//���� �̹���

	mTileAttribute _mTileObject;		//Ÿ�� ������Ʈ�� ���� ��
	mCharacter _mCharacter;				//ĳ���� ������Ʈ�� ���� ��

	MapToolScene* _mapToolScene;		//������

public:
	vector<string> _vStr_buf;		//���� ���ڸ� ���� ���� �׽�Ʈ

	void init();					//�ʱ�ȭ
    void update();                  //���� ������ ������Ʈ

	//GETTER
	mTileAttribute* GetMTileObject() { return &_mTileObject; }
	TileAttribute* FindTileObject(string key);
	TileAttribute* CreateTileObject(string key);

    string GetTimeSchedule();
	Character* FindCharacter(string key);
	Character* CreateCharacter(string key);
	mCharacter* GetMCharacter() { return &_mCharacter; }

	MapToolScene* GetMapToolScene() { return _mapToolScene; }

	//��Ŀ
	void SetLinkMapToolScene(MapToolScene* mapToolScene) { _mapToolScene = mapToolScene; };

	tagDataInfo& GetInfo() { return _info; }

	Image* GetTerrainImage() { return _terrainImg; }

	//SETTER

	//FUNCTION
	void UpdateTime();
    void Save();
    void Load();


};

