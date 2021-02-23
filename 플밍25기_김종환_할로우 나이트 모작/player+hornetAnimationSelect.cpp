#include "stdafx.h"
#include "player.h"
#include "mapManager.h"
#include "projectile.h"

void player::hornetAnimationSelect()
{
    if (_player.atkType == NON_ATTACK)
    {
        if (_player.stateType == HIT)
        {
            if (_player.dirType == LEFT)
            {
                _player.curPlayAni = ANIMATIONMANAGER->findAnimation("hornet_stun_left");
            }
            else if (_player.dirType == RIGHT)
            {
                _player.curPlayAni = ANIMATIONMANAGER->findAnimation("hornet_stun_right");
            }
            _player.curPlayAni->resume();
        }
        else
        {
            // ������ ������ ���� ��
            if (_player.dirType == LEFT && _player.posType == ONTHEGROUND &&
                _player.stateType == IDLE_NORMAL && _player.jumpType == NON_JUMP)
            {
                _player.curPlayAni = ANIMATIONMANAGER->findAnimation("hornet_idle_normal_left");
                _player.curPlayAni->resume();
                ANIMATIONMANAGER->resetCurrentAni("hornet_run_left_1");
                ANIMATIONMANAGER->resetCurrentAni("hornet_run_right_1");
            }
            else if (_player.dirType == RIGHT && _player.posType == ONTHEGROUND &&
                _player.stateType == IDLE_NORMAL && _player.jumpType == NON_JUMP)
            {
                _player.curPlayAni = ANIMATIONMANAGER->findAnimation("hornet_idle_normal_right");
                _player.curPlayAni->resume();
                ANIMATIONMANAGER->resetCurrentAni("hornet_run_left_1");
                ANIMATIONMANAGER->resetCurrentAni("hornet_run_right_1");
            }
            // ������ �޸� ��
            else if (_player.dirType == LEFT && _player.posType == ONTHEGROUND &&
                _player.stateType == RUN && _player.jumpType == NON_JUMP)
            {
                if (_player.curPlayAni == ANIMATIONMANAGER->findAnimation("hornet_run_left_2"))
                {
                    ANIMATIONMANAGER->resetCurrentAni("hornet_run_left_1");
                    _player.curPlayAni->resume();
                }
                else
                {
                    _player.curPlayAni = ANIMATIONMANAGER->findAnimation("hornet_run_left_1");
                    _player.curPlayAni->resume();
                }
            }
            else if (_player.dirType == RIGHT && _player.posType == ONTHEGROUND &&
                _player.stateType == RUN && _player.jumpType == NON_JUMP)
            {
                if (_player.curPlayAni == ANIMATIONMANAGER->findAnimation("hornet_run_right_2"))
                {
                    ANIMATIONMANAGER->resetCurrentAni("hornet_run_right_1");
                    _player.curPlayAni->resume();
                }
                else
                {
                    _player.curPlayAni = ANIMATIONMANAGER->findAnimation("hornet_run_right_1");
                    _player.curPlayAni->resume();
                }
            }
            // ���ڸ� �������� ��
            else if (_player.dirType == LEFT && _player.posType == INTHEAIR &&
                _player.stateType == IDLE_NORMAL && _player.jumpType == JUMP)
            {
                if (_player.curPlayAni == ANIMATIONMANAGER->findAnimation("hornet_jump_left_2"))
                {
                    ANIMATIONMANAGER->resetCurrentAni("hornet_jump_left_1");
                    _player.curPlayAni->resume();
                }
                else
                {
                    _player.curPlayAni = ANIMATIONMANAGER->findAnimation("hornet_jump_left_1");
                    ANIMATIONMANAGER->resetCurrentAni("hornet_jump_left_2");
                    _player.curPlayAni->resume();
                }
            }
            else if (_player.dirType == RIGHT && _player.posType == INTHEAIR &&
                _player.stateType == IDLE_NORMAL && _player.jumpType == JUMP)
            {
                if (_player.curPlayAni == ANIMATIONMANAGER->findAnimation("hornet_jump_right_2"))
                {
                    ANIMATIONMANAGER->resetCurrentAni("hornet_jump_right_1");
                    _player.curPlayAni->resume();
                }
                else
                {
                    _player.curPlayAni = ANIMATIONMANAGER->findAnimation("hornet_jump_right_1");
                    ANIMATIONMANAGER->resetCurrentAni("hornet_jump_right_2");
                    _player.curPlayAni->resume();
                }
            }
            // �޸��� �������� ��
            else if (_player.dirType == LEFT && _player.posType == INTHEAIR &&
                _player.stateType == RUN && _player.jumpType == JUMP)
            {
                if (_player.curPlayAni == ANIMATIONMANAGER->findAnimation("hornet_jump_left_2"))
                {
                    ANIMATIONMANAGER->resetCurrentAni("hornet_jump_left_1");
                    _player.curPlayAni->resume();
                }
                else
                {
                    _player.curPlayAni = ANIMATIONMANAGER->findAnimation("hornet_jump_left_1");
                    ANIMATIONMANAGER->resetCurrentAni("hornet_jump_left_2");
                    _player.curPlayAni->resume();
                }
            }
            else if (_player.dirType == RIGHT && _player.posType == INTHEAIR &&
                _player.stateType == RUN && _player.jumpType == JUMP)
            {
                if (_player.curPlayAni == ANIMATIONMANAGER->findAnimation("hornet_jump_right_2"))
                {
                    ANIMATIONMANAGER->resetCurrentAni("hornet_jump_right_1");
                    _player.curPlayAni->resume();
                }
                else
                {
                    _player.curPlayAni = ANIMATIONMANAGER->findAnimation("hornet_jump_right_1");
                    ANIMATIONMANAGER->resetCurrentAni("hornet_jump_right_2");
                    _player.curPlayAni->resume();
                }
            }
            //===============================*����*===============================//
            // ���ڸ� ������ ��
            else if (_player.dirType == LEFT && _player.posType == INTHEAIR &&
                _player.stateType == IDLE_NORMAL && _player.jumpType == LAND)
            {
                _player.curPlayAni = ANIMATIONMANAGER->findAnimation("hornet_jump_left_2");
                ANIMATIONMANAGER->resetCurrentAni("hornet_jump_left_1");
                _player.curPlayAni->resume();
            }
            else if (_player.dirType == RIGHT && _player.posType == INTHEAIR &&
                _player.stateType == IDLE_NORMAL && _player.jumpType == LAND)
            {
                _player.curPlayAni = ANIMATIONMANAGER->findAnimation("hornet_jump_right_2");
                ANIMATIONMANAGER->resetCurrentAni("hornet_jump_right_1");
                _player.curPlayAni->resume();
            }
            // �޸��� ������ ��
            else if (_player.dirType == LEFT && _player.posType == INTHEAIR &&
                _player.stateType == RUN && _player.jumpType == LAND)
            {
                _player.curPlayAni = ANIMATIONMANAGER->findAnimation("hornet_jump_left_2");
                ANIMATIONMANAGER->resetCurrentAni("hornet_jump_left_1");
                _player.curPlayAni->resume();
            }
            else if (_player.dirType == RIGHT && _player.posType == INTHEAIR &&
                _player.stateType == RUN && _player.jumpType == LAND)
            {
                _player.curPlayAni = ANIMATIONMANAGER->findAnimation("hornet_jump_right_2");
                ANIMATIONMANAGER->resetCurrentAni("hornet_jump_right_1");
                _player.curPlayAni->resume();
            }
            //==============================================================//
            // ���� �Ŵ޷��� ��
            else if (_player.dirType == LEFT && _player.posType == HANGING &&
                _player.stateType == HANG && _player.jumpType == NON_JUMP)
            {
                _player.curPlayAni = ANIMATIONMANAGER->findAnimation("hornet_hang_left");
                _player.curPlayAni->resume();
            }
            else if (_player.dirType == RIGHT && _player.posType == HANGING &&
                _player.stateType == HANG && _player.jumpType == NON_JUMP)
            {
                _player.curPlayAni = ANIMATIONMANAGER->findAnimation("hornet_hang_right");
                _player.curPlayAni->resume();
            }
            // �� ���� ���� ��
            else if (_player.dirType == LEFT && _player.posType == INTHEAIR &&
                _player.stateType == RUN && _player.jumpType == WALL_JUMP)
            {
                _player.curPlayAni = ANIMATIONMANAGER->findAnimation("hornet_jump_left_1");
                ANIMATIONMANAGER->resetCurrentAni("hornet_jump_left_2");
                _player.curPlayAni->resume();
            }
            else if (_player.dirType == RIGHT && _player.posType == INTHEAIR &&
                _player.stateType == RUN && _player.jumpType == WALL_JUMP)
            {
                _player.curPlayAni = ANIMATIONMANAGER->findAnimation("hornet_jump_right_1");
                ANIMATIONMANAGER->resetCurrentAni("hornet_jump_right_2");
                _player.curPlayAni->resume();
            }
        }
    }
    else // ������ ��
    {
        if (_player.stateType == HIT)
        {

        }
        else
        {
            switch (_player.atkType)
            {
            case NON_ATTACK:
                break;
            case NORMAL_ATTACK:
                if (_player.dirType == LEFT)
                {
                    _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_attack_left");

                }
                else if (_player.dirType == RIGHT)
                {
                    _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_attack_right");
                    
                }
                _player.curPlayAtkAni->resume();
                break;
            case FLOURISH:
                break;
            case THROW:
                // â������ ����
                if (_player.dirType == LEFT)
                {
                    if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_throw_left_2"))
                    {
                            _player.curPlayAtkAni->resume();
                            ANIMATIONMANAGER->resetCurrentAni("hornet_throw_left_1");
                            ANIMATIONMANAGER->resetCurrentAni("hornet_throw_left_3");
                    }
                    else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_throw_left_2_1"))
                    {
                        _player.curPlayAtkAni->resume();
                    }
                    else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_throw_left_3"))
                    {
                        _player.curPlayAtkAni->resume();
                        ANIMATIONMANAGER->resetCurrentAni("hornet_throw_left_1");
                        ANIMATIONMANAGER->resetCurrentAni("hornet_throw_left_2");
                    }
                    else
                    {
                        _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_throw_left_1");
                        _player.curPlayAtkAni->resume();
                        ANIMATIONMANAGER->resetCurrentAni("hornet_throw_left_2");
                        ANIMATIONMANAGER->resetCurrentAni("hornet_throw_left_3");
                    }
                }
                // â������ ������
                else if (_player.dirType == RIGHT)
                {
                    if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_throw_right_2"))
                    {
                        _player.curPlayAtkAni->resume();
                        ANIMATIONMANAGER->resetCurrentAni("hornet_throw_right_1");
                        ANIMATIONMANAGER->resetCurrentAni("hornet_throw_right_3");
                    }
                    else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_throw_right_2_1"))
                    {
                        _player.curPlayAtkAni->resume();
                    }
                    else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_throw_right_3"))
                    {
                        _player.curPlayAtkAni->resume();
                        ANIMATIONMANAGER->resetCurrentAni("hornet_throw_right_1");
                        ANIMATIONMANAGER->resetCurrentAni("hornet_throw_right_2");
                    }
                    else
                    {
                        _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_throw_right_1");
                        _player.curPlayAtkAni->resume();
                        ANIMATIONMANAGER->resetCurrentAni("hornet_throw_right_2");
                        ANIMATIONMANAGER->resetCurrentAni("hornet_throw_right_3");
                    }
                }
                break;
            case DASH_AIR:
                // ���߿��� ���� �뽬
                if (_player.dirType == LEFT)
                {
                    if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_dash_air_left_2"))
                    {
                        if (fabs(_player.dashX - _player.x) >= DASHLENGTH)
                        {
                            _player.curPlayAtkAni->stop();
                        }
                        else
                        {
                            _player.curPlayAtkAni->resume();
                            ANIMATIONMANAGER->resetCurrentAni("hornet_dash_air_left_1");
                            ANIMATIONMANAGER->resetCurrentAni("hornet_dash_air_left_3");
                        }
                    }
                    else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_dash_air_left_3"))
                    {
                        _player.curPlayAtkAni->resume();
                        ANIMATIONMANAGER->resetCurrentAni("hornet_dash_air_left_1");
                        ANIMATIONMANAGER->resetCurrentAni("hornet_dash_air_left_2");
                    }
                    else
                    {
                        _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_dash_air_left_1");
                        _player.curPlayAtkAni->resume();
                        ANIMATIONMANAGER->resetCurrentAni("hornet_dash_air_left_2");
                        ANIMATIONMANAGER->resetCurrentAni("hornet_dash_air_left_3");
                    }
                }
                // ���߿��� ������ �뽬
                else if (_player.dirType == RIGHT)
                {
                    if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_dash_air_right_2"))
                    {
                        if (fabs(_player.dashX - _player.x) >= DASHLENGTH)
                        {
                            _player.curPlayAtkAni->stop();
                        }
                        else
                        {
                            _player.curPlayAtkAni->resume();
                            ANIMATIONMANAGER->resetCurrentAni("hornet_dash_air_right_1");
                            ANIMATIONMANAGER->resetCurrentAni("hornet_dash_air_right_3");
                        }
                    }
                    else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_dash_air_right_3"))
                    {
                        _player.curPlayAtkAni->resume();
                        ANIMATIONMANAGER->resetCurrentAni("hornet_dash_air_right_1");
                        ANIMATIONMANAGER->resetCurrentAni("hornet_dash_air_right_2");
                    }
                    else
                    {
                        _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_dash_air_right_1");
                        _player.curPlayAtkAni->resume();
                        ANIMATIONMANAGER->resetCurrentAni("hornet_dash_air_right_2");
                        ANIMATIONMANAGER->resetCurrentAni("hornet_dash_air_right_3");
                    }
                }
                break;
            case DASH_GROUND:
                // ������ ���� �뽬
                if (_player.dirType == LEFT)
                {
                    if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_dash_ground_left_2"))
                    {
                        if (fabs(_player.dashX - _player.x) >= DASHLENGTH)
                        {
                            _player.curPlayAtkAni->stop();
                        }
                        else
                        {
                            _player.curPlayAtkAni->resume();
                            ANIMATIONMANAGER->resetCurrentAni("hornet_dash_ground_left_1");
                            ANIMATIONMANAGER->resetCurrentAni("hornet_dash_ground_left_3");
                        }
                    }
                    else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_dash_ground_left_3"))
                    {
                        _player.curPlayAtkAni->resume();
                        ANIMATIONMANAGER->resetCurrentAni("hornet_dash_ground_left_1");
                        ANIMATIONMANAGER->resetCurrentAni("hornet_dash_ground_left_2");
                    }
                    else
                    {
                        _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_dash_ground_left_1");
                        _player.curPlayAtkAni->resume();
                        ANIMATIONMANAGER->resetCurrentAni("hornet_dash_ground_left_2");
                        ANIMATIONMANAGER->resetCurrentAni("hornet_dash_ground_left_3");
                    }
                }
                // ������ ������ �뽬
                else if (_player.dirType == RIGHT)
                {
                    if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_dash_ground_right_2"))
                    {
                        if (fabs(_player.dashX - _player.x) >= DASHLENGTH)
                        {
                            _player.curPlayAtkAni->stop();
                        }
                        else
                        {
                            _player.curPlayAtkAni->resume();
                            ANIMATIONMANAGER->resetCurrentAni("hornet_dash_ground_right_1");
                            ANIMATIONMANAGER->resetCurrentAni("hornet_dash_ground_right_3");
                        }
                    }
                    else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_dash_ground_right_3"))
                    {
                        _player.curPlayAtkAni->resume();
                        ANIMATIONMANAGER->resetCurrentAni("hornet_dash_ground_right_1");
                        ANIMATIONMANAGER->resetCurrentAni("hornet_dash_ground_right_2");
                    }
                    else
                    {
                        _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_dash_ground_right_1");
                        _player.curPlayAtkAni->resume();
                        ANIMATIONMANAGER->resetCurrentAni("hornet_dash_ground_right_2");
                        ANIMATIONMANAGER->resetCurrentAni("hornet_dash_ground_right_3");
                    }
                }
                break;
            case SPLASH_AIR:
                // ���߿��� ���� ���÷���
                if (_player.dirType == LEFT)
                {
                    if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_splashAttack_left_2"))
                    {

                        _player.curPlayAtkAni->resume();
                        ANIMATIONMANAGER->resetCurrentAni("hornet_splashAttack_air_left_1");
                        ANIMATIONMANAGER->resetCurrentAni("hornet_splashAttack_left_3");

                    }
                    else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_splashAttack_left_3"))
                    {
                        _player.curPlayAtkAni->resume();
                        ANIMATIONMANAGER->resetCurrentAni("hornet_splashAttack_air_left_1");
                        ANIMATIONMANAGER->resetCurrentAni("hornet_splashAttack_left_2");
                    }
                    else
                    {
                        _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_splashAttack_air_left_1");
                        _player.curPlayAtkAni->resume();
                        ANIMATIONMANAGER->resetCurrentAni("hornet_splashAttack_left_2");
                        ANIMATIONMANAGER->resetCurrentAni("hornet_splashAttack_left_3");
                    }
                }
                // ���߿��� ������ ���÷���
                else if (_player.dirType == RIGHT)
                {
                    if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_splashAttack_right_2"))
                    {
                        _player.curPlayAtkAni->resume();
                        ANIMATIONMANAGER->resetCurrentAni("hornet_splashAttack_air_right_1");
                        ANIMATIONMANAGER->resetCurrentAni("hornet_splashAttack_right_3");
                    }
                    else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_splashAttack_right_3"))
                    {
                        _player.curPlayAtkAni->resume();
                        ANIMATIONMANAGER->resetCurrentAni("hornet_splashAttack_air_right_1");
                        ANIMATIONMANAGER->resetCurrentAni("hornet_splashAttack_right_2");
                    }
                    else
                    {
                        _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_splashAttack_air_right_1");
                        _player.curPlayAtkAni->resume();
                        ANIMATIONMANAGER->resetCurrentAni("hornet_splashAttack_right_2");
                        ANIMATIONMANAGER->resetCurrentAni("hornet_splashAttack_right_3");
                    }
                }
                break;
            case SPLASH_GROUND:
                // ������ ���� ���÷���
                if (_player.dirType == LEFT)
                {
                    if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_splashAttack_left_2"))
                    {
                            _player.curPlayAtkAni->resume();
                            ANIMATIONMANAGER->resetCurrentAni("hornet_splashAttack_ground_left_1");
                            ANIMATIONMANAGER->resetCurrentAni("hornet_splashAttack_left_3");
                    }
                    else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_splashAttack_left_3"))
                    {
                        _player.curPlayAtkAni->resume();
                        ANIMATIONMANAGER->resetCurrentAni("hornet_splashAttack_ground_left_1");
                        ANIMATIONMANAGER->resetCurrentAni("hornet_splashAttack_left_2");
                    }
                    else
                    {
                        _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_splashAttack_ground_left_1");
                        _player.curPlayAtkAni->resume();
                        ANIMATIONMANAGER->resetCurrentAni("hornet_splashAttack_left_2");
                        ANIMATIONMANAGER->resetCurrentAni("hornet_splashAttack_left_3");
                    }
                }
                // ������ ������ ���÷���
                else if (_player.dirType == RIGHT)
                {
                    if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_splashAttack_right_2"))
                    {
                        _player.curPlayAtkAni->resume();
                        ANIMATIONMANAGER->resetCurrentAni("hornet_splashAttack_ground_right_1");
                        ANIMATIONMANAGER->resetCurrentAni("hornet_splashAttack_right_3");
                    }
                    else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_splashAttack_right_3"))
                    {
                        _player.curPlayAtkAni->resume();
                        ANIMATIONMANAGER->resetCurrentAni("hornet_splashAttack_ground_right_1");
                        ANIMATIONMANAGER->resetCurrentAni("hornet_splashAttack_right_2");
                    }
                    else
                    {
                        _player.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("hornet_splashAttack_ground_right_1");
                        _player.curPlayAtkAni->resume();
                        ANIMATIONMANAGER->resetCurrentAni("hornet_splashAttack_right_2");
                        ANIMATIONMANAGER->resetCurrentAni("hornet_splashAttack_right_3");
                    }
                }
                break;
            }
        }
    }

}

