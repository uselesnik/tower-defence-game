#pragma once
#include"pch.h"
#include "ListManager.h"
#include "Enemy.h"
class Window
{
	sf::RenderWindow* window;
	sf::Event event;
public:

	Window();
	~Window();

	bool open();
	void update();
	void render();
	void renderSprite(sf::Sprite sprite);
	void renderEnemy();

};

