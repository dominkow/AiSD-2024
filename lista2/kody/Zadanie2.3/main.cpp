#include <iostream>
using namespace std;

int porownania = 0;
int przypisania = 0;

void RESETUJ() {
    porownania = 0;
    przypisania = 0;
}

//definicja wêz³a dla listy (na wskaŸnikach) - jeden element listy
//struct sluzy do tworzenia struktur danych

struct WEZEL {
    double wartosc;       //wartoœæ przechowywana w wêŸle
    WEZEL* prev;          //wskaŸnik na poprzedni wêze³
    WEZEL* next;          //wskaŸnik na nastêpny wêze³

    WEZEL(double war) : wartosc(war), prev(nullptr), next(nullptr) {}    //konstruktor wezla

    //WEZEL przyjmuje war, inicjujacy pole wartosc,
    //inicjalizuje pole wartosc wartoœci¹ przekazan¹ w parametrze war
    //inicjalizuje wskaŸnik prev wartoœci¹ nullptr - wêze³ nie ma na pocz¹tku poprzednika
    //to samo dla wskaznika next - wezel nie ma na poczatku nastepcy
};
//
struct LISTA {
    WEZEL* head;                                //wskaŸnik na pierwszy element listy
    LISTA() : head(nullptr) {}                  //konstruujemy pust¹ listê
};

//pseudokod z wykladu (1 do 1) funkcji dodajacej element do list
void LIST_INSERT(LISTA& lista, WEZEL* x ){      //x to wskaznik odwolujacy sie do WEZEL w naszej liscie, lista to alias
    x->next = lista.head;                       //nowy wezel wskazuje na aktualna "g³owê" listy
    x->prev = nullptr;                          //nowy wezel nie ma poprzednika (bedzie na poczatku listy)
                                                //nullptr to NIL z wykladu
    if (lista.head == nullptr) {
        lista.head = x;                         //jesli lista jest pusta to nowy wezel staje siê pierwszym elementem listy
    } else {
        lista.head->prev = x;                   //poprzedni pierwszy wezel wskazuje na nowy wezel
        lista.head = x;                         //nowy wezel staje siê "g³ow¹" listy
    }
}

//pseudokod z wykladu (1 do 1) funkcji usuwajacy element z listy
void LISTA_DELATE(LISTA& lista, WEZEL* x) {                 //wskaznik x na element do usuniecia z listy
    if (x->prev != nullptr){                                //sprawdzamy czy wezel ma poprzednika, jesli ma to
        x->prev->next = x->next;                            //ustawiamy wskaznik next na wezel nastepujacy po x, usuwajac x
    } else {
        lista.head = x->next;                               //jesli nie ma poprzednika, to usuwamy glowe i przenosimy ja
    }                                                       //na nastepny wezel
    if (x->next != nullptr){                                //sprawdzamy czy nastepnik istnieje
        x->next->prev = x->prev;                            //jesli x nie jest ostatnim wezlem to chcemy ustawic wskaŸnik
    }                                                       //prev nastêpnego wêz³a na wêze³ przed x (x->prev)
    delete x;                                               //po unormowaniu wskaznikow w wezlach usuwamy x
}

//funkcja drukujaca, wyswietlajaca liste
void PRINT_LIST(LISTA& lista) {
    WEZEL* x = lista.head;
    while (x != nullptr) {
        cout << x->wartosc << " ";
        x = x->next;
    }
    cout << endl;
}

//pseudokod z wykladu (1 do 1) funckji szukajcej elemntu listy
WEZEL* LIST_SEARCH(LISTA& lista, double k){                 //funckja zwraca wskaznik na wezel w liscie
    WEZEL* x = lista.head;                                  //wskaznik na pierwszy element listy
    while (x != nullptr && x->wartosc != k){                //sprawdza czy dotarlismy do konca listy
        x = x->next;                                        //jesli aktualny wezel nie ma wartosci k to przechodzimy do nastepnego wezla
    }
    return x;                                               //zwracamy wezel
}

// Funkcja sortuj¹ca listê metod¹ Insertion Sort
void INSERTION_SORT(LISTA& lista) {
    if (lista.head == nullptr || lista.head->next == nullptr) {
        return;                                                     //lista jest pusta lub ma tylko jeden element
    }

    WEZEL* x = lista.head->next;                                    //rozpoczynamy od drugiego elementu
    while (x != nullptr) {                                          //sprawdzamy czy x istnieje
        WEZEL* temp = x;                                            //
        x = x->next;

