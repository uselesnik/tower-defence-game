#pragma once
#include "Enemy.h"

template <typename T>

class ListManager
{
    unsigned long int idAssigner;
    static int steviloObj;
   // unsigned 
public:
    struct  listObject {
        listObject* nasl, * prej;
        T data;
        unsigned long int id;
    };
 
    ListManager();
    ~ListManager();
    
 
    static void setStObj(int i);
    static int getStObj();

    void vnos(T value);
   
    listObject* start;
    listObject* zaklj;
};




	// metode so definirane tukaj ker linker ne more povezati classa s templati do .cpp datoteke (VS error 2001)

template<typename T>
ListManager<T>::ListManager()
{
    idAssigner = 0;
    steviloObj++;
    start = NULL;
    zaklj = NULL;
}

template<typename T>
ListManager<T>::~ListManager()
{
   if (steviloObj > 1) {
        steviloObj--;
    }
    else {
        steviloObj--;
        while (start != NULL && zaklj != NULL) {

            if (start == zaklj) //zbrise zadnji element
            {
                std::cout << "deliting(z):  "<< start->id <<"\n";
                delete start;
                start = zaklj = NULL;

            }
            else
            {
                start = start->nasl;
                std::cout << "deliting:  " << start->prej->id << "\n";
                delete start->prej;
                start->prej = NULL;
            }
        }
    }
}


template<typename T>
void ListManager<T>::setStObj(int i)
{
    steviloObj = i;
}

template<typename T>
int ListManager<T>::getStObj()
{
    return steviloObj;
}

template<typename T>
void ListManager<T>::vnos(T value)
{
    listObject* novi = new listObject;
    novi->id = idAssigner;
    idAssigner++;
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



