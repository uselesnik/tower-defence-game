#include "pch.h"
#include "DiagonalShooter.h"

DiagonalShooter::DiagonalShooter()
{
	texture.loadFromFile("images\\diagonalTower.png");
	sprite.setTexture(texture);
}

bool DiagonalShooter::shoot(Bullet bullArr[4])
{
	if (reloadClock.getElapsedTime().asMilliseconds() < reloadSpeed) return 0;
	for (int i = 0; i < 4; i++) {
		reloadClock.restart();
		Bullet bullet;
		bullet.setup(bulletDuration, this->getSprite().getPosition().x, this->getSprite().getPosition().y, (i * 90) + 45, 5, 1);
		bullArr[i] = bullet;
	}
	return 1;
}

int DiagonalShooter::getPrice()
{
	return price;
}

void DiagonalShooter::setPrice(int x)
{
	price = x;
}