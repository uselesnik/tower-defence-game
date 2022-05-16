#include "pch.h"
#include "PlusShooter.h"

bool PlusShooter::shoot(Bullet bullArr[4])
{
	if (reloadClock.getElapsedTime().asMilliseconds() < reloadSpeed) return 0;
	for (int i = 0; i < 4; i++) {
		reloadClock.restart();
		Bullet bullet;
		bullet.setup(bulletDuration, this->getSprite().getPosition().x, this->getSprite().getPosition().y, i * 90, 7, 5);
		bullArr[i] = bullet;
	}		
	return 1;
}

