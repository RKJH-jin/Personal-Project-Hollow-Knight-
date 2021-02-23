#pragma once
class camera
{
public:
    //===================================���� ����===================================//
    typedef struct tagCameraInfo
    {
        float centerX, centerY;                 // ī�޶��� �߽���ǥ X, Y ��
        float cameraWidth, cameraHeight;        // ī�޶��� ���� ����, ���� ���� ��
        POINT cameraLT, cameraRB;               // ī�޶��� �»��(LEFT, TOP)�� ���ϴ�(RIGHT, BOTTOM) ��ǥ ��

        float Magnification;                    // ī�޶� ���� (���� ������Ʈ ����)

        tagCameraInfo()                         // �ʱⰪ ����
        {
            centerX = 0;
            centerY = 0;
            cameraWidth = 0;
            cameraHeight = 0;
            cameraLT.x = 0;
            cameraLT.y = 0;
            cameraRB.x = 0;
            cameraRB.y = 0;
            Magnification = 1;
        }
    }CAMERA_INFO, *LPCAMERA_INFO;

private:
    LPCAMERA_INFO _cameraInfo;                  // ī�޶� ������ ����


public:
    camera();
    ~camera();

    HRESULT init(float x, float y, int width, int height, int mag);               // ī�޶� �ʱⰪ
    void release();

    void updateVertax();                                                          // ����ī�޶� �»��/���ϴ� ��ǥ ������Ʈ
    
    inline void setX(float x) { _cameraInfo->centerX = x; }                       // ����ī�޶� �߽� X��ǥ ����
    inline float getX() { return _cameraInfo->centerX; }                          // ����ī�޶� �߽� X��ǥ ȹ��

    inline void setY(float y) { _cameraInfo->centerY = y; }                       // ����ī�޶� �߽� X��ǥ ����
    inline float getY() { return _cameraInfo->centerY; }                          // ����ī�޶� �߽� X��ǥ ȹ��

    inline float setWidth(int width) { _cameraInfo->cameraWidth = width; }        // ����ī�޶� ���� ���� ����
    inline float getWidth() { return _cameraInfo->cameraWidth; }                  // ����ī�޶� ���� ���� ȹ��
    inline float setHeight(int height) { _cameraInfo->cameraHeight = height; }    // ����ī�޶� ���� ���� ����
    inline float getHeight() { return _cameraInfo->cameraHeight; }                // ����ī�޶� ���� ���� ȹ��

    inline float getLTX() { return _cameraInfo->cameraLT.x; }                     // ����ī�޶� LEFT�� ȹ��
    inline float getLTY() { return _cameraInfo->cameraLT.y; }                     // ����ī�޶� TOP�� ȹ��
    inline float getRBX() { return _cameraInfo->cameraRB.x; }                     // ����ī�޶� RIGHT�� ȹ��
    inline float getRBY() { return _cameraInfo->cameraRB.y; }                     // ����ī�޶� BOTTOM�� ȹ��
    
};

