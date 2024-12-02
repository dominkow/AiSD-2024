#include <iostream>
#include <ctime>    // dla inicjalizacji generatora liczb losowych
#include <cstdlib>  // generowanie losowych liczb
#include <chrono>
using namespace std;
using namespace std::chrono;

int przypisania = 0;
int porownania = 0;

void RESETUJ() {                            //funkcja zerujaca po kazdym posortowaniu tablicy
    porownania = 0;
    przypisania = 0;
}

void GENERATOR_TABLIC(int A[], int n) {
    srand(time(0));                             // Inicjalizacja generatora losowego
    for (int i = 0; i < n; i++) {               // Generowanie liczb aż do n
        A[i] = rand() % 50001;                  // Generowanie liczby całkowitej w zakresie od 0 do 50000
    }
}
void WYPISZ_TABLICE(int* A, int n) {
    for (int i = 0; i < n; i++) {
        //cout << fixed << setprecision(3) << A[i] << " ";       //ustawiamy ze wyswietlane liczby w tablicy beda ze stale
    }                                                           //liczbe po przecinku (fixed) , 2 (setprecision)
    cout << endl;
}
void WYPISZ_WYNIK(int A[], int n) {
    cout << endl;
    cout << "Liczba porownan: " << porownania << endl;
    cout << "Liczba przypisan: " << przypisania << endl;
}
void COUNTING_SORT(int A[], int n, int exp, int d) {
    int* B = new int[n];                            //tablica wynikowa (dynamiczna)
    int* C = new int[d];                            //tablica pomocnicza do zliczania (dynamiczna)
                                                    //d to nasza podstawa systemu np. dziesietnego: d = 10
                                                    //(ale moze tez byc binarny wtedy d = 0,1)
    for (int i = 0; i < d; i++) {                   //wypełnimy tablice pomocnicza C samymi 0
        C[i] = 0;                                   //exp to wykladnik naszej podstawy, ma na celu pokazanie
        przypisania++;                              //po ktorej czesci sortujemy (czy po jednosciach, czy po dziesiatkach itd.)
    }
    for (int i = 0; i < n; i++) {
        int j = (A[i] / exp) % d;                   //wyodrebniamy cyfre z liczby A[i] na pozycji określonej przez exp
        przypisania++;
        C[j]++;                                     //tablica C liczy ilosc wystapien danej cyfry, zwiekszamy jej licznik
        przypisania++;
    }
    for (int i = 1; i < d; i++) {                   //akumulacja licznikow, C[i] zawsze bedzie zawirala mniejsze lub rowne
        C[i] += C[i - 1];
        przypisania++;
    }
    for (int i = n - 1; i >= 0; i--) {
        int j = (A[i] / exp) % d;                    //wyodrebniamy j z liczby A[i]
        B[C[j] - 1] = A[i];                          //-1, aby indeksowanie bylo od 0, przypisujemy do tablicy wynikowej B
        C[j]--;                                      //miejsce dla następnej liczby o tej samej cyfrze j przesuwa się na wcześniejszą pozycję
        przypisania += 3;
    }
    for (int i = 0; i < n; i++) {
        A[i] = B[i];                                 //przepisanie posortowanej tablicy B do pierwotnej tablicy A
        przypisania++;
    }
    delete[] B;                                      //zwolnienie pamieci
    delete[] C;
}

void RADIX_SORT(int A[], int n, int k, int d) {            //k maksymalna liczba pozycji (cyfr) w największej liczbie w A
    for (int i = 0, exp = 1; i < k; i++, exp *= d) {       // sortuje dla każdej cyfry od 1 do k
        COUNTING_SORT(A, n, exp, d);                        //esp = 1 - jednosci (zaczynamy)
    }
}

void RADIX_SORT2(int A[], int n, int d, int k) {
    // Policz liczby dodatnie i ujemne
    int liczba_dodatnich = 0, liczba_ujemnych = 0;
    przypisania += 2;

    for (int i = 0; i < n; i++) {
        if (A[i] >= 0) {
            porownania++;
            liczba_dodatnich++;
            przypisania++;
        } else {
            porownania++;
            liczba_ujemnych++;
            przypisania++;
        }
    }
    // Utwórz tablice pomocnicze
    int* dodatnie = new int[liczba_dodatnich];
    int* ujemne = new int[liczba_ujemnych];

    // Rozdziel liczby dodatnie i ujemne
    int dod = 0, uje = 0;
    przypisania += 2;
    for (int i = 0; i < n; i++) {
        if (A[i] >= 0) {
            porownania++;
            dodatnie[dod++] = A[i];
            przypisania++;
        } else {
            porownania++;
            ujemne[uje++] = -A[i]; // Zamiana ujemnych na dodatnie
            przypisania++;
        }
    }

    // Posortuj liczby dodatnie za pomocą Counting sort
    if (liczba_dodatnich > 0) {
        porownania++;
        for (int exp = 1, iter = 0; iter < k; exp *= d, iter++) {
            COUNTING_SORT(dodatnie, liczba_dodatnich, exp, d);
        }
    }

    // Posortuj liczby ujemne (jako dodatnie) za pomocą Counting Sort
    if (liczba_ujemnych > 0) {
        porownania++;
        for (int exp = 1, iter = 0; iter < k; exp *= d, iter++) {
            COUNTING_SORT(ujemne, liczba_ujemnych, exp, d);
        }
    }

    // Połącz wyniki: liczby ujemne (od największej do najmniejszej), a potem dodatnie
    int x = 0;
    przypisania++;

    // Liczby ujemne w odwrotnej kolejności
    for (int i = liczba_ujemnych - 1; i >= 0; i--) {
        A[x++] = -ujemne[i]; // Przywrócenie ujemnych wartości
        przypisania++;
    }

    // Liczby dodatnie
    for (int i = 0; i < liczba_dodatnich; i++) {
        A[x++] = dodatnie[i];
        przypisania++;
    }

    // Zwolnienie pamięci
    delete[] dodatnie;
    delete[] ujemne;
}
int main() {
    // Tablica do posortowania
    int A[] = {170, -45, 75, -90, 802, 24, 2, -500, 66, 33};
    int n = sizeof(A) / sizeof(A[0]);

    int d = 10; // Podstawa systemu liczbowego (dziesiętny)
    int k = 3;  // Liczba cyfr w największej liczbie (tu zakładamy max 3 cyfry)

    // Wywołanie Radix Sorta
    RADIX_SORT2(A, n, d, k);

    // Wyświetlenie posortowanej tablicy
    cout << "Posortowana tablica: ";
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }

    int sizes[] = {10, 100000, 200000, 300000, 400000, 500000}; // wielkości tablic do testów
    for (int i = 0; i < 5; i++) {
        int n = sizes[i];
        int* A = new int[n]; // dynamiczne przechowywanie tablicy A o długości n
        int* B = new int[n]; // dodatkowa tablica B do zapamiętania oryginalnej kolejności

        GENERATOR_TABLIC(A, n); // generujemy losowe liczby całkowite

        // Kopiujemy wygenerowaną tablicę A do B, aby zapamiętać początkową kolejność
        for (int j = 0; j < n; j++) {
            B[j] = A[j];
        }
        // Mierzenie czasu i liczenie przypisań i porównań dla RADIX_SORT
        RESETUJ();
        clock_t start_time = clock();
        RADIX_SORT(A, n, 2, 10); // Wywołanie podstawowego Radix Sort
        clock_t end_time = clock();
        double elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC * 1000; // w milisekundach
        cout << "RADIX_SORT dla rozmiaru " << n << ":\n";
        cout << "Czas trwania: " << elapsed_time << " ms" << endl;
        WYPISZ_WYNIK(A, n);

        // Wyświetlanie posortowanej tablicy A po RADIX_SORT (dla rozmiaru 10)
        if (n == 10) {
            cout << "Posortowana tablica A po RADIX_SORT: ";
            WYPISZ_TABLICE(A, n);
        }

        // Przywracamy oryginalną kolejność liczb z B do A
        for (int j = 0; j < n; j++) {
            A[j] = B[j];
        }

        // Mierzenie czasu i liczenie przypisań i porównań dla RADIX_SORT2
        RESETUJ();
        start_time = clock();
        RADIX_SORT2(A, n, 2, 10); // Wywołanie modyfikowanego Radix Sort
        end_time = clock();
        elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC * 1000; // w milisekundach
        cout << "RADIX_SORT2 dla rozmiaru " << n << ":\n";
        cout << "Czas trwania: " << elapsed_time << " ms" << endl;
        WYPISZ_WYNIK(A, n);

        // Wyświetlanie posortowanej tablicy A po RADIX_SORT2 (dla rozmiaru 10)
        if (n == 10) {
            cout << "Posortowana tablica A po RADIX_SORT2: ";
            WYPISZ_TABLICE(A, n);
        }

        // Przywracamy oryginalną kolejność liczb z B do A
        for (int j = 0; j < n; j++) {
            A[j] = B[j];
        }
        delete[] A; // Zwalniamy pamięć poprzez usunięcie tablicy A
        delete[] B; // Zwalniamy pamięć poprzez usunięcie tablicy B
        cout << endl;
    }

    return 0;
}


