#pragma once
#define TILESIZE 64
#define TILECOUNTX 60
#define TILECOUNTY 50

//����
enum class TILEAREA
{
	JAIL,			//����
	KITCHEN,		//�ξ�
	FOODCOURT,		//�Ĵ�
	SHOWERROOM,		//������
	STORAGE,		//â��
	DUMP,			//��������
	FIELD,			//���
	MEDICAL,		//�ǹ���
	LOUNGE,			//�ްԽ�
	OFFICE,
	STUDYROOM,
	WARDENROOM,
	END,			//����
};

//���콺 ����
enum class MOUSESTATE
{
	BUILD,
	DESTROY,	//�ı�
	DELETECHAR,	//ĳ���� ����
	SELECT,

};

//�����
enum class GOALSTATE
{
	NONE,
	GOALSET,
	GOALRUNNING,
	GOALREACH,
};

//�ൿ����
enum class BTSTATE
{
	NONE,
	COOKING,
    SERVING,
    EAT,
	END
};
//���콺 �巡��
enum class MOUSEDRAG
{
	POINT,		//��
	LINE,		//��
	RECT,		//��Ʈ
	END,		//����
};

//������Ʈ Ÿ��
enum class TILEATTRIBUTE
{
	TERRAIN,	//����
	WALL,		//��
	OBJECT,		//����
	AREA,		//����
	END,		//����
};

//�� Ÿ��
enum class STUFFTTYPE
{
	COOKBACON,
	FOODBACON,
	BACONS,
	BOX,			//����
	GRAYBRICKS,		//ȸ����
	REDBRICKS,		//������
	CABBAGES,
	REBARS,
	SOUPGREENS,
	SOUPS,
	TRAYS,
	TRAYDIRTYS,
	WOODCUTS,
	CAR,
	TRASH,			//������
	POTATOS,
	END,

};

//����Ÿ��
enum class TOOLTYPE
{
	NONE,           //�� ��
	BACON,			//������
	BOX,			//����
	GRAYBRICK,		//ȸ����
	REDBRICK,		//������
	CABBAGE,
	DOCUMENT,
	DRIVER,
	MOP,
	POTATO,
	REBAR,
	SOUP,
	SOUPGREEN,
	SPATULA,
	SYRIGNE,
	TRAY,
	TRAYDIRTY,
	WOODCUT,
	TRASH,			//������
	END,

};

enum class DIRECTION
{
	FRONT,		//��
	LEFT,		//��
	BACK,		//��
	RIGHT,		//��
};

enum class ANCHORPIVOT
{
	LeftTop,
	LeftCenter,
	LeftBottom,
	CenterTop,
	Center,
	CenterBottom,
	RightTop,
	RightCenter,
	RightBottom,
};
enum class TILETERRAIN
{
	GRASS1,
	GRASS2,
	GRASS3,
	GROUND,
	CONCRETE1,
	CONCRETE2,
	CONCRETE3,
	FLOOR,
	ROAD,
	ASPHALT,
	MUD,
	BRICK,
	ROCK,
	MOON,
	FLOOR2,
	FLOWER,
	CRACK,
	TILE,
	CARPET,
	MONO,
	END,
};

enum class TILEWALL
{
	WALL0,	 WALL1, WALL2,	WALL3,	WALL4,
	WALL5,	WALL6,	WALL7,	WALL8,	WALL9,
	WALL10, WALL11, WALL12, WALL13, WALL14,
	WALL15, WALL16, WALL17, WALL18, WALL19,
	WALL20, WALL21, WALL22, WALL23, WALL24,
	WALL25, WALL26, WALL27, WALL28, WALL29,
	END,
};

enum class TILEOBJECT
{
	����������,
	��Ĵ�,
	��ġ,
	����,
	�繫��å��,
	������,
	����������,
	����,
	��Ź,
	��ũ��,
	����,
	����öâ��,
	���Ǳ�,
	������,
	öâ��,
	ħ��,
	END,
};

//���� ����
enum class STAFFROLE
{
	ACCOUNTANT,
	CLEANER,
	COOKER,
	DOCTER,
	WORKER,
	WARDER,
	TEACHER,
	WARDEN,
	END,
};

//ĳ��������
enum class CHARACTERTYPE
{
	PEOPLE,
	PRISONER,
	STAFF,
	END
};

//�������
enum class PEOPLEROLE
{
	BITALIA,
	BOSS,
	NICO,
	END,
};

// test��
enum class LOCATION : int
{
    STORAGE,
    NON_STORAGE,
};

enum class SITUATION : int
{
    ORDINARY,
    RIOT,

};

enum class SEARCHDIRECTION : int
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
    UPPERLEFT,
    UPPERRIGHT,
    LOWERLEFT,
    LOWERRIGHT,
};

//�ð�ǥ
enum class TIMESCHEDULE : int
{
	SLEEP,		//��ħ
	MEAL,		//�Ļ�
	WASH,		//����
	GROUND,		//�
	REST,		//�޽�
	IMPRISON,	//����
};