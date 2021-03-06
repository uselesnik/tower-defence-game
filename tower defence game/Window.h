#pragma once
#include"pch.h"
#include "ListManager.h"
#include "Enemy.h"
class Window

{
	sf::RenderWindow* window;
	sf::Vector2i mouseClickLocation;
	sf::Texture texture;
	sf::Sprite bg;
	sf::Image icon;
public:

	Window();
	~Window();

	sf::Vector2i getMouseClickLocation();
	sf::Vector2f getMouseWorldLocation();

	bool open();

	template <class T>
	void renderList(ListManager<T> list);
	
	void update();
	void render();
	void renderSprite(sf::Sprite sprite);
	void renderText(sf::Text text);

	bool isSpacePressed();
	bool isMousePressed();
	

};

template<class T>
void Window::renderList(ListManager<T> list)
{
	
	list.setStObj(list.getStObj() + 1);
	for (ListManager<T>::template listObject* tren = list.start; tren != NULL; tren = tren->nasl) {

		window->draw(tren->data.getSprite());
	}


}
