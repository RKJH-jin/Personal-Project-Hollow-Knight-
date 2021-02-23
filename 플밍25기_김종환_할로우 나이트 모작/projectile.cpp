#include "stdafx.h"
#include "projectile.h"
#include "player.h"
#include "enemyManager.h"

HRESULT projectile::init()
{
    return S_OK;
}

void projectile::release()
{
}

void projectile::update()
{
    playerPJUpdate();
    aspidPJUpdate();
    xeroPJUpdate();
    collision();
}

void projectile::render()
{
    playerPJRender();
    aspidPJRender();
    xeroPJRender();
}

void projectile::hornetSpearInit(float playerX, float playerY, float playerWidth, float playerHeight, PLAYER::DIRECTION dir)
{
    _spear = new playerProjectile;
    _spear->init(playerX, playerY, playerWidth, playerHeight, dir);
}

void projectile::playerPJUpdate()
{
    if (_spear != nullptr)
    {
        _spear->update();
        if (_spear->hornetSpearCheck())
        {
            SAFE_DELETE(_spear);
        }
    }
}

void projectile::playerPJRender()
{
    if (_spear != nullptr)
    {
        _spear->render();
    }
}

void projectile::aspidPJInit(float enemyX, float enemyY, float enemyWidth, float enemyHeight, float enemyAngle, ENEMY::ENEMYTYPE enemyType, ENEMY::DIRECTIONTYPE dir)
{
    enemyProjectile* temp;
    temp = new enemyProjectile;
    temp->init(enemyX, enemyY, enemyWidth, enemyHeight, enemyAngle, ASPID, dir);
    _vAspidPJ.push_back(temp);
}

void projectile::aspidPJUpdate()
{
    for (_viAspidPJ = _vAspidPJ.begin(); _viAspidPJ != _vAspidPJ.end();)
    {
        if ((*_viAspidPJ)->aspidProjectileMove())
        {
            _viAspidPJ = _vAspidPJ.erase(_viAspidPJ);
        }
        else ++_viAspidPJ;
    }
}

void projectile::aspidPJRender()
{
    for (int i = 0; i < _vAspidPJ.size(); ++i)
    {
        _vAspidPJ[i]->aspidProjectileRender();
    }
}

void projectile::removeAspidPJ(int arrNum)
{
    _vAspidPJ.erase(_vAspidPJ.begin() + arrNum);
}
//===============================XERO===============================//
void projectile::xeroPJInit(float enemyX, float enemyY, float enemyWidth, float enemyHeight, float enemyAngle, ENEMY::PHASE ph)
{
    if (ph == ENEMY::PHASE::PHASE_1)
    {
        enemyProjectile* tempL;
        tempL = new enemyProjectile;
        tempL->xeroProjectileInit(enemyX, enemyY, enemyWidth, enemyHeight, enemyAngle, 40, ENEMY::DIRECTIONTYPE::LEFT);
        _vXeroPJ.push_back(tempL);

        enemyProjectile* tempR;
        tempR = new enemyProjectile;
        tempR->xeroProjectileInit(enemyX, enemyY, enemyWidth, enemyHeight, enemyAngle, 40, ENEMY::DIRECTIONTYPE::RIGHT);
        _vXeroPJ.push_back(tempR);
    }
    else if (ph == ENEMY::PHASE::PHASE_2)
    {
        enemyProjectile* tempL;
        tempL = new enemyProjectile;
        tempL->xeroProjectileInit(enemyX, enemyY, enemyWidth, enemyHeight, enemyAngle, 100, ENEMY::DIRECTIONTYPE::LEFT);
        _vXeroPJ.push_back(tempL);

        enemyProjectile* tempR;
        tempR = new enemyProjectile;
        tempR->xeroProjectileInit(enemyX, enemyY, enemyWidth, enemyHeight, enemyAngle, 100, ENEMY::DIRECTIONTYPE::RIGHT);
        _vXeroPJ.push_back(tempR);
    }
    else if (ph == ENEMY::PHASE::PHASE_3)
    {
        enemyProjectile* tempL;
        tempL = new enemyProjectile;
        tempL->xeroProjectileInit(enemyX, enemyY, enemyWidth, enemyHeight, enemyAngle, 150, ENEMY::DIRECTIONTYPE::LEFT);
        _vXeroPJ.push_back(tempL);

        enemyProjectile* tempR;
        tempR = new enemyProjectile;
        tempR->xeroProjectileInit(enemyX, enemyY, enemyWidth, enemyHeight, enemyAngle, 150, ENEMY::DIRECTIONTYPE::RIGHT);
        _vXeroPJ.push_back(tempR);
    }
}

void projectile::xeroPJUpdate()
{
    for (int j = 0; j < _cEnemyManager->getVXero().size(); ++j)
    {
        if (_cEnemyManager->getVXero()[j]->getEnemy().atkType == ENEMY::ATTACKTYPE::NON_ATTACK) // ���� ���̾ƴϸ�
        {
            for (int i = 0; i < _vXeroPJ.size(); ++i)
            {
                // �׳� ����ٴ�
                _vXeroPJ[i]->xeroProjectileMove(_cEnemyManager->getVXero()[0]->getEnemy().x, _cEnemyManager->getVXero()[0]->getEnemy().y);
            }
        }
        else if (_cEnemyManager->getVXero()[j]->getEnemy().atkType == ENEMY::ATTACKTYPE::NORMAL_ATTACK) // �����ϰԵǸ�
        {
            // �߻� ���̸� �������� �߻��� â ����
            if (!_cEnemyManager->getVXero()[j]->getEnemy().isAtking)
            {
                vector<int> tmpV; // ��ü �ε��� ���� ����
                vector<vector<int>> ansV; // ����� �޾��� ����
                for (int k = 0; k < _vXeroPJ.size(); ++k)
                {
                    tmpV.push_back(k);
                }
                if (_cEnemyManager->getVXero()[j]->getEnemy().phase == ENEMY::PHASE::PHASE_1)
                {
                    ansV = GetCombinationInt(tmpV, 1);
                    int randNum = RND->getFromIntTo(0, ansV.size());
                    _vAtkSpearIdx = ansV[randNum];
                }
                else if (_cEnemyManager->getVXero()[j]->getEnemy().phase == ENEMY::PHASE::PHASE_2)
                {
                    ansV = GetCombinationInt(tmpV, 2);
                    int randNum = RND->getFromIntTo(0, ansV.size());
                    _vAtkSpearIdx = ansV[randNum];
                }
                else if (_cEnemyManager->getVXero()[j]->getEnemy().phase == ENEMY::PHASE::PHASE_3)
                {
                    ansV = GetCombinationInt(tmpV, 3);
                    int randNum = RND->getFromIntTo(0, ansV.size());
                    _vAtkSpearIdx = ansV[randNum];
                }
                _vNonAtkSpearIdx = GetDifferenceVectorInt(tmpV, _vAtkSpearIdx);
                _cEnemyManager->getVXero()[j]->setEnemyIsAtking(true);
            }
            // �߻� ���̸�
            else
            {
                for (int k = 0; k < _vAtkSpearIdx.size(); ++k)
                {
                    if (!_vXeroPJ[_vAtkSpearIdx[k]]->getProjectileIsFire()) // �� �߻� ���������� angle �־��ְ�
                    {
                        float tAngle = getAngle(_vXeroPJ[_vAtkSpearIdx[k]]->getProjectileX(), _vXeroPJ[_vAtkSpearIdx[k]]->getProjectileY(), _cPlayer->getPlayer().x, _cPlayer->getPlayer().y);
                        _vXeroPJ[_vAtkSpearIdx[k]]->xeroProjectileFire(tAngle);
                    }
                    // �߻��ϰ� �� �� ������ �����ΰ� �ƴϸ� �������ְ�
                    if (!_vXeroPJ[_vAtkSpearIdx[k]]->getProjectileIsEnd())
                    {
                        _vXeroPJ[_vAtkSpearIdx[k]]->xeroProjectileFireMove();
                        // ������ �����ΰŸ� ��ġ �ʱ�ȭ ���ְ�
                        if (_vXeroPJ[_vAtkSpearIdx[k]]->xeroProjectileFireMoveCheck(_cEnemyManager->getVXero()[j]->getEnemy().x,
                            _cEnemyManager->getVXero()[j]->getEnemy().y,
                            _cEnemyManager->getVXero()[j]->getEnemy().width,
                            _cEnemyManager->getVXero()[j]->getEnemy().height))
                        {
                            spearEndCount++;
                        }
                    }          
                }
                // ���δ� ������ �����ΰŸ� ���� �����ٰ� ���ְ� isEnd = false��
                if (spearEndCount == _vAtkSpearIdx.size())
                {
                    _cEnemyManager->getVXero()[j]->setEnemyAtkType(ENEMY::ATTACKTYPE::NON_ATTACK);
                    spearEndCount = 0;
                    for (int k = 0; k < _vAtkSpearIdx.size(); ++k)
                    {
                        _vXeroPJ[_vAtkSpearIdx[k]]->setProjectileIsEnd(false);
                        _vXeroPJ[_vAtkSpearIdx[k]]->setProjectileIsFire(false);
                        _cEnemyManager->getVXero()[j]->setEnemyIsAtking(false);
                    }
                }
            }
        }
    }

    if (KEYMANAGER->isOnceKeyDown('K'))
    {
        _cEnemyManager->getVXero()[0]->setEnemyPhase(PHASE_2);
        xeroPJInit(_cEnemyManager->getVXero()[0]->getEnemy().x, _cEnemyManager->getVXero()[0]->getEnemy().y,
            _cEnemyManager->getVXero()[0]->getEnemy().width, _cEnemyManager->getVXero()[0]->getEnemy().height,
            _cEnemyManager->getVXero()[0]->getEnemy().angle,
            _cEnemyManager->getVXero()[0]->getEnemy().phase);     
    }
    if (KEYMANAGER->isOnceKeyDown('L'))
    {
        _cEnemyManager->getVXero()[0]->setEnemyPhase(PHASE_3);
        xeroPJInit(_cEnemyManager->getVXero()[0]->getEnemy().x, _cEnemyManager->getVXero()[0]->getEnemy().y,
            _cEnemyManager->getVXero()[0]->getEnemy().width, _cEnemyManager->getVXero()[0]->getEnemy().height,
            _cEnemyManager->getVXero()[0]->getEnemy().angle,
            _cEnemyManager->getVXero()[0]->getEnemy().phase);
    }
}

void projectile::xeroPJRender()
{
    for (int j = 0; j < _cEnemyManager->getVXero().size(); ++j)
    {
        if (_cEnemyManager->getVXero()[j]->getEnemy().atkType == ENEMY::ATTACKTYPE::NON_ATTACK) // ���� ���̾ƴϸ�
        {
            for (int i = 0; i < _vXeroPJ.size(); ++i)
            {
                // �׳� ����ٴ� �� �׸�
                _vXeroPJ[i]->xeroProjectileRender();
            }
        }
        else if (_cEnemyManager->getVXero()[j]->getEnemy().atkType == ENEMY::ATTACKTYPE::NORMAL_ATTACK) // �����ϰԵǸ�
        {
            // ���� ���ΰ� fireRender
            for (int k = 0; k < _vAtkSpearIdx.size(); ++k)
            {
                _vXeroPJ[_vAtkSpearIdx[k]]->xeroProjectileFireRender();
            }
            // ���� ���� �ƴѰ� �׳� ����
            for (int k = 0; k < _vNonAtkSpearIdx.size(); ++k)
            {
                _vXeroPJ[_vNonAtkSpearIdx[k]]->xeroProjectileRender();
            }
        }
    }
}

void projectile::removeXeroPJ(int arrNum)
{
}

void projectile::collision()
{
    
    if (_cPlayer->getPlayer().stateType != PLAYER::STATE::HIT)
    {
        RECT tmp;
        // ASPID
        for (_viAspidPJ = _vAspidPJ.begin(); _viAspidPJ != _vAspidPJ.end();)
        {
            if (IntersectRect(&tmp, &_cPlayer->getRect(), &(*_viAspidPJ)->getRect()))
            {
                _viAspidPJ = _vAspidPJ.erase(_viAspidPJ);
                _cPlayer->setPlayerState(PLAYER::STATE::HIT);
                //_cPlayer->hitDamage(20);
            }
            else ++_viAspidPJ;
        }
        // XERO
        // ���͸� ����� ���а� ������ ������ �浹 ����, �÷��̾�RECT�� 4 ���� �� �ϳ��� �����ϸ� �浹
        // LB, RB ������ ���� ���̹Ƿ� �ش� ���и� Ȯ���ϸ� ��.
        MATHVECTOR rcLT = MATHVECTOR(_cPlayer->getRect().left, _cPlayer->getRect().top);
        MATHVECTOR rcRT = MATHVECTOR(_cPlayer->getRect().right, _cPlayer->getRect().top);
        MATHVECTOR rcLB = MATHVECTOR(_cPlayer->getRect().left, _cPlayer->getRect().bottom);
        MATHVECTOR rcRB = MATHVECTOR(_cPlayer->getRect().right, _cPlayer->getRect().bottom);
        for (int i = 0; i < _vAtkSpearIdx.size(); ++i)
        {
            MATHVECTOR pjLB = MATHVECTOR(_vXeroPJ[_vAtkSpearIdx[i]]->getLB().x, _vXeroPJ[_vAtkSpearIdx[i]]->getLB().y);
            MATHVECTOR pjRB = MATHVECTOR(_vXeroPJ[_vAtkSpearIdx[i]]->getRB().x, _vXeroPJ[_vAtkSpearIdx[i]]->getRB().y);
            if (SegmentIntersect(pjLB, pjRB, rcLT, rcRT) ||
                SegmentIntersect(pjLB, pjRB, rcRT, rcRB) ||
                SegmentIntersect(pjLB, pjRB, rcRB, rcLB) ||
                SegmentIntersect(pjLB, pjRB, rcLB, rcLT))
            {
               _cPlayer->setPlayerState(PLAYER::HIT);
               //_cPlayer->hitDamage(20);
            }
        }
    }
}
