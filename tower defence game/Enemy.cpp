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

// other

void Enemy::followPath()
{
	 //za stetje na katerem elementu tabele poti smo
	if (pathpoint < 5) {
		int predzn = 0;
		if (path[pathpoint].x != 0.0) predzn = path[pathpoint].x / abs(path[pathpoint].x); //da dobimo ali je v x os pozitivna ali negativna st ( ker je cosinus soda funkcija i think)
		
		float alpha = atan(path[pathpoint].y / path[pathpoint].x);
		if (hyp - speed > 0) { //pomeni da se ni na koncu trenutnega dela poti
			this->sprite.move(sf::Vector2f(cos(alpha) * speed * predzn, sin(alpha) * speed));//trigonometrija  
			hyp -= speed;
		}
		else {
			this->sprite.move(sf::Vector2f(cos(alpha) * hyp * predzn, sin(alpha) * hyp));
			//premakne se do konca trenutne poti
			pathpoint++;//gre na naslednje mesto v arrayu
			std::cout <<"nasl\n";
			if (pathpoint < 5) hyp = sqrt(powf(path[pathpoint].x, 2) + powf(path[pathpoint].y, 2)); // izracuna hipotenuzo za naslednje mesto
		}
	}
	else {
		//ga izbrise
	}
}


void Enemy::setup()
{
	this->speed = 12.0;

	this->path[0] = sf::Vector2f(600, 0.0);
	this->path[1] = sf::Vector2f(100.0, 200);
	this->path[2] = sf::Vector2f(-650.0, 0.0);
	this->path[3] = sf::Vector2f(100, 200.0);
	this->path[4] = sf::Vector2f(600.0, 0.0);

	this->hyp = sqrt(powf(path[0].x, 2) + powf(path[0].y, 2));

	this->texture.loadFromFile("volleyball.png");
	this->sprite.setTexture(texture);
}
