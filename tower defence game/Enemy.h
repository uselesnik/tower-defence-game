#pragma once
#include"pch.h"
#include <SFML/Graphics/Color.hpp>


class Enemy
{
private:

	sf::Texture texture;
	sf::Sprite sprite;

	sf::Vector2f path[5];
	int points;
	int health;
	float speed;
	int pathpoint;
	float hyp; //trenutni del poti
	
public:
	

	//constructors and destructors
	Enemy();
	~Enemy();
	// setters & getters
	sf::Sprite getSprite();
	int getPoints();



	//other methods
	bool followPath();
	void setup(int i);
	bool hit(int damage);

};

