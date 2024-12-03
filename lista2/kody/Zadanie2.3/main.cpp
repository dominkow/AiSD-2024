#include <iostream>
#include <cstdlib> // Dla funkcji rand()
#include <ctime>   // Dla funkcji time()
using namespace std;

// Definicja węzła
struct WEZEL {
    double wartosc; // Wartość przechowywana w węźle
    WEZEL* prev;    // Wskaźnik na poprzedni węzeł
    WEZEL* next;    // Wskaźnik na następny węzeł

    WEZEL(double war) : wartosc(war), prev(nullptr), next(nullptr) {} // Konstruktor
};

// Definicja listy
struct LISTA {
    WEZEL* head;                // Wskaźnik na pierwszy element listy
    LISTA() : head(nullptr) {}  // Konstruktor - pusta lista


// Dodawanie elementu do listy
    void LIST_INSERT(LISTA& lista, WEZEL* x) {
        x->next = lista.head;
        x->prev = nullptr;
        if (lista.head == nullptr) {
            lista.head = x;
        } else {
            lista.head->prev = x;
            lista.head = x;
        }
    }

// Usuwanie elementu z listy
    void LISTA_DELATE(LISTA& lista, WEZEL* x) {
        if (x->prev != nullptr) {
            x->prev->next = x->next;
        } else {
            lista.head = x->next;
        }
        if (x->next != nullptr) {
            x->next->prev = x->prev;
        }
        delete x;
    }

// Wyszukiwanie elementu w liście
    WEZEL* LIST_SEARCH(LISTA& lista, double k) {
        WEZEL* x = lista.head;
        while (x != nullptr && x->wartosc != k) {
            x = x->next;
        }
        return x;
    }

// Drukowanie listy
    void PRINT_LIST(LISTA& lista) {
        WEZEL* x = lista.head;
        while (x != nullptr) {
            cout << x->wartosc << " ";
            x = x->next;
        }
        cout << endl;
    }

    // Sortowanie listy metodą Insertion Sort
    void LIST_INSERTION_SORT(LISTA& lista) {
        if (lista.head == nullptr || lista.head->next == nullptr) {
            return; // Lista pusta lub z jednym elementem, już posortowana
        }

        WEZEL* current = lista.head->next; // Zaczynamy od drugiego elementu
        while (current != nullptr) {
            double key = current->wartosc; // Klucz do wstawienia
            WEZEL* prev = current->prev;   // Porównujemy z poprzednimi elementami

            // Przesuwamy węzły o większej wartości w prawo
            while (prev != nullptr && prev->wartosc > key) {
                prev->next->wartosc = prev->wartosc;
                prev = prev->prev;
            }

            // Wstawiamy klucz w odpowiednie miejsce
            if (prev == nullptr) {
                lista.head->wartosc = key; // Na początek listy
            } else {
                prev->next->wartosc = key; // Do miejsca po `prev`
            }

            current = current->next; // Przechodzimy do kolejnego elementu
        }
    }

    // Tworzenie losowej listy
    void STWORZ_LOSOWA_LISTE(LISTA& lista, int liczba_elementow, int min_wartosc, int max_wartosc) {
        srand(time(nullptr)); // Inicjalizacja generatora liczb losowych
        for (int i = 0; i < liczba_elementow; ++i) {
            int wartosc = min_wartosc + rand() % (max_wartosc - min_wartosc + 1);
                LIST_INSERT(lista, new WEZEL(wartosc));
        }
    }
};
int main() {
    LISTA lista;

    // Tworzenie losowej listy z 10 elementami, wartości w przedziale 1 do 100
    lista.STWORZ_LOSOWA_LISTE(lista, 10, 1.0, 100.0);

    cout << "Lista przed sortowaniem: ";
    lista.PRINT_LIST(lista);

    // Sortowanie
    lista.LIST_INSERTION_SORT(lista);

    cout << "Lista po sortowaniu: ";
    lista.PRINT_LIST(lista);

    return 0;
}

