#pragma once
#include "Placeable.h"
#include "Bullet.h"

class ShooterTower :  public Placeable
{
    sf::Clock reloadClock;
    int bulletDuration, reloadSpeed;
public:
    bool shoot(Bullet bulletArr[6]);
    void place(float x, float y, int reload, int duration);
};

