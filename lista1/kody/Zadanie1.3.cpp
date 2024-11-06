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
void WYPISZ_WYNIK(int A[], int n) {
//    cout << "Posortowana tablica: ";
//    for (int m = 0; m < n; m++) {
//        cout << A[m] << " ";
//    }
    cout << endl;
    cout << "Liczba porownan: " << porownania << endl;
    cout << "Liczba przypisan: " << przypisania << endl;
}

void GENERATOR_TABLIC(int A[], int n) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 100001;
    }
}


int main() {
    int sizes[] = {10, 100, 1000, 10000, 50000}; // wielkosci tablic do testu
    for (int i = 0; i < 5; i++) {
        int n = sizes[i];
        int* A = new int[n]; // dynamiczne przechowywanie tablicy A o dlugosci n
        GENERATOR_TABLIC(A, n); // generujemy losowe liczby

        // Mierzenie czasu i liczenie przypisan i porównan dla standardowego HEAPSORT
        RESETUJ();
        clock_t start_time = clock();
        HEAPSORT(A, n); // poprawne wywołanie HEAPSPORT z zakresem (0, n-1)
        clock_t end_time = clock();
        double elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC * 1000; // w milisekundach
        cout << "HEAPSORT dla rozmiaru " << n << ":\n";
        cout << "Czas trwania: " << elapsed_time << " ms" << endl;
        WYPISZ_WYNIK(A, n);

        // Ponownie generujemy
        GENERATOR_TABLIC(A, n);

        // Mierzenie czasu i liczenie przypisan oraz porownan dla HEAP_SORT_T
        RESETUJ();
        start_time = clock();
        HEAP_SORT_T(A, n); // poprawne wywolanie HEAP_SORT_T z zakresem (0, n-1)
        end_time = clock();
        elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC * 1000; // w milisekundach
        cout << "HEAP_SORT_T dla rozmiaru " << n << ":\n";
        cout << "Czas trwania: " << elapsed_time << " ms" << endl;
        WYPISZ_WYNIK(A, n);

        delete[] A; // zwalniamy pamiec, usuwajac tablice A
        cout << endl;
    }

    return 0;
}
