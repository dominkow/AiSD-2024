#include <iostream>
#include <limits>
#include <ctime>    // dla inicjalizacji generatora liczb losowych
#include <cstdlib>  // generowanie losowych liczb
using namespace std;

constexpr float inf = -std::numeric_limits<float>::infinity();  // ustawienie -nieskonczonosci na floatach

// Wersja Cut_Rod w wersji naiwnej
float CUT_ROD_NAIWNY(float* p, int n) {
    if (n == 0) {
        return 0;
    }
    float q = inf; // q ustawione na minimalna wartosc (na - nieskonczonosc)
    for (int i = 1; i <= n; ++i) {
        q = max(q, p[i - 1] + CUT_ROD_NAIWNY(p, n - i));
    }
    return q;
}

// Wersja MEMORIZED_CUT_ROD z pamietaniem wynikow
float MEMORIZED_CUT_ROD(float* p, float* r, int n) {
    if (r[n] >= 0) {
        return r[n];
    }
    float q;
    if (n == 0) {
        q = 0;
    } else {
        q = inf; // podobnie jak u góry q ustawione na -nieskonczonosc
        for (int i = 1; i <= n; ++i) {
            q = max(q, p[i - 1] + MEMORIZED_CUT_ROD(p, r, n - i));
        }
    }
    r[n] = q; // zapamietanie wyniku
    return q;
}

// Wersja iteracyjna CUT_ROD
void EXT_BOT_UP_CUT_ROD(float* p, float* r, int* s, int n) {
    r[0] = 0;
    for (int j = 1; j <= n; ++j) {
        float q = inf;
        for (int i = 1; i <= j; ++i) {
            if (q < p[i - 1] + r[j - i]) {
                q = p[i - 1] + r[j - i];
                s[j] = i;
            }
        }
        r[j] = q;
    }
}

// funkcja PRINT_SOLUTION - wypisanie rozwiazania
void PRINT_SOLUTION(float* p, int* s, int n) {
    cout << "Rozwiazanie: ";
    while (n > 0) {
        cout << s[n] << " ";
        n -= s[n];
    }
    cout << endl;
}

// funkcja do inicjalizacji tablicy wynikow
void inicjalizujTabliceWynikow(float* r, int rozmiar) {
    for (int i = 0; i <= rozmiar; ++i) {
        r[i] = -1;
    }
}

// Funkcja do uruchomienia testów
void uruchomTest(float* ceny, int n, const string& nazwaTestu) {
    cout << "=== Test: " << nazwaTestu << " ===" << endl;
    cout << "Dlugosc preta: " << n << endl;
    cout << "Ceny: ";
    for (int i = 0; i < n; ++i) {
        cout << ceny[i] << " ";
    }
    cout << endl;

    float* r = new float[n + 1];
    int* s = new int[n + 1];
    inicjalizujTabliceWynikow(r, n);

    // Obliczenie maksymalnego zysku
    cout << "Maksymalny zysk: " << MEMORIZED_CUT_ROD(ceny, r, n) << endl;

    // Obliczenie maksymalnego zysku i rozwiazania
    EXT_BOT_UP_CUT_ROD(ceny, r, s, n);
    cout << "Maksymalny zysk iteracja: " << r[n] << endl;
    PRINT_SOLUTION(ceny, s, n);

    delete[] s;
    delete[] r;
}
// funkcja do losowego generowania dlugosci preta
//int generujDlugoscPreta(int maxDlugosc) {
  //  return rand() % maxDlugosc + 1;
}

// funkcja do generowania bardziej zróżnicowanych cen
//void generujCeny(float* ceny, int n, int maxCena) {
  //  for (int i = 0; i < n; ++i) {
    //    // Ceny rosną w miarę zwiększania się długości, z dodatkowym elementem losowym
      //  ceny[i] = (i + 1) * (maxCena / 10.0f) + static_cast<float>(rand() % (maxCena / 2));
    //}
//}

// funkcja do inicjalizacji tablicy wynikow
//void inicjalizujTabliceWynikow(float* r, int rozmiar) {
  //  for (int i = 0; i <= rozmiar; ++i) {
    //    r[i] = -1;
   // }
//}


int main() {
    // Test 1: Dane predefiniowane (różnorodne ceny)
    float ceny1[] = {1, 5, 8, 9, 10, 17, 17, 20}; // Ceny kawałków o długości od 1 do 8
    uruchomTest(ceny1, 8, "Predefiniowany 1");

    // Test 2: Dane predefiniowane (duże różnice w cenach)
    float ceny2[] = {3, 7, 8, 9, 10, 20, 24, 30}; // Ceny kawałków o długości od 1 do 8
    uruchomTest(ceny2, 8, "Predefiniowany 2");

    // Test 3: Losowe dane (generowane losowo)
    srand(static_cast<unsigned>(time(0)));
    int n = 10; // Losowa długość preta
    float* cenyLosowe = new float[n];
    for (int i = 0; i < n; ++i) {
        cenyLosowe[i] = static_cast<float>(rand() % 20 + 1);
    }
    uruchomTest(cenyLosowe, n, "Losowe dane");
    delete[] cenyLosowe;

    return 0;
}
