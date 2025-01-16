#include <iostream>
#include <cstdlib>          //inicjalizacja generatora
#include <ctime>            //do czasu
#include <chrono>           //do czasu
#include <algorithm>        //do sorta
using namespace std;
using namespace std::chrono;
constexpr float inf = -std::numeric_limits<float>::infinity();        //ustawienie -nieskonczonosci na floatach
constexpr float maks = std::numeric_limits<float>::infinity();        //ustawienie nieskonczonosci na floatach


//normalna implementacja rekurencyjna na podstawie pseudokodu
void RECURSIVE_ACTIVITY_SELECTOR(float s[], float f[], int n, int k, int zajecia[], int &ilosc){    //s,f tablice start finisz, n ich wielkosc (aktywnosci)
                                                                                                //k aktualne indeks sal, licznik zajec
    int m =k + 1;                                                       //zaczynamy od zajec nastepujacych po aktualnych

    while(m <= n && s[m] < f[k]){                                       //sprawdzamy czy poczatek zajec koliduje czy nie
        m = m + 1;                                                      //jesli tak to zwiekszamy m ( przechodzimy do nastepnych zajec)
    }
    if (m <= n){
        zajecia[ilosc++] = m;                                           //dodajemy aktywnosc m do tablicy zajecia
        RECURSIVE_ACTIVITY_SELECTOR(s, f, n, m, zajecia, ilosc);        //rekurencja m - nowa ostatnie wybrane zajecia
    }
}                                                                       //nie ma return bo wedlug psuodokodu wywoluje pusty

//funkcja wypisujaca rozwiazanie z wersji rekurencyjnej
void PRINT_SOLUTION_R1(float s[], float f[], int n) {
    int zajecia[n];                                     //tablica na indeksy zajec pasujacych
    int ilosc = 0;                                      //licznik wybranych zajec

    RECURSIVE_ACTIVITY_SELECTOR(s, f, n, 0, zajecia, ilosc);  //rekurencja wywolana

    cout << "Wybrane aktywnoœci:\n";
    for (int i = 0; i < ilosc; i++) {
        int aktywnosc = zajecia[i];
        cout << "Zajecia " << aktywnosc << ": Start = " << s[aktywnosc] << ", Koniec = " << f[aktywnosc] << "\n";
    }
}


//normalna implementacja iteracyjna na podstawie pseudokodu
void ACTIVITY_SELECTOR(float s[], float f[], int n, int zajecia[], int &ilosc) {
    ilosc = 0;                                                       //startujemy od 0
    zajecia[ilosc++] = 1;                                            //pierwsze zajecia zawsze sa wybrane

    int k = 1;                                                       //indeks ostatnich zajec

    for (int m = 2; m <= n; m++) {
        if (s[m] >= f[k]) {                                          //sprawdzamy czy zajecia koliduja
            zajecia[ilosc++] = m;                                    //jesli nie to dodajemy zajecia do tablicy zajecia
            k = m;                                                   //aktualizujemy ostatnio wybran¹ aktywnosc
        }
    }
}

//funkjca wypisujaca rozwiazanie z funkcji iteracyjnej
void PRINT_SOLUTION_I1(float s[], float f[], int n) {
    int zajecia[n];                                         //tablica na indeksy zajec pasujacych
    int ilosc = 0;                                          //licznik wybranych zajec

    ACTIVITY_SELECTOR(s, f, n, zajecia, ilosc);             //wywolujemy rekurencje

    cout << "Wybrane aktywnoœci:\n";                        //wypisujemy dane
    for (int i = 0; i < ilosc; i++) {
        int aktywnosc = zajecia[i];
        cout << "Zajecia " << aktywnosc << ": Start = " << s[aktywnosc] << ", Koniec = " << f[aktywnosc] << "\n";
    }
}

void CZAS_START(float s[], int n) {
    s[0] = 0.0f;                                                    //fikcyjny na pocz¹tku, ustawiony na 0
    for (int i = 1; i <= n; i++) {
        s[i] = static_cast<float>(rand()) / RAND_MAX * (n * 2);     //losowanie floata
    }
}

void CZAS_FINISZ(float f[], float s[], int n) {
    f[0] = inf;                             //fikcyjny na poczatek, -nieskonczonosc

    for (int i = 1; i <= n; i++) {
        f[i] = s[i] + static_cast<float>(rand() % 100 + 1);     //losowy float
    }
    sort(f + 1, f + n + 1);                     //sortowanie f[], funkcja wbudowana
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {      //po posortowaniu f[] zachowujemy odpowiednie wartosci s[] w zgodzie z f[]
            if (s[i] > s[j]) {
                swap(s[i], s[j]);
            }
        }
    }
}





//modyfikacja rekurencji aby zamiast po koncu sortowala po starcie - s
void RECURSIVE_ACTIVITY_SELECTOR_MOD(float s[], float f[], int k, int zajecia[], int &ilosc){
        int m = k - 1;                                  //interesuja nas teraz zajecia odbywajace sie przed aktualnym

    while (m > 0 && f[m] > s[k]) {                      //szukamy zajecia, konczacego sie przed zajêciem k (aktualnym)
        m--;
    }
    if (m > 0) {                                                //jeœli znaleziono pasuj¹ce zajêcie
        zajecia[ilosc++] = m;                                   //dodajemy indeks zajêcia do wyniku
        RECURSIVE_ACTIVITY_SELECTOR_MOD(s, f, m, zajecia, ilosc);    //rekurencyjnie wybieramy wczeœniejsze zajêcia
    }
}

void PRINT_SOLUTION_R_MOD(float s[], float f[], int n) {
    int zajecia[n];                                         //tablica na indeksy zajêæ pasuj¹cych
    int ilosc = 0;                                          //licznik wybranych zajêæ

    RECURSIVE_ACTIVITY_SELECTOR_MOD(s, f, n, zajecia, ilosc);

    cout << "Wybrane aktywnoœci:\n";
    for (int i = 0; i < ilosc; i++) {
        int aktywnosc = zajecia[i];
        cout << "Zajêcia " << aktywnosc << ": Start = " << s[aktywnosc] << ", Koniec = " << f[aktywnosc] << "\n";
    }
}

void ACTIVITY_SELECTOR_MOD(float s[], float f[], int n, int zajecia[], int &ilosc) {        //pomijamy k
    zajecia[ilosc++] = n - 1;             // Ostatnie zajêcie przed fikcyjnym jest zawsze wybrane
    int k = n - 1;

    for (int m = n - 2; m >= 1; m--) {      // Iterujemy od koñca i wybieramy zajêcia, które koñcz¹ siê przed rozpoczêciem ostatnio wybranego zajêcia
        if (f[m] <= s[k]) {
            zajecia[ilosc++] = m;             // Dodajemy indeks zajêcia do wyniku
            k = m;
        }
    }
}

//funkjca wypisujaca rozwiazanie z funkcji iteracyjnej
void PRINT_SOLUTION_I_MOD(float s[], float f[], int n) {
    int zajecia[n];                                         //tablica na indeksy zajec pasujacych
    int ilosc = 0;                                          //licznik wybranych zajec

    ACTIVITY_SELECTOR_MOD(s, f, n, zajecia, ilosc);         //wywolujemy rekurencje

    cout << "Wybrane aktywnoœci:\n";                        //wypisujemy dane
    for (int i = 0; i < ilosc; i++) {
        int aktywnosc = zajecia[i];
        cout << "Zajecia " << aktywnosc << ": Start = " << s[aktywnosc] << ", Koniec = " << f[aktywnosc] << "\n";
    }
}
//analogicznie jak przy normalnych tylko ¿e s jak f, a f jak s
void CZAS_S(float s[], int n) {
    s[0] = 0.0f;                                                    //pierwszy element musi byc rowny 0
    for (int i = 1; i <= n; i++) {
        s[i] = static_cast<float>(rand()) / RAND_MAX * (n * 2);     //generujemy losowe floaty
            }
    s[n + 1] = maks;                                                //ustawiamy jako maximum
    sort(s + 1, s + n + 1);                                         //sortujemy aby bylo rosnaco (z uzyciem wbudowanego sorta)
}                                                                   //tu nie trzeba swapowac bo f jest zalezne od s

void CZAS_F(float f[], float s[], int n) {
    f[0] = inf;                                                     //-nieskonczonosc

    for (int i = 1; i <= n; i++) {
        f[i] = s[i] + static_cast<float>(rand() % 100 + 1);         //generujemy losowe floaty (woparciu o s)
    }

    f[n + 1] = 0.0f;                                                //ostatnia element (indeks n+1) musi byc rowny 0
}





//funkcja na zdobycie rozwiazania z dynamicznej implementacji
void PRINT_DYNAMICZNE(int **c, int **b, int i, int j) {
    if (c[i][j] > 0) {                             //jesli istnieje aktywnosc miedzy i a j
        int k = b[i][j];
        cout << k << " ";                            //bierzemy k takie samo jak u gory (tylko juz po petli czyli optymalne)
        PRINT_DYNAMICZNE(c, b, i, k);         //rekurencyjne lewy
        PRINT_DYNAMICZNE(c, b, k, j);         //rekurencyjne prawy
    }
}

//Implementacja poprzez programowanie dynamiczne
void ACTIVITY_SELECTOR_DYNAMICZNY(float s[], float f[], int n) {
    int **c = new int *[n + 2];                               //tworzymy tablice c i b do przechowywania podproblemow i zajec
    int **b = new int *[n + 2];                               //tak jak zaklada programowanie dynamiczne (n + 2 spowodowane
    for (int i = 0; i < n + 2; ++i) {                   //dodaniem sztucznych granic na start i na koniec)
        c[i] = new int[n + 2]();                        //na start ustawiamy je na same 0
        b[i] = new int[n + 2]();                        //b - przechowuje wartosci k (dzielacej na podproblemy)
    }                                                   //c - przechowuje maksymalna liczbe zajec na przedziale [i,j]

    for (int l = 2; l <= n + 1; ++l) {                  //iterujemy po dlugosci przedzialow
        for (int i = 0; i <= n - l + 1; ++i) {          //l dlugosc, startujemy od 2 bo 1 jest samo w sobie ok
            int j = i + l;                              // i - poczatek przedzialu, j - koniec przedialu
            for (int k = i + 1; k < j; ++k) {           //k -indeks zajec, potencjalnie optymalna, sprawdzamy w srodku przedzialu czy sa odpowiednie zajecia
                if (f[i] <= s[k] && f[k] <= s[j]) {     //sprawdzamy czy k miesci sie pomiedzy i i j
                    int element = c[i][k] + c[k][j] + 1;//definiujemy element, ktory dzieli nam od i do k oraz j do k
                    if (element > c[i][j]) {            //dodajemy +1 bo wliczamy w to te¿ samo k
                        c[i][j] = element;              //jezeli element (z uwzglenieniem k)jest wiêkszy od aktualnego to podmieniamy
                        b[i][j] = k;                    //aktualizujemy i zapamiêtujemy indeksu zajec
                    }
                }
            }
        }
    }
    cout << "Maksymalna liczba zajec " << c[0][n + 1] << endl;
    cout << "Zajecia: ";
    PRINT_DYNAMICZNE(c, b, 0, n + 1);
    cout << endl;

    for (int i = 0; i < n + 2; ++i) {
        delete[] c[i];
        delete[] b[i];
    }
    delete[] c;
    delete[] b;
}


int main() {
    float v[] = {0, 2.2, 3, 4.7, 5.1, 8}; // Czasy rozpoczêcia (indeks 0 to fikcyjny element)
    float u[] = {inf, 3.3, 7, 5.6, 7, 9.7}; // Czasy zakoñczenia (indeks 0 to fikcyjny element)
    int o = 5; // Liczba aktywnoœci (bez indeksu 0)
    PRINT_SOLUTION_R1(v, u, o);
    PRINT_SOLUTION_I1(v, u, o);

    float y[] = {0, 2.2, 3, 4.7, 5.1, 8, maks};
    float g[] = {inf, 3.3, 7, 5.6, 7, 9.7, 0};
    int m = 6;//o 1 wiêcej ni¿ zajêæ bo ostatnie fikcyjne
    PRINT_SOLUTION_R_MOD(y,g,m);
    PRINT_SOLUTION_I_MOD(y,g,m);

    ACTIVITY_SELECTOR_DYNAMICZNY(y, g, o);


    srand(time(0)); // Inicjalizacja generatora losowego

    for (int n = 1000; n <= 10000; n += 1000) {
        float *s = new float[n + 2];
        float *f = new float[n + 2];

        // Generowanie danych testowych
        CZAS_START(s, n);
        CZAS_FINISZ(f, s, n);

        cout << "Porównanie czasów wykonania dla n = " << n << ":\n";

        // Test implementacji rekurencyjnej klasycznej
        auto start = high_resolution_clock::now();
        PRINT_SOLUTION_R1(s, f, n);
        auto end = high_resolution_clock::now();
        auto duration_recursive = duration_cast<milliseconds>(end - start);
        cout << "Czas wykonania rekurencyjnej klasycznej: " << duration_recursive.count() << " ms\n";

        // Test implementacji iteracyjnej klasycznej
        start = high_resolution_clock::now();
        PRINT_SOLUTION_I1(s, f, n);
        end = high_resolution_clock::now();
        auto duration_iterative = duration_cast<milliseconds>(end - start);
        cout << "Czas wykonania iteracyjnej klasycznej: " << duration_iterative.count() << " ms\n";

        // Przygotowanie danych dla wersji modyfikowanej
        CZAS_S(s, n);
        CZAS_F(f, s, n);

        // Test implementacji rekurencyjnej zmodyfikowanej
        start = high_resolution_clock::now();
        PRINT_SOLUTION_R_MOD(s, f, n + 1);
        end = high_resolution_clock::now();
        auto duration_recursive_mod = duration_cast<milliseconds>(end - start);
        cout << "Czas wykonania rekurencyjnej zmodyfikowanej: " << duration_recursive_mod.count() << " ms\n";

        // Test implementacji iteracyjnej zmodyfikowanej
        start = high_resolution_clock::now();
        PRINT_SOLUTION_I_MOD(s, f, n + 1);
        end = high_resolution_clock::now();
        auto duration_iterative_mod = duration_cast<milliseconds>(end - start);
        cout << "Czas wykonania iteracyjnej zmodyfikowanej: " << duration_iterative_mod.count() << " ms\n";

        // Test implementacji dynamicznej
        start = high_resolution_clock::now();
        ACTIVITY_SELECTOR_DYNAMICZNY(s, f, n);
        end = high_resolution_clock::now();
        auto duration_dynamic = duration_cast<milliseconds>(end - start);
        cout << "Czas wykonania dynamicznej: " << duration_dynamic.count() << " ms\n";

        // Zwolnienie pamiêci
        delete[] s;
        delete[] f;

        cout << "-------------------------------------------\n";
    }

    return 0;
}



