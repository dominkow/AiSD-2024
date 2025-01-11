#include <iostream>
#include <limits>
#include <ctime>    // dla inicjalizacji generatora liczb losowych
#include <cstdlib>  // generowanie losowych liczb
#include <chrono>    // do mierzenia czasu wykonania
using namespace std;
using namespace std::chrono;
constexpr float inf = -std::numeric_limits<float>::infinity();        //ustawienie -nieskonczonosci na floatach

//wersja Cut_Rod w wersji naiwnej
float CUT_ROD_NAIWNY(float* p, int n) {                               //tablica p - cen, n dlugosc preta
    if (n == 0) {                                                     //zysk 0 dla dlugosci 0
        return 0;
    }
    float q = inf;                                                    //q ustawione poczatkowo na wartosc -nieskonczonosc
    for (int i = 1; i <= n; ++i) {
        q = max(q, p[i - 1] + CUT_ROD_NAIWNY(p, n - i));              //maksymalna cena dla danego odcinka lub jego pocietych czesci
    }
    return q;
}

//wersja MEMORIZED_CUT_ROD z pamietaniem wynikow
float MEMORIZED_CUT_ROD(float* p, float* r, int* s, int n) {        //tablica cen p, r do zapamietywania max zysku, s - optymalnych ciec n dlugosc preta
    if (r[n] >= 0) {                                                  //sprawdzamy czy mamy juz zapisany w tablicy r wynik dla preta
        return r[n];
    }
    float q;
    if (n == 0) {                                                        //zysk 0 dlugosci 0
        q = 0;                                                           //zmienna q przechowujaca maksymalny zysk
    } else {
        q = inf;                                                         //podobnie jak u góry q ustawione na -nieskonczonosc
        for (int i = 1; i <= n; ++i) {
            float m = p[i - 1] + MEMORIZED_CUT_ROD(p, r, s, n - i);      //ustwiamy zmienna m oznaczajaca tymczasowy zysk
            if (m > q){                                                  //maksymalizacja wyniku, max zysku
                q = m;                                                   //jesli aktualny zysk mniejszy od q to podmieniamy
                s[n] = i;                                                //zapisujemy optymalne ciecie
            }
        }
    }
    r[n] = q;                                                            //zapamietanie wyniku
    return q;
}

//wersja iteracyjna CUT_ROD
float EXT_BOT_UP_CUT_ROD(float* p, float* r, int* s, int n) {     //tablica cen p, r do zapamietywania max zysku, s - optymalnych ciec n dlugosc preta
    r[0] = 0;                                                       //tablica zyskow na 0
    for (int j = 1; j <= n; ++j) {                                  //liczymy maksymalne zyski
        float q = inf;                                              //ustawiamy q na -nieskonczonosc
        for (int i = 1; i <= j; ++i) {                              //pierwsze ciecie
            if (q < p[i - 1] + r[j - i]) {
                q = p[i - 1] + r[j - i];                            //jesli lepsze do przypisujemy do q
                s[j] = i;                                           //zapisujemy dlugosci ciecia
            }
        }
        r[j] = q;                                                   //maksymalny zysk
    }
    return r[n];
}

//funkcja do wypisywania, odzyskania rozwiazan z EXT_BOT_UP_CUT_ROD
void PRINT_SOLUTION_EXT(float* p, int* s, int n) {
    float* r = new float [n + 1];       //tablica maksymalnych zyskow
    int* c = new int [n + 1];       //tablica optymalnych ciec

    cout << "Maksymalny zysk: " << EXT_BOT_UP_CUT_ROD(p, r, c, n) << endl;
    cout << "Rozwiazanie: ";
    while (n > 0) {
        cout << c[n] << " ";
        n -= c[n];
    }
    cout << endl;
    delete[] r;
    delete[] c;
}

//funkcja do wypisywania, odzyskiwania rozwiazan z MEMORIZED_CUT_ROD
void PRINT_SOLUTION_MEM(float* p, int* s, int n) {
    float* r = new float [n + 1];       //tablica maksymlanych zyskow
    int* c = new int [n + 1];       //tablica optymalnych ciec

    for (int i = 0; i <= n; ++i) {
        r[i] = inf;                     //wypełniamy tablicę r minimalnymi wartościami
        c[i] = 0;                       //wypełniamy tablicę c zerami
    }
    cout << "Maksymalny zysk: " << MEMORIZED_CUT_ROD(p, r, c, n) << endl;
    cout << "Optymalne ciecia: ";
    while (n > 0) {
        cout << c[n] << " ";
        n -= c[n];
    }
    cout << endl;
    delete[] r;
    delete[] c;
}


//funkcja do inicjalizacji tablicy wynikow
void TabliceWynikow(float* r, int rozmiar) {
    for (int i = 0; i <= rozmiar; ++i) {
        r[i] = -1;
    }
}

//funkcja do generowania cen
float* generujCeny(int n) {
    srand(static_cast<unsigned>(time(0))); // Inicjalizacja generatora pseudolosowego

    float* prices = new float[n];
    prices[0] = 2.0f + static_cast<float>(rand()) / RAND_MAX * (5.0f - 2.0f); // Pierwsza cena w zakresie [2.0, 5.0]
    for (int i = 1; i < n; ++i) {
        prices[i] = prices[i - 1] + 2.0f + static_cast<float>(rand()) / RAND_MAX * 3.0f;
        // Każda kolejna cena wzrasta o losową wartość w zakresie [2.0, 5.0]
    }
    return prices;
}

// funkcja do losowego generowania dlugosci preta
//int generujDlugoscPreta(int maxDlugosc) {
  //  return rand() % maxDlugosc + 1;
//}

int main() {
    srand(static_cast<unsigned>(time(0))); // inicjalizacja generatora liczb losowych

    // Test 1: Wersja naiwna CUT_ROD_NAIWNY
    {
        int test_lengths[] = {5, 10, 15, 20, 25, 30}; // różne długości preta dla wersji naiwnej
        for (int n : test_lengths) {
            float* ceny = generujCeny(n);

            auto start = chrono::high_resolution_clock::now();
            CUT_ROD_NAIWNY(ceny, n);
            auto end = chrono::high_resolution_clock::now();

            cout << "\n[NAIWNY] Czas wykonania dla n = " << n << ": "
                 << chrono::duration_cast<chrono::milliseconds>(end - start).count()
                 << " ms\n";

            delete[] ceny;
        }
    }

    // Test 2: Wersja z pamięcią MEMORIZED_CUT_ROD
    {
        int test_lengths[] = {5, 10, 15, 20, 25, 30, 1000, 2000, 4000, 6000, 8000, 10000, 12500, 15000, 17500, 20000};
        for (int n : test_lengths) {
            float* ceny = generujCeny(n);

            float* r = new float[n + 1];
            int* s = new int[n + 1];
            for (int i = 0; i <= n; ++i) {
                r[i] = -1; // Wypełniamy tablicę wyników wartością początkową
            }

            auto start = chrono::high_resolution_clock::now();
            MEMORIZED_CUT_ROD(ceny, r, s, n);
            auto end = chrono::high_resolution_clock::now();

            cout << "\n[MEMORIZED] Czas wykonania dla n = " << n << ": "
                 << chrono::duration_cast<chrono::milliseconds>(end - start).count()
                 << " ms\n";

            delete[] ceny;
            delete[] r;
            delete[] s;
        }

    // Test 3: Iteracyjna wersja EXT_BOT_UP_CUT_ROD
    {
        int test_lengths[] = {5, 10, 15, 20, 25, 30, 1000, 2000, 4000, 6000, 8000, 10000, 12500, 15000, 17500, 20000};
        for (int n : test_lengths) {
            float* ceny = generujCeny(n);

            float* r = new float[n + 1];
            int* s = new int[n + 1];

            auto start = chrono::high_resolution_clock::now();
            EXT_BOT_UP_CUT_ROD(ceny, r, s, n);
            auto end = chrono::high_resolution_clock::now();

            cout << "\n[ITERACYJNY] Czas wykonania dla n = " << n << ": "
                 << chrono::duration_cast<chrono::milliseconds>(end - start).count()
                 << " ms\n";

            delete[] ceny;
            delete[] r;
            delete[] s;
        }

        // Test wypisania cen, kosztu i podziału preta dla n = 10
        int n = 10;
        float* ceny = generujCeny(n);

        float* r = new float[n + 1];
        int* s = new int[n + 1];
        float* k = new float[n + 1];
        for (int i = 0; i <= n; ++i) {
                k[i] = -1; // Wypełniamy tablicę wyników wartością początkową
        }
        int wynik = EXT_BOT_UP_CUT_ROD(ceny, r, s, n);
        int wynik1 = MEMORIZED_CUT_ROD(ceny, k, s, n);

        cout << "\n[ITERACYJNY] Dla n = 10:\n";
        cout << "Ceny: ";
        for (int i = 0; i < n; ++i) cout << ceny[i] << " " << endl;
        cout << "Podzial: ";
        PRINT_SOLUTION_EXT(ceny, s, n);
        cout << "\n[MEMORIZED] Dla n = 10:\n";
        cout << "Ceny: ";
        for (int i = 0; i < n; ++i) cout << ceny[i] << " " << endl;
        cout << "Podzial: ";
        PRINT_SOLUTION_MEM(ceny, s, n);
        delete[] ceny;
        delete[] r;
        delete[] s;
    }
    return 0;
}
}



