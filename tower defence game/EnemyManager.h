#pragma once
#include "Enemy.h"

template <typename T>



class EnemyManager
{
    struct  listObject {
        listObject* nasl, * prej;
        T data;
    };

    listObject* start;
    listObject* zaklj;
public:

    void vnos(T value);
    void loop(sf::RenderWindow window);

/*



template <typename T>
void vnos(T value) {
    Uhu<T>* novi = new Uhu<T>;
    novi->data = value;
    if (start<T> == nullptr && zaklj<T> == nullptr) {
        start<T> = novi;
        zaklj<T> = novi;
        novi->prej = NULL;
        novi->nasl = NULL;
        std::cout << "zacetni\n";
    }
    else {
     
        start<T>->prej = novi;
        novi->nasl = start<T>;
        novi->prej = NULL;
        start<T> = novi;
        std::cout << "zdej pa mas memory leak ;)\n";
    }
}
template <typename T>
void loop() {
    for (Uhu<T>* temp = start<T>; temp != NULL; temp = temp->nasl) {
        std::cout << temp->data << " ";
    }
}

	*/

};

