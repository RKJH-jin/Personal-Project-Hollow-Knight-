#include "stdafx.h"
#include "player.h"
#include "mapManager.h"
#include "projectile.h"

void player::playerControl()
{
    // �ǰ� �� Ű �ȸ���
    if (_player.stateType != HIT)
    {
        // �� ���� ���� ���� �� ������
        if (_player.jumpType != WALL_JUMP)
        {
            // ����/���÷���/â������ �߿��� �� ������
            if (_player.atkType == NON_ATTACK || _player.atkType == NORMAL_ATTACK)
            {
                //================���� ����Ű ������ �ִ� ���================//
                // ���������� ��Ÿ �߿��� �������� �� ������
                if (!(_player.dirType == RIGHT && _player.atkType == NORMAL_ATTACK))
                {
                    if (KEYMANAGER->isStayKeyDown(VK_LEFT))
                    {
                        // �� ������ �޸��� ������ ���
                        if (_player.posType == ONTHEGROUND && _player.stateType == IDLE_NORMAL && _player.jumpType == NON_JUMP)
                        {
                            _player.dirType = LEFT;
                            _player.posType = ONTHEGROUND;
                            _player.stateType = RUN;
                            _player.jumpType = NON_JUMP;
                        }
                        // �� ������ �޸��� ���� ���
                        else if (_player.posType == ONTHEGROUND && _player.stateType == RUN && _player.jumpType == NON_JUMP)
                        {
                            _player.dirType = LEFT;
                            _player.posType = ONTHEGROUND;
                            _player.stateType = RUN;
                            _player.jumpType = NON_JUMP;
                        }
                        // ���߿��� �����̱� �����ϴ� ���
                        else if (_player.posType == INTHEAIR && _player.stateType == IDLE_NORMAL && _player.jumpType == JUMP)
                        {
                            _player.dirType = LEFT;
                            _player.posType = INTHEAIR;
                            _player.stateType = RUN;
                            _player.jumpType = JUMP;
                        }
                        // ���߿��� �����̴� ���
                        else if (_player.posType == INTHEAIR && _player.stateType == RUN && _player.jumpType == JUMP)
                        {
                            _player.dirType = LEFT;
                            _player.posType = INTHEAIR;
                            _player.stateType = RUN;
                            _player.jumpType = JUMP;
                        }
                        // ���Ͻ� �����̱� ���� ���
                        else if (_player.posType == INTHEAIR && _player.stateType == IDLE_NORMAL && _player.jumpType == LAND)
                        {
                            _player.dirType = LEFT;
                            _player.posType = INTHEAIR;
                            _player.stateType = RUN;
                            _player.jumpType = LAND;
                        }
                        // ���Ͻ� �����̴� ���
                        else if (_player.posType == INTHEAIR && _player.stateType == RUN && _player.jumpType == LAND)
                        {
                            _player.dirType = LEFT;
                            _player.posType = INTHEAIR;
                            _player.stateType = RUN;
                            _player.jumpType = LAND;
                        }
                        // �Ŵ޷��� �ϴ� ���
                        else if (pixelCheckLeft() && _player.posType == INTHEAIR &&
                            _player.stateType == RUN && _player.jumpType == LAND)
                        {
                            _player.dirType = LEFT;
                            _player.posType = HANGING;
                            _player.stateType = HANG;
                            _player.jumpType = NON_JUMP;
                        }
                        // �Ŵ޸��� �ְ� �� ������ �����̴� ���
                        else if (pixelCheckLeft() && _player.posType == HANGING &&
                            _player.stateType == HANG && _player.jumpType == NON_JUMP)
                        {
                            _player.dirType = LEFT;
                            _player.posType = HANGING;
                            _player.stateType = HANG;
                            _player.jumpType = NON_JUMP;
                        }
                        // �Ŵ޸��� �ְ� �� �ݴ������� �����̴� ���
                        else if (pixelCheckRight() && _player.dirType == RIGHT && _player.posType == HANGING &&
                            _player.stateType == HANG && _player.jumpType == NON_JUMP)
                        {
                            _player.dirType = LEFT;
                            _player.posType = INTHEAIR;
                            _player.stateType = RUN;
                            _player.jumpType = LAND;
                            _player.preDirType = RIGHT;
                            _player.prePosType = HANGING;
                            _player.preStateType = HANG;
                            _player.preJumpType = NON_JUMP;
                            _player.preX = _player.x;
                            _player.preY = _player.y;
                        }
                        // �� ���� ���� ������ ���
                        else if (_player.posType == INTHEAIR && _player.preJumpType == WALL_JUMP)
                        {
                            _player.posType = INTHEAIR;
                            _player.stateType = RUN;
                            _player.jumpType = JUMP;
                        }
                    }
                }
                // �������� ��Ÿ �߿��� ���������� �� ������
                if (!(_player.dirType == LEFT && _player.atkType == NORMAL_ATTACK))
                {
                    //================������ ����Ű ������ �ִ� ���================//
                    if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
                    {
                        // �� ������ �޸��� ������ ���
                        if (_player.posType == ONTHEGROUND && _player.stateType == IDLE_NORMAL && _player.jumpType == NON_JUMP)
                        {
                            _player.dirType = RIGHT;
                            _player.posType = ONTHEGROUND;
                            _player.stateType = RUN;
                            _player.jumpType = NON_JUMP;
                        }
                        // �� ������ �޸��� ���� ���
                        else if (_player.posType == ONTHEGROUND && _player.stateType == RUN && _player.jumpType == NON_JUMP)
                        {
                            _player.dirType = RIGHT;
                            _player.posType = ONTHEGROUND;
                            _player.stateType = RUN;
                            _player.jumpType = NON_JUMP;
                        }
                        // ���߿��� �����̱� �����ϴ� ���
                        else if (_player.posType == INTHEAIR && _player.stateType == IDLE_NORMAL && _player.jumpType == JUMP)
                        {
                            _player.dirType = RIGHT;
                            _player.posType = INTHEAIR;
                            _player.stateType = RUN;
                            _player.jumpType = JUMP;
                        }
                        // ���߿��� �����̴� ���
                        else if (_player.posType == INTHEAIR && _player.stateType == RUN && _player.jumpType == JUMP)
                        {
                            _player.dirType = RIGHT;
                            _player.posType = INTHEAIR;
                            _player.stateType = RUN;
                            _player.jumpType = JUMP;
                        }
                        // ���Ͻ� �����̱� ���� ���
                        else if (_player.posType == INTHEAIR && _player.stateType == IDLE_NORMAL && _player.jumpType == LAND)
                        {
                            _player.dirType = RIGHT;
                            _player.posType = INTHEAIR;
                            _player.stateType = RUN;
                            _player.jumpType = LAND;
                        }
                        // ���Ͻ� �����̴� ���
                        else if (_player.posType == INTHEAIR && _player.stateType == RUN && _player.jumpType == LAND)
                        {
                            _player.dirType = RIGHT;
                            _player.posType = INTHEAIR;
                            _player.stateType = RUN;
                            _player.jumpType = LAND;
                        }
                        // �Ŵ޷��� �ϴ� ���
                        else if (pixelCheckRight() && _player.posType == INTHEAIR &&
                            _player.stateType == RUN && _player.jumpType == LAND)
                        {
                            _player.dirType = RIGHT;
                            _player.posType = HANGING;
                            _player.stateType = HANG;
                            _player.jumpType = NON_JUMP;
                        }
                        // �Ŵ޸��� �ְ� �� ������ �����̴� ���
                        else if (pixelCheckRight() && _player.posType == HANGING &&
                            _player.stateType == HANG && _player.jumpType == NON_JUMP)
                        {
                            _player.dirType = RIGHT;
                            _player.posType = HANGING;
                            _player.stateType = HANG;
                            _player.jumpType = NON_JUMP;
                        }
                        // �Ŵ޸��� �ְ� �� �ݴ������� �����̴� ���
                        else if (pixelCheckLeft() && _player.dirType == LEFT && _player.posType == HANGING &&
                            _player.stateType == HANG && _player.jumpType == NON_JUMP)
                        {
                            _player.dirType = RIGHT;
                            _player.posType = INTHEAIR;
                            _player.stateType = RUN;
                            _player.jumpType = LAND;
                            _player.preDirType = LEFT;
                            _player.prePosType = HANGING;
                            _player.preStateType = HANG;
                            _player.preJumpType = NON_JUMP;
                            _player.preX = _player.x;
                            _player.preY = _player.y;
                        }
                        // �� ���� ���� ������ ���
                        else if (_player.posType == INTHEAIR && _player.preJumpType == WALL_JUMP)
                        {
                            _player.posType = INTHEAIR;
                            _player.stateType = RUN;
                            _player.jumpType = JUMP;
                        }
                    }
                }
            }

        }

        // ����/���÷���/â������ �߿��� �� ������
        if (_player.atkType == NON_ATTACK || _player.atkType == NORMAL_ATTACK)
        {
            if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
            {
                // ������ �޸��ٰ� �� ���
                if (_player.dirType == LEFT && _player.posType == ONTHEGROUND &&
                    _player.stateType == RUN && _player.jumpType == NON_JUMP)
                {
                    _player.dirType = LEFT;
                    _player.posType = ONTHEGROUND;
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = NON_JUMP;
                }
                // ���߿��� �޸��ٰ� �� ���
                else if (_player.dirType == LEFT && _player.posType == INTHEAIR &&
                    _player.stateType == RUN && _player.jumpType == JUMP)
                {
                    _player.dirType = LEFT;
                    _player.posType = INTHEAIR;
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = JUMP;
                }
                // ���� �� �޸��ٰ� �� ���
                else if (_player.dirType == LEFT && _player.posType == INTHEAIR &&
                    _player.stateType == RUN && _player.jumpType == LAND)
                {
                    _player.dirType = LEFT;
                    _player.posType = INTHEAIR;
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = LAND;
                }
                // ��� �����̵� �Ŵ޸��� �ִٰ� ����
                else if (_player.posType == HANGING && _player.stateType == HANG && _player.jumpType == NON_JUMP)
                {
                    _player.dirType = LEFT;
                    _player.posType = HANGING;
                    _player.stateType = HANG;
                    _player.jumpType = NON_JUMP;
                }
            }

            if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
            {
                // ������ �޸��ٰ� �� ���
                if (_player.dirType == RIGHT && _player.posType == ONTHEGROUND &&
                    _player.stateType == RUN && _player.jumpType == NON_JUMP)
                {
                    _player.dirType = RIGHT;
                    _player.posType = ONTHEGROUND;
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = NON_JUMP;
                }
                // ���߿��� �޸��ٰ� �� ���
                else if (_player.dirType == RIGHT && _player.posType == INTHEAIR &&
                    _player.stateType == RUN && _player.jumpType == JUMP)
                {
                    _player.dirType = RIGHT;
                    _player.posType = INTHEAIR;
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = JUMP;
                }
                // ���� �� �޸��ٰ� �� ���
                else if (_player.dirType == RIGHT && _player.posType == INTHEAIR &&
                    _player.stateType == RUN && _player.jumpType == LAND)
                {
                    _player.dirType = RIGHT;
                    _player.posType = INTHEAIR;
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = LAND;
                }
                // ��� �����̵� �Ŵ޸��� �ִٰ� ����
                else if (_player.posType == HANGING && _player.stateType == HANG && _player.jumpType == NON_JUMP)
                {
                    _player.dirType = RIGHT;
                    _player.posType = HANGING;
                    _player.stateType = HANG;
                    _player.jumpType = NON_JUMP;
                }
            }
            if (!(_player.posType == HANGING && _player.stateType == HANG && _player.jumpType == NON_JUMP))
            {
                if (KEYMANAGER->isStayKeyDown('C'))
                {
                    // ������ ���ڸ� ������ ���
                    if (_player.posType == ONTHEGROUND && _player.stateType == IDLE_NORMAL && _player.jumpType == NON_JUMP
                        && (_player.jumpTimer < _player.jumpTimeLimit) && _player.jumpCount == 0)
                    {
                        _player.posType = INTHEAIR;
                        _player.stateType = IDLE_NORMAL;
                        _player.jumpType = JUMP;
                    }
                    // ������ �޸��� ������ ���
                    else if (_player.posType == ONTHEGROUND && _player.stateType == RUN && _player.jumpType == NON_JUMP
                        && (_player.jumpTimer < _player.jumpTimeLimit) && _player.jumpCount == 0)
                    {
                        _player.posType = INTHEAIR;
                        _player.stateType = RUN;
                        _player.jumpType = JUMP;
                    }
                }
            }

            // �� ����
            if (KEYMANAGER->isOnceKeyDown('C'))
            {
                if (_player.posType == HANGING && _player.stateType == HANG && _player.jumpType == NON_JUMP)
                {
                    _player.jumpTimer += TIMEMANAGER->getElapsedTime();
                    _player.preDirType = _player.dirType;
                    if (_player.dirType == LEFT) _player.dirType = RIGHT;
                    else if (_player.dirType == RIGHT) _player.dirType = LEFT;
                    _player.posType = INTHEAIR;
                    _player.stateType = RUN;
                    _player.jumpType = WALL_JUMP;
                    _player.preJumpType = WALL_JUMP;
                    _player.preX = _player.x;
                    _player.preY = _player.y;
                }
                // Ű ���� - ������ �ݴ�������� ����Ű + ������ ��
                else if (!(GetAsyncKeyState(VK_LEFT) & 0x8001) &&
                    _player.posType == INTHEAIR && _player.stateType == RUN && _player.jumpType == LAND &&
                    _player.prePosType == HANGING && _player.preStateType == HANG && _player.preJumpType == NON_JUMP &&
                    fabs(_player.preX - _player.x) < 40)
                {
                    _player.posType = INTHEAIR;
                    _player.stateType = RUN;
                    _player.jumpType = WALL_JUMP;
                }
                else if (!(GetAsyncKeyState(VK_RIGHT) & 0x8001) &&
                    _player.posType == INTHEAIR && _player.stateType == RUN && _player.jumpType == LAND &&
                    _player.prePosType == HANGING && _player.preStateType == HANG && _player.preJumpType == NON_JUMP &&
                    fabs(_player.preX - _player.x) < 40)
                {
                    _player.posType = INTHEAIR;
                    _player.stateType = RUN;
                    _player.jumpType = WALL_JUMP;
                }
            }

            //===================����Ű �� ���===================//
            if (KEYMANAGER->isOnceKeyUp('C') || (_player.jumpTimer >= _player.jumpTimeLimit))
            {
                // ������ ���ڸ� ������ ���
                if (_player.posType == INTHEAIR && _player.stateType == IDLE_NORMAL && _player.jumpType == JUMP)
                {
                    _player.posType = INTHEAIR;
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = LAND;
                }
                // ������ �޸��� ������ ���
                else if (_player.posType == INTHEAIR && _player.stateType == RUN && _player.jumpType == JUMP)
                {
                    _player.posType = INTHEAIR;
                    _player.stateType = RUN;
                    _player.jumpType = LAND;
                }
            }
        }

        //=========================== ���� Ű ���� ===========================//
        // ��Ÿ�� ���� �ִϸ��̼��� ������ ����!
        if (_player.atkType == NON_ATTACK && _player.curPlayAtkAni != nullptr && !_player.curPlayAtkAni->isPlay())
        {
            // ��Ÿ
            if (KEYMANAGER->isOnceKeyDown('X'))
            {
                //���� �Ŵ޷����� ��ŸX
                if (!(_player.posType == HANGING && _player.stateType == HANG && _player.jumpType == NON_JUMP))
                {
                    _player.atkType = NORMAL_ATTACK;
                    _player.attackX = _player.x;
                    _player.attackY = _player.y;
                    if (_player.dirType == LEFT)
                    {
                        ANIMATIONMANAGER->resetCurrentAni("hornet_attack_left");
                    }
                    else if (_player.dirType == RIGHT)
                    {
                        ANIMATIONMANAGER->resetCurrentAni("hornet_attack_right");
                    }
                }
            }
            if (KEYMANAGER->isOnceKeyUp('X'))
            {

            }
        }

        // Ư�� ���� �� �ٸ� ���� �Ұ�
        if ((_player.atkType != DASH_GROUND && _player.atkType != DASH_AIR &&
            _player.atkType != SPLASH_GROUND && _player.atkType != SPLASH_AIR &&
            _player.atkType != THROW) &&
            !_player.curPlayAtkAni->isPlay())
        {
            _player.groundDashCount = 0;
            // �뽬
            if (KEYMANAGER->isOnceKeyDown('Z'))
            {
                // ������ �뽬
                if (_player.posType == ONTHEGROUND && _player.groundDashCount == 0)
                {
                    if (_player.dirType == LEFT) _player.dirType = LEFT;

                    else if (_player.dirType == RIGHT)
                    {
                        _player.dirType = RIGHT;
                        
                    }
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = NON_JUMP;
                    _player.atkType = DASH_GROUND;
                    _player.dashX = _player.x;
                    _player.dashY = _player.y;
                    _player.groundDashCount += 1;
                }
                // ���߿��� �뽬
                else if (_player.posType == INTHEAIR && _player.airDashCount == 0)
                {
                    if (_player.dirType == LEFT) _player.dirType = LEFT;
                    else if (_player.dirType == RIGHT) _player.dirType = RIGHT;
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = LAND;
                    _player.atkType = DASH_AIR;
                    _player.dashX = _player.x;
                    _player.dashY = _player.y;
                    _player.airDashCount += 1;
                }
                // �Ŵ޷��� �� �뽬
                else if (_player.posType == HANGING && _player.stateType == HANG && _player.jumpType == NON_JUMP)
                {
                    if (_player.dirType == LEFT) _player.dirType = RIGHT;
                    else if (_player.dirType == RIGHT) _player.dirType = LEFT;
                    _player.posType = INTHEAIR;
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = NON_JUMP;
                    _player.atkType = DASH_AIR;
                    _player.dashX = _player.x;
                    _player.dashY = _player.y;
                    _player.airDashCount += 1;
                }
            }
            if (KEYMANAGER->isOnceKeyUp('Z'))
            {

            }
            //===============================================//
            // â������
            if (KEYMANAGER->isOnceKeyDown('A'))
            {
                // �������� ���� �� ����
                if (_player.posType == ONTHEGROUND)
                {
                    if (_player.dirType == LEFT) _player.dirType = LEFT;
                    else if (_player.dirType == RIGHT) _player.dirType = RIGHT;
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = NON_JUMP;
                    _player.atkType = THROW;
                    _player.throwX = _player.x;
                    _player.throwY = _player.y;
                    
                }
            }
            if (KEYMANAGER->isOnceKeyUp('A'))
            {

            }
            //===============================================//
            // ���÷���
            if (KEYMANAGER->isOnceKeyDown('S'))
            {
                _player.groundSplashCount = 0;

                // ������ ���÷���
                if (_player.posType == ONTHEGROUND && _player.groundSplashCount == 0)
                {
                    if (_player.dirType == LEFT) _player.dirType = LEFT;
                    else if (_player.dirType == RIGHT) _player.dirType = RIGHT;
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = NON_JUMP;
                    _player.atkType = SPLASH_GROUND;
                    _player.splashX = _player.x;
                    _player.splashY = _player.y;
                    _player.groundSplashCount += 1;
                }
                // ���߿��� ���÷���
                else if (_player.posType == INTHEAIR && _player.airSplashCount == 0)
                {
                    if (_player.dirType == LEFT) _player.dirType = LEFT;
                    else if (_player.dirType == RIGHT) _player.dirType = RIGHT;
                    _player.stateType = IDLE_NORMAL;
                    _player.atkType = SPLASH_AIR;
                    _player.splashX = _player.x;
                    _player.splashY = _player.y;
                    _player.airSplashCount += 1;
                }
                // �Ŵ޷��� �� ���÷���
                else if (_player.posType == HANGING && _player.stateType == HANG && _player.jumpType == NON_JUMP)
                {
                    if (_player.dirType == LEFT) _player.dirType = RIGHT;
                    else if (_player.dirType == RIGHT) _player.dirType = LEFT;
                    _player.posType = INTHEAIR;
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = LAND;
                    _player.atkType = SPLASH_AIR;
                    _player.splashX = _player.x;
                    _player.splashY = _player.y;
                }
            }
            if (KEYMANAGER->isOnceKeyUp('S'))
            {

            }
            //===============================================//
        }
    }

    //================���� Ÿ�̸� ����================//
    if ((!(!(GetAsyncKeyState('C') & 0x8000)) || _player.jumpType == JUMP) && (_player.jumpTimer < _player.jumpTimeLimit))
    {
        _player.jumpTimer += TIMEMANAGER->getElapsedTime();
        _player.jumpType = JUMP;

    }
}

