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
    srand(time(0));                                                     //inicjalizacja generatora losowego
    for (int i = 0; i < n; i++) {                                       //po kolei generujemy az do n
        A[i] = static_cast<float>(rand()) / RAND_MAX * 50000.00;        //static_cast<float> - przeksztalcamy na floata
                                                                        //liczbe calkowita generowana przez rand() / RAND_MAX
    }                                                                   //dostajemy liczbe od 0 do 1, co mno¿ymy przez 50000
}
void WYPISZ_TABLICE(int* A, int n) {
    for (int i = 0; i < n; i++) {
        //cout << fixed << setprecision(3) << A[i] << " ";       //ustawiamy ze wyswietlane liczby w tablicy beda ze stale
    }                                                           //liczbe po przecinku (fixed) , 2 (setprecision)
    cout << endl;
}
void WYPISZ_WYNIK(float A[], int n) {
    cout << endl;
    cout << "Liczba porownan: " << porownania << endl;
    cout << "Liczba przypisan: " << przypisania << endl;
}
void COUNTINGSORT(int A[], int n, int exp, int base) {
    int* B = new int[n];    // Tablica wynikowa
    int* C = new int[base]; // Tablica pomocnicza do zliczania

    // Inicjalizacja tablicy C
    for (int i = 0; i < base; i++) {
        C[i] = 0;
        przypisania++;
    }

    // Liczenie wystąpień cyfr na danej pozycji
    for (int i = 0; i < n; i++) {
        int j = (A[i] / exp) % base;
        przypisania++;
        C[j]++;
        przypisania++;
    }

    // Akumulacja liczników
    for (int i = 1; i < base; i++) {
        C[i] += C[i - 1];
        przypisania++;
    }

    // Umieszczanie elementów w tablicy wynikowej w odpowiedniej kolejności
    for (int i = n - 1; i >= 0; i--) {
        int j = (A[i] / exp) % base;
        B[C[j] - 1] = A[i]; // -1, żeby od 0 były w tablicy B
        C[j]--;
        przypisania += 3;
    }

    // Przepisanie posortowanej tablicy wynikowej do pierwotnej tablicy A
    for (int i = 0; i < n; i++) {
        A[i] = B[i];
        przypisania++;
    }

    // Zwolnienie pamięci
    delete[] B;
    delete[] C;
}

void RADIX_SORT(int A[], int n, int d, int k) {
    for (int i = 0, exp = 1; i < k; i++, exp *= d) {        // sortuje dla każdej cyfry od 1 do k
        COUNTINGSORT(A, n, exp, d);
    }
}

// Funkcja testująca
int main() {
    int A[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(A) / sizeof(A[0]);
    int d = 10; // Baza systemu dziesiętnego
    int k = 3;  // Maksymalna liczba cyfr w liczbach

    cout << "Przed sortowaniem:\n";
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << endl;

    RADIX_SORT(A, n, d, k);

    cout << "Po sortowaniu:\n";
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << endl;

    cout << "Liczba przypisań: " << przypisania << endl;

    return 0;
}

