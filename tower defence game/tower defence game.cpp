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

int main() {
    Bullet b;

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


    ListManager<Bullet> bulletList;

    ListManager<Enemy> enemyList;

  
    ListManager<ShooterTower> shooterList;



    // program traja dokler je okno odprto

    while (window.open()) {

        window.update();

        for (ListManager<Enemy>::listObject* temp = enemyList.start; temp != NULL;) {
            if (!temp->data.followPath()) { //pomeni da je na koncu poti in ga je potrebno izbrisati
                
                ListManager<Enemy>::listObject* tnasl = temp->nasl;
                bool premik = enemyList.delitefromLoop(temp);
                if (!premik) temp = NULL;
                else temp = tnasl;  
            }
            else temp = temp->nasl;  
        }

        for (ListManager<Bullet>::listObject* temp = bulletList.start; temp != NULL;) {
            if (temp->data.lifespanCheck()) { //pomeni da je na koncu zivljenja in ga je potrebno izbrisati
                ListManager<Bullet>::listObject* tnasl = temp->nasl;
                int premik = bulletList.delitefromLoop(temp);
                if (premik == 0) temp = NULL;
                else if (premik == 1) temp = tnasl;
            }
            /*else {
                bool jeZbrisan = 0;
                for (ListManager<Enemy>::listObject* tempE = enemyList.start; tempE != NULL; tempE = tempE->nasl) {
                    if (temp->data.coliding(tempE->data.getSprite())) {
                        std::cout << "deleting bullets (collision)\n";
                        int premik = bulletList.delitefromLoop(temp);  //zbrise bullet
                        if (premik == 0) temp = NULL;
                        else if (premik == 1) temp = temp->nasl;
                        enemyList.delite(tempE->id);
                        jeZbrisan = 1;
                        break;
                    }
                }
                if (jeZbrisan == 0) {
                    temp->data.move();
                    temp = temp->nasl;
                }
                
            }*/
            else {
                temp->data.move();
                temp = temp->nasl;
            }
        }

        for (ListManager<ShooterTower>::listObject* temp = shooterList.start; temp != NULL;temp = temp->nasl) {
            Bullet bullArr[8];
            
            if (temp->data.shoot(bullArr)) {
                for (int i = 0; i < 8; i++) {
                    bulletList.vnos(bullArr[i]);
                }
            }
            
        }

        /*for (ListManager<Bullet>::listObject* temp = bulletList.start; temp != NULL; temp = temp->nasl) {
            if (!temp->data.lifespanCheck()) { //pomeni da je potrebno bullet izbrisati
                
                if (temp == bulletList.start && temp == bulletList.zaklj) { // edini element v listu
                    bulletList.delite(temp->id);
                    break;
                }
                else if (temp == bulletList.start) { // prvi element v listu ampak ni edini
                    temp = temp->nasl;
                    bulletList.delite(temp->prej->id);
                }
                else {
                    temp = temp->prej;
                    bulletList.delite(temp->nasl->id); //izbrse katerikoli ostal element

                }
            
            }
            else {
                for (ListManager<Enemy>::listObject* tempE = enemyList.start; tempE != NULL; tempE = tempE->nasl) 
                    if (temp->data.coliding(tempE->data.getSprite())) std::cout << "\n bullet:" << temp->id << " coliding with: " << tempE->id; //

                
            }
        }*/
    
            
            if (window.getMouseClickLocation().x > -1 && window.getMouseClickLocation().y > -1) {
                if (Placeable::jeProsto(window.getMouseClickLocation().y / 50, window.getMouseClickLocation().x / 50)) {
                    Placeable::setProsto(window.getMouseClickLocation().y / 50, window.getMouseClickLocation().x / 50, 0);
                    std::cout << "placed tile \n";
                    ShooterTower* p = new ShooterTower;
                    p->place(float(window.getMouseClickLocation().x / 50 * 50 + 25), float(window.getMouseClickLocation().y / 50 * 50 + 25), 800, 250);
                    shooterList.vnos(*p);
                }
            }
            window.renderList(shooterList);
            window.renderList(enemyList);
            window.renderList(bulletList);
            window.renderSprite(b.getSprite());

            window.render();
            if (clock.getElapsedTime().asMilliseconds() > 2500) {
                enemyList.vnos(enemy);
                clock.restart();
            };
        }
        return 0;
    }

