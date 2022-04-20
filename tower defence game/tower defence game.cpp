#include"pch.h" //precompiled header, kjer je includan sfml, iostream in string
#include "Enemy.h"
#include "ListManager.h"
#include "Window.h"
#include <vector>

int ListManager<Enemy>::steviloObj;

int main(){
    ListManager<Enemy>::setStObj(0);

    //nastavljanje spremenjlivk
    Window window;
    Enemy enemy;

    enemy.setup();
    ListManager<Enemy> enemyList;
    enemyList.vnos(enemy);
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

        window.renderList(enemyList);
        
        window.render();
        if (window.getSpawn())enemyList.vnos(enemy);
    }
    return 0;
}