#pragma once
#include <vector>

class animation
{
private:
    typedef vector<POINT>   vFrameList;     //������ ����Ʈ ���� ����
    typedef vector<int>     vPlayList;    //�÷��� ����Ʈ ���� ����

private:
    int _frameNum;

    vFrameList _vFrameList;
    vPlayList _vPlayList;

    int _frameWidth;
    int _frameHeight;

    BOOL _loop;

    float _frameUpdateSec;
    float _elapsedSec;

    DWORD _nowPlayIndex;
    BOOL _play;


public:
    animation();
    ~animation();

    virtual HRESULT init(int totalW, int totalH, int frameW, int frameH);
    virtual void release();
    
    //�ִϸ��̼� ��� ����Ʈ �Լ�
    void setDefaultPlayFrame(BOOL reverse = FALSE, BOOL loop = FALSE);
    //���ϴ� �κи� �ִϸ��̼� ��� �Լ�
    void setPlayFrame(int* playArr, int arrLen, BOOL loop = FALSE);
    //���� �����Ӻ��� �������ӱ��� ������ �ִϸ��̼� ���
    void setPlayFrame(int start, int end, BOOL reverse = FALSE, BOOL loop = FALSE);
    //������ ����
    void setFPS(int framePerSec);
    //������ ��� �ӵ� ����
    void frameUpdate(float elapsedTime);

    void start();   //�ִϸ��̼� ���
    void stop();    //�ִϸ��̼� ��ž
    void pause();   //�ִϸ��̼� �Ͻ�����
    void resume();  //�ִϸ��̼� �ٽ����

    inline BOOL isPlay() { return _play; }
    inline POINT getFramePos() { return _vFrameList[_vPlayList[_nowPlayIndex]]; }
    inline int getFrameWidth() { return _frameWidth; }
    inline int getFrameHeight() { return _frameHeight; }
    inline int getNowPlayIndex() { return _nowPlayIndex; }
    inline void setNowPlayIndex(int idx) { _nowPlayIndex = idx; }
    inline BOOL getIsEnd() {
        if (_nowPlayIndex == _frameNum - 1) return true;
        else return false;
    }
    inline vPlayList getPlayList() { return _vPlayList; }
    inline int getFrameNum() { return _frameNum; }
    inline float getElapsedSec() { return _elapsedSec; }
    inline float getFrameUpdateSec() { return _frameUpdateSec; }
};

