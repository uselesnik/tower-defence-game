#include "pch.h"
#include "Placeable.h"

void Placeable::place(float x, float y)
{
	sprite.setPosition(x, y);
	sprite.setOrigin(16, 16);

}


void Placeable::initProsto()
{
	bool temp[12][16] =
	{	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	/*
	for (int y = 0; y < 12; y++) {
		for (int x = 0; x < 16; x++) {
			std::cout << temp[y][x] << ", ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";*/

	for (int y = 0; y < 12; y++) {
		for (int x = 0; x < 16; x++) {
			prosto[y][x] =  temp[y][x];
		}
	}
}

bool Placeable::jeProsto(int y, int x)
{
	if ((x >= 0 && x < 16) && (y >= 0 && y < 12)) {
		return prosto[y][x];
	}
	
	return 0; // pomeni da je vnesena vrednost napacna
}

void Placeable::setProsto(int y, int x, bool data)
{
	if ((x >= 0 && x < 16) && (y >= 0 && y < 12)) {
		prosto[y][x] = data;
	}
}



sf::Sprite Placeable::getSprite()
{
	return sprite;
}
