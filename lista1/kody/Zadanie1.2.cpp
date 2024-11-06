#include <iostream>
#include <limits.h>
#include <ctime>
#include <cstdlib>
using namespace std;

int porownania = 0;                         //zmienne globalne do przypisan i porownan
int przypisania = 0;

void RESETUJ() {                            //funkcja zerujaca po kazdym posortowaniu tablicy
    porownania = 0;
    przypisania = 0;
}

void MERGE(int A[], int p, int s, int k){   //utworzenie tablicy A, o poczatku p, srodku s, koncu k
    int n1 = s - p + 1;                     //zdefiniowanie dlugosci lewej i prawej czesci tablicy
    int n2 = k - s;
    int L[n1 + 1];
    int P[n2 + 1];
    przypisania +=4;

    L[n1] = INT_MAX;                        //dodanie "wartoœci nieskoñczonoœci" na koñcach tych tablic.
    P[n2] = INT_MAX;                        //gdy skoñczymy przegladac jedna z czesci, dalsze porównania obejma tylko druga czesc.
    przypisania +=2;

    for (int i = 0; i < n1; i++) {          //przypisujemy elementy z lewej czesci do L
        L[i] = A[p + 1];
        przypisania++;
    }
    for (int j = 0; j < n2; j++ ){          //przypisujemy elementy z prawej strony do P
        P[j] = A[s + 1 + j];
        przypisania++;
    }

    int i = 0;                              //i dla lewej, j dla prawej
    int j = 0;
    przypisania +=2;
    for (int l = p; l <= k; l++) {          //zmienna l zaczynajaca od p, mniejsza od k
        if (L[i] <= P[j]) {                 //sprawdzamy co jest wieksze
            porownania++;
            A[l] = L[i];                    //przepisujemy mniejszy element do A[] i zwiekszamy i.
            przypisania++;
            i++;
            przypisania++;
        }
        else {
            A[l] = P[j];                    //w przeciwnym razie przepisujemy element z P[] do A[] i zwiekszamy j.
            porownania++;
            przypisania;
            j++;
            przypisania++;
        }
    }
}

void MERGE_SORT(int A[], int p, int k){     //tworzymy tablice A, z poczakiem p i koncem k
    if (p < k) {                            //jesli p mniejsze od k (jezeli na odwrot to element jest juz posortowany)
        porownania++;
        int s = (p + k) / 2;
        przypisania++;                      //liczymy srodek
        MERGE_SORT(A, p, s);                //wywolujemy rekurencyjne sortowanie lewej strony
        MERGE_SORT(A, s + 1, k);            //wywolujemy rekurencyjne sortowanie prawej strony
        MERGE(A, p, s, k);                  //scalamy
    }
}

void MERGE_MODYFIKOWANY(int A[], int p, int s1, int s2, int k){ //tworzymy tablice A, z pocztakiem p, jedna/trzecia s1, dwiema/trzecimi s2, koncem k
    int n1 = s1 - p + 1;        //zdefiniowanie dlugosci lewej, srodkowej i prawej czesci
    int n2 = s2- s1;
    int n3 = k - s2;
    przypisania +=3;
    int L[n1 + 1];
    int S[n2 + 1];
    int P[n3 + 1];
    przypisania +=3;
    L[n1] = INT_MAX;            //dodanie "wartosci nieskonczonosci" na koncach tych tablic.
    S[n2] = INT_MAX;            //gdy skonczymy przegladac jedna z czesci, dalsze porównania nie obejma juz jej
    P[n3] = INT_MAX;
    przypisania +=3;

    for (int i = 0; i < n1; i++){       //przypisujemy elementy z lewej do L
        L[i] = A[p + 1];
        przypisania++;
    }
    for (int j = 0; j < n2; j++){       //przypisujemy elementy ze srodka do S
        S[j] = A[s1 + 1 + j];
        przypisania++;
    }
    for (int m = 0; m < n3; m++){       //przypisujemy elementy z prawej do P
        P[m] = A[s2 + 1 + m];
        przypisania++;
    }
    int i = 0;                          // i dla lewej, j dla srodka, m dla prawej
    int j = 0;
    int m = 0;
    przypisania =+3;

    for (int x = p; x <= k; x++) {          //przeglad kazdego elementu od p do k
         if (L[i] <= S[j] && L[i] <= P[m]) {    //jak srodek wiekszy/rowny lewej i prawa wieksza/rowna lewej
            porownania++;
            A[x] = L[i];                        //najmnijeszy element przypisujemy na biezaca pozycje A[x]
            przypisania++;
            i++;                                //przesuwamy wskaznik i do nastepnego elementu
            przypisania++;
        } else if (S[j] <= L[i] && S[j] <= P[m]) {  //jak lewa wieksza/rowna od srodka i prawa wieksza rowna od srodka
            porownania++;
            A[x] = S[j];                            //przypisujemy element na biezca pozycje
            przypisania++;
            j++;                                    //idziemy do nastepnego elementu
            przypisania++;
        } else {                                    // w przeciwnym wypadku
            porownania++;
            A[x] = P[m];                            //przypisujemy element na biezaca pozycje
            przypisania++;
            m++;                                    //idzemy do nastepnego
            przypisania++;

        }
    }
}

void MERGE_SORT_MODYFIKOWANY(int A[], int p, int k) {   //tworzymy tablice A z poczatkiem p i koncem k
    if (p < k) {                        //jezeli p mniejsze od k (odwrotnie mamy juz element posortowany
        porownania++;
        int s1 = p + (k - p) / 3;       //dzielimy tablice na czesc 1 i 2
        int s2 = p + 2 * (k - p) / 3;   //dzielimy tablice na czesc 2 i 3
        przypisania +=2;
        MERGE_SORT_MODYFIKOWANY(A, p, s1);  //sortujemy pierwsza czesc
        MERGE_SORT_MODYFIKOWANY(A, s1 + 1, s2); //sortujemy 2 czesc
        MERGE_SORT_MODYFIKOWANY(A, s2 + 1, k);  //sortujemy 3 czesc
        MERGE_MODYFIKOWANY(A, p, s1, s2, k);    //scalamy
    }
}
void WYPISZ_WYNIK(int A[], int n) {
//    cout << "Posortowana tablica: ";
//    for (int m = 0; m < n; m++) {
//        cout << A[m] << " ";
//    }
    cout << endl;
    cout << "Liczba porownan: " << porownania << endl;
    cout << "Liczba przypisan: " << przypisania << endl;
}

void GENERATOR_TABLIC(int A[], int n) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 100001;
    }
}


int main() {
    int sizes[] = {10, 100, 1000, 10000, 50000}; // wielkosci tablic do testu
    for (int i = 0; i < 5; i++) {
        int n = sizes[i];
        int* A = new int[n]; // dynamiczne przechowywanie tablicy A o dlugosci n
        GENERATOR_TABLIC(A, n); // generujemy losowe liczby

        // Mierzenie czasu i liczenie przypisan i porównan dla standardowego MERGE_SORT
        RESETUJ();
        clock_t start_time = clock();
        MERGE_SORT(A, 0, n - 1); // poprawne wywołanie MERGE_SORT z zakresem (0, n-1)
        clock_t end_time = clock();
        double elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC * 1000; // w milisekundach
        cout << "MERGE_SORT dla rozmiaru " << n << ":\n";
        cout << "Czas trwania: " << elapsed_time << " ms" << endl;
        WYPISZ_WYNIK(A, n);

        // Ponownie generujemy
        GENERATOR_TABLIC(A, n);

        // Mierzenie czasu i liczenie przypisan oraz porownan dla MERGE_SORT_MODYFIKOWANY
        RESETUJ();
        start_time = clock();
        MERGE_SORT_MODYFIKOWANY(A, 0, n - 1); // poprawne wywolanie MERGE_SORT_MODYFIKOWANY z zakresem (0, n-1)
        end_time = clock();
        elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC * 1000; // w milisekundach
        cout << "MERGE_SORT_MODYFIKOWANY dla rozmiaru " << n << ":\n";
        cout << "Czas trwania: " << elapsed_time << " ms" << endl;
        WYPISZ_WYNIK(A, n);

        delete[] A; // zwalniamy pamiec, usuwajac tablice A
        cout << endl;
    }

    return 0;
}
