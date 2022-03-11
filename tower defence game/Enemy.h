#pragma once
#include<SFML/Graphics.hpp>


class Enemy
{
private:
	
	sf::Texture texture;
	sf::Sprite sprite;
	
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

