#include"pch.h" //precompiled header, kjer je includan sfml, iostream in string
#include "Enemy.h"
#include "ListManager.h"
#include "Window.h"



int ListManager<Enemy>::steviloObj;

int main()

{
    ListManager<Enemy>::setStObj(0);



    //nastavljanje spremenjlivk
    Window window;
    Enemy enemy;

    enemy.setup();
    ListManager<Enemy> test;
    test.setStObj(1);
    test.vnos(enemy);
    
    //window.renderList(test);
    // program traja dokler je okno odprto
    while (window.open())
    {

        window.update();
        for (ListManager<Enemy>::listObject* temp = test.start; temp != NULL; temp = temp->nasl) {
            temp->data.followPath();
        }

        
        window.renderList(test);
        
        window.render();
        if (window.getSpawn())test.vnos(enemy);
        

        //risanje na ekran
             // window.clear(sf::Color(48, 199, 65, 255));
       // emananger.loop(window);
            //window.display();
    }

    return 0;
    }