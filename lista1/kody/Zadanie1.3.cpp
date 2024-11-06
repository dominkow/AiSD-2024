#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int porownania = 0;     //tworzymy zmienne globalne
int przypisania = 0;

void RESETUJ() {        //funkcje zerujaca zmienne globalne po kazdym posortowaniu
    porownania = 0;
    przypisania = 0;
}
// dla kopca binarnego mamy pozycje:
int LEWA(int i) {           //pozycja lewego dziecka w drzewie binarnym
    return 2 * i;
    przypisania++;
}

int PRAWA(int i) {          //pozycja prawego dziecka w drzewie binarnym
    return 2 * i + 1;
    przypisania++;
}

void HEAPIFY(int A[], int i, int n) {       //twirzymy tablice A, i - korzen, n - dlugosc
    int l = LEWA(i);                        //liczymy indeks lewego dziecka
    int p = PRAWA(i);                       //liczymy indeks prawego dziecka
    int naj = i;                            //zakladamy ze najwieksze to i
    przypisania +=3;

    if (l < n && A[l] > A[i]) {             //jesli lewe dziecko (mniejsze od n) jest większe niż i
        porownania++;
        naj = l;                            //to naj ustawiamy na l
        przypisania++;
    }

    if (p < n && A[p] > A[naj]) {           //jesli prawe dziecko (mniejsze od n) jest wieksze niz nasze naj (ba naszym naj moze byc l nie i)
        porownania++;
        naj = p;                            //to naj ustawiamy na p
        przypisania++;
    }

    if (naj != i) {                         //jezeli naj nie rowna sie i (czyli sie zmienil, poprzez ify na gorze)
        porownania++;
        swap(A[i], A[naj]);                 //to zamieniamy miejscami i z naszym nowym naj
        przypisania +=2;
        HEAPIFY(A, naj, n);                 //wywołujemy rekurencyjnie HEAPIFY dla naj, aby sprawdzić,
                                            //czy poddrzewo również spełnia własność kopca.
    }
}


void BUILD_HEAP(int A[], int n) {               //tworzymy tablice A dlugosci c
    for (int i = n / 2 - 1; i >= 0; i--) {      //iterujemy wstecz od środka tablicy (n / 2 - 1)  do początku (0).
    HEAPIFY(A, i, n);                           //elementy od n / 2 do n - 1 to liście, które same w sobie spełniają własność kopca
    }                                           //wywołujemy HEAPIFY, by upewnić się, że poddrzewo z korzeniem i spełnia własność kopca

}

void HEAPSORT(int A[], int n) {                 //tworzymy tablice A dlugosci n
    BUILD_HEAP(A, n);                           //budujemy kopiec z tablicy

    for (int i = n - 1; i >= 1; i--) {          //od 1 do n-1 (od 2 i przedostatniego indeksu) wstecz
        swap(A[0], A[i]);                       //zamieniamy najwiekszy element kopca z A[i]
        przypisania +=2;
        n--;                                    //zmniejszamy rozmiar kopca bo ostatni element jest juz na swojej pozycji
        przypisania++;
        HEAPIFY(A, 0, n);                       //wywolujemy HEAPIFY dla korzenia 0 aby sprawdzic czy zachowana jest wlasciwosc kopca
    }
}

//dla kopca ternarnego mamy:
int LEWA_T(int i){                          //pozycja lewego dziecka w drzewie
    return 3 * i;
    przypisania++;
}
int SRODEK_T (int i){                       //pozycja srodkowego dziecka w drzewie
    return 3 * i + 1;
    przypisania++;
}
int PRAWA_T(int i){                         //pozycja prawego dziecka w drzewie
    return 3 * i + 2;
    przypisania++;
}

void HEAPIFY_T(int A[], int i, int n) {     //tworzymy tablice A dlugosci n, z korzeniem i
    int l = LEWA_T(i);                      //liczymy indeks lewego dziecka
    int s = SRODEK_T(i);                    //liczymy indeks srodkowego dziecka
    int p = PRAWA_T(i);                     //liczymy indeks prawego dziecka
    int naj = i;                            //zakladamy ze nasz naj na starcie jest i
    przypisania +=4;

    if (l < n && A[l] > A[i]) {             //jesli l (mniesze od n) jest wieksze od i
        porownania++;
        naj = l;                            //l staje sie naszym naj
        przypisania++;
    }

    if (s < n && A[s] > A[naj]) {           //jesli s (mniejsze od n) jest wieksze od naszego nowego/starego naj
        porownania++;
        naj = s;                            //s staje sie naszym naj
        przypisania++;
    }

    if (p < n && A[p] > A[naj]) {           //jezeli p (mniejsze od n) jest wieksze od naszego nowego/starego naj
        porownania++;
        naj = p;                            //p staje sie naszym naj
        przypisania++;
    }

    if (naj != i) {                         //jezeli naj nie jest juz najwieksze
        porownania++;
        swap(A[i], A[naj]);                 //to zamieniamy pozycje A[i] z naszym nowym najwiekszynm
        przypisania +=2;
        HEAPIFY_T(A, naj, n);               //wywolujemy rekurencyjne HEAPIFY aby sprawdzic czy wlasnosc korzenia jest zachowana

    }
}
void BUILD_HEAP_T(int A[], int n){          //tworzymy tablice A dlugosci n
    for (int i = n / 3 - 1; i >= 0; i--) {  //interujemy wstecz od 1/3 tablicy
        HEAPIFY_T(A, i, n);                 //wywolujemy HEAPIFY ...
    }
}
void HEAP_SORT_T(int A[], int n) {      //tworzymy tablice A dlugosci n
    BUILD_HEAP_T(A, n);                 //budujemy kopiec z tablicy

    for (int i = n - 1; i >= 1; i--) {  //od 1 do n-1 (od 2 i przedostatniego indeksu) wstecz
        swap(A[0], A[i]);               //zamieniamy najwiekszy element kopca z A[i]
        przypisania +=2;
        n--;                            //zmniejszamy rozmiar kopca bo ostatni element mamy uporzadkowany
        przypisania++;
        HEAPIFY_T(A, 0, n);             //wywolujemy HEAPIFY...
    }
}
void WYPISZ_WYNIK(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    srand(time(0));

    // Przyk³adowe rozmiary do testów
    int rozmiary[5] = {6, 8, 10, 12, 15};
    int proby = 5;

    cout << "Test binarnego HEAP_SORTA:" << endl;
    for (int i = 0; i < proby; i++) {
        int n = rozmiary[i];
        int arr[n];
        for (int j = 0; j < n; j++) {
            arr[j] = rand() % 100; // Losowe liczby od 0 do 19
        }

        RESETUJ();
        HEAPSORT(arr, n);
        cout << "Proba " << i + 1 << " dla " << n << " elementow:" << endl;
        WYPISZ_WYNIK(arr, n);
        cout << endl;
    }

    // Zak³adamy, ¿e mamy te¿ zmodyfikowan¹ wersjê HEAP_SORT_BIN, jeœli jest dostêpna
    // Funkcjê mo¿na pomin¹æ, jeœli HEAP_SORT_BIN nie istnieje
    cout << "Test ternarnego HEAP_SORT):" << endl;
    for (int i = 0; i < proby; i++) {
        int n = rozmiary[i];
        int arr[n];
        for (int j = 0; j < n; j++) {
            arr[j] = rand() % 100; // Losowe liczby od 0 do 19
        }

        RESETUJ();
        HEAP_SORT_T(arr, n); // Zamieñ na HEAP_SORT_BIN, jeœli jest dostêpna
        cout << "Proba " << i + 1 << " dla " << n << " elementow:" << endl;
        WYPISZ_WYNIK(arr, n);
        cout << endl;
    }

    return 0;
}
