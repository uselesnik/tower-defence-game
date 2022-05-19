#include"pch.h" //precompiled header, kjer je includan sfml, iostream in string
#include "Enemy.h"
#include "ListManager.h"
#include "Window.h"
#include "Placeable.h"
#include "ShooterTower.h"
#include "PlusShooter.h"
#include "DiagonalShooter.h"
#include "Bullet.h"
#include "Player.h"
#include <ctime>


sf::Text textSetup(sf::Text text, std::string printedText, sf::Color fill, sf::Color outline) {
    text.setFillColor(fill);
    text.setOutlineColor(outline);
    text.setOutlineThickness(1);
    text.setCharacterSize(18);
    text.setString(printedText);
    return text;
}

//nastavljanje staticnih lastnosti
int ShooterTower::price;
int PlusShooter::price;
int DiagonalShooter::price;
int ListManager<Enemy>::steviloObj; //stevilo obj pomeni koliko seznamov je trenutno da jih na koncu lahko izbrise
int ListManager<ShooterTower>::steviloObj;
int ListManager<PlusShooter>::steviloObj;
int ListManager<DiagonalShooter>::steviloObj;
int ListManager<Bullet>::steviloObj;
bool Placeable::prosto[12][16];

int main() {
    ShooterTower::setPrice(75);
    DiagonalShooter::setPrice(25);
    PlusShooter::setPrice(200);
    ListManager<Enemy>::setStObj(0);
    ListManager<ShooterTower>::setStObj(0);
    ListManager<PlusShooter>::setStObj(0);
    ListManager<DiagonalShooter>::setStObj(0);
    ListManager<Bullet>::setStObj(0);
    Placeable::initProsto();
    //nastavljanje spremenjlivk

    Window window;
    Enemy enemy, enemy2, enemy3;
    enemy.setup(1);
    enemy2.setup(2);
    enemy3.setup(3);

    srand(time(NULL));
    sf::Clock clock;
    sf::Font font;
    sf::Text text, prices, stats;
    font.loadFromFile("Daydream.ttf");
    text.setFont(font);
    prices.setFont(font);
    stats.setFont(font);
    Player *player = new Player;
    

    ListManager<Bullet> bulletList;
    ListManager<Enemy> enemyList;
    ListManager<ShooterTower> shooterList;
    ListManager<PlusShooter> plusList;
    ListManager<DiagonalShooter> diagonalList;

    // program traja dokler je okno odprto

    while (window.open()) {

        window.update();
        if (player->getHealth() > 0) {
            for (ListManager<Enemy>::listObject* temp = enemyList.start; temp != NULL;) {
                if (!temp->data.followPath()) { //pomeni da je na koncu poti in ga je potrebno izbrisati
                    player->setHealth(player->getHealth() - temp->data.getPoints() * 2);
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
                    else  temp = tnasl;
                }
                else {
                    bool jeZbrisan = 0;
                    for (ListManager<Enemy>::listObject* tempE = enemyList.start; tempE != NULL; tempE = tempE->nasl) {
                        if (temp->data.coliding(tempE->data.getSprite())) {
                            ListManager<Bullet>::listObject* tnasl = temp->nasl;
                            int damage = temp->data.getDamage();
                            int points = tempE->data.getPoints();
                            bool premik = bulletList.delitefromLoop(temp);  //zbrise bullet
                            if (premik == 0) temp = NULL;
                            else  temp = tnasl;
                            if (tempE->data.hit(damage)) {
                                enemyList.delite(tempE->id);
                                player->setMoney(player->getMoney() + points * 5);
                                player->setScore(player->getScore() + points * 2);
                            }
                            jeZbrisan = 1;
                            break;
                        }
                    }
                    if (jeZbrisan == 0) {
                        temp->data.move();
                        temp = temp->nasl;
                    }

                }

            }

            for (ListManager<ShooterTower>::listObject* temp = shooterList.start; temp != NULL; temp = temp->nasl) {
                Bullet bullArr[6];
                if (temp->data.shoot(bullArr)) {
                    for (int i = 0; i < 6; i++) {
                        bulletList.vnos(bullArr[i]);
                        bulletList.start->data.setSprite();
                    }
                }
            }
            for (ListManager<PlusShooter>::listObject* temp = plusList.start; temp != NULL; temp = temp->nasl) {
                Bullet bullArr[4];

                if (temp->data.shoot(bullArr)) {
                    for (int i = 0; i < 4; i++) {
                        bulletList.vnos(bullArr[i]);
                        bulletList.start->data.setSprite();
                    }
                }
            }
            for (ListManager<DiagonalShooter>::listObject* temp = diagonalList.start; temp != NULL; temp = temp->nasl) {
                Bullet bullArr[4];

                if (temp->data.shoot(bullArr)) {
                    for (int i = 0; i < 4; i++) {
                        bulletList.vnos(bullArr[i]);
                        bulletList.start->data.setSprite();
                    }
                }
            }

            //postavlja towerje
            if (window.getMouseClickLocation().x > -1 && window.getMouseClickLocation().y > -1) {
                if (Placeable::jeProsto(window.getMouseClickLocation().y / 50, window.getMouseClickLocation().x / 50)) {
                    Placeable::setProsto(window.getMouseClickLocation().y / 50, window.getMouseClickLocation().x / 50, 0);
                    
                    // std::cout << "placed tile \n";
                    /* DiagonalShooter* p = new DiagonalShooter;
                     p->place(float(window.getMouseClickLocation().x / 50 * 50 + 25), float(window.getMouseClickLocation().y / 50 * 50 + 25), 800, 580);
                     diagonalList.vnos(*p);*/
                     //plus shooter
                    PlusShooter* p = new PlusShooter;
                    player->setMoney(player->getMoney() - PlusShooter::getPrice());
                    p->place(float(window.getMouseClickLocation().x / 50 * 50 + 25), float(window.getMouseClickLocation().y / 50 * 50 + 25), 1400, 600);
                    plusList.vnos(*p);

                    //shooter
                    /*
                    ShooterTower* p = new ShooterTower;
                    p->place(float(window.getMouseClickLocation().x / 50 * 50 + 25), float(window.getMouseClickLocation().y / 50 * 50 + 25), 480, 285);
                    shooterList.vnos(*p);*/


                }
            }
            text = textSetup(text, "shop", sf::Color::Black, sf::Color::White);
            stats = textSetup(stats, "health :" + std::to_string(player->getHealth()) + " \n money: " + std::to_string(player->getMoney()) + "\n score: " + std::to_string(player->getScore()) + "\n highscore: " + std::to_string(player->getHighscore()), sf::Color::Black, sf::Color::White);
            prices = textSetup(prices, std::to_string(ShooterTower::getPrice()) + "$ \t \t" + std::to_string(DiagonalShooter::getPrice()) + "$ \t \t" + std::to_string(PlusShooter::getPrice()) + "$", sf::Color::Yellow, sf::Color::Black);
            text.setPosition(5, 475.0);
            stats.setPosition(520, 475.0);
            prices.setPosition(15, 570.0);


            if (player->getScore() < 40) {
                if (clock.getElapsedTime().asMilliseconds() > 3000) {
                    enemyList.vnos(enemy);
                    clock.restart();
                }
            }
            else if (player->getScore() < 80) {
                if (clock.getElapsedTime().asMilliseconds() > 2500) {
                    if (rand() % 10 < 6) enemyList.vnos(enemy);
                    else enemyList.vnos(enemy2);
                    clock.restart();
                }
            }
            else if (player->getScore() < 200) {
                if (clock.getElapsedTime().asMilliseconds() > 2000) {
                    if (rand() % 3 == 0) enemyList.vnos(enemy);
                    else if (rand() % 5 < 3) enemyList.vnos(enemy2);
                    else enemyList.vnos(enemy3);
                    clock.restart();
                }
            }
            else {
                if (clock.getElapsedTime().asMilliseconds() > 2000) {
                    if (rand() % 9 == 0) enemyList.vnos(enemy);
                    else if (rand() % 2 == 0) enemyList.vnos(enemy2);
                    else enemyList.vnos(enemy3);
                    clock.restart();
                }
            }
        }
        //za game over
        else {
        if (clock.getElapsedTime().asMilliseconds() % 2 == 0) text = textSetup(text, "game over!", sf::Color::Red, sf::Color::Black);
        else text = textSetup(text, "game over!", sf::Color::Black, sf::Color::Red);
        prices = textSetup(prices, "press  space  to play again", sf::Color::Black, sf::Color::White);
        if (window.isPressed()) {
            player->resetPlayer();
            diagonalList.deliteList();
            plusList.deliteList();
            shooterList.deliteList();
            enemyList.deliteList();
            enemyList.deliteList();
        }
    } 
        
        window.renderList(diagonalList);
        window.renderList(plusList);
        window.renderList(shooterList);
        window.renderList(enemyList);
        window.renderList(bulletList);
        window.renderText(text);
        window.renderText(prices);
        window.renderText(stats);
        window.render();
        

    }
        return 0;
    }

