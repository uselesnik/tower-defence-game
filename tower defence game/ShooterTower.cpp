#include "pch.h"
#include "ShooterTower.h"
#include "Bullet.h"
#include "ListManager.h"




Bullet ShooterTower::shoot()
{
	Bullet* temp = new Bullet;
	//Bullet* temp = new Bullet(bulletDuration, this->getSprite().getPosition().x, this->getSprite().getPosition().x);
	return *temp;

}
