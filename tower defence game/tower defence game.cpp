#include"pch.h" //precompiled header, kjer je includan sfml, iostream in string
#include "Enemy.h"
#include "ListManager.h"
#include "Window.h"
#include <vector>
#include "Placeable.h"
#include "ShooterTower.h"
#include "Bullet.h"

int ListManager<Enemy>::steviloObj;
int ListManager<ShooterTower>::steviloObj;
int ListManager<Bullet>::steviloObj;
bool Placeable::prosto[12][16];

int main(){
    
    ListManager<Enemy>::setStObj(0);
    ListManager<ShooterTower>::setStObj(0);
    ListManager<Bullet>::setStObj(0);

    Placeable::initProsto();
    //nastavljanje spremenjlivk
    



    Window window;
    Enemy enemy, enemy2;
    enemy.setup(1);
    enemy2.setup(2);
    sf::Clock clock;
    Bullet d;
   
    ListManager<Bullet> bulletList;
    ListManager<Enemy> enemyList;
    ListManager<ShooterTower> placeableList;
    

    // program traja dokler je okno odprto
    
    while (window.open()) {

        window.update();

        for (ListManager<Enemy>::listObject* temp = enemyList.start; temp != NULL; temp = temp->nasl) {
            if (!temp->data.followPath()) { //pomeni da je na koncu poti in ga je potrebno izbrisati
                if (temp == enemyList.start && temp == enemyList.zaklj) { // zadnji element v listu
                    enemyList.delite(temp->id);
                    break;
                }
                else if (temp == enemyList.start) { // prvi element v listu ampak ni edini
                    temp = temp->nasl;
                    enemyList.delite(temp->prej->id);
                }
                else {
                    temp = temp->prej;
                    enemyList.delite(temp->nasl->id); //idZaIzbris.push_back(temp->id);    

                }
            }
        }
        
        if (window.getMouseClickLocation().x > -1 && window.getMouseClickLocation().y > -1) {
            if (Placeable::jeProsto( window.getMouseClickLocation().y / 50, window.getMouseClickLocation().x / 50)){
                Placeable::setProsto(window.getMouseClickLocation().y / 50, window.getMouseClickLocation().x / 50, 0);
                std::cout << "placed tile \n";
                ShooterTower* p = new ShooterTower;
                p->place(float(window.getMouseClickLocation().x / 50 * 50 + 25), float(window.getMouseClickLocation().y / 50 * 50 + 25));
                placeableList.vnos(*p);
            }
        }

        window.renderList(placeableList);
        window.renderList(enemyList);
        window.renderSprite(d.getSprite());
        
        window.render();
        if (clock.getElapsedTime().asMilliseconds() > 400) {
            enemyList.vnos(enemy);
            
            clock.restart();
        };
        
    }
    return 0;
}