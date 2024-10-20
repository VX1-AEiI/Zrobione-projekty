<h1>(PL) Projekt Statki++</h1>

<h2>StatkiPlusPlus</h2>
<h3>Opis:</h3>
Konsolowa wersja gry w statki, przeznaczona do rozgrywki na jednym urządzeniu. Oprócz klasycznej rozgrywki, gra jest rozbudowana o dodatkowy tryb gry: Statki++, gdzie każdy okręt ma dodatkową umiejętność specjalną.

Gra posiada zaimplementowany ekran hot-seat, ekran wygranej, dziennik zdarzeń, opcjonalne eksportowanie statystyk z rozgrywki.

Dla większej czytelności planszy można załączyć kolorowy interfejs (przed rozpoczęciem rozgrywki).

**Uwaga: W projekcie występuje 1 błąd związany z dostępem do pamięci. Ma to miejsce w szczególnym przypadku, gdy użyje się umiejętności okrętu "niszczyciel", który znajduje się na krawędzi planszy.**
<p>Zalecane jest otwarcie projektu w środowisku w trybie Debug lub umieszczenie okrętu niszczyciel bliżej środka planszy. </p>

<h3>Komentarz:</h3>
Projekt ten jest w pewnym sensie rozszerzeniem projektu z trzeciego semestru. Na przykład, w "Grze Logicznej" trzeba było dokończyć zaczętą rozgrywkę. Tutaj można wymusić wyjście do menu głównego z poziomu rozgrywki.

**Uwaga: Kod źródłowy jest bardzo obszerny, zwłaszcza w przypadku pliku graPlusPlus.cpp.**

<h2>StatkiPlusPlusV2 (Work-In-Progress)</h2>
<h3>Opis:</h3>

Wersja V2 stanowi próbę refaktoryzacji pierwotnego kodu. 
<p>Zmiany w porównaniu z pierownym kodem:</p>
<p>+ Wyciągnięto algorytmy umiejętności specjalnych z pliku graPlusPlus.cpp do ich odpowiednich plików</p>
<p>+ Ograniczono dostępność do metod wszystkich klas - zamiast w strefie public, są teraz w strefie protected lub private</p>
<p>+ Algorytm umiejętności specjalnej dla niszczyciela został skrócony w oparciu o nowe metody. Możliwe, że wyżej wymieniony błąd z wersji 1.0 został naprawiony</p>
<p>- Projekt nie jest jeszcze "sklejony w całość"</p>

**UWAGA: Wersja StatkiPlusPlusV2 jest niedokończona i nie należy jej kompilować!**

<h3>Czego się nauczyłem:</h3>
<p>+ działanie bibliotek *threads*,*regex*,*filesystem*</p>
<p>+ dlaczego warto rozbijać większe algorytmy na mniejsze funkcje</p>
<p>+ refaktoryzacja kodu</p>
<p>+ implementacja wzorcu projektowego "strategia"</p>
