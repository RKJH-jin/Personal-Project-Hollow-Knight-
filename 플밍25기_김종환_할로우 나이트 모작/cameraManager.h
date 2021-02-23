#pragma once
#include "singletonBase.h"
#include "camera.h"
#include <map>

class cameraManager : public singletonBase<cameraManager>
{
private:
    typedef map<string, camera*>				mapCameraList;              // ī�޶� ������ Map
    typedef map<string, camera*>::iterator	    mapCameraIter;              

private:
    mapCameraList _mCameraList;                                             // ī�޶� ������ Map
    camera* _mainCamera;                                                    // ����ī�޶�
    string mc = "mainCamera";                                               // ����ī�޶� String ��
    int maxScreenWidth, maxScreenHeight;                                    // �� �ִ� ���� ����, ���� ����

public:
    cameraManager();
    ~cameraManager();

    HRESULT init();
    void release();

    BOOL deleteCamera(string strKey);
    BOOL deleteAll();

    void setMaxScreen(int width, int height) { maxScreenWidth = width, maxScreenHeight = height; }

    //-----------���� ī�޶�(Main Camera == MC) �Լ�-----------//
    void mainCameraUpdate(float x, float y);
    camera* getMainCamera() { return _mainCamera; }
    
    
    void cameraUpdate(string strKey, float x, float y);

    camera* findCamera(string strkey);
    camera* addCamera(string strKey, float x, float y, int width, int height, int mag);

    // �̱��� �Լ�(���� ������Ʈ ����)
    void shakeMainCamera();
    void shakeCamera(string strKey);
};

