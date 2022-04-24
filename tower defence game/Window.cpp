#include "pch.h"
#include "Window.h"


Window::Window()
{
    spawn = 0;
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "tower defence game");
	window->setFramerateLimit(60);
}

Window::~Window()
{
	delete window;
}

bool Window::getSpawn()
{
    return spawn;
}

bool Window::open()
{
	return window->isOpen();
}

void Window::update()
{
    while (window->pollEvent(event))
    {
        sf::Vector2i mousePosition;
        
        if (event.type == sf::Event::Closed){
            std::cout << "exited";
            window->close();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            mousePosition = sf::Mouse::getPosition(*window);
            std::cout << mousePosition.x / 50 << "\t" << mousePosition.y / 50 << "\t";
        }
        
    }


    window->clear(sf::Color(48, 199, 65, 255));
}

void Window::render()
{
    window->display();
}

void Window::renderSprite(sf::Sprite sprite)
{
    window->draw(sprite);
}


