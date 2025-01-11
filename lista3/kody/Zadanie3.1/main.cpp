#include <iostream>
#include <limits>
#include <ctime>    // dla inicjalizacji generatora liczb losowych
#include <cstdlib>  // generowanie losowych liczb
using namespace std;

constexpr float inf = -std::numeric_limits<float>::infinity();  // ustawienie -nieskonczonosci na floatach

//wersja Cut_Rod w wersji naiwnej
float CUT_ROD_NAIWNY(float* p, int n) {                     //tablica p - cen, n dlugosc preta
    if (n == 0) {                                           //zysk 0 dla dlugosci 0
        return 0;
    }
    float q = inf;                                          //q ustawione poczatkowo na wartosc -nieskonczonosc
    for (int i = 1; i <= n; ++i) {
        q = max(q, p[i - 1] + CUT_ROD_NAIWNY(p, n - i));    //maksymalna cena dla danego odcinka lub jego pocietych czesci
    }
    return q;
}

//wersja MEMORIZED_CUT_ROD z pamietaniem wynikow
float MEMORIZED_CUT_ROD(float* p, float* r, float* s, int n) {        //tablica cen p, r do zapamietywania max zysku, s - optymalnych ciec n dlugosc preta
    if (r[n] >= 0) {                //sprawdzamy czy mamy juz zapisany w tablicy r wynik dla preta
        return r[n];
    }
    float q;
    if (n == 0) {                   //zysk 0 dlugosci 0
        q = 0;                      //zmienna q przechowujaca maksymalny zysk (dla n == 0, naturalnie 0)
    } else {
        q = inf;                    //podobnie jak u góry q ustawione na -nieskonczonosc
        for (int i = 1; i <= n; ++i) {
            float m = p[i - 1] + MEMORIZED_CUT_ROD(p, r, s, n - 1);      //ustwiamy zmienna m oznaczajaca tymczasowy zysk
            if (m < q){             //maksymalizacja wyniku, max zysku
                q = m;              //jesli aktualny zysk mniejszy od q to podmieniamy
                s[n] = i;           //zapisujemy optymalne ciecie
            }
        }
    }
    r[n] = q;                       //zapamietanie wyniku
    return q;
}

//wersja iteracyjna CUT_ROD
float EXT_BOT_UP_CUT_ROD(float* p, float* r, int* s, int n) {       //tablica cen p, r do zapamietywania max zysku, s - optymalnych ciec n dlugosc preta
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
