#include"pch.h" //precompiled header, kjer je includan sfml, iostream in string
#include "Enemy.h"
#include "ListManager.h"
#include "Window.h"
#include <vector>

int ListManager<Enemy>::steviloObj;

void deliteEnemies(std::vector<unsigned long int> &x, ListManager<Enemy> &list) {
    //list.setStObj(list.getStObj()+1);
    while (x.size() > 0) {
        
        list.delite(x.back());
        x.pop_back();
    }
}

int main(){
    ListManager<Enemy>::setStObj(0);

    //nastavljanje spremenjlivk
    Window window;
    Enemy enemy;

    enemy.setup();
    ListManager<Enemy> enemyList;
    
    // program traja dokler je okno odprto
    while (window.open()){
        window.update();
        
        std::vector<unsigned long int> idZaIzbris;
        for (ListManager<Enemy>::listObject* temp = enemyList.start; temp != NULL; temp = temp->nasl) {
            if (!temp->data.followPath()) idZaIzbris.push_back(temp->id);    
        }
        if (idZaIzbris.size() > 0) deliteEnemies(idZaIzbris, enemyList);
        window.renderList(enemyList);
        
        window.render();
        if (window.getSpawn())enemyList.vnos(enemy);
    }
    return 0;
}