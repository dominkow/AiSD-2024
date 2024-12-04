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
        B[j] = LISTA();
        przypisania++;                                     //kazdy element B jest pusta lista
    }

    for (int i = 0; i < n; i++) {
        int index = static_cast<int>(n * A[i]);
        przypisania++;                                       //obliczamy indeks koszyka (n * A[i]), indeks to int!
        WEZEL* nowy_wezel = new WEZEL(A[i]);
        przypisania++;                                      //tworzymy nowy wezel z wartością A[i]
        B[index].LIST_INSERT(B[index], nowy_wezel);         //dodajemy element do odpowiedniego koszyka
    }

    for (int j = 0; j < n; j++) {                           //sortujemy insetion sortem dla list
        B[j].LIST_INSERTION_SORT(B[j]);
    }

    int s = 0;
    przypisania++;                                              //niech s to indeks w tablicy A
    for (int j = 0; j < n; j++) {
        WEZEL* element = B[j].head;
        przypisania++;                                       //bierzemy pierwszy element z listy B[j]
        while (element != nullptr) {
            porownania++;                                   //przechodzimy przez elemnty listy w tym koszyku
            A[s++] = element->wartosc;
            przypisania++;                                  //przypisujemy wartosc z elementu listy do A i zwiekszamy s (aby nastepny element byl o indkes dalej)
            element = element->next;
            przypisania++;                                  //przejscie do nastepnego elementu
        }
    }
    delete[] B;                                             //kasacja B
}

//modyfikacja dla bucket sorta aby dzialal dla dowolnych danych wejsciowych

void BUCKET_SORT_MOD(float A[], int n){
    float minimum = A[0];                       //tworzymy zmienne dla wartosci najwiekszej i najmniejszej (pierwsze tablicy)
    float maximum = A[0];
    przypisania+=2;

    for (int i = 1; i < n; i++) {
    if (A[i] < minimum) {                       //jesli badana wartosc jest mniejsza od minimum to sie nia staje
        porownania++;
        minimum = A[i];
        przypisania++;
    }

    if (A[i] > maximum) {                      //jesli badana wartosc jest wieksza od maksimum to sie nia staje
        porownania++;
        maximum = A[i];
        przypisania++;
    }
}
    if (maximum == minimum) {                  //jesli przeszlismy po calej liscie i minimu rowne minimu, to wszystkie
        for (int i = 0; i < n; i++) {          //wartosci tablicy sa takie same (nie ma zbytnio nic do roboty)
            porownania++;
            A[i] = minimum;
            przypisania++;
        }
        return;
    }
    LISTA* B = new LISTA[n];
    for (int j = 0; j < n; j++) {               // Inicjalizacja pustych list
        B[j] = LISTA();
        przypisania++;
    }

    for (int i = 0; i < n; i++) {
        int index = static_cast<int>(n * (A[i] - minimum) / (maximum - minimum));       //oblicz indeks kubelka
        przypisania++;
        if (index == n){
            porownania++;
            index = n - 1;                      //przypadek, gdy index=n, żeby był w kubełku n-1
            przypisania++;
        }
        WEZEL* nowy_wezel = new WEZEL(A[i]);
        przypisania++;                                      //tworzymy nowy wezel z wartością A[i]
        B[index].LIST_INSERT(B[index], nowy_wezel);         //wstawiamy wezel do odpowiedniego kubelka

    }

    for (int j = 0; j < n; j++) {                     //sortujemy insertion sortem na listach
        B[j].LIST_INSERTION_SORT(B[j]);
    }

    int s = 0;
    przypisania++;                                         //indeks w tablicy A
    for (int j = 0; j < n; j++) {
        WEZEL* element = B[j].head;
        przypisania++;                                    //bierzemy pierwszy element listy w kubelku
        while (element != nullptr) {
            porownania++;
            A[s++] = element->wartosc;
            przypisania++;                               //przepisujemy oryginalna wartosc z kubelka do tablicy
            element = element->next;
            przypisania++;                               //przechodzimy do nastepnego  elementu
        }
    }
    delete[] B;
}

void GENERATOR_TABLIC_1(float A[], int n) {
    srand(time(0));                                                     //inicjalizacja generatora losowego
    for (int i = 0; i < n; i++) {                                       //po kolei generujemy az do n
        A[i] = static_cast<float>(rand()) / RAND_MAX;             //static_cast<float> - przeksztalcamy na floata
                                                                        //liczbe calkowita generowana przez rand() / RAND_MAX
    }                                                                   //dostajemy liczbe od 0 do 1
}

void GENERATOR_TABLIC_2(float A[], int n) {
    srand(time(0));                                                     //inicjalizacja generatora losowego
    for (int i = 0; i < n; i++) {                                       //po kolei generujemy az do n
        A[i] = static_cast<float>(rand()) / RAND_MAX * 50000;
    }
}
void WYPISZ_TABLICE(float* A, int n) {
    for (int i = 0; i < n; i++) {
        cout << fixed << setprecision(3) << A[i] << " ";       //ustawiamy ze wyswietlane liczby w tablicy beda ze stale
    }                                                           //liczbe po przecinku (fixed) , 2 (setprecision)
    cout << endl;
}
void WYPISZ_WYNIK(float A[], int n) {
    cout << endl;
    cout << "Liczba porownan: " << porownania << endl;
    cout << "Liczba przypisan: " << przypisania << endl;
}

int main() {
    int n = 10;
    float C[n];

    // Generowanie tablicy losowych liczb
    GENERATOR_TABLIC_1(C, n);

    cout << "Tablica przed sortowaniem BUCKET_SORT:" << endl;
    for (int i = 0; i < n; i++) {
        cout << C[i] << " ";
    }
    cout << endl;

    // Sortowanie tablicy za pomocą Bucket Sort
    BUCKET_SORT(C, n);

    cout << "Tablica po sortowaniu BUCKET_SORT:" << endl;
    for (int i = 0; i < n; i++) {
        cout << C[i] << " ";
    }
    cout << endl;


    float D[n];

    // Generowanie tablicy losowych liczb
    GENERATOR_TABLIC_2(D, n);

    cout << "Tablica przed sortowaniem BUCKET_SORT_MOD:" << endl;
    for (int i = 0; i < n; i++) {
        cout << D[i] << " ";
    }
    cout << endl;

    // Sortowanie tablicy za pomocą Bucket Sort
    BUCKET_SORT_MOD(D, n);

    cout << "Tablica po sortowaniu BUCKET_SORT_MOD:" << endl;
    for (int i = 0; i < n; i++) {
        cout << D[i] << " ";
    }
    cout << endl;


    int sizes[] = {10000, 20000, 30000, 40000, 50000}; // wielkości tablic do testu
    for (int i = 0; i < 5; i++) {
        int n = sizes[i];
        float* A = new float[n]; // dynamiczne przechowywanie tablicy A o długości n
        float* B = new float[n]; // dodatkowa tablica B do zapamiętania oryginalnej kolejności

        GENERATOR_TABLIC_1(A, n); // generowanie losowe liczby dla Bucket Sort
        GENERATOR_TABLIC_2(B, n); // generowanie losowe liczby dla Bucket Sort MOD

        // Kopiowanie wygenerowanej tablicy A do B, aby zapamiętać początkową kolejność
        for (int j = 0; j < n; j++) {
            B[j] = A[j]; // kopiujemy dane z A do B
        }

        // Mierzenie czasu i liczenie przypisań i porównań dla standardowego Bucket Sort
        RESETUJ();
        clock_t start_time = clock();
        BUCKET_SORT(A, n); // używamy standardowego Bucket Sort na tablicy A
        clock_t end_time = clock();
        double elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC * 1000; // czas w milisekundach
        cout << "Bucket Sort dla rozmiaru " << n << ":\n";
        cout << "Czas trwania: " << elapsed_time << " ms" << endl;
        WYPISZ_WYNIK(A, n);

        // Mierzenie czasu i liczenie przypisań i porównań dla zmodyfikowanego Bucket Sort
        RESETUJ();
        start_time = clock();
        BUCKET_SORT_MOD(B, n); // używamy zmodyfikowanego Bucket Sort na tablicy B
        end_time = clock();
        elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC * 1000; // czas w milisekundach
        cout << "Bucket Sort MOD dla rozmiaru " << n << ":\n";
        cout << "Czas trwania: " << elapsed_time << " ms" << endl;
        WYPISZ_WYNIK(B, n);

        // Zwalnianie pamięci po zakończeniu testów dla jednej tablicy
        delete[] A;
        delete[] B;

        cout << endl; // oddzielenie wyników dla różnych rozmiarów tablic
    }

    return 0;
}

