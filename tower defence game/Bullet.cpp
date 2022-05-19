#include "pch.h"
#include "Bullet.h"
#include <cmath>






Bullet::Bullet()
{
}

void Bullet::setup(int milis, float towerX, float towerY, int angle, float speed, int damage)
{

    
    this->sprite.setPosition(towerX, towerY);
    this->angle = angle;
    this->speed = speed;
    this->damage = damage;
    bulletDuration = milis;
    durationClock.restart();


}
   




bool Bullet::lifespanCheck()
{
   // std::cout << "\ncurrent duration: " << durationClock.getElapsedTime().asMilliseconds() << " target duration: " << bulletDuration;
  //  std::cout << "duration clock: " << durationClock.getElapsedTime().asMilliseconds() << " target time: " << bulletDuration;
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
    sprite.move(cosf(angle * (3.14159/180))  * speed, sinf(angle * (3.14159 / 180)) * -1 * speed); //ker se pri sfml 0,0 zacne na vrhu zgoraj
}

void Bullet::setSprite()
{
    this->texture.loadFromFile("images\\bullet.png");
    this->sprite.setTexture(texture);
}

sf::Sprite Bullet::getSprite()
{
    return sprite;
}

void Bullet::setColor(sf::Color x)
{
    sprite.setColor(x);
}



int Bullet::getDamage()
{
    return damage;
}


