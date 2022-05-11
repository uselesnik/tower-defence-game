#pragma once
class Placeable
{
	sf::Sprite sprite;
	sf::Texture texture;

	static bool prosto[12][16];
public:
	void place(float y, float x);

	static void initProsto();
	static bool jeProsto(int x, int y);
	static void setProsto(int x, int y, bool data);

	sf::Sprite getSprite();

};

