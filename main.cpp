#include <stdio.h>
#include <math.h>
#include <iostream>
#include <string>
#include <complex> /*liczby zespolone*/
#include <utility>
using namespace std;
using C = complex<double>; /*alias, żebym nie musiała za każdym razem pisać "std :: complex<double>"*/

void znajdzMinPoz (double dane[], int ilDanych)
{
    int min =  (int)dane[0];
    for(int i = 1; i < ilDanych; i++) /*dlatego < ilDanych bo tablica zaczyna się od 0*/
    {
        if(dane[i] < min)
        {
            min = (int)dane[i];
        }
      
    }
    for(int i = 0; i < ilDanych; i++)
    {
        if(dane[i] == min)
        {
            cout<<i + 1<<' ';
        }

    }
    cout<<'\n';
}

void zamien(double *x, double *y)     /*musi działać na wskaźnikach, żeby zamieniał faktyczne wartości w tablicy, a nie ich kopie*/
{
    if(*x != *y)           /*unika wykonywania operacji, któe są niepotrzebne, a mogą wprowadzać błędy*/
    {
        *x = *x + *y;
        *y = *x - *y;
        *x = *x - *y;
    }
}

void sortuj(double dane[], int lewa, int prawa)    /*w funkcji zostało zastosowane sortowanie szybkie*/
{
    if (lewa < prawa)
    {
        int pivot = (int)dane[prawa];    /*możemy wybrać pivota jako ostatni el. tablicy, bo potem i tak byśmy go tam przesuwali*/
        int i = lewa - 1;           /*dlatego lewa - 1, żeby zacząć zamienianie jakby z opóźnieniem o 1 indeks i najwyżej*/
                                    /*pierwszy element zamienić z pierwszym, a potem już w każdej pętli jest zwiększana wartość o 1*/

        for(int j = lewa; j < prawa; j++)
        {
            if (dane[j] >= pivot)
            {
                i++;
                zamien(&dane[i], &dane[j]);
            }
        }
        zamien(&dane[i + 1],&dane[prawa]); /*pivot trafia na swoje docelowe miejsce w tabeli*/
         
        int indeksPivota = i + 1;       /*indeksPivota pozwala ustawić odkąd dokąd mają się odbyć kolejne sortowania rekruencyjne*/ 

        sortuj(dane, lewa, indeksPivota -1);    /*tutaj zmieniają się wartości lewej*/
        sortuj(dane, indeksPivota +1, prawa);   /*i prawej strony przy każdym wywołaniu funkcji sortuj*/
    }
}

double dlugoscWektora(double dane[], int ilDanych)
{
    double sumaKwadratow = 0.0;

    for(int i = 0; i < ilDanych; i++)
    {
        sumaKwadratow += (dane[i] * dane[i]);
    }

    return sqrt(sumaKwadratow);
    
}

void odchylStand(double dane[], int ilDanych)
{
    double kwadratDanych = 0.0;
    double sumaDanych = 0.0;
    double odchylStandBezPierw = 0.0;
    double odchylStand = 0.0;

    for(int i = 0; i < ilDanych; i++)
    {
        kwadratDanych += (dane[i]*dane[i]);
    }
    for(int i = 0; i < ilDanych; i++)
    {
        sumaDanych += (dane[i]);
    }

    odchylStandBezPierw = ((ilDanych * kwadratDanych) - (sumaDanych * sumaDanych)) / (ilDanych*ilDanych); 
    odchylStand = sqrt(odchylStandBezPierw);
    cout<<floor(odchylStand)<<'\n';
    //jest to przekształcony wzór na oblicznie odchylenia
}

void odwrocWMiejscu(double dane[], int ilDanych)
{
    int j = ilDanych - 1;
    for(int i = 0; i < (ilDanych / 2); i++)
    {   
        zamien(&dane[i],&dane[j]);
        j--;
    }
    for (int i = 0; i < ilDanych ; i++)
    {
        cout<<dane[i]<<' ';
    }
    cout<<'\n';
}

void czyLPierwsza()
{

}

void poleWielokata()
{

}

void rozwiazRownanie(double dane[])
{
    double a = dane[0];
    double b = dane[1];
    double c = dane[2];
    double d = dane[3];

    if(a == 0)  /* Równanie kwadratowe w R */
    {
        double delta;
        delta = (c * c) - (4 * b * d);
        double x1;
        double x2;
        x1 = (- c - sqrt(delta))/ (2 * b);
        x2 = (- c + sqrt(delta))/ (2 * b);
         if(x1 < x2)
        {
            cout<<floor(x1)<<' '<<floor(x2)<<'\n';
        }
        if(x1 > x2)
        {
             cout<<floor(x2)<<' '<<floor(x1)<<'\n';
        }
        if(x1 == x2)
        {
            cout<<floor(x1)<<'\n';
        }
    }
    else        /* Równanie sześcienne w l.zespolonych*/
    {
        C p = C((c / a) - ((b * b) / (3 * a * a)), 0.0);
        C q = C(((2 * b * b * b) / (27 * a * a * a)) + (d / a) - ((b * c) / (3 * a * a)), 0.0);
        C shift = C(b / (3.0 * a), 0.0);
        C delta = sqrt(pow(q / 2.0, 2) + pow(p / 3.0, 3));

        const double PI = acos(-1.0);
        C omega = polar(1.0, 2.0 * PI / 3.0);
        C omega2 = pow(omega, 2);

        
        C u1 = pow(-q / 2.0 - delta, 1.0 / 3.0);    /*Obliczenie pierwiastków sześciennych na u i v */
        C u2 = omega * u1;
        C u3 = omega2 * u1;

        C v1 = pow(-q / 2.0 + delta, 1.0 / 3.0);
        C v2 = omega * v1;
        C v3 = omega2 * v1;

        C uniqueResults[9];
        int uniqueCount = 0;

        for (C u : {u1, u2, u3})            
        {
            for(C v : {v1, v2, v3})
            {
                if(abs(u * v + p / 3.0) < 0.00000001)    /* Sprawdzenie wszystkich kombinacji u i v - wybór takich, że u*v = -p/3*/
                {
                    C x0 = u + v - shift;
                    C x1 = omega * v + omega2 * u - shift;
                    C x2 = omega2 * v + omega * u - shift;
                    for(C x : {x0, x1, x2})
                    {
                        bool isUnique = true;
                        for (int i = 0; i < uniqueCount; ++i)
                        {
                            if (abs(x.real() - uniqueResults[i].real()) < 1e-7 &&
                                abs(x.imag() - uniqueResults[i].imag()) < 1e-7)
                            {
                                isUnique = false;
                                break;
                            }
                        }
                        // Jeśli wynik jest unikalny, dodaj do tablicy
                        if (isUnique && uniqueCount < 9)
                        {
                            uniqueResults[uniqueCount++] = x;
                        }
                    }
                }
            }
        }
        for(int i = 0; i < uniqueCount; ++i)
        {
            double real = floor(uniqueResults[i].real());
            double imag = floor(uniqueResults[i].imag());
                    
            cout<<real;
            if(imag < 0 )
            {
                cout<< imag << 'i';
            }
            else if(imag > 0 )
            {
                cout<< '+' << imag << 'i';
            }
            // else if(imag == 1)
            // {
            //     cout<<'i';
            // }
            // else if (imag == -1)
            // {
            //      cout<<'-i';
            // }
            cout<< ' ';
        }
        cout << '\n';    
    }
}

    
    

    
    



void obliczWyrazenie(double dane[])
{
    long long wynik;
    long long n = (long long)dane[0];
    wynik = (3 * (n * n * n * n) + (14 * (n * n * n)) + (21 * (n * n)) + (10 * n)) / 12;
    cout<<wynik<<'\n';
    //wyrażenie można w taki sposób obliczyć poprzez przekształecenia matematyczne
    //1*2^2 + 2*3^2 + ... + n(n+1)^2 ---> Sn = suma(k*(k+1)^2)   , gdzie k zmienia się od 1 do n
    //(k+1)^2=k^2 + 2k + 1     ,czyli Sn = suma(k^3 + 2k^2 + k)  , gdzie k zmienia się od 1 do n
    //teraz możemy zapisać sumę Sn jako trzy oddzielne sumy i przekształcić odpowiednio ze wzorów na sumy potęg liczb naturalnych (z ciągów, szeregów itp)
    //suma(k^3) = (n^2(n+1)^2)/4
    //2*suma(k^2) = 2*n(n+1)(2n+1)/6 = n(n+1)(2n+1)/3
    //suma(k) = n(n+1)/2
    //Po przekształceniu wyrażeń, sprowadzeniu do wspólnego mianownika i zsumowaniu ich otrzymujemy uproszczony wzór na Sn
    //Sn = (3n^4 + 14n^3 + 21n^2 + 10n)/12

}

// void ileBitow(unsigned long long dane2[], int ilDanych)
// {
//     for(int i = 0; i < ilDanych; i++)
//     {
//         unsigned long long n = dane2[i] ;
//         int licz = 0;
//         //cout<<n<<':';
//         while (n != 0)
//         {
//             n = n & (n - 1);
//             licz++;
//         }
//         cout<<licz<<' ';
//     }

//     cout<<'\n';
// }
pair<uint64_t, uint64_t> zamienStringNa64Bity(const string & lDziesietnaString)
{
    // std::cout << "decimalString: " << decimalString << std::endl;
    // Ensure the input is a valid decimal number
    for (char c : lDziesietnaString)
    {
        if (!isdigit(c))
        {
            throw invalid_argument("Na wejściu musi być liczba");
        }
    }

    uint64_t high = 0;  /*zmienne do zapisu liczby w dwoch czesciach*/
    uint64_t low = 0;

    for (char c : lDziesietnaString) {
        int digit = c - '0'; /*zamienia string w liczbe*/

        // Simulate 128-bit arithmetic
        uint64_t newLow = low * 10 + digit;       // Add the new digit to the low part
        uint64_t reszta = (low > UINT64_MAX / 10) || (newLow < low); /*sprawdza czy nie ma przepelnienia*/
        low = newLow;

        uint64_t newHigh = high * 10 + reszta;    /*dodaje reszte do nowej liczby high*/
        if (newHigh < high)
        {                    
            throw overflow_error("Value exceeds 128-bit limit");
        }
        high = newHigh;
    }
    // std::cout << "high: " << high << " low: " << low << std::endl;
    return {high, low};
}
int liczBity(uint64_t number)
{
    int count = 0;
    while (number)
    {
        count += (number & 1);
        number >>= 1;   /*przesuwanie bitow*/
    }
    return count;
}
void function_9_1(string dane2[],int ilDanych)
{
    // Zlicz liczbę ustawionych bitów w liczbie naturalnej (unsigned).
    for (int i = 0; i < ilDanych; i++)
    {
        
        //convert 128 bit sting to hi and low 64 bits numbers
        auto [high, low] = zamienStringNa64Bity(dane2[i]); /*zamienia podany string na wejsciu na dwie liczby zeby miescily sie w zakresie*/

        cout << liczBity(high) + liczBity(low) << " ";

    }
    cout << '\n';
}


int main()
{

    int nrPodproblemu;
    int ilDanych;
    
    while(!cin.eof())
    {
        cin>>nrPodproblemu;

        if(cin.fail()) /*sprawdza czy nrPodproblemu jest int, a jeśli nie, to return -1*/
        {
            return -1;
        }

        cin>>ilDanych;
        
        double* dane = new double[ilDanych];

        string* dane2 = new string[ilDanych];

        if(nrPodproblemu == 9)
        {
            for(int i = 0; i < ilDanych; i++)
            {
                cin>>dane2[i];
            }
        }
        else
        {
            for(int i = 0; i < ilDanych; i++)
            {
                cin>>dane[i];
            }
        }
        



        if(nrPodproblemu == 0)
        {
            znajdzMinPoz(dane, ilDanych); /*jeśli wysyłamy dane do funkcji, to nie musimy ich już definiować, bo są zdefiniowane w funkcji wcześniej, dlatego nawet "dane" są bez nawiasów []*/
        }

        else if(nrPodproblemu == 1)
        {
            sortuj(dane, 0, ilDanych - 1);
            for (int i = 0; i < ilDanych; i++)
            {
                cout<<dane[i]<< ' ';
            }
            cout<< '\n';
        }

        else if(nrPodproblemu == 2)
        {
            double wynik = dlugoscWektora(dane, ilDanych);
            cout<<floor(wynik)<<'\n';
        }

        else if(nrPodproblemu == 3)
        {
            odchylStand(dane, ilDanych);
        }

        else if(nrPodproblemu == 4)
        {
            odwrocWMiejscu(dane, ilDanych);
        }

        else if(nrPodproblemu == 5)
        {
            czyLPierwsza();
        }

        else if(nrPodproblemu == 6)
        {
            poleWielokata();
        }
        
        else if(nrPodproblemu == 7)
        {
            
            rozwiazRownanie(dane);
           
        }

        else if(nrPodproblemu == 8)
        {
            obliczWyrazenie(dane);
        }
        
        else if(nrPodproblemu == 9)
        {
            function_9_1(dane2, ilDanych);
        }
        else
        {
            delete[] dane;
            delete[] dane2;
            return 0;
        }
        delete[] dane;

    }
        return 0;
}