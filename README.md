# Superkalkulator - Projekt Algorytmiczny

## Opis projektu
Projekt zrealizowany w ramach zajęć na uczelni. Jest to aplikacja konsolowa w C++ rozwiązująca zestaw 10 problemów matematycznych i algorytmicznych. 

Głównym założeniem i trudnością projektu był **całkowity zakaz używania wbudowanych funkcji biblioteki standardowej** (takich jak `std::sort`, `std::min`, `std::max`). Wymagało to samodzielnej implementacji algorytmów operujących bezpośrednio na tablicach i wskaźnikach, dbając o odpowiednią złożoność obliczeniową i zarządzanie pamięcią.

## Treść zadania (Wymagania)
*Zadanie polega na rozwiązaniu 10 podproblemów matematycznych. UWAGA! NIE WOLNO używać wbudowanych funkcji, takich jak min, max, sort i tym podobnych. Każdy podproblem to jedna funkcja.*

**Część podstawowa:**
0. Znajdź pozycje zawierające najmniejszą wartość dla wejściowego ciągu liczb.
1. Posortuj wejściowy ciąg liczb (wymagane użycie funkcji z zad. 0).
2. Znajdź długość euklidesową wektora (tzw. normę euklidesową).
3. Znajdź odchylenie standardowe dla wejściowego ciągu liczb.
4. Zapisz podany ciąg w tablicy i odwróć go w miejscu (in-place).

**Część zaawansowana:**
5. Odpowiedz, czy liczba jest pierwsza.
6. Znajdź pole wielokąta wypukłego (punkty jako tablica struktur).
7. Rozwiąż równanie kwadratowe oraz sześcienne w liczbach zespolonych.
8. Wyznacz wartość wyrażenia $1\cdot 2^2 + 2\cdot 3^2 + ... + n(n+1)^2$ dla zadanego $n$.
9. Zlicz liczbę ustawionych bitów w liczbie naturalnej (unsigned).

## Ciekawe problemy i zastosowane rozwiązania
Ze względu na nałożone ograniczenia, implementacja wymagała kilku niestandardowych podejść, na które warto zwrócić uwagę w kodzie:
* **Własny QuickSort:** Zaimplementowany rekurencyjnie z użyciem wskaźników (`zamien(&dane[i], &dane[j])`), aby działał w miejscu bez dodatkowej alokacji pamięci.
* **Symulacja arytmetyki 128-bitowej (Zadanie 9):** Aby uniknąć przepełnienia (overflow) przy zliczaniu bitów w bardzo dużych liczbach, napisałam funkcję parsowania wejściowego ciągu znaków (`string`) i dzielenia go na dwie oddzielne 64-bitowe liczby całkowite (`high` i `low`).
* **Optymalizacja matematyczna (Zadanie 8):** Zamiast liczyć sumę szeregu w pętli (co dałoby złożoność $O(n)$), wyprowadziłam algebraicznie wzór zwarty, co redukuje czas obliczeń do $O(1)$.
* **Równania sześcienne:** Zastosowano `std::complex` i wzory Cardano do znajdowania pierwiastków w dziedzinie zespolonej.

## Kompilacja i uruchomienie
Kompilacja przy użyciu standardowego kompilatora (np. g++):
```bash
g++ main.cpp -o superkalkulator