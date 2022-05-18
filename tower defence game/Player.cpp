#include "pch.h"
#include "Player.h"

Player::Player()
{
	score = 0;
	health = 100;
	money = 100;
	placingMode = 0;
}

int Player::getHealth()
{
	return health;
}

int Player::getMoney()
{
	return money;	
}

int Player::getMode()
{
	return placingMode;
}

void Player::setHealth(int x)
{
	health = x;
}

void Player::setMoney(int x)
{
	money = x;
}

void Player::setMode(int x)
{
	placingMode = x;
}
