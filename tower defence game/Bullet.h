#pragma once
class Bullet{
	
	sf::Texture texture;
	sf::Sprite sprite;
	int bulletDuration;
	sf::Clock durationClock;
public:
	Bullet();
	Bullet(int milis, float towerX, float towerY);
	//~Bullet();
	bool lifespanCheck();
	sf::Sprite getSprite();
	
};

