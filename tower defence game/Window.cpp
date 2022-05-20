#include "pch.h"
#include "Window.h"


Window::Window()
{
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "tower defence game", sf::Style::Close);
	window->setFramerateLimit(60);
    mouseClickLocation.x = -1;
    mouseClickLocation.y = -1;
    icon.loadFromFile("images\\volleyball.png");
    texture.loadFromFile("images\\bg.png");
    window->setIcon(icon.getSize().x, icon.getSize().x, icon.getPixelsPtr());
    bg.setTexture(texture);
}

Window::~Window()
{
	delete window;
}

sf::Vector2i Window::getMouseClickLocation()
{
    return mouseClickLocation;
}

sf::Vector2f Window::getMouseWorldLocation()
{
    return window->mapPixelToCoords(mouseClickLocation);
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
            std::cout << mousePosition.x  << "\t" << mousePosition.y  << "\n";
            if ((mousePosition.x >= 0 && mousePosition.x <= 800) && (mousePosition.y >= 0 && mousePosition.y <= 600)) mouseClickLocation = mousePosition;

        }
        else {
            mouseClickLocation.x = -1;
            mouseClickLocation.y = -1;
        }
    }


    window->clear(sf::Color(48, 199, 65, 255));
    window->draw(bg);
}

void Window::render()
{
    window->display();
}

void Window::renderSprite(sf::Sprite sprite)
{
    window->draw(sprite);
}

void Window::renderText(sf::Text text)
{
    window->draw(text);
}

bool Window::isSpacePressed()
{
    if (window->hasFocus() && (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))) return 1;
   return 0;
}

bool Window::isMousePressed()
{
    if (window->hasFocus() && (sf::Mouse::isButtonPressed(sf::Mouse::Left))) return 1;
    return 0;
}


