#include "stdafx.h"
#include "animation.h"

animation::animation()
    : _frameNum(0), _frameWidth(0), _frameHeight(0),
    _loop(FALSE),
    _frameUpdateSec(0), _elapsedSec(0), _nowPlayIndex(0),
    _play(FALSE)
{
}

animation::~animation()
{
}

HRESULT animation::init(int totalW, int totalH, int frameW, int frameH)
{
    _frameWidth = frameW;
    int _frameNumWidth = totalW / _frameWidth;

    _frameHeight = frameH;
    int _frameNumHeight = totalH / _frameHeight;

    _frameNum = _frameNumWidth * _frameNumHeight;

    for (int i = 0; i < _frameNumHeight; ++i)
    {
        for (int j = 0; j < _frameNumWidth; ++j)
        {
            POINT framePos;
            framePos.x = j * _frameWidth;
            framePos.y = i * _frameHeight;

            _vFrameList.push_back(framePos);
        }
    }

    //일단은 디폴트 애니메이션으로 셋팅
    setDefaultPlayFrame();

    return S_OK;
}

void animation::release()
{
}

void animation::setDefaultPlayFrame(BOOL reverse, BOOL loop)
{
    _loop = loop;
    _vPlayList.clear();

    if (reverse)
    {
        if (_loop)
        {
            for (int i = _frameNum - 1; i > -1; --i)/// 확인 필요
            {
                _vPlayList.push_back(i);
            }
        }
        else
        {
            for (int i = _frameNum - 1; i > -1; --i)/// 확인 필요
            {
                _vPlayList.push_back(i);
            }
        }
    }
    else
    {
        if (_loop)
        {
            for (int i = 0; i < _frameNum; ++i)
            {
                _vPlayList.push_back(i);
            }
        }
        else
        {
            for (int i = 0; i < _frameNum; ++i)
            {
                _vPlayList.push_back(i);
            }
        }
    }

}

void animation::setPlayFrame(int* playArr, int arrLen, BOOL loop)
{
    _loop = loop;

    _vPlayList.clear();

    for (int i = 0; i < arrLen; ++i)
    {
        _vPlayList.push_back(playArr[i]);
    }
}

void animation::setPlayFrame(int start, int end, BOOL reverse, BOOL loop)
{
    _loop = loop;

    _vPlayList.clear();

    if (start == end)
    {
        _vPlayList.clear();
        stop();
        return;
    }

    if (start > end)
    {
        if (reverse)
        {
            if (_loop)
            {
                for (int i = start; i >= end; --i)
                {
                    _vPlayList.push_back(i);
                }
            }
            else
            {
                for (int i = start; i >= end; --i)
                {
                    _vPlayList.push_back(i);
                }
            }
        }
        else
        {
            if (_loop)
            {
                for (int i = start; i >= end; --i)
                {
                    _vPlayList.push_back(i);
                }
            }
            else
            {
                for (int i = start; i >= end; --i)
                {
                    _vPlayList.push_back(i);
                }
            }
        }
    }
    else
    {
        if (reverse)
        {
            if (_loop)
            {
                for (int i = start; i < end; ++i)
                {
                    _vPlayList.push_back(i);
                }

                for (int i = end - 1; i > start; --i)
                {
                    _vPlayList.push_back(i);
                }
            }
            else
            {
                for (int i = end - 1; i >= start; --i)
                {
                    _vPlayList.push_back(i);
                }
            }
        }
        else
        {
            if (_loop)
            {
                for (int i = start; i <= end; ++i)
                {
                    _vPlayList.push_back(i);
                }
            }
            else
            {
                for (int i = start; i <= end; ++i)
                {
                    _vPlayList.push_back(i);
                }
            }
        }
    }
}

void animation::setFPS(int framePerSec)
{
    _frameUpdateSec = 1.0f / framePerSec;
}

void animation::frameUpdate(float elapsedTime)
{
    if (_play)
    {
        _elapsedSec += elapsedTime;
        
        if (_elapsedSec >= _frameUpdateSec)
        {
            _elapsedSec -= _frameUpdateSec;
            _nowPlayIndex++;
            
            if (_nowPlayIndex == _vPlayList.size())
            {
                
                if (_loop) _nowPlayIndex = 0;
                else
                {
                    _nowPlayIndex--;
                    _play = FALSE;
                }
            }
        }
    }
}

void animation::start()
{
    _play = TRUE;
    _nowPlayIndex = 0;
}

void animation::stop()
{
    _play = FALSE;
    _nowPlayIndex = 0;
}

void animation::pause()
{
    _play = FALSE;
}

void animation::resume()
{
    _play = TRUE;
}
