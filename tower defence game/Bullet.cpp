#include "pch.h"
#include "Bullet.h"
#include <cmath>




void Bullet::setup(int milis, float towerX, float towerY, int angle, float speed)
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

sf::Sprite Bullet::getSprite()
{
    return sprite;
}


