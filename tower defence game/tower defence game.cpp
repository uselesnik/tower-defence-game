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
#include "ShopItem.h"
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
    Enemy enemy, enemy2, enemy3, enemy4;
    enemy.setup(1);
    enemy2.setup(2);
    enemy3.setup(3);
    enemy4.setup(4);

    srand(time(NULL));
    sf::Clock clock;
    sf::Font font;
    sf::Text text, prices, stats;
    font.loadFromFile("Daydream.ttf");
    text.setFont(font);
    prices.setFont(font);
    stats.setFont(font);
    Player player;

    ShopItem shooterShop(1);
    ShopItem diagonalShop(2);
    ShopItem plusShop(3);   
    shooterShop.setPosition(24, 520);
    diagonalShop.setPosition(127, 520);
    plusShop.setPosition(240, 520);

    ListManager<Bullet> bulletList;
    ListManager<Enemy> enemyList;
    ListManager<ShooterTower> shooterList;
    ListManager<PlusShooter> plusList;
    ListManager<DiagonalShooter> diagonalList;

    // program traja dokler je okno odprto

    while (window.open()) {

        window.update();
        if (player.getHealth() > 0) {
            //preverja ce je kaksen enemy prisel do konca poti in ga izbrise
            for (ListManager<Enemy>::listObject* temp = enemyList.start; temp != NULL;) {
                if (!temp->data.followPath()) { //pomeni da je na koncu poti in ga je potrebno izbrisati
                    player.setHealth(player.getHealth() - temp->data.getPoints() * 2);
                    ListManager<Enemy>::listObject* tnasl = temp->nasl;
                    bool premik = enemyList.delitefromLoop(temp);
                    if (!premik) temp = NULL;
                    else temp = tnasl;
                }
                else temp = temp->nasl;
            }
            //preverja ce je kaksen metek prisel do konca poti (casovno) in ga brise
            for (ListManager<Bullet>::listObject* temp = bulletList.start; temp != NULL;) {
                if (temp->data.lifespanCheck()) { //pomeni da je na koncu zivljenja in ga je potrebno izbrisati
                    ListManager<Bullet>::listObject* tnasl = temp->nasl;
                    int premik = bulletList.delitefromLoop(temp);
                    if (premik == 0) temp = NULL;
                    else  temp = tnasl;
                }
                //preverja ce se kaksen enemy in metek prekrivata in metek izbrise, enemiju pa naredi damage
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
                                player.setMoney(player.getMoney() + points * 5);
                                player.setScore(player.getScore() + points * 2);
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

            //preverja, ce so towerji reloadali, in ce so ustreli metke
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
                if (window.getMouseClickLocation().y > 440) { // pomeni da smo kliknili nekam v shopu
                    if(shooterShop.isItemPressed(window.getMouseWorldLocation())) player.setMode(1);
                    if (diagonalShop.isItemPressed(window.getMouseWorldLocation())) player.setMode(2);
                    if (plusShop.isItemPressed(window.getMouseWorldLocation())) player.setMode(3);
                }
                else{
                    if (Placeable::jeProsto(window.getMouseClickLocation().y / 50, window.getMouseClickLocation().x / 50)) {
                        DiagonalShooter * d = new DiagonalShooter;
                        PlusShooter * p = new PlusShooter;
                        ShooterTower * s = new ShooterTower;
                        switch (player.getMode()) {
                        case 1:
                            if (shooterShop.buyItem(player.getMoney())) {
                                player.setMoney(player.getMoney() - ShooterTower::getPrice());
                                s->place(float(window.getMouseClickLocation().x / 50 * 50 + 25), float(window.getMouseClickLocation().y / 50 * 50 + 25), 500, 480);
                                shooterList.vnos(*s);
                                Placeable::setProsto(window.getMouseClickLocation().y / 50, window.getMouseClickLocation().x / 50, 0);
                            }
                           // delete s;
                            delete p;
                            delete d;
                            break;

                        case 2:
                            if (diagonalShop.buyItem(player.getMoney())) {
                                player.setMoney(player.getMoney() - DiagonalShooter::getPrice());
                                d->place(float(window.getMouseClickLocation().x / 50 * 50 + 25), float(window.getMouseClickLocation().y / 50 * 50 + 25), 800, 580);
                                diagonalList.vnos(*d);
                                Placeable::setProsto(window.getMouseClickLocation().y / 50, window.getMouseClickLocation().x / 50, 0);
                            }
                            delete s;
                            delete p;
                           // delete d;
                            break;

                        case 3:
                            if (plusShop.buyItem(player.getMoney())) {
                                player.setMoney(player.getMoney() - PlusShooter::getPrice());
                                p->place(float(window.getMouseClickLocation().x / 50 * 50 + 25), float(window.getMouseClickLocation().y / 50 * 50 + 25), 1400, 600);
                                plusList.vnos(*p);
                                Placeable::setProsto(window.getMouseClickLocation().y / 50, window.getMouseClickLocation().x / 50, 0);
                            }
                            delete s;
                            //delete p;
                            delete d;
                            break;

                        default:
                            delete s;
                            delete p;
                            delete d;
                        }
                        //player.setMode(0);
                    }
                }
            }
            
            text = textSetup(text, "shop", sf::Color::Black, sf::Color::White);
            stats = textSetup(stats, "health :" + std::to_string(player.getHealth()) + " \n money: " + std::to_string(player.getMoney()) + "$\n score: " + std::to_string(player.getScore()) + "\n highscore: " + std::to_string(player.getHighscore()), sf::Color::Black, sf::Color::White);
            prices = textSetup(prices, std::to_string(ShooterTower::getPrice()) + "$ \t \t" + std::to_string(DiagonalShooter::getPrice()) + "$ \t \t" + std::to_string(PlusShooter::getPrice()) + "$", sf::Color::Yellow, sf::Color::Black);
            text.setPosition(5, 480.0);
            stats.setPosition(520, 480.0);
            prices.setPosition(15, 570.0);

            //vnasa enemije glede na to koliko tock smo dosegli
            if (player.getScore() < 50) {
                if (clock.getElapsedTime().asMilliseconds() > 1800) {
                    enemyList.vnos(enemy);
                    clock.restart();
                }
            }
            else if (player.getScore() < 100) {
                if (clock.getElapsedTime().asMilliseconds() > 1300) {
                    if (rand() % 10 < 6) enemyList.vnos(enemy);
                    else enemyList.vnos(enemy2);
                    clock.restart();
                }
            }
            else if (player.getScore() < 200) {
                if (clock.getElapsedTime().asMilliseconds() > 1000) {
                    if (rand() % 3 == 0) enemyList.vnos(enemy);
                    else if (rand() % 5 < 3) enemyList.vnos(enemy2);
                    else enemyList.vnos(enemy3);
                    clock.restart();
                }
            }
            else if (player.getScore() < 1000) {
                if (clock.getElapsedTime().asMilliseconds() > 800) {
                    if (rand() % 9 == 0) enemyList.vnos(enemy);
                    else if (rand() % 2 == 0) enemyList.vnos(enemy2);
                    else enemyList.vnos(enemy3);
                    clock.restart();
                }
            }
            else{
                if (clock.getElapsedTime().asMilliseconds() > 790) {
                    if (rand() % 13000 < player.getScore()) enemyList.vnos(enemy4);
                    if (rand() % 9 == 0) enemyList.vnos(enemy);
                    else if (rand() % 3 < 2) enemyList.vnos(enemy2);
                    else enemyList.vnos(enemy3);
                    clock.restart();
                }
            }

        }
        //za game over
        else {
        if (clock.getElapsedTime().asMilliseconds() % 2 == 0) text = textSetup(text, "game over!", sf::Color::Red, sf::Color::Black);
        else text = textSetup(text, "game over!", sf::Color::Black, sf::Color::Red);
        prices = textSetup(prices, "press  space \n to play again", sf::Color::Black, sf::Color::White);
        prices.setCharacterSize(50);
        prices.setPosition(100, 175);
        if (window.isSpacePressed()) {
            player.resetPlayer();
            diagonalList.deliteList();
            plusList.deliteList();
            shooterList.deliteList();
            enemyList.deliteList();
            enemyList.deliteList();
        }
    } 
        //rendering
        window.renderList(diagonalList);
        window.renderList(plusList);
        window.renderList(shooterList);
        window.renderList(enemyList);
        window.renderList(bulletList);
        window.renderText(text);
        window.renderText(prices);
        window.renderText(stats);
        window.renderSprite(shooterShop.getSprite());
        window.renderSprite(plusShop.getSprite());
        window.renderSprite(diagonalShop.getSprite());
        window.render();
    }
        return 0;
    }

