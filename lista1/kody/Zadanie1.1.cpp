#include <iostream>
#include <cstdlib> // do losowych liczb
#include <ctime>   // do inicjalizacji losowych liczb
using namespace std;

int porownania = 0;
int przypisania = 0;

void RESETUJ() {
    porownania = 0;
    przypisania = 0;
}

void INSERTION_SORT(int A[], int n) {
    for (int i = 1; i < n; i++) {
        int key = A[i];
        przypisania++;
        int j = i - 1;
        while (j >= 0 && A[j] > key) {
            porownania++;
            A[j + 1] = A[j];
            przypisania++;
            j--;
        }
        porownania++; // Dodatkowe porównanie, gdy warunek while przestaje byæ spe³niony
        A[j + 1] = key;
        przypisania++;
    }
}

void INSERTION_SORT_MODIFIED(int A[], int n) {
    for (int s = 1; s < n - 1; s += 2) {
        int pierwszy = A[s];
        int drugi = A[s + 1];
        przypisania += 2;
        if (pierwszy > drugi) {
            swap(pierwszy, drugi);
            przypisania += 2;
            porownania++;
        }
        int k = s - 1;
        while (k >= 0 && A[k] > pierwszy) {
            porownania++;
            A[k + 1] = A[k];
            przypisania++;
            k--;
        }
        A[k + 1] = pierwszy;
        przypisania++;
        k = s;
        while (k >= 0 && A[k] > drugi) {
            porownania++;
            A[k + 1] = A[k];
            przypisania++;
            k--;
        }
        A[k + 1] = drugi;
        przypisania++;
    }
    if (n % 2 == 0) {
        porownania++;
        int ostatni = A[n - 1];
        przypisania++;
        int k = n - 2;
        while (k >= 0 && A[k] > ostatni) {
            porownania++;
            A[k + 1] = A[k];
            przypisania++;
            k--;
        }
        A[k + 1] = ostatni;
        przypisania++;
    }
}
void WYPISZ_WYNIK(int A[], int n) {
    cout << "Posortowana tablica: ";
    for (int m = 0; m < n; m++) {
        cout << A[m] << " ";
    }
    cout << endl;
    cout << "Liczba porównañ: " << porownania << endl;
    cout << "Liczba przypisañ: " << przypisania << endl;
}
int main() {
    srand(time(0)); // Inicjalizacja losowego generatora

    // Przyk³adowe dane wejœciowe do testów
    int rozmiary[5] = {6, 8, 10, 12, 15};
    int proby = 5;

    cout << "Test klasycznego insertion sort:" << endl;
    for (int i = 0; i < proby; i++) {
        int n = rozmiary[i];
        int arr[n];
        for (int j = 0; j < n; j++) {
            arr[j] = rand() % 100;
        }

        RESETUJ();
        INSERTION_SORT(arr, n);
        cout << "Próba " << i + 1 << " dla " << n << " elementów:" << endl;
        WYPISZ_WYNIK(arr, n);
        cout << endl;
    }

    cout << "Test zmodyfikowanego insertion sort (INSERTIONSORT2):" << endl;
    for (int i = 0; i < proby; i++) {
        int n = rozmiary[i];
        int arr[n];
        for (int j = 0; j < n; j++) {
            arr[j] = rand() % 100;
        }

        RESETUJ();
        INSERTION_SORT_MODIFIED(arr, n);
        cout << "Próba " << i + 1 << " dla " << n << " elementów:" << endl;
        WYPISZ_WYNIK(arr, n);
        cout << endl;
    }
    return 0;
}

