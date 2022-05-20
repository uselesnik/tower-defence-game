#include "pch.h"
#include "Enemy.h"
#include <cmath>


 // constructors & destructors

Enemy::Enemy()
{
	this->speed = 0.0;
	this->pathpoint = 0;
	this->hyp = 0;

}

Enemy::~Enemy()
{
}

// setters & getters

sf::Sprite Enemy::getSprite()
{
	return this->sprite;

}

int Enemy::getPoints()
{
	return points;
}

// other

bool Enemy::followPath()
{
	 //za stetje na katerem elementu tabele poti smo
	if (pathpoint < 5 && pathpoint >= 0) {
		int predznx = 0, predzny = 0;
		if (path[pathpoint].x != 0.0) predznx = path[pathpoint].x / abs(path[pathpoint].x); //da dobimo predznak x in y
		if (path[pathpoint].y != 0.0) predzny = path[pathpoint].y / abs(path[pathpoint].y);
		float alpha = atan(path[pathpoint].y / path[pathpoint].x);
		if (hyp - speed > 0) { //pomeni da se ni na koncu trenutnega dela poti
			this->sprite.move(sf::Vector2f(cos(alpha) * speed * predznx, sin(alpha) * predzny * speed));//trigonometrija  
			hyp -= speed;
		}
		else {
			this->sprite.move(sf::Vector2f(cos(alpha) * hyp * predznx, sin(alpha) * predzny * hyp));
			//premakne se do konca trenutne poti
			pathpoint++;//gre na naslednje mesto v arrayu
			if (pathpoint < 5) hyp = sqrt(powf(path[pathpoint].x, 2) + powf(path[pathpoint].y, 2)); // izracuna hipotenuzo za naslednje mesto
		}
		return  1;
	}
	return 0;
}


void Enemy::setup(int i)
{

	this->path[0] = sf::Vector2f(600, 0.0);
	this->path[1] = sf::Vector2f(100.0, 200);
	this->path[2] = sf::Vector2f(-650.0, 0.0);
	this->path[3] = sf::Vector2f(100, 200.0);
	this->path[4] = sf::Vector2f(600.0, 0.0);
	this->hyp = sqrt(powf(path[0].x, 2) + powf(path[0].y, 2));

	switch (i) {
	case 1:
		this->texture.loadFromFile("images\\volleyball.png");
		this->sprite.setTexture(texture);
		this->speed = 2;
		this->health = 10;
		this->points = 3;
		break;
	case 2:
		this->texture.loadFromFile("images\\football.png");
		this->sprite.setTexture(texture);
		this->speed = 4.6;
		this->health = 10;
		this->points = 5;
		break;
	case 3:
		this->texture.loadFromFile("images\\basketball.png");
		this->sprite.setTexture(texture);
		this->speed = 1;
		this->health = 40;
		this->points = 8;
		break;
	case 4:
		this->texture.loadFromFile("images\\beachBall.png");
		this->sprite.setTexture(texture);
		this->speed = 1.5;
		this->health = 100;
		this->points = 10;
		break;
	}
	/*this->texture.loadFromFile("volleyball.png");
	this->sprite.setTexture(texture);
	this->speed = 4.0;*/
}

bool Enemy::hit(int damage)
{
	health -= damage;
	//std::cout << "health: " << health << "\n";
	if (health <= 0) return 1;
	return 0;
}
