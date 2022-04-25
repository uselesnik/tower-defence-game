#include "pch.h"
#include "Placeable.h"

void Placeable::place(float x, float y)
{
	texture.loadFromFile("images\\temp.png");
	sprite.setTexture(texture);
	sprite.setPosition(x, y);

}


sf::Sprite Placeable::getSprite()
{
	return sprite;
}
