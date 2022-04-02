#pragma once
#include "Enemy.h"

template <typename T>

class ListManager
{
    struct  listObject {
        listObject* nasl, * prej;
        T data;
    };

    listObject* start;
    listObject* zaklj;
public:
 
    ListManager();
    ~ListManager();


    void vnos(T value);
    void loop();
};


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
*/


	// metode so definirane tukaj ker linker ne more povezati classa s templati do .cpp datoteke (VS error 2001)

template<typename T>
ListManager<T>::ListManager()
{
    start = NULL;
    zaklj = NULL;
}

template<typename T>
ListManager<T>::~ListManager()
{
    while (start != NULL && zaklj != NULL) {

        if (start == zaklj) //zbrise zadnji element
        {
            std::cout << "deliting(z): " << start->data << "\n";
            delete start;
            start = zaklj = NULL;
        }
        else 
        {
            start = start->nasl;
            std::cout << "deliting: " << start->prej->data<< "\n";
            delete start->prej;
            start->prej = NULL;
        }
    }
}

template<typename T>
void ListManager<T>::vnos(T value)
{
    listObject* novi = new listObject;
    novi->data = value;
    if (start == nullptr && zaklj == nullptr) { //vstavljamo v prazen list
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
void ListManager<T>::loop()
{
    for (listObject* temp = start; temp != NULL; temp = temp->nasl) {
        std::cout << temp->data << " ";
    }
}

