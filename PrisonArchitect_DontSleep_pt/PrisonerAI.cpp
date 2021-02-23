#include "stdafx.h"
#include "PrisonerAI.h"
#include "MapToolScene.h"
#include "Character.h"
#include "AssignTarget.h"
#include "AssignRNDGoalOnce.h"
#include "MoveToTarget.h"
#include "TileArea.h"
#include "PrisonerEat.h"
#include "TrayDirty.h"
#include "CreateTray.h"


PrisonerAI::PrisonerAI()
{
    _root = new Selector();
    // ���
    _selWait = new Selector();
    _conHaveGoalRND = new VoidCondition(bind(&PrisonerAI::CheckHaveGoalRND, this));
    _MTT = new MoveToTarget();
    _assRNDTarget = new AssignTarget();
    ///////////////////////////////////////

    // ��ħ
    _conTimeSleep = new StrCondition(bind(&PrisonerAI::CheckTimeSchedule, this, placeholders::_1), "SLEEP");
    _selTimeSleep = new Selector();
    _conHaveJail = new StrCondition(bind(&PrisonerAI::CheckHaveRegion, this, placeholders::_1), "����");
    _selHaveJail = new Selector();
    _conInJail = new StrCondition(bind(&PrisonerAI::CheckIsInRegion, this, placeholders::_1), "����");
    _conHaveGoalToJail = new VoidCondition(bind(&PrisonerAI::CheckHaveGoalToJail, this));
    _assJail = new AssignTarget();

    // �Ļ�
    _conTimeMeal = new StrCondition(bind(&PrisonerAI::CheckTimeSchedule, this, placeholders::_1), "MEAL");
    _selTimeMeal = new Selector();
    _conHaveRestaurant = new StrCondition(bind(&PrisonerAI::CheckHaveRegion, this, placeholders::_1), "�Ĵ�");
    _selHaveRestaurant = new Selector();
    _conInRestaurant = new StrCondition(bind(&PrisonerAI::CheckIsInRegion, this, placeholders::_1), "�Ĵ�");
    _conHaveGoalToRestaurant = new VoidCondition(bind(&PrisonerAI::CheckHaveGoalToRestaurant, this));
    _assRestaurant = new AssignTarget();

    // �Ĵ翡��
    _selInRestaurant = new Selector();
    _conHaveTable = new StrCondition(bind(&PrisonerAI::CheckHaveObject, this, placeholders::_1), "��Ź");

    // - ��Ź�� �ִ°��
    _selHaveTable = new Selector();
    _conHaveEmptyTable = new StrCondition(bind(&PrisonerAI::CheckObjectHaveEmpty, this, placeholders::_1), "��Ź");
    _seqUseTable = new Sequence();
    // - �� ��Ź�� �ִ� ���
    _selHaveEmptyTable = new Selector();
    _conHaveTray = new StrCondition(bind(&PrisonerAI::CheckHaveTool, this, placeholders::_1), "����");

    // - ������ �ִ� ���
    _selHaveTray = new Selector();
    _conHaveGoalToTable = new VoidCondition(bind(&PrisonerAI::CheckHaveGoalToTable, this));
    _assGoalToTable = new AssignTarget();
    _conUseTable = new VoidCondition(bind(&PrisonerAI::CheckUseTable, this));
    _conArriveTable = new VoidCondition(bind(&PrisonerAI::CheckArriveTable, this));
    _prisonerEat = new PrisonerEat();
    _trayDirty = new TrayDirty();
    
    // - ������ ���� ���
    _selNonHaveTray = new Selector();
    _conHaveDBTable = new StrCondition(bind(&PrisonerAI::CheckHaveObject, this, placeholders::_1), "��Ĵ�");

    // - ��Ĵ밡 �ִ� ���
    _selHaveDBTable = new Selector();
    _conHaveEmptyDBTable = new StrCondition(bind(&PrisonerAI::CheckObjectHaveEmpty, this, placeholders::_1), "��Ĵ�");

    // - ��Ĵ뿡 ���ڸ��� �ִ� ���
    _selHaveEmptyDBTable = new Selector();
    _conUseDBTable = new VoidCondition(bind(&PrisonerAI::CheckUseDBTable, this));
    _conHaveGoalToDBTable = new VoidCondition(bind(&PrisonerAI::CheckHaveGoalToDBTable, this));
    _assGoalToDBTable = new AssignTarget();
    _createTray = new CreateTray();
    _conArriveDBTable = new VoidCondition(bind(&PrisonerAI::CheckArriveDBTable, this));
    // ����
    _conTimeWash = new StrCondition(bind(&PrisonerAI::CheckTimeSchedule, this, placeholders::_1), "WASH");
    _selTimeWash = new Selector();
    _conHaveShowerRoom = new StrCondition(bind(&PrisonerAI::CheckHaveRegion, this, placeholders::_1), "������");
    _selHaveShowerRoom = new Selector();
    _conInShowerRoom = new StrCondition(bind(&PrisonerAI::CheckIsInRegion, this, placeholders::_1), "������");
    _conHaveGoalToShowerRoom = new VoidCondition(bind(&PrisonerAI::CheckHaveGoalToShowerRoom, this));
    _assShowerRoom = new AssignTarget();

    // �
    _conTimeGround = new StrCondition(bind(&PrisonerAI::CheckTimeSchedule, this, placeholders::_1), "GROUND");
    
    // �
    _conTimeRest = new StrCondition(bind(&PrisonerAI::CheckTimeSchedule, this, placeholders::_1), "REST");

    // ����
    _conTimeImprison = new StrCondition(bind(&PrisonerAI::CheckTimeSchedule, this, placeholders::_1), "IMPRISON");
    _selTimeImprison = new Selector();

}

PrisonerAI::~PrisonerAI()
{
}

HRESULT PrisonerAI::init(Character* character)
{
    _character = character;

    // ���� �ʱ�ȭ ������ �͵�
    _MTT->init(_character);
    _prisonerEat->init(_character);
    _trayDirty->init(_character);
    _createTray->init(_character);

    // ���
    _selWait->AddChild(_conHaveGoalRND);
    _conHaveGoalRND->AddChild(_assRNDTarget);
    _selWait->AddChild(_MTT);
    //////////


    //============================��ħ============================//
    _root->AddChild(_conTimeSleep);
    _conTimeSleep->AddChild(_selTimeSleep);
    _selTimeSleep->AddChild(_conHaveJail);
    _selTimeSleep->AddChild(_selWait);
    _conHaveJail->AddChild(_selHaveJail);
    _selHaveJail->AddChild(_conInJail);
    _conInJail->AddChild(_selWait);
    _selHaveJail->AddChild(_conHaveGoalToJail);
    _conHaveGoalToJail->AddChild(_assJail);
    _selHaveJail->AddChild(_MTT);
    //============================================================//

    //============================�Ļ�============================//
    _root->AddChild(_conTimeMeal);
    _conTimeMeal->AddChild(_selTimeMeal);
    _selTimeMeal->AddChild(_conHaveRestaurant);
    _selTimeMeal->AddChild(_selWait);
    _conHaveRestaurant->AddChild(_selHaveRestaurant);
    _selHaveRestaurant->AddChild(_conInRestaurant);
    _conInRestaurant->AddChild(_selInRestaurant);
    _selHaveRestaurant->AddChild(_conHaveGoalToRestaurant);
    _conHaveGoalToRestaurant->AddChild(_assRestaurant);
    _selHaveRestaurant->AddChild(_MTT);

    // �Ĵ翡��
    _selInRestaurant->AddChild(_conHaveTable);
    _selInRestaurant->AddChild(_selWait);
    _conHaveTable->AddChild(_selHaveTable);

    // -��Ź�� �ִ�?
    _selHaveTable->AddChild(_conUseTable);
    _conUseTable->AddChild(_seqUseTable);
    _seqUseTable->AddChild(_trayDirty);
    _seqUseTable->AddChild(_prisonerEat);

    _selHaveTable->AddChild(_conHaveEmptyTable);
    _selHaveTable->AddChild(_selWait);
    _conHaveEmptyTable->AddChild(_selHaveEmptyTable);
    _selHaveEmptyTable->AddChild(_conHaveTray);
    _conHaveTray->AddChild(_selNonHaveTray);
    _selHaveEmptyTable->AddChild(_selHaveTray);
    
    // -������ �ִ� ���
    _selHaveTray->AddChild(_conHaveGoalToTable);
    _conHaveGoalToTable->AddChild(_assGoalToTable);
    _selHaveTray->AddChild(_conArriveTable);
    _conArriveTable->AddChild(_MTT);
    
    // -������ ���� ���
    _selNonHaveTray->AddChild(_conHaveDBTable);
    _selNonHaveTray->AddChild(_selWait);
    _conHaveDBTable->AddChild(_selHaveDBTable);

    // -��Ĵ밡 �ִ� ���
    _selHaveDBTable->AddChild(_conUseDBTable);
    _conUseDBTable->AddChild(_createTray);
    _selHaveDBTable->AddChild(_conHaveEmptyDBTable);
    _conHaveEmptyDBTable->AddChild(_selHaveEmptyDBTable);
    _selHaveDBTable->AddChild(_selWait);

    // -��Ĵ뿡 �� �ڸ��� �ִ� ���
    _selHaveEmptyDBTable->AddChild(_conHaveGoalToDBTable);
    _conHaveGoalToDBTable->AddChild(_assGoalToDBTable);
    _selHaveEmptyDBTable->AddChild(_conArriveDBTable);
    _conArriveDBTable->AddChild(_MTT);

    //============================================================//

    //============================����============================//
    _root->AddChild(_conTimeWash);
    _conTimeWash->AddChild(_selTimeWash);
    _selTimeWash->AddChild(_conHaveShowerRoom);
    _selTimeWash->AddChild(_selWait);
    _conHaveShowerRoom->AddChild(_selHaveShowerRoom);
    _selHaveShowerRoom->AddChild(_conInShowerRoom);
    _conInShowerRoom->AddChild(_selWait);
    _selHaveShowerRoom->AddChild(_conHaveGoalToShowerRoom);
    _conHaveGoalToShowerRoom->AddChild(_assShowerRoom);
    _selHaveShowerRoom->AddChild(_MTT);
    //============================================================//
    
    //============================�============================//
    _root->AddChild(_conTimeGround);
    _conTimeGround->AddChild(_selWait);
    //============================================================//

    //============================�޽�============================//
    _root->AddChild(_conTimeRest);
    _conTimeRest->AddChild(_selWait);
    //============================================================//

    //============================��ħ============================//
    _root->AddChild(_conTimeImprison);
    _conTimeImprison->AddChild(_selTimeImprison);
    _selTimeImprison->AddChild(_conHaveJail);
    _selTimeImprison->AddChild(_selWait);
    //============================================================//


    return S_OK;
}

void PrisonerAI::Update()
{
    _root->invoke();   
}

bool PrisonerAI::CheckTimeSchedule(string schedule)
{
    if (DATAMANAGER->GetTimeSchedule() == schedule) return true;
    return false;
}

bool PrisonerAI::CheckHaveRegion(string region)
{
    if (DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->FindTileObject(region))  return true;
    return false;
}

bool PrisonerAI::CheckIsInRegion(string region)
{
    if ((*_character).GetIsInArea(region))  return true;
    return false;
}

bool PrisonerAI::CheckHaveGoalRND()
{
    if (_character->GetInfo().goalState == GOALSTATE::NONE || _character->GetInfo().goalState == GOALSTATE::GOALREACH)
    {
        //���� �ִ� ������ �����;��Ѵ�.
        Vector2 temp = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetCount(); // Ÿ�� ��ü ����
        Vector2 chaIndex = _character->GetTransform()->GetIndex();  // �� ��ġ �ε���
        Vector2 RNDtemp; //�����ε��� ���� ����
        TileAttribute* tempTile = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetvTile()[chaIndex.y * temp.x + chaIndex.x]->_area;
        if (tempTile != nullptr && (DATAMANAGER->GetTimeSchedule() != "GROUND" && DATAMANAGER->GetTimeSchedule() != "REST")) // ���� ���� ��� ������ ������
        {
            RNDtemp = tempTile->GetRandomIndex();
        }
        else
        {
            RNDtemp = Vector2(RND->getInt(temp.x), RND->getInt(temp.y));
            while (true)
            {
                if (DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetvTile()[RNDtemp.y * temp.x + RNDtemp.x]->GetTileEmpty()) break;
                RNDtemp = Vector2(RND->getInt(temp.x), RND->getInt(temp.y));
            }
        }
        _assRNDTarget->init(_character, RNDtemp);
        _character->GetInfo().goalState = GOALSTATE::GOALSET;
        return true;
    }
    return false;
}

bool PrisonerAI::CheckHaveObject(string objectName)
{
    Vector2 temp = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetCount(); // Ÿ�� ��ü ����
    Vector2 chaIndex = _character->GetTransform()->GetIndex();  // �� ��ġ �ε���
    TileAttribute* tempArea = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetvTile()[chaIndex.y * temp.x + chaIndex.x]->_area; // �� ��ġ
    if (tempArea == nullptr) return false;
    if (dynamic_cast<TileArea*>(tempArea)->CheckHaveObject(objectName)) return true;
    return false;
}

bool PrisonerAI::CheckObjectHaveEmpty(string objectName)
{
    Vector2 temp = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetCount(); // Ÿ�� ��ü ����
    Vector2 chaIndex = _character->GetTransform()->GetIndex();  // �� ��ġ �ε���
    TileAttribute* tempArea = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetvTile()[chaIndex.y * temp.x + chaIndex.x]->_area; // �� ��ġ
    vector<TileObject*> tempVObj = dynamic_cast<TileArea*>(tempArea)->GetHaveObject(objectName);
    if (!tempVObj.empty())
    {
        for (int i = 0; i < tempVObj.size(); ++i)
        {
            if (tempVObj[i]->CheckVoidIndex())  return true;
        }
    }

    return false;
}

bool PrisonerAI::CheckHaveTool(string toolName)
{
    if (_character->GetInfo().toolObject == nullptr)  return true;
    if (_character->GetInfo().toolObject->GetKey() == toolName)
    {
        return false;
    }
    return true;
}

bool PrisonerAI::CheckHaveGoalToJail()
{
    if (_character->GetInfo().goalState == GOALSTATE::NONE || _character->GetInfo().goalState == GOALSTATE::GOALREACH)
    {
        _assJail->init(_character, DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->FindTileObject("����")->GetCenterIndex());
        _character->GetInfo().goalState = GOALSTATE::GOALSET;
        
        return true;
    }
    return false;
}

bool PrisonerAI::CheckHaveGoalToRestaurant()
{
    if (_character->GetInfo().goalState == GOALSTATE::NONE || _character->GetInfo().goalState == GOALSTATE::GOALREACH)
    {
        _assRestaurant->init(_character, DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->FindTileObject("�Ĵ�")->GetCenterIndex());
        _character->GetInfo().goalState = GOALSTATE::GOALSET;
        return true;
    }
    return false;
}

bool PrisonerAI::CheckHaveGoalToShowerRoom()
{
    if (_character->GetInfo().goalState == GOALSTATE::NONE || _character->GetInfo().goalState == GOALSTATE::GOALREACH)
    {
        _assShowerRoom->init(_character, DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->FindTileObject("������")->GetCenterIndex());
        _character->GetInfo().goalState = GOALSTATE::GOALSET;
        return true;
    }
    return false;
}


bool PrisonerAI::CheckHaveGoalToDBTable()
{
    Vector2 temp = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetCount(); // Ÿ�� ��ü ����
    Vector2 chaIndex = _character->GetTransform()->GetIndex();  // �� ��ġ �ε���
    TileAttribute* tempArea = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetvTile()[chaIndex.y * temp.x + chaIndex.x]->_area; // �� ��ġ
    vector<TileObject*> tempVObj = dynamic_cast<TileArea*>(tempArea)->GetHaveObject("��Ĵ�");

    vector<Tile*> tempV = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetvTile();
    TileAttribute* tempTA = tempV[chaIndex.y * temp.x + chaIndex.x]->_tileObj;
    if (tempTA != nullptr && tempTA->GetKey() == "��Ĵ�")
    {
        _character->GetInfo().btState = BTSTATE::SERVING;
        return false;
    }

    if (!tempVObj.empty() && _character->GetInfo().goalState != GOALSTATE::GOALSET)
    {
        for (int i = 0; i < tempVObj.size(); ++i)
        {
            if (tempVObj[i]->CheckVoidIndex())
            {
                _assGoalToDBTable->init(_character, *tempVObj[i]->GetVoidIndexfromVector());
                _character->GetInfo().goalState = GOALSTATE::GOALSET;
                return true;
            }
        }
    }
    return false;
}

bool PrisonerAI::CheckHaveGoalToTable()
{
    Vector2 temp = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetCount(); // Ÿ�� ��ü ����
    Vector2 chaIndex = _character->GetTransform()->GetIndex();  // �� ��ġ �ε���
    TileAttribute* tempArea = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetvTile()[chaIndex.y * temp.x + chaIndex.x]->_area; // �� ��ġ
    vector<TileObject*> tempVObj = dynamic_cast<TileArea*>(tempArea)->GetHaveObject("��Ź");

    vector<Tile*> tempV = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetvTile();
    TileAttribute* tempTA = tempV[chaIndex.y * temp.x + chaIndex.x]->_tileObj;
    if (tempTA != nullptr && tempTA->GetKey() == "��Ź")
    {
        _character->GetInfo().btState = BTSTATE::EAT;
        return false;
    }

    if (!tempVObj.empty() && _character->GetInfo().goalState != GOALSTATE::GOALSET)
    {
        for (int i = 0; i < tempVObj.size(); ++i)
        {
            if (tempVObj[i]->CheckVoidIndex())
            {
                _assGoalToTable->init(_character, *tempVObj[i]->GetVoidIndexfromVector());
                _character->GetInfo().goalState = GOALSTATE::GOALSET;
                return true;
            }
        }
    }
    return false;
}

bool PrisonerAI::CheckUseTable()
{
    if (_character->GetInfo().btState == BTSTATE::EAT)
    {
        return true;
    }
    return false;
}

bool PrisonerAI::CheckUseDBTable()
{
    if (_character->GetInfo().btState == BTSTATE::SERVING)
    {
        return true;
    }
    return false;
}


bool PrisonerAI::CheckArriveDBTable()
{
    Vector2 temp = _character->GetTransform()->GetIndex();
    Vector2 tempC = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetCount(); // Ÿ�� ��ü ����
    vector<Tile*> tempV = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetvTile();
    TileAttribute* tempTA = tempV[temp.y * tempC.x + temp.x]->_tileObj;
    if (tempTA != nullptr && tempTA->GetKey() == "��Ĵ�")
    {
        _character->GetInfo().btState = BTSTATE::SERVING;
        return false;
    }
    return true;
}

bool PrisonerAI::CheckArriveTable()
{
    Vector2 temp = _character->GetTransform()->GetIndex();
    Vector2 tempC = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetCount(); // Ÿ�� ��ü ����
    vector<Tile*> tempV = DATAMANAGER->GetMapToolScene()->GetMapM()->GetTileMap()->GetvTile();
    TileAttribute* tempTA = tempV[temp.y * tempC.x + temp.x]->_tileObj;
    if (tempTA != nullptr && tempTA->GetKey() == "��Ź")
    {
        _character->GetInfo().btState = BTSTATE::EAT;
        return false;
    }
    return true;
}


