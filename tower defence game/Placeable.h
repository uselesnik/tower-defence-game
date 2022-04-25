#pragma once
class Placeable
{
	sf::Sprite sprite;
	sf::Texture texture;
public:
	void place(float x, float y);
	
	sf::Sprite getSprite();

};

