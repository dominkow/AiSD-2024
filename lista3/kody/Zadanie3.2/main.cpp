#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <cstring>
using namespace std;
using namespace std::chrono;

//implementacja LCS ze spamietywaniem w spossb rekurencyjny
int LCS_REKURENCJA(const string &w1, const string &w2, int m, int n, int** s){      //bierzemy zmienne przechowujace ciagi w1
    if (s[m][n] != -1){                                                         //w2, m i n (dlugosci ciagow), tablice s do spamietywania
        return s[m][n];                                             //jezeli s[m][n] nie jest pusta to zwracamy ja
    }
    if (m == 0 || n == 0){                                          //jezeli dlugosc ciagow 0 to zwracamy 0
        return s[m][n] = 0;
    }
    if (w1[m - 1] == w2[n - 1])                                   //jezeli ostanie znaki sa te same, dodajemy 1 (bo mamy wspólny znak)
        return s[m][n] = 1 + LCS_REKURENCJA(w1, w2, m - 1, n - 1, s);
    return s[m][n] = max(LCS_REKURENCJA(w1, w2, m, n - 1, s), LCS_REKURENCJA(w1, w2, m - 1, n, s));     //jezeli ostatnie znaki sa rozne, bierzem max z dwoch wynikow (jedziemy od n-1 do 1)

}

void ODZYSKIWANIE_ROZWIAZANIA_REKURENCJA(const string &w1, const string &w2) {
    int m = w1.length();                            //m,n jako dlugosci
    int n = w2.length();

    int **s = new int*[m + 1];                      // wypelniamy tablice s -1 - oznaczajaca brak danej
    for (int i = 0; i <= m; ++i) {
        s[i] = new int[n + 1];
        for (int j = 0; j <= n; ++j) {
            s[i][j] = -1;
        }
    }

    int k = LCS_REKURENCJA(w1, w2, m, n, s); // Jak długi najdłuższy podciąg

    string podciag = "";
    while (m > 0 && n > 0) {
        if (w1[m - 1] == w2[n - 1]) {// Jeśli znaki pasują, dodaj do wyniku
            podciag = w1[m - 1] + podciag;
            m--;
            n--;
        } else if (s[m - 1][n] > s[m][n - 1]) {// Przechodzimy w kierunku większej wartości
            m--;
        } else {
            n--;
        }
    }

    cout << "Dlugosc: " << k << endl;
    //cout << "Podciag: " << podciag << endl;

    for (int i = 0; i <= m; ++i) {
        delete[] s[i];
    }
    delete[] s;
}

//implementacja iteracyjna LCS (na podstawie pseudokodu z wykladu)
char** LCS_ITERACJA(const string &w1, const string &w2, int& dlugosc) {
    int m = w1.length();
    int n = w2.length();

    int** c = new int*[m + 1];                  //c odpowiada za
    char** b = new char*[m + 1];                //
    for (int i = 0; i <= m; i++) {
        c[i] = new int[n + 1];
        b[i] = new char[n + 1];
    }

    for (int i = 0; i <= m; i++) {
        c[i][0] = 0;
    }
    for (int j = 0; j <= n; j++) {
        c[0][j] = 0;
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (w1[i - 1] == w2[j - 1]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = '\\';
            } else if (c[i - 1][j] >= c[i][j - 1]) {
                c[i][j] = c[i - 1][j];
                b[i][j] = '|';
            } else {
                c[i][j] = c[i][j - 1];
                b[i][j] = '-';
            }
        }
    }
    // Zapisujemy długość LCS
    dlugosc = c[m][n];

    for (int i = 0; i <= m; i++) {
        delete[] c[i];
    }
    delete[] c;

    // Zwracamy tablicę kierunków
    return b;
}

// Funkcja do wypisywania optymalnego rozwiązania
void ODZYSKIWANIE_ROZWIAZANIA_ITERACJA(char** b, const char* X, int i, int j) {
    while (i > 0 && j > 0) {
        if (b[i][j] == '\\') {
            i--;
            j--;
            ODZYSKIWANIE_ROZWIAZANIA_ITERACJA(b, X, i, j); // Rekursja dla poprzedniego dopasowania
            cout << X[i]; // Wypisanie wspólnego znaku
            return;
        } else if (b[i][j] == '|') {
            i--;
        } else {
            j--;
        }
    }
}

string LOSOWY_NAPIS(int l) {
    string alfabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string napis;
    for (int i = 0; i < l; i++) {
        napis += alfabet[rand() % alfabet.length()];
    }
    return napis;
}

int main() {
    string w1 = "ABCBDAB";
    string w2 = "BDCABB";

    // Testowanie na jednym przykładzie (rekurencyjne)
    cout << "Testowanie na jednym przykladzie (rekurencyjne):" << endl;
    ODZYSKIWANIE_ROZWIAZANIA_REKURENCJA(w1, w2);

    // Testowanie na jednym przykładzie (iteracyjne)
    cout << "Testowanie na jednym przykladzie (iteracyjne):" << endl;
    int dlugosc = 0;
    char** b = LCS_ITERACJA(w1, w2, dlugosc);
    cout << "Dlugosc: " << dlugosc << endl;
    cout << "Podciag: ";
    ODZYSKIWANIE_ROZWIAZANIA_ITERACJA(b, w1.c_str(), w1.length(), w2.length());
    cout << endl;

    // Zwolnienie pamięci po tablicy b
    for (int i = 0; i <= w1.length(); i++) {
        delete[] b[i];
    }
    delete[] b;

    // Tablica z długościami do testowania
    int lengths[] = {500, 800, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
    int numTests = sizeof(lengths) / sizeof(lengths[0]);

    // Testowanie czasu dla różnych długości ciągów (rekurencyjne)
    cout << "Testowanie czasu dla roznych dlugosci ciagow (rekurencyjne):" << endl;
    for (int i = 0; i < numTests; i++) {
        int len = lengths[i];
        string w1 = LOSOWY_NAPIS(len);
        string w2 = LOSOWY_NAPIS(len);

        cout << "Dlugosc ciagu: " << len << endl;

        // Przygotowanie tablicy s
        int** s = new int*[len + 1];
        for (int j = 0; j <= len; ++j) {
            s[j] = new int[len + 1];
            for (int k = 0; k <= len; ++k) {
                s[j][k] = -1; // Inicjalizacja wartości w tablicy
            }
        }

        // Mierzenie czasu wykonania algorytmu
        auto start = high_resolution_clock::now();
        int dlugoscLCS = LCS_REKURENCJA(w1, w2, w1.length(), w2.length(), s);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        cout << "Dlugosc podciagu: " << dlugoscLCS << endl;
        cout << "Czas: " << duration.count() << " mikrosekund" << endl << endl;

        // Zwolnienie pamięci
        for (int j = 0; j <= len; ++j) {
            delete[] s[j];
        }
        delete[] s;
    }

    // Testowanie czasu dla różnych długości ciągów (iteracyjne)
    cout << "Testowanie czasu dla roznych dlugosci ciagow (iteracyjne):" << endl;
    for (int i = 0; i < numTests; i++) {
        int len = lengths[i];
        string w1 = LOSOWY_NAPIS(len);
        string w2 = LOSOWY_NAPIS(len);

        cout << "Dlugosc ciagu: " << len << endl;

        // Mierzenie czasu wykonania algorytmu
        auto start = high_resolution_clock::now();
        int dlugoscLCS = 0;
        char** b = LCS_ITERACJA(w1, w2, dlugoscLCS);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        cout << "Dlugosc podciagu: " << dlugoscLCS << endl;
        cout << "Czas: " << duration.count() << " mikrosekund" << endl << endl;

        // Zwolnienie pamięci
        for (int j = 0; j <= w1.length(); j++) {
            delete[] b[j];
        }
        delete[] b;
    }

    return 0;
}

