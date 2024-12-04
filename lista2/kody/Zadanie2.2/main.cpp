#include <iostream>
#include <ctime>    // dla inicjalizacji generatora liczb losowych
#include <cstdlib>  // generowanie losowych liczb
using namespace std;

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

void GENERATOR_TABLIC_NEG(int A[], int n) {
    srand(time(0));                             // Inicjalizacja generatora losowego
    for (int i = 0; i < n; i++) {               // Generowanie liczb aż do n
        A[i] = (rand() % 100001) - 50000;       // Generowanie liczby całkowitej w zakresie od -50000 do 50000
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

void RADIX_SORT_MOD(int A[], int n, int k, int d) {
    int liczba_dodatnich = 0;
    int liczba_ujemnych = 0;                                //policzmy liczby dodatnie i ujemne
    przypisania += 2;

    for (int i = 0; i < n; i++) {
        if (A[i] >= 0) {
            porownania++;
            liczba_dodatnich++;                             //spawdzamy czy sprawdzana wartosc jest wieksza/rowna/mniejsza
            przypisania++;                                  //i przypisujemy do odpowiedniej czesci ujemnej/dodatniej
        } else {
            porownania++;
            liczba_ujemnych++;
            przypisania++;
        }
    }
    int* dodatnie = new int[liczba_dodatnich];              //tworzymy die tablice z liczb ujemnych, duga z dodatnich
    int* ujemne = new int[liczba_ujemnych];

    int plusowe = 0;                                       //rozdzielamy liczby dodatnie i ujemne
    int minusowe = 0;
    przypisania += 2;
    for (int i = 0; i < n; i++) {
        if (A[i] >= 0) {
            porownania++;
            dodatnie[plusowe++] = A[i];
            przypisania++;
        } else {
            porownania++;
            ujemne[minusowe++] = -A[i];                     // Zamieniamy ujemne na dodatnie
            przypisania++;
        }
    }
    //sortujemy liczby dodatnie za pomocą Counting sort
    if (liczba_dodatnich > 0) {
        porownania++;
        for (int exp = 1, iter = 0; iter < k; exp *= d, iter++) {
            COUNTING_SORT(dodatnie, liczba_dodatnich, exp, d);
        }
    }
    //sortujemy liczby ujemne (jako dodatnie) za pomocą Counting Sort
    if (liczba_ujemnych > 0) {
        porownania++;
        for (int exp = 1, iter = 0; iter < k; exp *= d, iter++) {
            COUNTING_SORT(ujemne, liczba_ujemnych, exp, d);
        }
    }
    //laczymy wyniki: liczby ujemne (od największej do najmniejszej), a potem dodatnie
    int x = 0;
    przypisania++;

    // Liczby ujemne w odwrotnej kolejności
    for (int i = liczba_ujemnych - 1; i >= 0; i--) {
        A[x++] = -ujemne[i];                            // Przywrócenie ujemnych wartości
        przypisania++;
    }
    // Liczby dodatnie
    for (int i = 0; i < liczba_dodatnich; i++) {
        A[x++] = dodatnie[i];
        przypisania++;
    }
    delete[] dodatnie;
    delete[] ujemne;
}
int main() {
    //test sortowania
    int D[] = {170, -45, 75, -90, 802, 24, 2, -500, 66, 33};
    int C[] = {149, 67, 58, 321, 90, 124, 125, 67, 870, 13};
    int n = sizeof(D) / sizeof(D[0]);
    int m = sizeof(C) / sizeof(C[0]);
    int d = 10;                                             //podstawa systemu liczbowego
    int k = 3;                                              //liczba cyfr w największej liczbie

    RADIX_SORT_MOD(D, n, d, k);                             //wywolanie radix sortow
    RADIX_SORT(C, m, d, k);

    //wyświetlenie posortowanych tablic
    cout << "Posortowana tablica dla RADIX_SORT_MOD: ";
    for (int i = 0; i < n; i++) {
        cout << D[i] << " ";
    }
    cout << "\n\n"; // Dwa znaki nowej linii dla czytelności
    cout << "Posortowana tablica dla RADIX_SORT: ";
    for (int j = 0; j < m; j++) {
        cout << C[j] << " ";
    }
    cout << "\n\n";                                             // Dwa znaki nowej linii dla czytelności

//testy dla roznych d
    int sizes[] = {10, 100000, 200000, 300000, 400000, 500000};

    cout << "==== WYNIKI RADIX_SORT dla k = 6 i d = 2 ====\n";
    for (int i = 0; i < 6; i++) {
        int n = sizes[i];

    // Generowanie tablicy dla RADIX_SORT
    int* A = new int[n];
    GENERATOR_TABLIC(A, n);

    // RADIX_SORT
    RESETUJ();
    clock_t start_time = clock();
    RADIX_SORT(A, n, 6, 2); // 6 cyfr maksymalnie (np. dla zakresu 0-999999)
    clock_t end_time = clock();
    double elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC * 1000;
    cout << "RADIX_SORT dla rozmiaru " << n << ":\n";
    cout << "Czas trwania: " << elapsed_time << " ms";
    WYPISZ_WYNIK(A, n);
    cout << "\n";
    delete[] A;
    }
    cout << "\n\n";

    cout << "===========================\n\n";

    cout << "==== WYNIKI RADIX_SORT dla k = 6 i d = 6 ====\n";
    for (int i = 0; i < 6; i++) {
        int n = sizes[i];

    // Generowanie tablicy dla RADIX_SORT
    int* A = new int[n];
    GENERATOR_TABLIC(A, n);

    // RADIX_SORT
    RESETUJ();
    clock_t start_time = clock();
    RADIX_SORT(A, n, 6, 6); // 6 cyfr maksymalnie (np. dla zakresu 0-999999)
    clock_t end_time = clock();
    double elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC * 1000;
    cout << "RADIX_SORT dla rozmiaru " << n << ":\n";
    cout << "Czas trwania: " << elapsed_time << " ms";
    WYPISZ_WYNIK(A, n);
    cout << "\n";
    delete[] A;
    }
    cout << "\n\n";

    cout << "===========================\n\n";

       cout << "==== WYNIKI RADIX_SORT dla k = 6 i d = 10 ====\n";
    for (int i = 0; i < 6; i++) {
        int n = sizes[i];

    // Generowanie tablicy dla RADIX_SORT
    int* A = new int[n];
    GENERATOR_TABLIC(A, n);

    // RADIX_SORT
    RESETUJ();
    clock_t start_time = clock();
    RADIX_SORT(A, n, 6, 10); // 6 cyfr maksymalnie (np. dla zakresu 0-999999)
    clock_t end_time = clock();
    double elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC * 1000;
    cout << "RADIX_SORT dla rozmiaru " << n << ":\n";
    cout << "Czas trwania: " << elapsed_time << " ms";
    WYPISZ_WYNIK(A, n);
    cout << "\n";
    delete[] A;
    }
    cout << "\n\n";

    cout << "===========================\n\n";

       cout << "==== WYNIKI RADIX_SORT dla k = 6 i d = 14 ====\n";
    for (int i = 0; i < 6; i++) {
        int n = sizes[i];

    // Generowanie tablicy dla RADIX_SORT
    int* A = new int[n];
    GENERATOR_TABLIC(A, n);

    // RADIX_SORT
    RESETUJ();
    clock_t start_time = clock();
    RADIX_SORT(A, n, 6, 14); // 6 cyfr maksymalnie (np. dla zakresu 0-999999)
    clock_t end_time = clock();
    double elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC * 1000;
    cout << "RADIX_SORT dla rozmiaru " << n << ":\n";
    cout << "Czas trwania: " << elapsed_time << " ms";
    WYPISZ_WYNIK(A, n);
    cout << "\n";
    delete[] A;
    }
    cout << "\n\n";

    cout << "===========================\n\n";


    cout << "==== WYNIKI RADIX_SORT_MOD dla k = 6 i d = 2 ====\n";
    for (int i = 0; i < 6; i++) {
        int n = sizes[i];

    // Generowanie tablicy dla RADIX_SORT_MOD
    int* B = new int[n];
    GENERATOR_TABLIC_NEG(B, n);

    // RADIX_SORT_MOD
    RESETUJ();
    clock_t start_time = clock();
    RADIX_SORT_MOD(B, n, 6, 2); // 6 cyfr maksymalnie, podstawa dziesiętna
    clock_t end_time = clock();
    double elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC * 1000;
    cout << "RADIX_SORT_MOD dla rozmiaru " << n << ":\n";
    cout << "Czas trwania: " << elapsed_time << " ms ";
    WYPISZ_WYNIK(B, n);
    cout << "\n";
    delete[] B;
    }
    cout << "\n";

    cout << "===========================\n\n";

        cout << "==== WYNIKI RADIX_SORT_MOD dla k = 6 i d = 6 ====\n";
    for (int i = 0; i < 6; i++) {
        int n = sizes[i];

    // Generowanie tablicy dla RADIX_SORT_MOD
    int* B = new int[n];
    GENERATOR_TABLIC_NEG(B, n);

    // RADIX_SORT_MOD
    RESETUJ();
    clock_t start_time = clock();
    RADIX_SORT_MOD(B, n, 6, 6); // 6 cyfr maksymalnie, podstawa dziesiętna
    clock_t end_time = clock();
    double elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC * 1000;
    cout << "RADIX_SORT_MOD dla rozmiaru " << n << ":\n";
    cout << "Czas trwania: " << elapsed_time << " ms ";
    WYPISZ_WYNIK(B, n);
    cout << "\n";
    delete[] B;
    }
    cout << "\n";

    cout << "===========================\n\n";

        cout << "==== WYNIKI RADIX_SORT_MOD dla k = 6 i d = 10 ====\n";
    for (int i = 0; i < 6; i++) {
        int n = sizes[i];

    // Generowanie tablicy dla RADIX_SORT_MOD
    int* B = new int[n];
    GENERATOR_TABLIC_NEG(B, n);

    // RADIX_SORT_MOD
    RESETUJ();
    clock_t start_time = clock();
    RADIX_SORT_MOD(B, n, 6, 10); // 6 cyfr maksymalnie, podstawa dziesiętna
    clock_t end_time = clock();
    double elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC * 1000;
    cout << "RADIX_SORT_MOD dla rozmiaru " << n << ":\n";
    cout << "Czas trwania: " << elapsed_time << " ms ";
    WYPISZ_WYNIK(B, n);
    cout << "\n";
    delete[] B;
    }
    cout << "\n";

    cout << "===========================\n\n";

        cout << "==== WYNIKI RADIX_SORT_MOD dla k = 6 i d = 14 ====\n";
    for (int i = 0; i < 6; i++) {
        int n = sizes[i];

    // Generowanie tablicy dla RADIX_SORT_MOD
    int* B = new int[n];
    GENERATOR_TABLIC_NEG(B, n);

    // RADIX_SORT_MOD
    RESETUJ();
    clock_t start_time = clock();
    RADIX_SORT_MOD(B, n, 6, 14); // 6 cyfr maksymalnie, podstawa dziesiętna
    clock_t end_time = clock();
    double elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC * 1000;
    cout << "RADIX_SORT_MOD dla rozmiaru " << n << ":\n";
    cout << "Czas trwania: " << elapsed_time << " ms ";
    WYPISZ_WYNIK(B, n);
    cout << "\n";
    delete[] B;
    }
    cout << "\n";

    cout << "===========================\n\n";

return 0;

}


