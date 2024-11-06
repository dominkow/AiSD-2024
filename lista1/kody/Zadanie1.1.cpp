#include <iostream>
#include <cstdlib> // do losowych liczb
#include <ctime>   // do inicjalizacji losowych liczb
using namespace std;

int porownania = 0;     // zadanie 4 - utworzenie zmiennych do przechowywania porownan i przypisan
int przypisania = 0;

void RESETUJ() {        // zeruje liczniki porownan i przypisan co kazde sortowanie tablicy
    porownania = 0;
    przypisania = 0;
}

void INSERTION_SORT(int A[], int n) {       //utworzenie tablicy A, o wielkosci n
    for (int i = 1; i < n; i++) {           //wprowadzenie zmiennej i, i = 1 (bo przyjmujemy ze el. indeksu 0 jest posortowany)
        int key = A[i];                     //przypisanie dla key elementu ktory chcemy posortowac (wstawic w odpowiednie miejsce w naszej posortowanej tablicy)
        przypisania++;
        int j = i - 1;                      //przypisanie dla j miejsca tuz przed i w celu wskazania ostatniego posortowanego elementu
        przypisania++;
        while (j >= 0 && A[j] > key) {      //wykonujemy petle while dopuki miescimy sie w tablicy i element z posortowanej części tablicy (A[i]) jest większy od key.
            porownania++;
            A[j + 1] = A[j];                //przesuwamy A[j] o jedno miejsce w prawo aby zrobic miejsce dla key
            przypisania++;
            j--;
            przypisania++;                  //zmniejszamy wartosc o jeden, przesuwajac o jedna pozycje w lewo
        }
        porownania++;                       //dodatkowe porównanie, gdy warunek while przestaje byc spelniony
        A[j + 1] = key;                     //while skonczyl dzialac, czyli znalezlismy miejsce dla key, przypisujemy je
        przypisania++;
    }
}

void INSERTION_SORT_MODIFIED(int A[], int n) {   //stworzenie tablicy A, dlugosci n
    for (int s = 1; s < n - 1; s += 2) {         //wprowadzenie zm. s, ziwkesza sie o 2 aby przechodzic dwa elementy na raz
        int pierwszy = A[s];                     //definiujemy pierwsza i druga pozycje
        int drugi = A[s + 1];
        przypisania += 2;
        if (pierwszy > drugi) {                  //jesli pierwsz wiekszy od drugiego to zamieniamy je miescami (sort.rosnaco)
            swap(pierwszy, drugi);
            przypisania += 2;                    //swap traktujemy jako 2 przypisania
            porownania++;
        }
        int k = s - 1;
        przypisania++;                           //ustawiamy k na s-1, (miejsce bezposrednio przed pierwszy),przesuwamy sie w prawo
        while (k >= 0 && A[k] > pierwszy) {      //petla while, k musi byc wiekszy niz pierwszy, bo chcemy przesunac w prawo
            porownania++;
            A[k + 1] = A[k];                     //przesuwamy element o jedne w prawo(do k+1)
            przypisania++;
            k--;
            przypisania++;                        //zmniejszamy wartosc o 1
        }
        A[k + 1] = pierwszy;                     //wstawiamy pierwszy na odpowiednie miejsce A[k+1]
        przypisania++;
        k = s;
        przypisania++;                            //ustawiamy k na pozycje s aby moc sortowac element drugi
        while (k >= 0 && A[k] > drugi) {         //while analogicznie do tego przy pierwszym
            porownania++;
            A[k + 1] = A[k];
            przypisania++;
            k--;
            przypisania++;
        }
        A[k + 1] = drugi;
        przypisania++;
    }                                            //trzeba rozwazyc przypadki gdy n jest parzyste i nieprzyste
    if (n % 2 == 0) {                            //sprawdzamy czy n parzyste czy nie
        porownania++;
        int ostatni = A[n - 1];                  //jesli tak to robimy ekstra wstawienie dla ostatniego elementu bo nie mial pary
        przypisania++;
        int k = n - 2;
        przypisania++;                          //bierzemy k jako przedostatni element
        while (k >= 0 && A[k] > ostatni) {       // dzialanie analogiczne do powyzszych
            porownania++;
            A[k + 1] = A[k];                     //Przesuwamy elementy większe od ostatni o jedno miejsce w prawo
            przypisania++;
            k--;
        }
        A[k + 1] = ostatni;                      //przypisujemy ostatni element
        przypisania++;
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
    srand(time(0)); // Inicjalizacja losowego generatora

    // Przykladowe dane wejsciowe do testow
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
        cout << "Proba " << i + 1 << " dla " << n << " elementow:" << endl;
        WYPISZ_WYNIK(arr, n);
        cout << endl;
    }

    cout << "Test zmodyfikowanego insertion sort:" << endl;
    for (int i = 0; i < proby; i++) {
        int n = rozmiary[i];
        int arr[n];
        for (int j = 0; j < n; j++) {
            arr[j] = rand() % 100;
        }

        RESETUJ();
        INSERTION_SORT_MODIFIED(arr, n);
        cout << "Proba " << i + 1 << " dla " << n << " elementow:" << endl;
        WYPISZ_WYNIK(arr, n);
        cout << endl;
    }
    return 0;
}

