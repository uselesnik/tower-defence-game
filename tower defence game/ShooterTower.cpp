#include "pch.h"
#include "ShooterTower.h"
#include "Bullet.h"
#include "ListManager.h"

void ShooterTower::shoot(ListManager<Bullet> list)
{
	Bullet* temp = new Bullet(bulletDuration, this->getSprite().getPosition().x, this->getSprite().getPosition().x);
	list.vnos(*temp);
}
