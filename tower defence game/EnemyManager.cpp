#include "EnemyManager.h"
#include "Enemy.h"

template<class T>

inline void EnemyManager<T>::vnos(T value)
{
    listObject* novi = new listObject;
    novi->data = value;
    if (start == nullptr && zaklj == nullptr) {
        start = novi;
        zaklj = novi;
        novi->prej = NULL;
        novi->nasl = NULL;

    }
    else {

        start->prej = novi;
        novi->nasl = start;
        novi->prej = NULL;
        start = novi;

    }
}

template<typename T>
void EnemyManager<T>::loop(sf::RenderWindow window)
{
    for (listObject* temp = start; temp != NULL; temp = temp->nasl) {
        window.draw(temp->data);
    }

}
