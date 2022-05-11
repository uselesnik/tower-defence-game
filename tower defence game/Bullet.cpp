#include "pch.h"
#include "Bullet.h"

Bullet::Bullet()
{
    texture.loadFromFile("images\\bullet");
    sprite.setTexture(texture);
}

sf::Sprite Bullet::getSprite()
{
    return sprite;
}
