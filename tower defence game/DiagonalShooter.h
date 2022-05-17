#pragma once
#include "ShooterTower.h"
class DiagonalShooter :
    public ShooterTower
{
    static int price;
public:
    DiagonalShooter();
    bool shoot(Bullet bullArr[4]);
    static int getPrice();
    static void setPrice(int x);
};

