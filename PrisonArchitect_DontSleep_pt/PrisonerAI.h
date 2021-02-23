#pragma once

#include "AllComponents.h"

class PrisonerEat;
class TrayDirty;
class CreateTray;


class PrisonerAI : public AI
{
private:
    Selector* _root;
    //==========��ħ==========//
    StrCondition* _conTimeSleep;
    Selector* _selTimeSleep;
    StrCondition* _conHaveJail;

    StrCondition* _conInJail;
    Selector* _selHaveJail;
    AssignTarget* _assJail;
    VoidCondition* _conHaveGoalToJail;

    //==========�Ļ�==========//
    StrCondition* _conTimeMeal;
    Selector* _selTimeMeal;
    StrCondition* _conHaveRestaurant;
    Selector* _selHaveRestaurant;
    StrCondition* _conInRestaurant;
    VoidCondition* _conHaveGoalToRestaurant;
    AssignTarget* _assRestaurant;

    //==========�Ĵ翡��==========//
    Selector* _selInRestaurant;
    StrCondition* _conHaveTable;
    
    Selector* _selHaveTable;
    VoidCondition* _conUseTable;
    Sequence* _seqUseTable;
    TrayDirty* _trayDirty;
    PrisonerEat* _prisonerEat;

    StrCondition* _conHaveEmptyTable;
    Selector* _selHaveEmptyTable;
    StrCondition* _conHaveTray;
    
    Selector* _selHaveTray;
    VoidCondition* _conHaveGoalToTable;
    AssignTarget* _assGoalToTable;
    
    VoidCondition* _conArriveTable;
    

    Selector* _selNonHaveTray;
    StrCondition* _conHaveDBTable;

    Selector* _selHaveDBTable;
    VoidCondition* _conUseDBTable;
    StrCondition* _conHaveEmptyDBTable;
    Selector* _selHaveEmptyDBTable;
    VoidCondition* _conHaveGoalToDBTable;
    AssignTarget* _assGoalToDBTable;
    CreateTray* _createTray;
    VoidCondition* _conArriveDBTable;
    float eatTimer;
    //==========����==========//
    StrCondition* _conTimeWash;
    Selector* _selTimeWash;
    StrCondition* _conHaveShowerRoom;
    Selector* _selHaveShowerRoom;
    StrCondition* _conInShowerRoom;
    VoidCondition* _conHaveGoalToShowerRoom;
    AssignTarget* _assShowerRoom;

    //==========����==========//
    StrCondition* _conTimeImprison;
    Selector* _selTimeImprison;
    // �������� ��ħ�̶� ����

    //==========�==========//
    StrCondition* _conTimeGround;

    //==========�޽�==========//
    StrCondition* _conTimeRest;

    

    //==========���==========//
    Selector* _selWait;
    VoidCondition* _conHaveGoalRND;
    AssignTarget* _assRNDTarget;
    MoveToTarget* _MTT;
public:
	PrisonerAI();
	~PrisonerAI();

    HRESULT init(Character* character);
    void Update();

    // ���� ��� �Լ�
    bool CheckTimeSchedule(string schedule);        // �ð�ǥ Ȯ��
    bool CheckHaveRegion(string region);            // �ʿ� ������ �ִ��� Ȯ��
    bool CheckIsInRegion(string region);            // ĳ���Ͱ� ������ �ִ��� Ȯ��
    bool CheckHaveGoalRND();                        // ĳ���Ͱ� ������ ��ǥ�� �ִ��� Ȯ��
    bool CheckHaveObject(string objectName);        // ������ ������Ʈ�� �ִ��� Ž��
    bool CheckObjectHaveEmpty(string objectName);   // ������ �ִ� ������Ʈ�� ���ڸ��� �ִ��� Ž��
    bool CheckHaveTool(string toolName);            // �տ� �ش� ������ �ִ��� �Ǵ�

    bool CheckHaveGoalToJail();                     // �ش� �������� ���� ��������
    bool CheckHaveGoalToRestaurant();               // �ش� �������� ���� ��������
    bool CheckHaveGoalToShowerRoom();
    // �Ĵ翡��
    bool CheckHaveGoalToDBTable();                  // �� ��Ĵ븦 ��ǥ��
    bool CheckHaveGoalToTable();                    // �� ��Ź�� ��ǥ��
    bool CheckUseTable();                           // ��Ź ��������� üũ
    bool CheckUseDBTable();                         // ��Ĵ� ��������� üũ
    bool CheckArriveDBTable();
    bool CheckArriveTable();
};

