#pragma once
#include "ShooterTower.h"
class PlusShooter :
    public ShooterTower
{
    static int price;
public:
    PlusShooter();
    bool shoot(Bullet bullArr[4]);
    static int getPrice();
    static void setPrice(int x);
};

