# Moduły

Moduły to najważniesze klasy w całym projekcie. Ich zadaniem jest
koordynowanie działania pomniejszych klas, umożliwanie im komunikacji
między sobą oraz zapewninie im dostępu do zewnętrzych zasobów i
urządzeń.

## Moduł świata

Moduł świata odopowiada za inicjalizację pozostałych modułów,
komunikację z główną pętlą gry oraz obsługę krytycznych błędów.
W zależności od tego, w którym trybie się znajduje, wywołuje
funkcje aktualizujące i renderujące nadrzędnych klas.

### Inicjalizajca

Moduł wymaga podania ścieżki do pliku z ustawieniami. Jest ona
przekazywana na początku programu i jest jedyną sztywno ustaloną scieżką
w całym kodzie. Jej domyślna wartość to `scripts/settings.xml`.

Jeśli próba wczytania ustawień nie powiodła się, moduł przejdzie z trybu
`Init` w tryb `Idle`, pojawi się odpowiedni komunikat systemowy, a
następnie program zakończy działanie. W innym przypadku, wszelkie
pozostałe błędy zostaną już obsłużone przez moduł i zapisane w
dzienniku, o domyśnej nazwie `log.txt`.

Później moduł utworzy referencje do modułu graficznego i modułu audio
oraz ustawi odpowiednie wartości zmiennych. W tym momencie zebrane dane
wystarczą już do utworzenia okna pogramu, i to też nastąpi w głównej
pętli gry.

Następnie moduł stworzy dodatkowy wątek, w którym moduł graficzny i
moduł audio będą wczytywać zasoby z dysku. Będzie się to odbywać
całkowicie równolege, z wyjątkiem krótkich przerw, w których kontekst
OpenGL'a będzie inicjalizowany z głównego wątku (OpenGL wymaga by
wszelkie zasoby były inicjalizowane w tym samym wątku, w
którym są wykorzystywane). Dzięki temu zabiegowi okno programu
będzie w stanie reagować na zewnętrzne sygnały i renderować
ekran oczekiwania.

Jeśli któryś z modułów wyrzucił błąd, moduł świata przejdzie w tryb
`InitTimeError`, a z niego w tryb `Idle`. Potem program zakończy
działanie. W innym przypadku, moduł gry zostanie zainicjalizowany, a
następnie:

* Jeśli któryś z modułów wyrzucił ostrzeżenie, moduł świata przejdzie w
tryb `InitTimeWarning`, a z niego w tryb `Debug` lub `MainMenu`.
* Jeśli w ustawieniach wartość `Debug` została ustawiona na `true`,
moduł świata przejdzie w tryb `Debug`.
* Jeśli w ustawieniach wartość `Debug` została ustawiona na `false`,
moduł świata przejdzie w tryb `MainMenu`.

Szczegółowy opis inicjalizacji modułu graficznego, modułu audio i
modułu gry znajduje się w podsekcji `Inicjalizajca` sekcji
poszczególnych modułów.

### Tryby

Poniżej znajduje się kompletna lista trybów modułu świata wraz z krótkim
opisem.

* `Idle`
* `Init`
* `InitTimeWarning`
* `InitTimeError`
* `RunTimeError`
* `MainMenu`
* `Game`
* `PauseMenu`
* `ScoreBoard`
* `Debug`

## Moduł graficzny

TODO

### Inicjalizajca

TODO

### Udostępnianie zasobów

TODO

## Moduł audio

TODO

### Inicjalizajca

TODO

### Udostępnianie zasobów

TODO

## Moduł gry

Moduł gry odpowiada za przeprowadzenie rozgrywki od początku do końca.
Na podstawie danych uzyskanych przez pozostałe moduły tworzy
dwuwymiarowy obszar i wypełnia go obiektami. Następnie symuluje powstały w ten sposób
świat, aż do wystąpienia
[warunku kończącego](gameplay/#warunki-konczace).

### Inicjalizajca

W przeciwieństwie do pozostałych modułów, inicjalizacja modułu gry jest
bardzo prosta i odbywa się relatywnie szybko. Gdy szczegóły rozgrywki
zostaną już określone i przekazane do modułu gry, wykonuje on szereg
czynności:

* Określa rozmiar obszaru gry
* Generuje [obiekty bazowe](gameplay/#obiekty-bazowe), czyli planety i
statki
* Podłącza pod statki graczy
[kontrolery graczy](controllers/#kontrolery-graczy)
* Podłącza pod statki AI losowe
[kontrolery AI](controllers/#kontrolery-ai)

Następnie uruchamiana jest symulacja, podczas której powstają również
[obiekty generowane](gameplay/#obiekty-generowane), czyli asteroidy,
pociski i bonusy.

### Wyróżnione obiekty

Poniżej znajduje się lista ważniejszych obiektów, którymi zarządza moduł
gry. Koordynuje ich działanie oraz udostępnia im informacje o rozgrywce,
bez których nie mogłyby podejmować znaczących decyzji.

Jeżeli stosowany jest termin *ciało fizyczne*, oznacza to, że klasa,
do której należy obiekt, dziedziczy po klasie [Body]().

Natomiast, jeżeli stosowany jest termin *wchodzić w kolizję*, oznacza
to, że obiekt zmienia swój stan pod wpływem kolizji. Jako zmianę stanu
nie uznaje się niewielkiej zmiany prędkości lub toru ruchu. W innym
przypadku nie zmienia on swojego stanu lub kolizja w ogóle nie jest
wykrywana.

#### Planety

Planety to ciała fizyczne, których pozycja, ani prędkość nie zmienia
się. Nie podlegają działaniu grawitacji, ani nie wchodzą w kolizje.
Nie mogą zostać zniszczone. Służą one głównie jako przeszkody dla innych
ciał fizycznych.

Cechują je znaczne rozmiary i masa, rzędu kolejno kilkuset i kilku
tysięcy jednostek. W warunkach normalnej grawitacji, są jedynymi
obiektami, które potrafią w znaczący sposób zakrzywić tor ruchu
statków.

#### Asteroidy

Asteroidy to ciała fizyczne, które podlegają działaniu grawitacji i mogą
wchodzić w kolizje z planetami i innymi asteroidami. Zostają zniszczone
tylko w trakcie kolizji z planetą lub gdy zbyt długo znajdują się poza
obszarem gry. Służą jako dynamiczne przeszkody dla statków i pocisków.

Ich rozmiar jest zależny od masy, lecz nie bezpośrednio. Zachodzą
niewielkie, losowe odchylenia, które mają na celu symulować różnice
w gęstości. Są one dość różnorodne, z masami wahającymi się od kilku
do kilkunastu jednostek.

#### Statki

Statki to ciała fizyczne, które podlegają działaniu grawitacji i mogą
wchodzić w kolizje z planetami, asteroidami, pociskami i innymi
statkami. Zostają zniszczone kiedy ich poziom zdrowia spadnie do zera,
co może zostać wywołane licznymi czynnikami. Są jedynym obiektami, które
mogą być bezpośrednio kontrolowane przez graczy, ale służą także jako
ich przeciwnicy.

Ich rozmiary i masy są dość niewielkie, rzędu kolejno kilku i kilkunastu
jednostek, i zależą od typu statku.

Szczegółowe informace o statkach znajdują sie w dziale
[Statki](spaceships/).

#### Pociski

Pociski to ciała fizyczne, które podlegają działaniu grawitacji i mogą
wchodzić w kolizje z planetami, asteroidami, statkami i innymi
pociskami. Zostają zniszczone w trakcie kolizji z dowolnym obiektem,
po upływie określonego czasu lub po trafieniu promieniem.

Pociski, w przeciwieństwie do statków, nie są ograniczone przez ich
poziom energii, ale ciąg ich silników z czasem maleje. Poruszają się
one w kierunku swojego celu, czyli pierwszego statku jaki udało im się
wykryć. Do momentu wykrycia statku, poruszają się na wprost. Nie
omijają przeszkód, takich jak planety, asteroidy, czy inne pociski.

Ich rozmiary i masy są niewielkie, ale mniejsze od statków.

#### Bonusy

TODO

#### Promienie

TODO

#### Systemy cząstek

Systemy cząstek nie reagują z żadnymi innymi obiektami. Pełnią rolę
efektu graficznego, który pokazuje pracę silników lub który pojawia się
na skutek kolizji i destrukcji obiektów.

Są one zoptymalizowane w taki sposób, aby być w stanie zasymulować
kilkadziesiąt tysięcy cząstek w czasie rzeczywistym. Wykorzystują w tym
celu tablice wierzchołków, które są bezpośrednio wykorzystywane przez
OpenGL'a i przesyłane do procesora graficznego.

### Fizyka

TODO

#### Grawitacja

TODO

#### Kolizje

TODO

### Optmalizacje

TODO

#### Wykrywanie widoczności obiektu

TODO

#### Szybka funkcja obliczania dystansu

TODO

#### Redukcja opóźnień

TODO
