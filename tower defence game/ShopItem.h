#pragma once
#include "ShooterTower.h"
#include "DiagonalShooter.h"
#include "PlusShooter.h"
class ShopItem
{
	sf::Texture texture;
	sf::Sprite sprite;
	int cost;
public:
	ShopItem(int x);
	bool buyItem(int money);
	bool isItemPressed(sf::Vector2f mouse);
	void setPosition(float x, float y);
	sf::Sprite getSprite();
};

