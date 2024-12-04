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
    float x = A[r];
    przypisania++;                          //x - pivot
    int i = p - 1;
    przypisania++;                          //granica poczatkowa (ta z lewej strony), ktora przesuwamy jak pivot jak wiekszy

    for (int j = p; j <= r - 1; j++){       // pêtla iterujemy od p do r-1 (indkesy od 0 do r-1) przesuwajac sie w prawo
        if (A[j] <= x){
            porownania++;                                // warunek na to ze jesli nasza wartosc w j jest mniejsza od x to
            i = i + 1;
            przypisania++;                  // granice przesuwamy o jedno w prawo
            float temp = A[i];
            przypisania++;                  // bierzemy tymczasowa zmienna, ktora przechowuje nam wartosc w indeksie i (w celu jej nie utracenia)
            A[i] = A[j];
            przypisania++;                    // zastepujemy ja wartoscia na indeksie j
            A[j] = temp;
            przypisania++;                    // przypisujemy wartosc z temp (czyli oryginalna wartosc A[i]) do A[j]
        }
    }
    float temp = A[i + 1];
    przypisania++;                          // jak juz nasza petla skonczy dzialac bierzemy wartosc i+1 do temp
    A[i + 1] = A[r];
    przypisania++;                          // umiejscawaimy nasz pivot za nasza granica
    A[r] = temp;
    przypisania++;                          // przypisujemy wartoœæ przechowan¹ w zmiennej temp (A[i + 1] przed zmiana)
                                            //do komórki A[r], zwracamy indeks naszego podzialu, ktory nie bierze udzialu w quicksorcie
    return i + 1;
}

void QUICK_SORT(float A[], int p, int r){
    if (p < r){
        porownania++;                                //funkcja quicksort na bazie partition, znajduje dwa przedzialy ktore segregujemy
        int  s = PARTITION(A,p,r);
        przypisania++;                              // funkcjonowanie podobne jak merge sort
        QUICK_SORT(A,p,s-1);
        QUICK_SORT(A,s+1,r);
    }
}

// Modyfikacja polegajaca na dzieleniu tablicy na trzy czesci przy uzyciu dwoch pivotow
void PARTITION_MOD(float A[], int lewy, int prawy, int &p1Index, int &p2Index) {
    float p1 = A[lewy];
    przypisania++;                  //wybieramy pivoty
    float p2 = A[prawy];
    przypisania++;


    if (p1 > p2) {
        porownania++;                            //sprawdzenie warunku, ktory jest wiekszy
        swap(A[lewy], A[prawy]);
        przypisania +=2;                        //jesli konieczne zamienic miejscami
        p1 = A[lewy];
        przypisania++;                           //przypisanie wartosci pivotom
        p2 = A[prawy];
        przypisania++;
    }

    // Inicjalizacja wskaźników
    int L = lewy + 1;                               //miejsce gdzie bedziemy przenosci element mniejsze od p1
    int S = lewy + 1;                               //aktualny przegladany indeks (w petli)
    int P = prawy - 1;
    przypisania+=2;                              //miejsce gdzie bedziemy przenosic elementy wieksze od p2

    while (S <= P) {                                //przechodzimy przez petle do momentu przejscia wszystkich indeksow
        if (A[S] < p1) {
            porownania++;                           // jak wartosc jest mniejsza od pivota zamieniamy miejscami
            swap(A[S], A[L]);
            przypisania++;                          //przesuwamy nasza granica o jedno miejsce w prawo
            L++;
            przypisania++;
        } else if (A[S] >= p1 && A[S] <= p2) {
            porownania++;                               //jezeli A[S] ma wartosc pomiedzy pivotami to zostawiamy go bez zmian
        } else { // A[S] > p2
            porownania++;
            while (A[P] > p2 && S < P)                               //szukamy od prawej strony elementu, który nie jest większy od p2
                P--;
                przypisania++;                               //p przesuwamy w lewa strone
            swap(A[S], A[P]);
            przypisania+=2;                       //zamieniamy miejscami A[S] (wiekszy od p2) z A[P] (potencjalnie <=p2)
            P--;
            przypisania++;                                    //zmniejszamy p bo ilosc elementow rozpatrywanych sie zmniejszyla
            if (A[S] < p1) {
                porownania++;                       //zmniejszamy indeks bo ilosc elementow do posortowania sie zmniejszyla
                swap(A[S], A[L]);
                przypisania+=2;                     //jesli wartosc A[S] jest mniejsza od p1 to zamieniamy miejscami
                L++;
                przypisania++;                                //przesuwamy L (granice lewa) w prawo
            }
        }
        S++;
        przypisania++;                                        //zwieskzmay indeks S aby przejsc do nastepenego elementu
    }

    L--;                            // cofamy sie o jeden w lewo aby L wskazywalo ostatni element w strefie < p1
    P++;                            // idziemy o jeden w prawo aby P wskazywalo pierwsze miejsce w strefie > p2
    swap(A[lewy], A[L]);            //zamiana oryginalnego pivota z A[L]
    swap(A[prawy], A[P]);
    przypisania+=6;                 //zamiana oryginalnego powiota z A[P]

    p1Index = L;                    //ustawiamy indeksy pivotow p1 i p2 do wlasciwego quicksorta (podzial na 3 obszary)
    p2Index = P;
    przypisania+=2;
}

void QUICK_SORT_MOD(float A[], int lewy, int prawy) {
    if (lewy < prawy) {
        porownania++;
        int p1Index, p2Index;
        przypisania++;              //partition dzialanie
        PARTITION_MOD(A, lewy, prawy, p1Index, p2Index);
        QUICK_SORT_MOD(A, lewy, p1Index - 1);   // Czesc I
        QUICK_SORT_MOD(A, p1Index + 1, p2Index - 1); // Czesc II
        QUICK_SORT_MOD(A, p2Index + 1, prawy);  // Czesc III
    }
}

void GENERATOR_TABLIC(float A[], int n) {
    srand(time(0));                                                     //inicjalizacja generatora losowego
    for (int i = 0; i < n; i++) {                                       //po kolei generujemy az do n
        A[i] = static_cast<float>(rand()) / RAND_MAX * 50000.00;        //static_cast<float> - przeksztalcamy na floata
                                                                        //liczbe calkowita generowana przez rand() / RAND_MAX
    }                                                                   //dostajemy liczbe od 0 do 1, co mno¿ymy przez 50000
}
void WYPISZ_TABLICE(float* A, int n) {
    for (int i = 0; i < n; i++) {
        cout << fixed << setprecision(3) << A[i] << " ";       //ustawiamy ze wyswietlane liczby w tablicy beda ze stale
    }                                                           //liczbe po przecinku (fixed) , 2 (setprecision)
    cout << endl;
}
void WYPISZ_WYNIK(float A[], int n) {
    cout << endl;
    cout << "Liczba porownan: " << porownania << endl;
    cout << "Liczba przypisan: " << przypisania << endl;
}

int main() {
    int sizes[] = {100000, 200000, 300000, 400000, 500000}; // wielkosci tablic do testu
    for (int i = 0; i < 5; i++) {
        int n = sizes[i];
        float* A = new float[n]; // dynamiczne przechowywanie tablicy A o dlugosci n
        float* B = new float[n]; // dodatkowa tablica B do zapamietania oryginalnej kolejnosci

        GENERATOR_TABLIC(A, n); // generujemy losowe liczby

        // Kopiujemy wygenerowana tablice A do B, aby zapamietac poczatkowa kolejnosc
        for (int j = 0; j < n; j++) {
            B[j] = A[j];
        }

        // Mierzenie czasu i liczenie przypisan i porownan dla normalnego sortowania
        RESETUJ();
        clock_t start_time = clock();
        QUICK_SORT(A, 0, n-1);
        clock_t end_time = clock();
        double elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC * 1000; // w milisekundach
        cout << "QUICK_SORT dla rozmiaru " << n << ":\n";
        cout << "Czas trwania: " << elapsed_time << " ms";
        WYPISZ_WYNIK(A, n);
        cout << "\n";

        // Przywracamy oryginalna kolejnosc liczb z B do A
        for (int j = 0; j < n; j++) {
            A[j] = B[j];
        }

        // Mierzenie czasu i liczenie przypisan i porownan dla modyfikacji sortowania
        RESETUJ();
        start_time = clock();
        QUICK_SORT_MOD(A, 0, n-1);
        end_time = clock();
        elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC * 1000; // w milisekundach
        cout << "QUICK_SORT_MOD dla rozmiaru " << n << ":\n";
        cout << "Czas trwania: " << elapsed_time << " ms";
        WYPISZ_WYNIK(A, n);
        cout << "\n\n";


        delete[] A; // zwalniamy pamiec poprzez usuniecie tablicy A
        delete[] B; // zwalniamy pamiec poprzez usuniecie tablicy B
        cout << endl;
    }

    return 0;
}
