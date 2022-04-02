#include"pch.h" //precompiled header, kjer je includan sfml, iostream in string
#include "Enemy.h"
#include "ListManager.h"


int main()

{
    ListManager<int> emananger;
    emananger.vnos(4);
    emananger.vnos(5);
    emananger.vnos(6);
    emananger.loop();
    ListManager<char> r;
    r.vnos('g');
    r.vnos('a');
    r.vnos('p');
    r.loop();


    //nastavljanje spremenjlivk
    sf::RenderWindow window(sf::VideoMode(800, 600), "tower defence game");
    window.setFramerateLimit(60);
    Enemy enemy;

    enemy.setup();
   
    // program traja dokler je okno odprto
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized)
                std::cout << "window size x: " << event.size.width << " , y: " << event.size.height << "\n";

        }
        enemy.followPath();
        

        //risanje na ekran
        window.clear(sf::Color(48, 199, 65, 255));
       // emananger.loop(window);
        window.display();
    }

    return 0;
    }