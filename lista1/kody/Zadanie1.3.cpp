#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip> // dla precyzji floatow
using namespace std;

int porownania = 0;     //tworzymy zmienne globalne
int przypisania = 0;

void RESETUJ() {        //funkcja zerujaca zmienne globalne po kazdym posortowaniu
    porownania = 0;
    przypisania = 0;
}

// dla kopca binarnego mamy pozycje:
int LEWA(int i) {           //pozycja lewego dziecka w drzewie binarnym
    return 2 * i + 1;
}

int PRAWA(int i) {          //pozycja prawego dziecka w drzewie binarnym
    return 2 * i + 2;
}

void HEAPIFY(float A[], int i, int n) {       //twirzymy tablice A, i - korzen, n - dlugosc
    int l = LEWA(i);                        //liczymy indeks lewego dziecka
    int p = PRAWA(i);                       //liczymy indeks prawego dziecka
    int naj = i;                            //zakladamy ze najwieksze to i
    przypisania += 3;

    if (l < n && A[l] > A[i]) {             //jesli lewe dziecko (mniejsze od n) jest większe niż i
        porownania++;
        naj = l;                            //to naj ustawiamy na l
        przypisania++;
    }

    if (p < n && A[p] > A[naj]) {           //jesli prawe dziecko (mniejsze od n) jest wieksze niz nasze naj
        porownania++;
        naj = p;                            //to naj ustawiamy na p
        przypisania++;
    }

    if (naj != i) {                         //jezeli naj nie rowna sie i
        porownania++;
        swap(A[i], A[naj]);                 //zamieniamy miejscami i z naszym nowym naj
        przypisania += 2;
        HEAPIFY(A, naj, n);                 //rekurencyjnie wywołujemy HEAPIFY
    }
}


void BUILD_HEAP(float A[], int n) {          //tworzymy tablice A dlugosci n
    for (int i = n / 2 - 1; i >= 0; i--) {   //iterujemy wstecz od srodka
        HEAPIFY(A, i, n);                    //wywolujemy HEAPIFY
    }
}

void HEAPSORT(float A[], int n) {            //tworzymy tablice A dlugosci n
    BUILD_HEAP(A, n);                        //budujemy kopiec z tablicy

    for (int i = n - 1; i >= 1; i--) {       //od 1 do n-1 wstecz
        swap(A[0], A[i]);                    //zamieniamy najwiekszy element kopca z A[i]
        przypisania += 2;
        n--;                                 //zmniejszamy rozmiar kopca
        przypisania++;
        HEAPIFY(A, 0, n);                    //wywolujemy HEAPIFY dla korzenia 0
    }
}

//dla kopca ternarnego mamy:
int LEWA_T(int i){                          //pozycja lewego dziecka w drzewie
    return 3 * i + 1;
}
int SRODEK_T (int i){                       //pozycja srodkowego dziecka w drzewie
    return 3 * i + 2;
}
int PRAWA_T(int i){                         //pozycja prawego dziecka w drzewie
    return 3 * i + 3;
}

void HEAPIFY_T(float A[], int i, int n) {   //tworzymy tablice A dlugosci n, z korzeniem i
    int l = LEWA_T(i);                      //liczymy indeks lewego dziecka
    int s = SRODEK_T(i);                    //liczymy indeks srodkowego dziecka
    int p = PRAWA_T(i);                     //liczymy indeks prawego dziecka
    int naj = i;                            //zakladamy ze nasz naj na starcie jest i
    przypisania += 4;

    if (l < n && A[l] > A[i]) {             //jesli l (mniesze od n) jest wieksze od i
        porownania++;
        naj = l;                            //l staje sie naszym naj
        przypisania++;
    }

    if (s < n && A[s] > A[naj]) {           //jesli s (mniejsze od n) jest wieksze od naszego naj
        porownania++;
        naj = s;                            //s staje sie naszym naj
        przypisania++;
    }

    if (p < n && A[p] > A[naj]) {           //jezeli p (mniejsze od n) jest wieksze od naj
        porownania++;
        naj = p;                            //p staje sie naszym naj
        przypisania++;
    }

    if (naj != i) {                         //jezeli naj nie jest juz najwieksze
        porownania++;
        swap(A[i], A[naj]);                 //zamieniamy pozycje A[i] z najwiekszym
        przypisania += 2;
        HEAPIFY_T(A, naj, n);               //rekurencyjne HEAPIFY
    }
}

void BUILD_HEAP_T(float A[], int n){        //tworzymy tablice A dlugosci n
    for (int i = n / 3 - 1; i >= 0; i--) {  //interujemy wstecz od 1/3 tablicy
        HEAPIFY_T(A, i, n);                 //wywolujemy HEAPIFY
    }
}

void HEAP_SORT_T(float A[], int n) {        //tworzymy tablice A dlugosci n
    BUILD_HEAP_T(A, n);                     //budujemy kopiec z tablicy

    for (int i = n - 1; i >= 1; i--) {      //od 1 do n-1 wstecz
        swap(A[0], A[i]);                   //zamieniamy najwiekszy element kopca z A[i]
        przypisania += 2;
        n--;                                //zmniejszamy rozmiar kopca
        przypisania++;
        HEAPIFY_T(A, 0, n);                 //wywolujemy HEAPIFY
    }
}

void WYPISZ_WYNIK(float A[], int n) {
    cout << "Liczba porownan: " << porownania << endl;
    cout << "Liczba przypisan: " << przypisania << endl;
}

void GENERATOR_TABLIC(float A[], int n) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        A[i] = static_cast<float>(rand()) / (RAND_MAX / 100000.0); // generowanie losowych floatów
    }
}

void WYPISZ_TABLICE(float* tab, int n) {
    for (int i = 0; i < n; i++) {
        cout << fixed << setprecision(2) << tab[i] << " ";
    }
    cout << endl;
}


int main() {
    int sizes[] = {10, 100, 1000, 10000, 50000}; // wielkosci tablic do testu
    for (int i = 0; i < 5; i++) {
        int n = sizes[i];
        float* A = new float[n]; // dynamiczne przechowywanie tablicy A o dlugosci n
        float* B = new float[n]; // dodatkowa tablica B do zapamiętania oryginalnej kolejności

        GENERATOR_TABLIC(A, n); // generujemy losowe liczby

        for (int j = 0; j < n; j++) {
            B[j] = A[j];
        }

        if (n == 10) {
            cout << "Oryginalna tablica A: ";
            WYPISZ_TABLICE(A, n);
            cout << "Kopia tablicy B: ";
            WYPISZ_TABLICE(B, n);
        }

        RESETUJ();
        clock_t start_time = clock();
        HEAPSORT(A, n);
        clock_t end_time = clock();
        double elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC * 1000; // w milisekundach
        cout << "HEAPSORT dla rozmiaru " << n << ":\n";
        cout << "Czas trwania: " << elapsed_time << " ms" << endl;
        WYPISZ_WYNIK(A, n);

        if (n == 10) {
            cout << "Posortowana tablica A po HEAPSORT: ";
            WYPISZ_TABLICE(A, n);
        }

        for (int j = 0; j < n; j++) {
            A[j] = B[j];
        }

        if (n == 10) {
            cout << "Tablica A przywrócona z B: ";
            WYPISZ_TABLICE(A, n);
        }

        RESETUJ();
        start_time = clock();
        HEAP_SORT_T(A, n);
        end_time = clock();
        elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC * 1000; // w milisekundach
        cout << "HEAP_SORT_T dla rozmiaru " << n << ":\n";
        cout << "Czas trwania: " << elapsed_time << " ms" << endl;
        WYPISZ_WYNIK(A, n);

        if (n == 10) {
            cout << "Posortowana tablica A po HEAP_SORT_T: ";
            WYPISZ_TABLICE(A, n);
        }

        delete[] A;
        delete[] B;
        cout << endl;
    }

    return 0;
}
