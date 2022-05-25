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
    text.setCharacterSize(24);
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
    sf::Text text, prices, healthText, moneyText, scoreText;
    font.loadFromFile("superstar.ttf");
    text.setFont(font);
    prices.setFont(font);
    healthText.setFont(font);
    moneyText.setFont(font);
    scoreText.setFont(font);
    Player player;

    ShopItem shooterShop(1);
    ShopItem diagonalShop(2);
    ShopItem plusShop(3);  
    ShopItem deleteButton(4);
    ShopItem cancelButton(5);

    shooterShop.setPosition(32, 536);
    diagonalShop.setPosition(120, 536);
    plusShop.setPosition(212, 536);
    deleteButton.setPosition(295, 536);
    cancelButton.setPosition(410, 536);

    sf::Texture selectedTexture;
    sf::Sprite selected;
    selectedTexture.loadFromFile("images\\selected.png");
    selected.setTexture(selectedTexture);
    selected.setOrigin(24, 24);
    selected.setPosition(cancelButton.getSprite().getPosition());

    sf::Texture shopTexture;
    sf::Sprite shop;
    shopTexture.loadFromFile("images\\shop.png");
    shop.setTexture(shopTexture);
    shop.setPosition(0, 452);

    ListManager<Bullet> bulletList;
    ListManager<Enemy> enemyList;
    ListManager<ShooterTower> shooterList;
    ListManager<PlusShooter> plusList;
    ListManager<DiagonalShooter> diagonalList;

    // program traja dokler je okno odprto

    while (window.open()) {

        window.update();
        if (player.getHealth() > 0) {

            text = textSetup(text, "shop: \t \t \t \t   delete: \t cancel:", sf::Color::Cyan, sf::Color::Black);
            healthText = textSetup(healthText, " health :" + std::to_string(player.getHealth()), sf::Color::Red, sf::Color::Black);
            moneyText = textSetup(moneyText, "\n money: " + std::to_string(player.getMoney()) + "$", sf::Color::Green, sf::Color::Black);
            scoreText = textSetup(scoreText, "\n\n score: " + std::to_string(player.getScore()) + "\n highscore: " + std::to_string(player.getHighscore()), sf::Color::Yellow, sf::Color::Black);
            prices = textSetup(prices, std::to_string(ShooterTower::getPrice()) + "$  \t" + std::to_string(DiagonalShooter::getPrice()) + "$  \t" + std::to_string(PlusShooter::getPrice()) + "$", sf::Color::Green, sf::Color::Black);
            text.setPosition(5, 480.0);
            scoreText.setPosition(520, 480.0);
            moneyText.setPosition(520, 480.0);
            healthText.setPosition(520, 480.0);
            prices.setPosition(15, 570.0);

            //preverja ce je kaksen enemy prisel do konca poti in ga izbrise
            for (ListManager<Enemy>::listObject* temp = enemyList.start; temp != NULL;) {
                if (!temp->data.followPath()) { //pomeni da je na koncu poti in ga je potrebno izbrisati
                    player.setHealth(player.getHealth() - temp->data.getPoints() * 4);
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
                                player.setMoney(player.getMoney() + points * 3);
                                player.setScore(player.getScore() + points);
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
                if (window.getMouseClickLocation().y > 440) {// pomeni da smo kliknili nekam v shopu
                    if (shooterShop.isItemPressed(window.getMouseWorldLocation())) {
                        player.setMode(1);
                        selected.setPosition(shooterShop.getSprite().getPosition());
                        //std::cout << player.getMode();
                    }
                    if (diagonalShop.isItemPressed(window.getMouseWorldLocation())) {
                        player.setMode(2);
                        selected.setPosition(diagonalShop.getSprite().getPosition());
                        //std::cout << player.getMode();
                    }
                    if (plusShop.isItemPressed(window.getMouseWorldLocation())) {
                        player.setMode(3);
                        selected.setPosition(plusShop.getSprite().getPosition());
                        //std::cout << player.getMode();
                    }
                    if (cancelButton.isItemPressed(window.getMouseWorldLocation())) {
                        player.setMode(0);
                        selected.setPosition(cancelButton.getSprite().getPosition());
                        //std::cout << player.getMode();
                    }
                    if (deleteButton.isItemPressed(window.getMouseWorldLocation())) {
                        player.setMode(4);
                        selected.setPosition(deleteButton.getSprite().getPosition());
                        //std::cout << player.getMode();
                    }
                }


                else {
                    if (Placeable::jeProsto(window.getMouseClickLocation().y / 50, window.getMouseClickLocation().x / 50) || player.getMode() == 4) {
                        DiagonalShooter* d = new DiagonalShooter;
                        PlusShooter* p = new PlusShooter;
                        ShooterTower* s = new ShooterTower;
                        bool found = 0; //za deletanje
                        switch (player.getMode()) {
                        case 1:
                            if (shooterShop.buyItem(player.getMoney())) {
                                player.setMoney(player.getMoney() - ShooterTower::getPrice());
                                s->place(float(window.getMouseClickLocation().x / 50 * 50 + 25), float(window.getMouseClickLocation().y / 50 * 50 + 25), 500, 480);
                                shooterList.vnos(*s);
                                Placeable::setProsto(window.getMouseClickLocation().y / 50, window.getMouseClickLocation().x / 50, 0);
                            }
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
                            break;

                        case 3:
                            if (plusShop.buyItem(player.getMoney())) {
                                player.setMoney(player.getMoney() - PlusShooter::getPrice());
                                p->place(float(window.getMouseClickLocation().x / 50 * 50 + 25), float(window.getMouseClickLocation().y / 50 * 50 + 25), 1400, 600);
                                plusList.vnos(*p);
                                Placeable::setProsto(window.getMouseClickLocation().y / 50, window.getMouseClickLocation().x / 50, 0);
                            }
                            delete s;
                            delete d;
                            break;
                        case 4:

                            for (ListManager<ShooterTower>::listObject* temp = shooterList.start; temp != NULL;) {
                                if (temp->data.getSprite().getGlobalBounds().contains(window.getMouseWorldLocation())) {
                                    found = 1;
                                    Placeable::setProsto(window.getMouseClickLocation().y / 50, window.getMouseClickLocation().x / 50, 1);
                                    player.setMoney(player.getMoney() + ShooterTower::getPrice() / 2);
                                    shooterList.delite(temp->id);
                                    temp = NULL;
                                }
                                else  temp = temp->nasl;
                            }
                            if (found == 0) {
                                for (ListManager<DiagonalShooter>::listObject* temp = diagonalList.start; temp != NULL;) {
                                    if (temp->data.getSprite().getGlobalBounds().contains(window.getMouseWorldLocation())) {
                                        found = 1;
                                        Placeable::setProsto(window.getMouseClickLocation().y / 50, window.getMouseClickLocation().x / 50, 1);
                                        player.setMoney(player.getMoney() + DiagonalShooter::getPrice() / 2);
                                        diagonalList.delite(temp->id);
                                        temp = NULL;
                                    }
                                    else temp = temp->nasl;
                                }
                            }
                            if (found == 0) {
                                for (ListManager<PlusShooter>::listObject* temp = plusList.start; temp != NULL;) {
                                    if (temp->data.getSprite().getGlobalBounds().contains(window.getMouseWorldLocation())) {
                                        found = 1;
                                        Placeable::setProsto(window.getMouseClickLocation().y / 50, window.getMouseClickLocation().x / 50, 1);
                                        player.setMoney(player.getMoney() + PlusShooter::getPrice() / 2);
                                        plusList.delite(temp->id);
                                        temp = NULL;
                                    }
                                    else temp = temp->nasl;
                                }
                            }
                            delete s;
                            delete p;
                            delete d;
                            break;

                        default:
                            delete s;
                            delete p;
                            delete d;
                        }
                    }
                }
            }
        
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
            //rendering
            window.renderList(diagonalList);
            window.renderList(plusList);
            window.renderList(shooterList);
            window.renderList(enemyList);
            window.renderList(bulletList);
            window.renderSprite(shop);
            window.renderText(healthText);
            window.renderText(scoreText);
            window.renderText(moneyText);
            window.renderSprite(shooterShop.getSprite());
            window.renderSprite(plusShop.getSprite());
            window.renderSprite(diagonalShop.getSprite());
            window.renderSprite(cancelButton.getSprite());
            window.renderSprite(deleteButton.getSprite());
            window.renderSprite(selected);
        }
        //za game over
        else {
        text = textSetup(text, "game over!", sf::Color::Black, sf::Color::Red);
        text.setCharacterSize(52);
        prices = textSetup(prices, "press  space to play again", sf::Color::Black, sf::Color::White);
        prices.setCharacterSize(52);
        text.setPosition(64, 500);
        prices.setOutlineThickness(2);
        prices.setPosition(100, 175);
        if (window.isSpacePressed()) {
            player.resetPlayer();
            diagonalList.deliteList();
            plusList.deliteList();
            shooterList.deliteList();
            enemyList.deliteList();
            enemyList.deliteList();
            Placeable::initProsto();
        }
    } 
        //rendering
        window.renderText(healthText);
        window.renderText(scoreText);
        window.renderText(moneyText);
        window.renderText(text);
        window.renderText(prices);
        window.render();
    }
        return 0;
    } 

