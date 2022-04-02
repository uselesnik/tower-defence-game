#include"pch.h" //precompiled header, kjer je includan sfml, iostream in string
#include "Enemy.h"
#include "ListManager.h"
#include "Window.h"

int main()

{



    //nastavljanje spremenjlivk
    Window window;
    Enemy enemy;

    enemy.setup();
   
    // program traja dokler je okno odprto
    while (window.open())
    {

        window.update();

        enemy.followPath();
        window.renderSprite(enemy.getSprite());
        window.render();
        

        //risanje na ekran
             // window.clear(sf::Color(48, 199, 65, 255));
       // emananger.loop(window);
            //window.display();
    }

    return 0;
    }