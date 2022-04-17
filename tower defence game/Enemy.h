#pragma once
#include"pch.h"


class Enemy
{
private:

	sf::Texture texture;
	sf::Sprite sprite;

	sf::Vector2f path[5];
	
	float speed;
	int pathpoint;
	float hyp; //trenutni del poti
	
public:
	

	//constructors and destructors
	Enemy();
	~Enemy();
	// setters & getters
	sf::Sprite getSprite();



	//other methods
	void followPath();
	void setup();

};

