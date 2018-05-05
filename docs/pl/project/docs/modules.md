# Moduły

Moduły to najważniesze klasy w całym projekcie. Ich zadaniem jest
kontrolowanie działania pomniejszych klas oraz komunikacji między nimi,
a także zapewninie im dostępu do zewnętrzych zasobów i urządzeń.

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
modułu gry znajduje się w podsekcji `Inicjalizajca`, sekcji
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

## Moduł audio

TODO

## Moduł gry

TODO

### Inicjalizajca

TODO

### Główne obiekty

TODO

#### Planety

TODO

#### Asteroidy

TODO

#### Statki

TODO

#### Bonusy

TODO

#### Promienie

TODO

#### Systemy cząstek

TODO

### Fizyka

TODO

### Optmalizacje

TODO

### Warunek kończący

TODO