#include <iostream>
#include <limits>
#include <ctime>    // dla inicjalizacji generatora liczb losowych
#include <cstdlib>  // generowanie losowych liczb
using namespace std;
constexpr float inf = -std::numeric_limits<float>::infinity();  //ustawienie -nieskonczonosci na floatach

//Wersja Cut_Rod w wersji naiwnej
float CUT_ROD_NAIWNY(float* p, int n){
    if (n == 0){
        return 0;
    }
    float q = inf;                  // q ustawione na minimaln¹ wartoœæ (na - nieskonczonosc)
    for (int i = 1; i <= n; ++i) {
        q = max(q, p[i - 1] + CUT_ROD_NAIWNY(p, n - i));
    }
    return q;
}

//Wersja MEMORIZED_CUT_ROD z pamietaniem wynikow
float MEMORIZED_CUT_ROD(float* p, float* r, int n) {
    if (r[n] >= 0) {
        return r[n];
    }
    float q;
    if (n == 0) {
        q = 0;
    } else {
        q = inf;         // podobnie jak u góry q ustawione na -nieskonczonosc
        for (int i = 1; i <= n; ++i) {
            q = max(q, p[i - 1] + MEMORIZED_CUT_ROD(p, r, n - i));
        }
    }
    r[n] = q;           //zapamietanie wyniku
    return q;
}

//Wersja iteracyjna CUT_ROD
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

//funkcja PRINT_SOLUTION - wypisanie rozwi¹zania
void PRINT_SOLUTION(float* p, int* s, int n) {
    float* r = new float[n + 1];
    int* solution = new int[n + 1];

    EXT_BOT_UP_CUT_ROD(p, r, solution, n);

    cout << "Rozwi¹zanie: ";
    while (n > 0) {
        cout << solution[n] << " ";
        n -= solution[n];
    }
    cout << endl;

    delete[] r;
    delete[] solution;
}

//funkcja do losowego generowania d³ugoœci prêta
int generujDlugoscPreta(int maxDlugosc) {
    return rand() % maxDlugosc + 1;
}

//funkcja do losowego generowania cen
void generujCeny(float* ceny, int n, int maxCena) {
    for (int i = 0; i < n; ++i) {
        ceny[i] = static_cast<float>(rand() % maxCena + 1);
    }
}

//funkcja do inicjalizacji tablicy wyników
void inicjalizujTabliceWynikow(float* r, int rozmiar) {
    for (int i = 0; i <= rozmiar; ++i) {
        r[i] = -1;
    }
}
//cos tu nie tak!!!! --- print soluton same 1 zwraca - chyba bezsens
int main() {
    srand(static_cast<unsigned>(time(0)));

    int maxDlugosc = 500; // Maksymalna d³ugoœæ prêta
    int maxCena = 1000;   // Maksymalna cena za kawa³ek prêta

    int n = generujDlugoscPreta(maxDlugosc); // Losowa d³ugoœæ prêta
    float* ceny = new float[n];
    generujCeny(ceny, n, maxCena); // Losowe ceny dla ka¿dego kawa³ka prêta

    float* r = new float[n + 1];
    int* s = new int[n + 1];
    inicjalizujTabliceWynikow(r, n); // Inicjalizacja tablicy wyników

    // Obliczenie maksymalnego zysku
    cout << "D³ugoœæ prêta: " << n << endl;
    cout << "Ceny: ";
    for (int i = 0; i < n; ++i) {
        cout << ceny[i] << " ";
    }
    cout << endl;

    cout << "Maksymalny zysk: " << MEMORIZED_CUT_ROD(ceny, r, n) << endl;

    // Obliczenie maksymalnego zysku i rozwi¹zania
    EXT_BOT_UP_CUT_ROD(ceny, r, s, n);
    cout << "Maksymalny zysk iteracja: " << r[n] << endl;
    PRINT_SOLUTION(ceny, s, n);

    delete[] s;
    delete[] ceny;
    delete[] r;

    //cout << "Maksymalny zysk: " << CUT_ROD_NAIWNY(ceny, n) << endl;
    return 0;
}
