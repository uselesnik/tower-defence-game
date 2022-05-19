#include "pch.h"
#include "Player.h"

Player::Player()
{
	score = 0;
	health = 100;
	money = 100;
	placingMode = 0;
	highscore = 0; //kasneje tu beremo high score iz datoteke

}

void Player::resetPlayer()
{
	if (score > highscore) highscore = score;
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

int Player::getScore()
{
	return score;
}

int Player::getHighscore()
{
	return highscore;
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

void Player::setScore(int x)
{
	score = x;
}

void Player::setHighscore(int x)
{
	highscore = x;
}
