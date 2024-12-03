#include <iostream>
#include <cstdlib> // Dla funkcji rand()
#include <ctime>   // Dla funkcji time()
using namespace std;

//wezel - definicja elementu listy
struct WEZEL {
    float wartosc;      //przehowuje wartość wezla w floacia
    WEZEL* prev;        //wskaznik na poprzedni wezel
    WEZEL* next;        //wskaznik na następny wezel

    WEZEL(float war) : wartosc(war), prev(nullptr), next(nullptr) {} // Konstruktor wskaznika
    //pozwala na utworzenie wezla z okreslona wartoscia war, jako ze nowy wezel nie jest z niczym powiazany to next i
    //prev oznaczamy jaklo puste
};

//stworzenie listy oraz podfunkcji (?) tworzace ta liste
struct LISTA {
    WEZEL* head;                //wskaznik na pierwszy element listy (glowa - z wykladu)
    LISTA() : head(nullptr) {}  //zainicjowanie pustej listy


    //pseudokod z wykladu (1 do 1) na dodawanie elementu do listy
    void LIST_INSERT(LISTA& lista, WEZEL* x) {          //alias dla listy
        x->next = lista.head;                           //nowy wezel ustawiony na head, bo nowy element bedzie nowym poczatkiem listy
        x->prev = nullptr;                              //wezel nie ma poprzednika wiec nil
        if (lista.head == nullptr) {                    //sprawdzamy czy list jest pusta
            lista.head = x;                             //jesli tak to glowa, x to nasz pierwszy element
        } else {                                        //jesli nie to ustawiamy jako poprzednika naszje glowy x
            lista.head->prev = x;
            lista.head = x;                             //x to nowy poczatek listy
        }
    }

    //pseudokod z wykladu (1 do 1) na usuwanie elementu z listy
    void LISTA_DELATE(LISTA& lista, WEZEL* x) {
        if (x->prev != nullptr) {                       //jesli wezel nie jest pierwszy to
            x->prev->next = x->next;                    //poprzedni wezel staje sie nastepnym wezlem
        } else {
            lista.head = x->next;                       //jesli wezel jest pierwszy to glowe przesuwamy na nexta
        }
        if (x->next != nullptr) {                       //jesli nastepnik istnieje (wezel nie jest ostatni)
            x->next->prev = x->prev;                    //nastepny wezel next staje sie wezlem prev
        }
        delete x;                                       //zwalniamy pamiec
    }

    //pseudokod z wykladu (1 do 1) na szukanie elementu w liscie
    WEZEL* LIST_SEARCH(LISTA& lista, float k) {
        WEZEL* x = lista.head;                          //start od poczatku listy
        while (x != nullptr && x->wartosc != k) {       //przechodzimy az znajdziemy wezel o wartosci k lub dotrzemy do konca
            x = x->next;
        }
        return x;                                       //zwracamy znaleziony wezel
    }

    //pseudokod z drukowania elementu
    void PRINT_LIST(LISTA& lista) {                     //zaczynamy od poczatku i dopuki nie dotrzemy
        WEZEL* x = lista.head;                          //do konca to wypisujemy wartosc wezla i przechodzimy do nastepnego
        while (x != nullptr) {
            cout << x->wartosc << " ";
            x = x->next;
        }
        cout << endl;
    }

    //implementacja insertion sorta na strukturze listy
    void LIST_INSERTION_SORT(LISTA& lista) {
        if (lista.head == nullptr || lista.head->next == nullptr) {
            return;                                                 //lista pusta lub z jednym elementem (posortowana)
        }
        WEZEL* element = lista.head->next;                          //zaczynamy od drugiego elementu (bo pierwszy jest posortowany)
        while (element != nullptr) {                                //lecimy po wszystkich elementach
            float key = element->wartosc;                           //klucz do wstawienia, przechowuje wartosc aktualnego wezla
            WEZEL* prev = element->prev;                            //wskaznik na el. znajdujacy sie przed element (do porownywania z poprzednimi elementami)

            while (prev != nullptr && prev->wartosc > key) {        //sprawdzamy czy wartosc w wezlie prev jest wieksza niz key
                prev->next->wartosc = prev->wartosc;                //jesli jest to przesuwamy ja w prawo do biezacego wezla
                prev = prev->prev;                                  //prev przesuwamy do jeszcze wczesniejszego wezla
            }

            if (prev == nullptr) {                                  //osiagniecie poczatku listy
                lista.head->wartosc = key;                          //wstawiamy key jako pierwsza wartosc
            } else {
                prev->next->wartosc = key;                          //jesli nie to wstawiamy key za wezlem prev
            }

            element = element->next;                                //przechodzimy do kolejnego elementu
        }
    }

    //funkcja tworzaca losowa liste
    void LOSOWA_LISTA(LISTA& lista, int liczba_elementow, int min_wartosc, int max_wartosc) {
        srand(time(nullptr));                                       // Inicjalizacja generatora liczb losowych
        for (int i = 0; i < liczba_elementow; ++i) {                //petla dziala tyle ile elementow
            float wartosc = min_wartosc + static_cast<float>(rand()) / RAND_MAX * (max_wartosc - min_wartosc);  //generujemy floata
                LIST_INSERT(lista, new WEZEL(wartosc));             //tworzenie nowego wezla i dodanie go do listy
        }
    }
};

int main() {
    //inicjalizacja list
    LISTA lista1, lista2, lista3;

    //tworzenie i sortowanie list
    cout << "Lista 10 elementow (przed sortowaniem):" << endl;
    lista1.LOSOWA_LISTA(lista1, 10, 0, 1000);
    lista1.PRINT_LIST(lista1);
    lista1.LIST_INSERTION_SORT(lista1);
    cout << "Lista 10 elementow (po sortowaniu):" << endl;
    lista1.PRINT_LIST(lista1);

    cout << "\nLista 20 elementow (przed sortowaniem):" << endl;
    lista2.LOSOWA_LISTA(lista2, 20, 0, 1000);
    lista2.PRINT_LIST(lista2);
    lista2.LIST_INSERTION_SORT(lista2);
    cout << "Lista 20 elementow (po sortowaniu):" << endl;
    lista2.PRINT_LIST(lista2);

    cout << "\nLista 30 elementow (przed sortowaniem):" << endl;
    lista3.LOSOWA_LISTA(lista3, 30, 0, 1000);
    lista3.PRINT_LIST(lista3);
    lista3.LIST_INSERTION_SORT(lista3);
    cout << "Lista 30 elementow (po sortowaniu):" << endl;
    lista3.PRINT_LIST(lista3);

    return 0;
}
