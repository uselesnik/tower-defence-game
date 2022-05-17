#pragma once
class Placeable
{
	static bool prosto[12][16];
protected:
	sf::Sprite sprite;
	sf::Texture texture;
public:
	virtual void place(float y, float x);

	static void initProsto();
	static bool jeProsto(int x, int y);
	static void setProsto(int x, int y, bool data);
	

	sf::Sprite getSprite();

};

