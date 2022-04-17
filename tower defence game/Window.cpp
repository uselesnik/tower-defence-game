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
        if (event.type == sf::Event::Closed or event.key.code == sf::Keyboard::Escape)
            window->close();
        if (event.type == sf::Event::Resized)
            std::cout << "window size x: " << event.size.width << " , y: " << event.size.height << "\n";
        if (event.type == sf::Event::Closed or event.key.code == sf::Keyboard::Enter)
            spawn = !spawn;

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

void Window::renderEnemy()
{
    std::cout << "uhu";
}

