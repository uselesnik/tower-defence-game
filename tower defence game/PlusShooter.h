#pragma once
#include "ShooterTower.h"
class PlusShooter :
    public ShooterTower
{
    public:
    PlusShooter();
    bool shoot(Bullet bullArr[4]);
};

