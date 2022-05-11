#pragma once
class Bullet
{
	sf::Texture texture;
	sf::Sprite sprite;
public:
	Bullet();
	~Bullet();

	sf::Sprite getSprite();

};

