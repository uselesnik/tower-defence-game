#include "pch.h"
#include "Window.h"


Window::Window()
{
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "tower defence game");
	window->setFramerateLimit(60);
    mouseClickLocation.x = -1;
    mouseClickLocation.y = -1;
}

Window::~Window()
{
	delete window;
}

sf::Vector2i Window::getMouseClickLocation()
{
    return mouseClickLocation;
}

bool Window::open()
{
	return window->isOpen();
}

void Window::update()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        sf::Vector2i mousePosition;
        
        if (event.type == sf::Event::Closed){
            std::cout << "exited";
            window->close();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            mousePosition = sf::Mouse::getPosition(*window);
           // std::cout << mousePosition.x / 50 << "\t" << mousePosition.y / 50 << "\t";
            if ((mousePosition.x >= 0 && mousePosition.x <= 800) && (mousePosition.y >= 0 && mousePosition.y <= 600)) mouseClickLocation = mousePosition;

        }
        else {
            mouseClickLocation.x = -1;
            mouseClickLocation.y = -1;
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


