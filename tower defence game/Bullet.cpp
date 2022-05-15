#include "pch.h"
#include "Bullet.h"
#include <cmath>


Bullet::Bullet()
{
    texture.loadFromFile("images\\bullet.png");
    sprite.setTexture(texture);
    bulletDuration = 0;
}
   


Bullet::Bullet(int milis, float towerX, float towerY, int angle, float speed)
{
    texture.loadFromFile("images\\bullet.png");
    sprite.setTexture(texture);
    sprite.setPosition(towerX, towerY);
    this->angle = angle;
    this->speed = speed;
    bulletDuration = milis;
    durationClock.restart();
   

}

bool Bullet::lifespanCheck()
{
    if (durationClock.getElapsedTime().asMilliseconds() > bulletDuration) return 1;
    return 0;
}

bool Bullet::coliding(sf::Sprite other)
{
    if (sprite.getGlobalBounds().intersects(other.getGlobalBounds())) return 1;
    return 0;
}

void Bullet::move()
{
    sprite.move(sinf(angle) * speed, cosf(angle) * speed);
}

sf::Sprite Bullet::getSprite()
{
    return sprite;
}


