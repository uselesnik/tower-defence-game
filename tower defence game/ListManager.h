#pragma once
#include "Enemy.h"
#include "Bullet.h"

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
    bool delite(unsigned long int x);

    unsigned long int getNextId();

    bool delitefromLoop(listObject* temp);

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
               // std::cout << "deliting(z):  "<< start->id <<"\n";
                delete start;
                start = zaklj = NULL;

            }
            else
            {
                start = start->nasl;
                //std::cout << "deliting:  " << start->prej->id << "\n";
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

template<typename T>
bool ListManager<T>::delite(unsigned long int x)
{
    if (start == zaklj && start != NULL && start->id == x){
       // std::cout << "deliting(z): " << start->id << "\n";
        delete start;
        start = zaklj = NULL;
        return 1;
    }
    listObject* temp;
    for (temp = zaklj; temp != NULL && temp->id != x; temp = temp->prej);//gre od zadaj naprej ker veckrat brisemo zadnji element na listu
   
    if (zaklj->id == x) {
        zaklj = zaklj->prej;
       // std::cout << "deliting: " << zaklj->nasl->id << "\n";
        delete zaklj->nasl;
        zaklj->nasl = NULL;
        return 1;
    }
    if (start->id == x) {
        start = start->nasl;
       // std::cout << "deliting: " << start->prej->id << "\n";
        delete start->prej;
        start->prej = NULL;
        return 1;
    }
    if (temp != NULL) { //element obstaja
        temp->nasl->prej = temp->prej;
        temp->prej->nasl = temp->nasl;
        //std::cout << "deliting: " << temp->id << "\n";
        delete temp;
        return 1;
    }
    std::cout << "nwm";
    return 0;
}

template<typename T>
inline unsigned long int ListManager<T>::getNextId()
{
    return idAssigner;
}

template<typename T>
inline bool ListManager<T>::delitefromLoop(listObject* temp)
{
    if (temp == start && temp == zaklj) { // edini element v listu
       // std::cout << "del.1" << temp->id;
        delite(temp->id);
        return 0; //return 0 pomeni da naj gre ven iz zunanjega loopa (temp = NULL)
    }
    else if (temp == start) { // prvi element v listu ampak ni edini
        temp = temp->nasl;
        delite(temp->prej->id);
        return 1; //return 2 pomeni da naj ostane na istem elementu naslednji cikel loopa
    }
    else {
        temp = temp->prej;
       // std::cout << "del.3" << temp->nasl->id;
        delite(temp->nasl->id); //izbrse katerikoli ostal element
        if (temp == zaklj) return 0;
        return 1; //return 1 pomeni naj nadaljuje z loopom
    }
}
