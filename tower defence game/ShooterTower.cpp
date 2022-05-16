#include "pch.h"
#include "ShooterTower.h"
#include "Bullet.h"
#include "ListManager.h"


bool ShooterTower::shoot(Bullet bulletArr[6])
{
	if (reloadClock.getElapsedTime().asMilliseconds() < reloadSpeed) return 0;
	for (int i = 0; i < 6; i++) {
		reloadClock.restart();
		Bullet bullet;
		bullet.setup(bulletDuration, this->getSprite().getPosition().x, this->getSprite().getPosition().y, i * 60, 5, 2);
		bulletArr[i] = bullet;
		
	}
	return 1;
}

void ShooterTower::place(float x, float y, int reload, int duration)
{
	Placeable::place(x, y);
	bulletDuration = duration;
	reloadSpeed = reload;
	reloadClock.restart();


}
