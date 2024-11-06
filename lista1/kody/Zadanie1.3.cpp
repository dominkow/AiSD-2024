#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int porownania = 0;
int przypisania = 0;

void RESETUJ() {
    porownania = 0;
    przypisania = 0;
}
// dla kopca binarnego mamy pozycje:
int LEWA(int i) {
    return 2 * i;
}

int PRAWA(int i) {
    return 2 * i + 1;
}

void HEAPIFY(int A[], int i, int n) {
    int l = LEWA(i);
    int p = PRAWA(i);
    int naj = i;

    if (l < n && A[l] > A[i]) {
        porownania++;
        naj = l;
        przypisania++;
    }

    if (p < n && A[p] > A[naj]) {
        porownania++;
        naj = p;
        przypisania++;
    }

    if (naj != i) {
        porownania++;
        swap(A[i], A[naj]);
        przypisania +=2;
        HEAPIFY(A, naj, n);
    }
}


void BUILD_HEAP(int A[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
    HEAPIFY(A, i, n);
    }
}

void HEAPSORT(int A[], int n) {
    BUILD_HEAP(A, n);

    for (int i = n - 1; i >= 1; i--) {
        swap(A[0], A[i]);
        przypisania +=2;
        n--;
        HEAPIFY(A, 0, n);
    }
}


int LEWA_T(int i){
    return 3 * i;
}
int SRODEK_T (int i){
    return 3 * i + 1;
}
int PRAWA_T(int i){
    return 3 * i + 2;
}

void HEAPIFY_T(int A[], int i, int n) {
    int l = LEWA_T(i);
    int s = SRODEK_T(i);
    int p = PRAWA_T(i);
    int naj = i;

    if (l < n && A[l] > A[i]) {
        porownania++;
        przypisania++;
        naj = l;
    }

    if (s < n && A[s] > A[naj]) {
        naj = s;
        porownania++;
        przypisania++;
    }

    if (p < n && A[p] > A[naj]) {
        porownania++;
        przypisania++;
        naj = p;
    }

    if (naj != i) {
        porownania++;
        swap(A[i], A[naj]);
        przypisania +=2;
        HEAPIFY_T(A, naj, n);

    }
}
void BUILD_HEAP_T(int A[], int n){
    for (int i = n / 3 - 1; i >= 0; i--) {
        HEAPIFY_T(A, i, n);
    }
}
void HEAP_SORT_T(int A[], int n) {
    BUILD_HEAP_T(A, n);

    for (int i = n - 1; i >= 1; i--) {
        swap(A[0], A[i]);
        przypisania +=2;
        n--;
        HEAPIFY_T(A, 0, n);
    }
}
void WYPISZ_WYNIK(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    srand(time(0));

    // Przyk³adowe rozmiary do testów
    int rozmiary[5] = {6, 8, 10, 12, 15};
    int proby = 5;

    cout << "Test binarnego HEAP_SORTA:" << endl;
    for (int i = 0; i < proby; i++) {
        int n = rozmiary[i];
        int arr[n];
        for (int j = 0; j < n; j++) {
            arr[j] = rand() % 100; // Losowe liczby od 0 do 19
        }

        RESETUJ();
        HEAPSORT(arr, n);
        cout << "Proba " << i + 1 << " dla " << n << " elementow:" << endl;
        WYPISZ_WYNIK(arr, n);
        cout << endl;
    }

    // Zak³adamy, ¿e mamy te¿ zmodyfikowan¹ wersjê HEAP_SORT_BIN, jeœli jest dostêpna
    // Funkcjê mo¿na pomin¹æ, jeœli HEAP_SORT_BIN nie istnieje
    cout << "Test ternarnego HEAP_SORT):" << endl;
    for (int i = 0; i < proby; i++) {
        int n = rozmiary[i];
        int arr[n];
        for (int j = 0; j < n; j++) {
            arr[j] = rand() % 100; // Losowe liczby od 0 do 19
        }

        RESETUJ();
        HEAP_SORT_T(arr, n); // Zamieñ na HEAP_SORT_BIN, jeœli jest dostêpna
        cout << "Proba " << i + 1 << " dla " << n << " elementow:" << endl;
        WYPISZ_WYNIK(arr, n);
        cout << endl;
    }

    return 0;
}
