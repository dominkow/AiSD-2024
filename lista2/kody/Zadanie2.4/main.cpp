#include <iostream>
#include <ctime>    // dla inicjalizacji generatora liczb losowych
#include <cstdlib>  // generowanie losowych liczb
#include <iomanip> // dla precyzji floatow
using namespace std;

int przypisania = 0;
int porownania = 0;

void RESETUJ() {                            //funkcja zerujaca po kazdym posortowaniu tablicy
    porownania = 0;
    przypisania = 0;
}

//wezel - definicja elementu listy
struct WEZEL {
    float wartosc;      //przehowuje wartoœæ wezla w floacia
    WEZEL* prev;        //wskaznik na poprzedni wezel
    WEZEL* next;        //wskaznik na nastêpny wezel

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
};

//u gory copy-paste z zadania 3 struktura listy potrzebna do bucket sorta

//tu jedziemy z funkcja Bucket Sort
void BUCKET_SORT(float* A, int n) {
    LISTA* B = new LISTA[n];                                //pomocnicza tablica kubelkow

    for (int j = 0; j < n; j++) {
        B[j] = LISTA();                                     //kazdy element B jest pusta lista
    }

    for (int i = 0; i < n; i++) {
        int index = static_cast<int>(n * A[i]);             //obliczamy indeks koszyka (n * A[i]), indeks to int!
        B[index].LIST_INSERT(B[index], new WEZEL(A[i]));    //dodajemy element do odpowiedniego koszyka
    }

    for (int j = 0; j < n; j++) {                           //sortujemy insetion sortem dla list
        B[j].LIST_INSERTION_SORT(B[j]);
    }

    int s = 0;                                              //niech s to indeks w tablicy A
    for (int j = 0; j < n; j++) {
        WEZEL* element = B[j].head;                         //bierzemy pierwszy element z listy B[j]
        while (element != nullptr) {                        //przechodzimy przez elemnty listy w tym koszyku
            A[s++] = element->wartosc;                      //przypisujemy wartosc z elementu listy do A i zwiekszamy s (aby nastepny element byl o indkes dalej)
            element = element->next;                        //przejscie do nastepnego elementu
        }
    }
    delete[] B;                                             //kasacja B
}
int main() {
    int n = 10;
    float A[] = {0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68};

    cout << "Tablica przed sortowaniem:" << endl;
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << endl;

    BUCKET_SORT(A, n);

    cout << "Tablica po sortowaniu:" << endl;
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << endl;

    return 0;
}
