#pragma once
class Placeable
{
	sf::Sprite sprite;
	sf::Texture texture;

	static bool prosto[12][16];
public:
	void place(float y, float x);

	static void coutProsto();
	static void initProsto();
	static bool jeProsto(int x, int y);
	sf::Sprite getSprite();

};

