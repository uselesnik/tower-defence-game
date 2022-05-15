#pragma once
class Bullet{
	
	sf::Texture texture;
	sf::Sprite sprite;
	int bulletDuration, angle;
	float speed;
	sf::Clock durationClock;
public:
	Bullet();
	Bullet(int milis, float towerX, float towerY, int angle, float speed);
	//~Bullet();
	bool lifespanCheck();
	bool coliding(sf::Sprite other);
	void move();
	sf::Sprite getSprite();

	
};

