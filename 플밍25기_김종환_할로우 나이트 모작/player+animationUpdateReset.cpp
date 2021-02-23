#include "stdafx.h"
#include "player.h"
#include "mapManager.h"
#include "projectile.h"

void player::animationUpdateReset()
{
      //======================�ִϸ��̼� ������ ������Ʈ======================
    if (_player.atkType != NON_ATTACK) // ���� ��� ������ ������Ʈ
    {
        if (_player.atkType == NORMAL_ATTACK)
        {
            _player.curPlayAtkAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 20);
        }
        else if (_player.atkType == DASH_AIR || _player.atkType == DASH_GROUND)
        {
            _player.curPlayAtkAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 20);
        }
        else if (_player.atkType == THROW)
        {
            _player.curPlayAtkAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 15);
        }
        else if (_player.atkType == SPLASH_GROUND || _player.atkType == SPLASH_AIR)
        {
            _player.curPlayAtkAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 15);
        }
    }
    else if (_player.atkType == NON_ATTACK) // �̵� ��� ������ ������Ʈ
    {
        if (_player.stateType == PLAYER::HIT)
        {
            _player.curPlayAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 5);
        }
        else
        {
            _player.curPlayAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
        }
    }
    
}
