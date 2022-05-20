#include "pch.h"
#include "ShopItem.h"

ShopItem::ShopItem(int x)
{
	switch(x){
	case 1:
		texture.loadFromFile("images\\shooterTower.png");
		cost = ShooterTower::getPrice();
		break;
	case 2:
		texture.loadFromFile("images\\diagonalTower.png");
		cost = DiagonalShooter::getPrice();
		break;
	case 3:
		texture.loadFromFile("images\\plusTower.png");
		cost = PlusShooter::getPrice();
		break;
	case 4:
		texture.loadFromFile("images\\delete.png");
		cost = 0;
		break;
	case 5:
		texture.loadFromFile("images\\cancel.png");
		cost = 0;
		break;
	default:
		texture.loadFromFile("images\\temp.png");
		cost = 0;
	}
	sprite.setTexture(texture);
	sprite.setOrigin(16, 16);
}

bool ShopItem::buyItem(int money)
{
	if (money >= cost) return 1;
	return 0;
}

bool ShopItem::isItemPressed(sf::Vector2f mouse)
{
	if (sprite.getGlobalBounds().contains(mouse)) return 1;
	return 0;
}

void ShopItem::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
}

sf::Sprite ShopItem::getSprite()
{
	return sprite;
}
