#include <iostream>
#include <ctime>    // dla inicjalizacji generatora liczb losowych
#include <cstdlib>  // generowanie losowych liczb
#include <iomanip> // dla precyzji floatow
using namespace std;

int przypisania = 0;
int porownania = 0;

void RESETUJ() {                            //funkcja zerujaca po kazdym posortowaniu tablicy
    porownania = 0;
    przypisania = 0;
}

int PARTITION(float A[], int p, int r){     //int bo mamy zwrocic ostateczny indeks naszego pivota
    float x = A[r];                         //x - pivot
    int i = p - 1;                          //granica poczatkowa (ta z lewej strony), ktora przesuwamy jak pivot jak wiekszy

    for (int j = p; j <= r - 1; j++){       // pêtla iterujemy od p do r-1 (indkesy od 0 do r-1) przesuwajac sie w prawo
        if (A[j] <= x){                     // warunek na to ze jesli nasza wartosc w j jest mniejsza od x to
            i = i + 1;                      // granice przesuwamy o jedno w prawo
            float temp = A[i];              // bierzemy tymczasowa zmienna, ktora przechowuje nam wartosc w indeksie i (w celu jej nie utracenia)
            A[i] = A[j];                    // zastepujemy ja wartoscia na indeksie j
            A[j] = temp;                    // przypisujemy wartoœæ z temp (czyli oryginaln¹ wartoœæ A[i]) do A[j]
        }
    }
    float temp = A[i + 1];                  // jak juz nasza petla skonczy dzialac bierzemy wartosc i+1 do temp
    A[i + 1] = A[r];                        // umiejscawaimy nasz pivot za nasza granica
    A[r] = temp;                            // przypisujemy wartoœæ przechowan¹ w zmiennej temp (A[i + 1] przed zmiana)
                                            //do komórki A[r], zwracamy indeks naszego podzialu, ktory nie bierze udzialu w quicksorcie
    return i + 1;
}

void QUICK_SORT(float A[], int p, int r){
    if (p < r){                             //funkcja quicksort na bazie partition, znajduje dwa przedzialy ktore segregujemy
        int  s = PARTITION(A,p,r);          // funkcjonowanie podobne jak merge sort
        QUICK_SORT(A,p,s-1);
        QUICK_SORT(A,s+1,r);
    }
}

// Funkcja do partycjonowania tablicy na trzy czêœci przy u¿yciu dwóch pivota
void PARTITION_MOD(float A[], int lewy, int prawy, int &p1Index, int &p2Index) {
    // Wybór dwóch pivotów
    float p1 = A[lewy];
    float p2 = A[prawy];

    // Zapewnienie, ¿e p1 < p2, zamiana miejscami jeœli to konieczne
    if (p1 > p2) {
        swap(A[lewy], A[prawy]);
        p1 = A[lewy];
        p2 = A[prawy];
    }

    // Inicjalizacja wskaŸników
    int L = lewy + 1;
    int S = lewy + 1;
    int P = prawy - 1;

    // Proces partycjonowania
    while (S <= P) {
        if (A[S] < p1) {
            swap(A[S], A[L]);
            L++;
        } else if (A[S] >= p1 && A[S] <= p2) {
            // Element nale¿y do czêœci II, nie wykonuj zamiany
        } else { // A[K] > p2
            while (A[P] > p2 && S < P)
                P--;
            swap(A[S], A[P]);
            P--;
            if (A[S] < p1) {
                swap(A[S], A[L]);
                L++;
            }
        }
        S++;
    }

    // Umieszczanie pivotów na w³aœciwych pozycjach
    L--; P++;
    swap(A[lewy], A[L]);
    swap(A[prawy], A[P]);

    // Aktualizacja indeksów pivotów
    p1Index = L;
    p2Index = P;
}

// Rekurencyjna funkcja wykonuj¹ca zmodyfikowany quicksort
void QUICK_SORT_MOD(float A[], int lewy, int prawy) {
    if (lewy < prawy) {
        // Partycjonowanie tablicy na trzy czêœci
        int p1Index, p2Index;
        PARTITION_MOD(A, lewy, prawy, p1Index, p2Index);

        // Rekurencyjne sortowanie trzech czêœci
        QUICK_SORT_MOD(A, lewy, p1Index - 1);   // Czêœæ I
        QUICK_SORT_MOD(A, p1Index + 1, p2Index - 1); // Czêœæ II
        QUICK_SORT_MOD(A, p2Index + 1, prawy);  // Czêœæ III
    }
}

void GENERATOR_TABLIC(float A[], int n) {
    srand(time(0));                             //inicjalizacja generatora losowego
    for (int i = 0; i < n; i++) {               //po kolei generujemy az do n
        A[i] = static_cast<float>(rand()) / RAND_MAX * 50000.00;        //static_cast<float> - przekszta³camy na floata
                                                    //liczbê ca³kowit¹ generowan¹ przez rand() / RAND_MAX
    }                                               //dostajemy liczbe od 0 do 1, co mno¿ymy przez 50000
}
void WYPISZ_TABLICE(float* A, int n) {
    for (int i = 0; i < n; i++) {
        cout << fixed << setprecision(3) << A[i] << " ";       //ustawioamy ze wyswietlane liczby w tablicy beda ze sta³¹
    }                                                    //liczb¹ po przecinku (fixed) , 2 (setprecision)
    cout << endl;
}
void WYPISZ_WYNIK(float A[], int n) {
    cout << endl;
    cout << "Liczba porownan: " << porownania << endl;
    cout << "Liczba przypisan: " << przypisania << endl;
}

int main() {
    int sizes[] = {10, 100, 1000, 10000, 50000}; // wielkosci tablic do testu
    for (int i = 0; i < 5; i++) {
        int n = sizes[i];
        float* A = new float[n]; // dynamiczne przechowywanie tablicy A o dlugosci n
        float* B = new float[n]; // dodatkowa tablica B do zapamiêtania oryginalnej kolejnoœci

        GENERATOR_TABLIC(A, n); // generujemy losowe liczby

        // Kopiujemy wygenerowan¹ tablicê A do B, aby zapamiêtaæ pocz¹tkow¹ kolejnoœæ
        for (int j = 0; j < n; j++) {
            B[j] = A[j];
        }

        // Wyœwietlanie oryginalnej zawartoœci tablic A i B (dla rozmiaru 10)
        if (n == 10) {
            cout << "Oryginalna tablica A: ";
            WYPISZ_TABLICE(A, n);
            cout << "Kopia tablicy B: ";
            WYPISZ_TABLICE(B, n);
        }

        // Mierzenie czasu i liczenie przypisan i porownan dla normalnego sortowania
        RESETUJ();
        clock_t start_time = clock();
        QUICK_SORT(A, 0, n-1);
        clock_t end_time = clock();
        double elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC * 1000; // w milisekundach
        cout << "QUICK_SORT dla rozmiaru " << n << ":\n";
        cout << "Czas trwania: " << elapsed_time << " ms" << endl;
        WYPISZ_WYNIK(A, n);

        // Wyœwietlanie posortowanej tablicy A po normalnym sortowaniu (dla rozmiaru 10)
        if (n == 10) {
            cout << "Posortowana tablica A po QUICK_SORT: ";
            WYPISZ_TABLICE(A, n);
        }

        // Przywracamy oryginaln¹ kolejnoœæ liczb z B do A
        for (int j = 0; j < n; j++) {
            A[j] = B[j];
        }

        // Wyœwietlanie przywróconej tablicy A (dla rozmiaru 10)
        if (n == 10) {
            cout << "Tablica A przywrócona z B: ";
            WYPISZ_TABLICE(A, n);
        }

        // Mierzenie czasu i liczenie przypisan i porownan dla modyfikacji sortowania
        RESETUJ();
        start_time = clock();
        QUICK_SORT_MOD(A, 0, n-1);
        end_time = clock();
        elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC * 1000; // w milisekundach
        cout << "QUICK_SORT_MOD dla rozmiaru " << n << ":\n";
        cout << "Czas trwania: " << elapsed_time << " ms" << endl;
        WYPISZ_WYNIK(A, n);

        // Wyœwietlanie posortowanej tablicy A po zmodyfikowanym sortowaniu (dla rozmiaru 10)
        if (n == 10) {
            cout << "Posortowana tablica A po QUICK_SORT_MOD: ";
            WYPISZ_TABLICE(A, n);
        }

        delete[] A; // zwalniamy pamiec poprzez usuniecie tablicy A
        delete[] B; // zwalniamy pamiec poprzez usuniecie tablicy B
        cout << endl;
    }

    return 0;
}
