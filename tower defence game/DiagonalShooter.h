#pragma once
#include "ShooterTower.h"
class DiagonalShooter :
    public ShooterTower
{
public:
    bool shoot(Bullet bullArr[4]);
};

