#include"pch.h" //precompiled header, kjer je includan sfml, iostream in string
#include "Enemy.h"
#include "ListManager.h"
#include "Window.h"

int ListManager<Enemy>::steviloObj;

void updateEnemyPath(ListManager<Enemy>::listObject* temp) {
    if (temp == NULL) return;
    temp->data.followPath();
    updateEnemyPath(temp->nasl);
}

int main(){
    ListManager<Enemy>::setStObj(0);

    //nastavljanje spremenjlivk
    Window window;
    Enemy enemy;

    enemy.setup();
    ListManager<Enemy> test;
    test.vnos(enemy);
    
    //window.renderList(test);
    // program traja dokler je okno odprto
    while (window.open()){
        window.update();
        
        updateEnemyPath(test.start);
        
        window.renderList(test);
        
        window.render();
        if (window.getSpawn())test.vnos(enemy);
    }
    return 0;
}