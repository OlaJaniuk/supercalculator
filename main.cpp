#include <stdio.h>
#include <math.h>
#include <iostream>
#include <string>
#include <complex> /*liczby zespolone*/
#include <utility>
#include <cstdint> /*żeby głupiego błędu nie wywalało w windowsie z uint64_t*/
using namespace std;
using C = complex<long double>; /*alias, żebym nie musiała za każdym razem pisać "std :: complex<double>"*/
#define PI 3.141592653589793238462643

void znajdzMinPoz(int dane[], int ilDanych)
{
    int min = dane[0];
    for (int i = 1; i < ilDanych; i++) /*dlatego < ilDanych bo tablica zaczyna się od 0*/
    {
        if (dane[i] < min)
        {
            min = dane[i];
        }
    }
    for (int i = 0; i < ilDanych; i++)
    {
        if (dane[i] == min)
        {
            cout << i + 1 << ' ';
        }
    }
    cout << '\n';
}

void zamien(int *x, int *y) /*musi działać na wskaźnikach, żeby zamieniał faktyczne wartości w tablicy, a nie ich kopie*/
{
    if (*x != *y) /*unika wykonywania operacji, któe są niepotrzebne, a mogą wprowadzać błędy*/
    {
        *x = *x + *y;
        *y = *x - *y;
        *x = *x - *y;
    }
}

void sortuj(int dane[], int lewa, int prawa) /*w funkcji zostało zastosowane sortowanie szybkie*/
{
    if (lewa < prawa)
    {
        int pivot = dane[prawa]; /*możemy wybrać pivota jako ostatni el. tablicy, bo potem i tak byśmy go tam przesuwali*/
        int i = lewa - 1;        /*dlatego lewa - 1, żeby zacząć zamienianie jakby z opóźnieniem o 1 indeks i najwyżej*/
        /*pierwszy element zamienić z pierwszym, a potem już w każdej pętli jest zwiększana wartość o 1*/

        for (int j = lewa; j < prawa; j++)
        {
            if (dane[j] >= pivot)
            {
                i++;
                zamien(&dane[i], &dane[j]);
            }
        }
        zamien(&dane[i + 1], &dane[prawa]); /*pivot trafia na swoje docelowe miejsce w tabeli*/

        int indeksPivota = i + 1; /*indeksPivota pozwala ustawić odkąd dokąd mają się odbyć kolejne sortowania rekruencyjne*/

        sortuj(dane, lewa, indeksPivota - 1);  /*tutaj zmieniają się wartości lewej*/
        sortuj(dane, indeksPivota + 1, prawa); /*i prawej strony przy każdym wywołaniu funkcji sortuj*/
    }
}

double dlugoscWektora(int dane[], int ilDanych)
{
    double sumaKwadratow = 0.0;

    for (int i = 0; i < ilDanych; i++)
    {
        sumaKwadratow += (dane[i] * dane[i]);
    }

    return sqrt(sumaKwadratow);
}

void odchylStand(int dane[], int ilDanych)
{
    double kwadratDanych = 0.0;
    double sumaDanych = 0.0;
    double odchylStandBezPierw = 0.0;
    double odchylStand = 0.0;

    for (int i = 0; i < ilDanych; i++)
    {
        kwadratDanych += (dane[i] * dane[i]);
    }
    for (int i = 0; i < ilDanych; i++)
    {
        sumaDanych += (dane[i]);
    }

    odchylStandBezPierw = ((ilDanych * kwadratDanych) - (sumaDanych * sumaDanych)) / (ilDanych * ilDanych);
    odchylStand = sqrt(odchylStandBezPierw);
    cout << floor(odchylStand) << '\n';
    // jest to przekształcony wzór na oblicznie odchylenia
}

void odwrocWMiejscu(int dane[], int ilDanych)
{
    int j = ilDanych - 1;
    for (int i = 0; i < (ilDanych / 2); i++)
    {
        zamien(&dane[i], &dane[j]);
        j--;
    }
    for (int i = 0; i < ilDanych; i++)
    {
        cout << dane[i] << ' ';
    }
    cout << '\n';
}

void generujSito(long long sito[], long long rozmiar, int &ilePierwszych)
{
    for (int i = 0; i <= rozmiar; i++)
    {
        sito[i] = 1; // Zakładamy, że wszystkie liczby są pierwsze
    }

    sito[0] = sito[1] = 0; // 0 i 1 nie są pierwsze

    for (int i = 2; i * i <= rozmiar; i++)
    {
        if (sito[i]) // Jeśli liczba jest pierwsza
        {
            for (int j = i * i; j <= rozmiar; j += i)
            {
                sito[j] = 0; // Oznaczamy wielokrotności jako złożone
            }
        }
    }

    // Zapisujemy liczby pierwsze w tej samej tablicy
    ilePierwszych = 0;
    for (int i = 2; i <= rozmiar; i++)
    {
        if (sito[i])
        {
            sito[ilePierwszych++] = i; // Zapisujemy liczby pierwsze na początku tablicy
        }
    }
}

bool szybkieSprawdzenie(long long liczba)
{
    if (liczba == 2 || liczba == 3) // Obsługa przypadków 2 i 3
    {
        return true;
    }

    if (liczba < 2) // Obsługa liczb mniejszych niż 2
    {
        return false;
    }

    int ostatniaCyfra = liczba % 10; // Sprawdzamy ostatnią cyfrę

    // Sprawdzenie podzielności przez 2 lub 5
    if (ostatniaCyfra == 0 || ostatniaCyfra == 2 || ostatniaCyfra == 4 ||
        ostatniaCyfra == 5 || ostatniaCyfra == 6 || ostatniaCyfra == 8)
    {
        return false;
    }

    // Sprawdzenie podzielności przez 3
    int sumaCyfr = 0;
    long long temp = liczba;
    while (temp > 0)
    {
        sumaCyfr += temp % 10;
        temp /= 10;
    }

    if (sumaCyfr % 3 == 0)
    {
        return false;
    }

    return true;
}

void czyLPierwsza(long long dane3[], int ilDanych)
{
    long long maxLiczba = 0; // Znalezienie maksymalnej liczby dla której musimy wygenerować sito
    for (int i = 0; i < ilDanych; i++)
    {
        if (dane3[i] > maxLiczba)
        {
            maxLiczba = dane3[i];
        }
    }

    int maxIlSprawdzen = (int)sqrt(maxLiczba);           // Zakres do pierwiastka z największej liczby
    long long *sito = new long long[maxIlSprawdzen + 1]; // Tablica na liczby pierwsze czyli dzielniki naszych liczb
    int ilePierwszych = 0;                               // Liczba znalezionych liczb pierwszych
    long long *pierwiastki = new long long[ilDanych];

    for (int i = 0; i < ilDanych; i++)
    {
        pierwiastki[i] = (long long)sqrt(dane3[i]);
    }

    generujSito(sito, maxIlSprawdzen, ilePierwszych); // Generujemy sito Eratostenesa

    for (int i = 0; i < ilDanych; i++)
    {
        long long liczba = dane3[i];
        bool wynik = true;

        // Nowe szybkie sprawdzenie na początku
        if (liczba < 2 || !szybkieSprawdzenie(liczba))
        {
            wynik = false;
        }
        else
        {
            long long lokalneMaxIlSprawdzen = pierwiastki[i]; // Poczatkowy zakres sprawdzania dzielników

            for (int j = 0; j < ilePierwszych && (long long)sito[j] <= lokalneMaxIlSprawdzen; j++)
            {
                if (liczba % sito[j] == 0)
                {
                    wynik = false;
                    break;
                }
                else
                {
                    if (liczba / sito[j] < lokalneMaxIlSprawdzen)
                    {
                        lokalneMaxIlSprawdzen = liczba / sito[j];
                    }
                }
            }
        }
        cout << (wynik ? 1 : 0) << " ";
    }
    cout << '\n';
    delete[] sito;
    delete[] pierwiastki;
}

struct Punkt
{
    long long x, y;
};

// Funkcja do zamiany dwóch punktów
void zamienPunkty(Punkt &a, Punkt &b)
{
    Punkt temp = a;
    a = b;
    b = temp;
}

// Funkcja do obliczenia kąta od punktu odniesienia
double katOdnosnie(const Punkt &p, const Punkt &ref)
{
    long long dx = p.x - ref.x;
    long long dy = p.y - ref.y;
    return atan2(dy, dx);
}

// Funkcja główna obliczająca pole wielokąta
void poleWielokata(long long dane[], int ilDanych)
{
    int n = ilDanych / 2;
    Punkt *punkty = new Punkt[n];

    // Wypełnij tablicę struktur
    for (int i = 0; i < n; ++i)
    {
        punkty[i].x = dane[2 * i];
        punkty[i].y = dane[2 * i + 1];
    }

    // Oblicz środek matematyczny wielokąta
    Punkt srodek = {0, 0};
    for (int i = 0; i < n; ++i)
    {
        srodek.x += punkty[i].x;
        srodek.y += punkty[i].y;
    }
    srodek.x /= n; // dzieli sumę współrzędnych przez ilość punktów
    srodek.y /= n;

    // Sortowanie bąbelkowe względem kątów
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            double kat1 = katOdnosnie(punkty[j], srodek);
            double kat2 = katOdnosnie(punkty[j + 1], srodek);
            if (kat1 > kat2)
            {
                zamienPunkty(punkty[j], punkty[j + 1]);
            }
        }
    }

    // Usunięcie duplikatów kątów
    int unikalne = 1;
    for (int i = 1; i < n; ++i)
    {
        double kat1 = katOdnosnie(punkty[i], srodek);
        double kat2 = katOdnosnie(punkty[unikalne - 1], srodek);
        if (kat1 != kat2)
        {
            punkty[unikalne] = punkty[i];
            unikalne++;
        }
    }
    n = unikalne;

    // Oblicz pole wielokąta za pomocą wzoru "shoelace"
    long long suma = 0;
    for (int i = 0; i < n; ++i)
    {
        int j = (i + 1) % n;
        suma += punkty[i].x * punkty[j].y - punkty[j].x * punkty[i].y;
    }
    long long pole = abs(suma) / 2;

    cout << pole << endl;

    delete[] punkty;
}

void sortujIWyswietlajWynik(int n, int *xReal, int *xImag)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            // Porównanie części rzeczywistej i, w przypadku równości, części urojonej
            if (xReal[i] > xReal[j] || (xReal[i] == xReal[j] && xImag[i] > xImag[j]))
            {
                // Zamiana elementów części rzeczywistej
                zamien(&xReal[i], &xReal[j]);

                // Zamiana elementów części urojonej
                zamien(&xImag[i], &xImag[j]);
            }
        }
    }

    // Wyświetlanie wyników
    for (int j = 0; j < n; j++)
    {
        if (xReal[j] != 0)
        {
            cout << xReal[j];
            if (xImag[j] > 0)
            {
                cout << "+";
            }
            else if (xImag[j] == 0)
            {
                cout << " ";
            }
        }

        if (xImag[j] == 1)
        {
            cout << "i ";
        }
        else if (xImag[j] == -1)
        {
            cout << "-i ";
        }
        else if (xImag[j] != 0)
        {
            cout << xImag[j] << "i ";
        }
        else if (xReal[j] == 0)
        {
            cout << xReal[j] << " ";
        }
    }
}
void rozwiazRownanie(long double dane1[])
{
    long double a = dane1[0];
    long double b = dane1[1];
    long double c = dane1[2];
    long double d = dane1[3];

    if (a == 0) /* Równanie kwadratowe w R */
    {
        long double delta = (c * c) - (4 * b * d);
        long double x1;
        long double x2;
        x1 = (-c - sqrt(delta)) / (2 * b);
        x2 = (-c + sqrt(delta)) / (2 * b);
        if (x1 < x2)
        {
            cout << floor(x1) << " " << floor(x2) << "\n";
        }
        if (x1 > x2)
        {
            cout << floor(x2) << " " << floor(x1) << "\n";
        }
        if (x1 == x2)
        {
            cout << floor(x1) << "\n";
        }
    }
    else /* Równanie sześcienne w l.zespolonych*/
    {
        long double p = (c / a) - ((b * b) / (3.0 * a * a));
        long double q = (2.0 * b * b * b) / (27.0 * a * a * a) + (d / a) - ((b * c) / (3.0 * a * a));
        long double shift = b / (3.0 * a); /*zamienia y na x*/
        long double delta = q * q + (4 * p * p * p / 27.0);

        if (abs(delta) < 0.000001) /* delta bliska zeru lub równa 0 tylko rzeczywiste pierwiastki i x2 podwójny perwiastek*/
        {
            long double u = cbrt(-q / 2.0);
            long double x1 = 2.0 * u - shift;
            long double x2 = -u - shift;

            if (floor(x1) > floor(x2))
            {
                cout << floor(x2) << " " << floor(x1) << " " << floor(x1);
            }
            else
            {
                cout << floor(x1) << " " << floor(x2) << " " << floor(x2);
            }
        }
        else if (delta < 0) /*delta mniejsza od 0, więc rzeczywiste pierwiastki*/
        {
            long double r = sqrt(-p * p * p / 27.0);
            long double fi = acos(-q / (2.0 * r));

            // long double x1 = 2.0 * cbrt(r) * cos(fi / 3.0) - shift;               /*NIE DZIAŁA! bo daje wynik 1.9999999999999*/
            long double x1 = 2.0 * sqrt(-p / 3) * cos(fi / 3.0) - shift;
            long double x2 = 2.0 * sqrt(-p / 3) * cos((fi + 2.0 * PI) / 3.0) - shift;
            long double x3 = 2.0 * sqrt(-p / 3) * cos((fi + 4.0 * PI) / 3.0) - shift;
            // int x[3] = {(int)floor(x1 + 0.000000001), (int)floor(x2 + 0.000000001), (int)floor(x3 + 0.000000001)};
            int x[3] = {(int)floor(x1), (int)floor(x2), (int)floor(x3)};

            for (int i = 0; i < 2; i++) // Sortowanie 3 elementów - iterujemy 2 razy, aby dokładnie posortować 3 elementy
            {
                for (int j = 0; j < 2 - i; j++) // ograniczamy do elementów, które jeszcze nie są posortowane
                {
                    if (x[j] > x[j + 1])
                    {
                        zamien(&x[j], &x[j + 1]);
                    }
                }
            }

            cout << x[0] << " " << x[1] << " " << x[2];
        }
        else /* delta > 0, czyli jeden pierwiastek rzeczywisty i dwa zespolone*/
        {
            long double u = cbrt((-q + sqrt(delta)) / 2.0);
            long double v = cbrt((-q - sqrt(delta)) / 2.0);
            C x1 = {u + v - shift, 0};
            C x2 = {-0.5 * (u + v) - shift, 0.5 * sqrt(3.0) * (u - v)};
            C x3 = {-0.5 * (u + v) - shift, -0.5 * sqrt(3.0) * (u - v)};
            int xImag[3] = {(int)floor(x1.imag()), (int)floor(x2.imag()), (int)floor(x3.imag())};
            int xReal[3] = {(int)floor(x1.real()), (int)floor(x2.real()), (int)floor(x3.real())};

            sortujIWyswietlajWynik(3, xReal, xImag);
        }
        cout << '\n';
    }
}

void obliczWyrazenie(int dane[])
{
    long long wynik;
    long long n = (long long)dane[0];
    wynik = (3 * (n * n * n * n) + (14 * (n * n * n)) + (21 * (n * n)) + (10 * n)) / 12;
    cout << wynik << '\n';
    // wyrażenie można w taki sposób obliczyć poprzez przekształecenia matematyczne
    // 1*2^2 + 2*3^2 + ... + n(n+1)^2 ---> Sn = suma(k*(k+1)^2) , gdzie k zmienia się od 1 do n
    //(k+1)^2=k^2 + 2k + 1 ,czyli Sn = suma(k^3 + 2k^2 + k) , gdzie k zmienia się od 1 do n
    // teraz możemy zapisać sumę Sn jako trzy oddzielne sumy i przekształcić odpowiednio ze wzorów na sumy potęg liczb naturalnych (z ciągów, szeregów itp)
    // suma(k^3) = (n^2(n+1)^2)/4
    // 2*suma(k^2) = 2*n(n+1)(2n+1)/6 = n(n+1)(2n+1)/3
    // suma(k) = n(n+1)/2
    // Po przekształceniu wyrażeń, sprowadzeniu do wspólnego mianownika i zsumowaniu ich otrzymujemy uproszczony wzór na Sn
    // Sn = (3n^4 + 14n^3 + 21n^2 + 10n)/12
}

pair<uint64_t, uint64_t> zamienStringNa64Bity(const string &lDziesietnaString)
{
    uint64_t high = 0; // górna (bardziej znacząca) część liczby
    uint64_t low = 0;  // dolna (mniej znacząca) część liczby

    for (char c : lDziesietnaString)
    {
        if (!isdigit(c)) // sprawdza, czy napis jest liczbą
        {
            throw invalid_argument("Na wejściu musi być liczba");
        }

        int digit = c - '0'; // zamienia string w liczbę

        // Sprawdzenie przepełnienia przed dodaniem nowej cyfry
        uint64_t newLow = low * 10 + digit;
        uint64_t reszta = (low > UINT64_MAX / 10) || (newLow < low); // Przeniesienie reszty
        low = newLow;

        uint64_t newHigh = high * 10 + reszta;
        if (newHigh < high)
        {
            throw overflow_error("Wartość przekracza limit 128-bitowy");
        }
        high = newHigh;
    }

    return {high, low};
}

void liczBity(const string dane2[], int ilDanych)
{
    for (int i = 0; i < ilDanych; i++)
    {
        pair<uint64_t, uint64_t> wynik = zamienStringNa64Bity(dane2[i]);
        uint64_t high = wynik.first;
        uint64_t low = wynik.second;

        int bityHigh = 0;
        while (high)
        {
            high = high & (high - 1);
            bityHigh++;
        }

        int bityLow = 0;
        while (low)
        {
            low = low & (low - 1);
            bityLow++;
        }

        cout << bityHigh + bityLow << " ";
    }
    cout << '\n';
}

int main()
{

    int nrPodproblemu;
    int ilDanych;

    while (!cin.eof())
    {
        cin >> nrPodproblemu;

        if (cin.fail()) /*sprawdza czy nrPodproblemu jest int, a jeśli nie, to return -1*/
        {
            return -1;
        }

        cin >> ilDanych;
        int *dane = new int[ilDanych];
        long double *dane1 = new long double[ilDanych];
        string *dane2 = new string[ilDanych];
        long long *dane3 = new long long[ilDanych];

        if (nrPodproblemu == 9)
        {
            for (int i = 0; i < ilDanych; i++)
            {
                cin >> dane2[i];
            }
        }
        else if (nrPodproblemu == 7)
        {
            for (int i = 0; i < ilDanych; i++)
            {
                cin >> dane1[i];
            }
        }
        else if (nrPodproblemu == 5 || nrPodproblemu == 6)
        {
            for (int i = 0; i < ilDanych; i++)
            {
                cin >> dane3[i];
            }
        }
        else
        {
            for (int i = 0; i < ilDanych; i++)
            {
                cin >> dane[i];
            }
        }

        if (nrPodproblemu == 0)
        {
            znajdzMinPoz(dane, ilDanych); /*jeśli wysyłamy dane do funkcji, to nie musimy ich już definiować, bo są zdefiniowane w funkcji wcześniej, dlatego nawet "dane" są bez nawiasów []*/
        }

        else if (nrPodproblemu == 1)
        {
            sortuj(dane, 0, ilDanych - 1);
            for (int i = 0; i < ilDanych; i++)
            {
                cout << dane[i] << ' ';
            }
            cout << '\n';
        }

        else if (nrPodproblemu == 2)
        {
            double wynik = dlugoscWektora(dane, ilDanych);
            cout << floor(wynik) << '\n';
        }

        else if (nrPodproblemu == 3)
        {
            odchylStand(dane, ilDanych);
        }

        else if (nrPodproblemu == 4)
        {
            odwrocWMiejscu(dane, ilDanych);
        }

        else if (nrPodproblemu == 5)
        {
            czyLPierwsza(dane3, ilDanych);
        }

        else if (nrPodproblemu == 6)
        {
            poleWielokata(dane3, ilDanych);
        }

        else if (nrPodproblemu == 7)
        {

            rozwiazRownanie(dane1);
        }

        else if (nrPodproblemu == 8)
        {
            obliczWyrazenie(dane);
        }

        else if (nrPodproblemu == 9)
        {
            liczBity(dane2, ilDanych);
        }

        delete[] dane;
        delete[] dane1;
        delete[] dane2;
        delete[] dane3;
    }
    return 0;
}