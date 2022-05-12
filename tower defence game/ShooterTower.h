#pragma once
#include "Placeable.h"
class ShooterTower :
    public Placeable
{
    int bulletDuration;
public:
    void shoot(ListManager<Bullet> list);
};

