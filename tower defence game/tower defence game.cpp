#include"pch.h" //precompiled header, kjer je includan sfml, iostream in string
#include "Enemy.h"
#include "ListManager.h"
#include "Window.h"

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
    while (window.open()){
        window.update();
        
        //updateEnemyPath(test.start);
        for (ListManager<Enemy>::listObject* temp = enemyList.start; temp != NULL; temp = temp->nasl) {
            if(!temp->data.followPath()) enemyList.delite(temp->id);
        }

        window.renderList(enemyList);
        
        window.render();
        if (window.getSpawn())enemyList.vnos(enemy);
    }
    return 0;
}