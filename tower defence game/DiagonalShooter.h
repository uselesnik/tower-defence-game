#pragma once
#include "ShooterTower.h"
class DiagonalShooter :
    public ShooterTower
{
public:
    DiagonalShooter();
    bool shoot(Bullet bullArr[4]);
};

