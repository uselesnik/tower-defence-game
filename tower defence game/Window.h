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

	template <class T>
	void renderList(ListManager<T> list);
	
	void update();
	void render();
	void renderSprite(sf::Sprite sprite);
	void renderEnemy();

};

template<class T>
void Window::renderList(ListManager<T> list)
{
	list.steviloObj++;
	for (ListManager<T>::template listObject* tren = list.start; tren != NULL; tren = tren->nasl) {

		window->draw(tren->data.getSprite());
	}


}
