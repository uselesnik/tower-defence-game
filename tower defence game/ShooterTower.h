#pragma once
#include "Placeable.h"
#include "Bullet.h"

class ShooterTower :  public Placeable
{
    static int price;
protected:
    sf::Clock reloadClock;
    int bulletDuration, reloadSpeed;
public:
    ShooterTower();
    bool shoot(Bullet bulletArr[6]);
    void place(float x, float y, int reload, int duration);
    static int getPrice();
    static void setPrice(int x);
};

