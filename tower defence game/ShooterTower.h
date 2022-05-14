#pragma once
#include "Placeable.h"
#include "Bullet.h"

class ShooterTower :
    public Placeable
{
    int bulletDuration;
public:
    Bullet shoot();

};

