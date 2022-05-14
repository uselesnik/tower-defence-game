#include "pch.h"
#include "Bullet.h"



Bullet::Bullet()
{
    texture.loadFromFile("images\\bullet.png");
    sprite.setTexture(texture);
    bulletDuration = 0;
}
   


Bullet::Bullet(int milis, float towerX, float towerY)
{
    texture.loadFromFile("images\\bullet");
    sprite.setTexture(texture);
    sprite.setPosition(towerX, towerY);
    bulletDuration = milis;
    durationClock.restart();
    

}

bool Bullet::lifespanCheck()
{
    if (durationClock.getElapsedTime().asMilliseconds() > bulletDuration) return 1;
    return 0;
}

sf::Sprite Bullet::getSprite()
{
    return sprite;
}
