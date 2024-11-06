#include <iostream>
#include <limits.h>
#include <ctime>
#include <cstdlib>
using namespace std;

int porownania = 0;
int przypisania = 0;

void RESETUJ() {
    porownania = 0;
    przypisania = 0;
}

void MERGE(int A[], int p, int s, int k){
    int n1 = s - p + 1;
    int n2 = k - s;
    int L[n1 + 1];
    int P[n2 + 1];

    L[n1] = INT_MAX;
    P[n2] = INT_MAX;
    przypisania +=2;

    for (int i = 0; i < n1; i++) {
        L[i] = A[p + 1];
        przypisania++;
    }
    for (int j = 0; j < n2; j++ ){
        P[j] = A[s + 1 + j];
        przypisania++;
    }

    int i = 0;
    int j = 0;
    for (int l = p; l <= k; l++) {
        if (L[i] <= P[j]) {
            porownania++;
            A[l] = L[i];
            przypisania++;
            i++;
        }
        else {
            A[l] = P[j];
            porownania++;
            przypisania;
            j++;
        }
    }
}

void MERGE_SORT(int A[], int p, int k){
    if (p < k) {
        porownania++;
        int s = (p + k) / 2;
        MERGE_SORT(A, p, s);
        MERGE_SORT(A, s + 1, k);
        MERGE(A, p, s, k);
    }
}

void MERGE_MODYFIKOWANY(int A[], int p, int s1, int s2, int k){
    int n1 = s1 - p + 1;
    int n2 = s2- s1;
    int n3 = k - s2;

    int L[n1 + 1];
    int S[n2 + 1];
    int P[n3 + 1];
    L[n1] = INT_MAX;
    S[n2] = INT_MAX;
    P[n3] = INT_MAX;
    przypisania +=3

    for (int i = 0; i < n1; i++){
        L[i] = A[p + 1];
        przypisania++
    }
    for (int j = 0; j < n2; j++){
        S[j] = A[s1 + 1 + j];
        przypisania++
    }
    for (int m = 0; m < n3; m++){
        P[m] = A[s2 + 1 + m];
        przypisania++
    }
    int i = 0;
    int j = 0;
    int m = 0;

    for (int x = p; x <= k; x++) {
         if (L[i] <= S[j] && L[i] <= P[m]) {
            porownania++;
            A[x] = L[i];
            przypisania++;
            i++;
        } else if (S[j] <= L[i] && S[j] <= P[m]) {
            porownania++;
            A[x] = S[j];
            przypisania++;
            j++;
        } else {
            porownania++;
            A[x] = P[m];
            przypisania++;
            m++;

        }
    }
}

void MERGE_SORT_MODYFIKOWANY(int A[], int p, int k) {
    if (p < k) {
        porownania++;
        int s1 = p + (k - p) / 3;
        int s2 = p + 2 * (k - p) / 3;
        MERGE_SORT_MODYFIKOWANY(A, p, s1);
        MERGE_SORT_MODYFIKOWANY(A, s1 + 1, s2);
        MERGE_SORT_MODYFIKOWANY(A, s2 + 1, k);
        MERGE_MODYFIKOWANY(A, p, s1, s2, k);
    }
}

void WYPISZ_WYNIK(int A[], int n) {
    cout << "Posortowana tablica: ";
    for (int m = 0; m < n; m++) {
        cout << A[m] << " ";
    }
    cout << endl;
    cout << "Liczba porownan: " << porownania << endl;
    cout << "Liczba przypisan: " << przypisania << endl;
}

int main() {
    srand(time(0));

    int rozmiary[5] = {6, 8, 10, 12, 15};
    int proby = 5;

    cout << "Test klasycznego MERGE_SORT:" << endl;
    for (int i = 0; i < proby; i++) {
        int n = rozmiary[i];
        int arr[n];
        for (int j = 0; j < n; j++) {
            arr[j] = rand() % 1000;
        }

        RESETUJ();
        MERGE_SORT(arr, 0, n - 1);
        cout << "Proba " << i + 1 << " dla " << n << " elementow:" << endl;
        WYPISZ_WYNIK(arr, n);
        cout << endl;
    }

    cout << "Test zmodyfikowanego MERGE_SORT:" << endl;
    for (int i = 0; i < proby; i++) {
        int n = rozmiary[i];
        int arr[n];
        for (int j = 0; j < n; j++) {
            arr[j] = rand() % 1000;
        }

        RESETUJ();
        MERGE_SORT_MODYFIKOWANY(arr, 0, n - 1);
        cout << "Proba " << i + 1 << " dla " << n << " elementow:" << endl;
        WYPISZ_WYNIK(arr, n);
        cout << endl;
    }

    return 0;
}
