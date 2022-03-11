#include "Enemy.h"
 // constructors & destructors
Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}
// setters & getters

sf::Sprite Enemy::getSprite()
{
	return this->sprite;
}
// other
void Enemy::followPath()
{
	this->sprite.move(sf::Vector2f(2.0, 0));
}

void Enemy::setup()
{
	this->texture.loadFromFile("volleyball.png");
	this->sprite.setTexture(texture);
}
