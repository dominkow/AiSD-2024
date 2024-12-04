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
//pseudokod z wykladu 1 do 1
void COUNTING_SORT(int A[], int n, int exp, int d) {    //esp odpowiada za miejsce dziesietne sortowania
    int* B = new int[n];                            //dynamiczna tablica wynikowa
    int* C = new int[d]();
    przypisania+=2;                                   //pusta tablica dynamiczna - tablica licznikow

    for (int i = 0; i < n; i++) {
        int j = (A[i] / exp) % d;                   //wyznaczamy czy patrzymy na setki, dzisiatki czy jednosci
        przypisania++;
        C[j]++;                                     //dodajemy zliczenie do tablicy licznikow
        przypisania++;
    }

    for (int i = 1; i < d; i++) {                   //dodajemy wartosci poprzenich elementow w zliczaniu aby moc ustalic
        C[i] += C[i - 1];                           //ustalic pozycje w tablicy wynikowej
        przypisania++;
    }

    for (int i = n - 1; i >= 0; i--) {              //umieszczanie w odpowiednim miejscu w B
        int j = (A[i] / exp) % d;                   //obliczne miejsce dziesietne do przypisania w C
        B[C[j] - 1] = A[i];                         // -1, żeby indeksowanie zaczynało się od 0
        C[j]--;                                     //zmniejszamy licznik aby elementy z tego samej grupy byly odpowiednio umieszczane
        przypisania += 3;
    }

    for (int i = 0; i < n; i++) {                   //wracamy do tablicy A
        A[i] = B[i];
        przypisania++;
    }

    delete[] B;
    delete[] C;
}

void RADIX_SORT(int A[], int n, int d) {
    int maks_war = A[0];
    przypisania++;                         //oznaczamy maksymalna wartosc na A[0] (poczatkowo)
    for (int i = 1; i < n; i++) {           //i jedziemy petla w poszukiwaniu wartosci maksymalnej
        if (A[i] > maks_war) {
            porownania++;
            maks_war = A[i];
            przypisania++;
        }
    }
    int k = 0;                              //majac wartosc najwieksza mozemy wyznaczyc ilosc jej cyfr, czyli nasze k
    while (maks_war > 0) {
        porownania++;
        maks_war /= d;
        przypisania++;                      //przypisanie z dzieleniem
        k++;
        przypisania++;
    }
    for (int exp = 1, iter = 0; iter < k; exp *= d, iter++)     //sortowanie za pomoca counting sorta (wyklad 1 do 1)
        COUNTING_SORT(A, n, exp, d);
}

//modyfikacja do radixa, aby radzil sobie jakos z ujemnymi
void RADIX_SORT_MOD(int A[], int n, int d) {
    int liczba_dodatnich = 0;                           //tworzymy zmienne przechowujace liczbe dodatnnich (wraz z 0)
    int liczba_ujemnych = 0;
    przypisania+=2;                            //oraz ujemnych

    for (int i = 0; i < n; i++) {                       //zliczamy ich ilosc za pomoca petli for
        if (A[i] >= 0) {
            porownania++;
            liczba_dodatnich++;
            przypisania++;
        } else {
            liczba_ujemnych++;
            przypisania++;
        }
    }

    int* dodatnie = new int[liczba_dodatnich];          //tworzymy tablice dynamiczne na przechowywyanie liczb ujemnych i dodatnich
    int* ujemne = new int[liczba_ujemnych];
    przypisania+=2;

    int plusowe = 0;                                    //indeksy dla dodatnich i ujemnych
    int minusowe = 0;
    przypisania+=2;

    for (int i = 0; i < n; i++) {
        if (A[i] >= 0) {
            porownania++;
            dodatnie[plusowe++] = A[i];
            przypisania++;                          //dodanie liczby do tablicy dodatnich
        } else {
            ujemne[minusowe++] = -A[i];
            przypisania++;                       //ujemne do ujemnych
        }
    }

  int max_dodatnie = 0;
  przypisania++;
    if (liczba_dodatnich > 0) {
        porownania++;
        max_dodatnie = dodatnie[0];
        przypisania++;                              //ustawiamy max_dodatnie na pierwszą liczbę (o ile sa)
    }
    for (int i = 1; i < liczba_dodatnich; i++) {
        if (dodatnie[i] > max_dodatnie) {
            porownania++;
            max_dodatnie = dodatnie[i];
            przypisania++;                          //szukamy najwiekszej liczby w tablicy dodatnich
        }
    }

    int k_dodatnie = 0;
    przypisania++;                                //obliczamy wartosc k - ile cyfr w najwiekszej liczbie
    while (max_dodatnie > 0) {
        porownania++;
        max_dodatnie /= d;
        przypisania++;
        k_dodatnie++;
        przypisania++;
    }

    int max_ujemne = 0;
    przypisania++;
    if (liczba_ujemnych > 0) {
        porownania++;
        max_ujemne = ujemne[0];
        przypisania++;                          //ustawiamy max_ujemne na pierwszą liczbę (o ile istnieja)
    }
    for (int i = 1; i < liczba_ujemnych; i++) {
        if (ujemne[i] > max_ujemne) {
            porownania++;
            max_ujemne = ujemne[i];
            przypisania++;                      //szukamy największej liczby w tablicy ujemnych
        }
    }

    int k_ujemne = 0;
    przypisania++;                                        //zliczamy cyfry najwiekszej liczby ujmmenj k
    while (max_ujemne > 0) {
        porownania++;
        max_ujemne /= d;
        przypisania++;
        k_ujemne++;
        przypisania++;
    }

    if (liczba_dodatnich > 0) {
        porownania++;
        for (int exp = 1, iter = 0; iter < k_dodatnie; exp *= d, iter++) {      //sotujemy dodatnie counting sortem
            COUNTING_SORT(dodatnie, liczba_dodatnich, exp, d);
        }
    }

    if (liczba_ujemnych > 0) {
        porownania++;                                       //sortujemy ujemne counting osrtem
        for (int exp = 1, iter = 0; iter < k_ujemne; exp *= d, iter++) {
            COUNTING_SORT(ujemne, liczba_ujemnych, exp, d);
        }
    }

    int x = 0;                      //laczymy - najpierw ujemne potem dodatnie
    przypisania++;

    for (int i = liczba_ujemnych - 1; i >= 0; i--) {        //przywracamy znak dla ujemnych
        A[x++] = -ujemne[i];
        przypisania++;
    }

    for (int i = 0; i < liczba_dodatnich; i++) {            //dodatnie normalnie po ujemnych
        A[x++] = dodatnie[i];
        przypisania++;
    }

    delete[] dodatnie;
    delete[] ujemne;
}

void GENERATOR_TABLIC_1(int A[], int n) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 10001; // Generowanie liczby całkowitej z zakresu [0, 10000]
    }
}

void GENERATOR_TABLIC_NEG(int A[], int n) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        int value = rand() % 10001; // Generowanie liczby całkowitej z zakresu [0, 10000]
        if (rand() % 2 == 0) {      // 50% szans na zmianę znaku na minus
            value = -value;
        }
        A[i] = value;
    }
}

void WYPISZ_TABLICE(int A[], int n) {
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
}

void WYPISZ_WYNIK(int A[], int n) {
    cout << endl;
    cout << "Liczba porownan: " << porownania << endl;
    cout << "Liczba przypisan: " << przypisania << endl;
}

int main() {
    //test sortowania
    int D[] = {170, -45, 75, -90, 802, 24, 2, -500, 66, 33};
    int C[] = {149, 67, 58, 321, 90, 124, 125, 67, 870, 13};
    int n = sizeof(D) / sizeof(D[0]);
    int m = sizeof(C) / sizeof(C[0]);
    int d = 2;                                             //podstawa systemu liczbowego
                                                            //liczba cyfr w największej liczbie

    RADIX_SORT_MOD(D, n, d );                             //wywolanie radix sortow
    RADIX_SORT(C, m, d);

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
    int sizes[] = {100000, 200000, 300000, 400000};

    cout << "==== WYNIKI RADIX_SORT dla d = 2 ====\n";
    for (int i = 0; i < 4; i++) {
        int n = sizes[i];

        //generowanie tablicy dla RADIX_SORT
        int* A = new int[n];
        GENERATOR_TABLIC_1(A, n);

        //RADIX_SORT
        RESETUJ();
        clock_t start_time = clock();
        RADIX_SORT(A, n, 2);
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

    cout << "==== WYNIKI RADIX_SORT dla d = 6 ====\n";
    for (int i = 0; i < 4; i++) {
        int n = sizes[i];

        //generowanie tablicy dla RADIX_SORT
        int* A = new int[n];
        GENERATOR_TABLIC_1(A, n);

        //RADIX_SORT
        RESETUJ();
        clock_t start_time = clock();
        RADIX_SORT(A, n, 6);
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

    cout << "==== WYNIKI RADIX_SORT dla d = 10 ====\n";
    for (int i = 0; i < 4; i++) {
        int n = sizes[i];

        //generowanie tablicy dla RADIX_SORT
        int* A = new int[n];
        GENERATOR_TABLIC_1(A, n);

        //RADIX_SORT
        RESETUJ();
        clock_t start_time = clock();
        RADIX_SORT(A, n, 10);
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

    cout << "==== WYNIKI RADIX_SORT dla d = 14 ====\n";
    for (int i = 0; i < 4; i++) {
        int n = sizes[i];

        //generowanie tablicy dla RADIX_SORT
        int* A = new int[n];
        GENERATOR_TABLIC_1(A, n);

        //RADIX_SORT
        RESETUJ();
        clock_t start_time = clock();
        RADIX_SORT(A, n, 14);
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

    cout << "==== WYNIKI RADIX_SORT_MOD dla d = 2 ====\n";
    for (int i = 0; i < 4; i++) {
        int n = sizes[i];

        //generowanie tablicy dla RADIX_SORT_MOD
        int* B = new int[n];
        GENERATOR_TABLIC_NEG(B, n);

        // RADIX_SORT_MOD
        RESETUJ();
        clock_t start_time = clock();
        RADIX_SORT_MOD(B, n, 2);
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

    cout << "==== WYNIKI RADIX_SORT_MOD dla d = 6 ====\n";
    for (int i = 0; i < 4; i++) {
        int n = sizes[i];

        //generowanie tablicy dla RADIX_SORT_MOD
        int* B = new int[n];
        GENERATOR_TABLIC_NEG(B, n);

        //RADIX_SORT_MOD
        RESETUJ();
        clock_t start_time = clock();
        RADIX_SORT_MOD(B, n, 6);
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

    cout << "==== WYNIKI RADIX_SORT_MOD dla d = 10 ====\n";
    for (int i = 0; i < 4; i++) {
        int n = sizes[i];

        //generowanie tablicy dla RADIX_SORT_MOD
        int* B = new int[n];
        GENERATOR_TABLIC_NEG(B, n);

        //RADIX_SORT_MOD
        RESETUJ();
        clock_t start_time = clock();
        RADIX_SORT_MOD(B, n, 10);
        clock_t end_time = clock();
        double elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC * 1000;
        cout << "RADIX_SORT_MOD dla rozmiaru " << n << ":\n";
        cout << "Czas trwania: " << elapsed_time << " ms ";
        WYPISZ_WYNIK(B, n);
        cout << "\n";
        delete[] B;
    }
    cout << "\n";

    cout << "==== WYNIKI RADIX_SORT_MOD dla d = 14 ====\n";
    for (int i = 0; i < 4; i++) {
        int n = sizes[i];

        //generowanie tablicy dla RADIX_SORT_MOD
        int* B = new int[n];
        GENERATOR_TABLIC_NEG(B, n);

        //RADIX_SORT_MOD
        RESETUJ();
        clock_t start_time = clock();
        RADIX_SORT_MOD(B, n, 14);
        clock_t end_time = clock();
        double elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC * 1000;
        cout << "RADIX_SORT_MOD dla rozmiaru " << n << ":\n";
        cout << "Czas trwania: " << elapsed_time << " ms ";
        WYPISZ_WYNIK(B, n);
        cout << "\n";
        delete[] B;
    }
    cout << "\n";

    return 0;
}


