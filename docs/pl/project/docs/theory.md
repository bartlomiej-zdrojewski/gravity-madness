# Teoria

Poniżej przedstawiono problemy matematyczne i fizyczne, których
rozwiązanie jest konieczne do zaimplementowania kluczowych mechanik w
grze. Zostały one posortowane w kolejności od najbardziej znaczącego
do najmniej znaczącego.

## Pozycja, prędkość i przyspieszenie

abc

## Przyspieszenie grawitacyjne

Należy wyprowadzić wzór na przyspieszenie grawitacyjne działające w
osiach x i y na ciało (spaceship) pod wpływem ciałą centralnego
(planet). Ciało centralne może pozostać nieruchome (jak w przypadku
planet) lub przyspieszać pod wpływem drugiego ciała (jak w przypadku
asteroid). Uzyskany wzór zostanie zastosowany później w równaniach
ruchu.

Dana jest masa ciała \(M_{S}\) i ciała centralnego \(M_{P}\), pozycja
ciała \((X_{S},Y_{S})\) i ciała centralnego \((X_{P},Y_{P})\) oraz
stała grawitacji \(G\), która wbrew nazwie może zmieniać się w trakcie
rozgrywki.

$$F = G {M_{1} \cdot M_{2} \over R^2}$$
$$F = M_{1} \cdot a_{1} = M_{2} \cdot a_{2}$$
$$M_{S} \cdot a_{S} = G {M_{S} \cdot M_{P} \over R_{SP}^2}$$
$$a_{S} = G {M_{P} \over R_{SP}^2}$$
$$\Delta x = X_{P} - X_{S} \quad \Delta y = Y_{P} - Y_{S}$$
$$r = R_{SP} = \sqrt{(\Delta x)^2+(\Delta y)^2}$$
$$\cos\alpha = {\Delta x \over r} \quad \sin\alpha = {\Delta y
\over r}$$
$$a_{x_{S}} = a_{S} \cdot \cos\alpha = G {M_{P} \over r^2} \cdot
{\Delta x \over r} = G {M_{P} \cdot (X_{P} - X_{S}) \over r^3}$$
$$a_{y_{S}} = a_{S} \cdot \sin\alpha = G {M_{P} \over r^2} \cdot
{\Delta y \over r} = G {M_{P} \cdot (Y_{P} - Y_{S}) \over r^3}$$

Otrzymaliśmy wzory na przyspieszenie grawitacyjne w osi x
(\(a_{x_{S}}\)) oraz w osi y (\(a_{y_{S}}\)). Dla zmniejszenia
złożoności operacji wyznaczania ich wartości, odległość między ciałami
\(r\) została obliczona tylko raz.

## Kolizje sprężyste

abc

## Kolizje niesprężyste

abc

## Kąt między dwoma punktami

Należy podać wzór na kąt \(\alpha\) między dwoma punktami względem osi
x.

Dana jest pozycja punktu \(A = (X_{A},Y_{A})\) oraz punktu
\(B = (X_{B},Y_{B})\).

$$ \alpha = \arctan{Y_{B}-Y_{A} \over X_{B}-X_{A}} $$

## Kąt między półprostą i punktem

abc

## Badanie przecięcia półprostej i okręgu

Należy określić, czy dana półprosta (ray) przecina dany okrąg (circle).
Jeśli tak, podać punkt przecięcia najmniej odległy od początku
półprostej względem osi x oraz odległość między początkiem półrpostej,
a środkiem okręgu.

Dany jest początek półprostej \((X_{R},Y_{R})\), kąt \(\alpha\) między
półprostą a osią x oraz środek \((X_{C},Y_{C})\) i promień \(R\) okręgu.

$$ a = \tan \alpha $$
$$ b = Y_{R} - a \cdot X _{R} $$
$$ \begin{cases} y = a \cdot x + b \\ (X_{C}-x)^2 + (Y_{C}-y)^2 = R^2
\end{cases} $$
$$ \begin{cases} y = a \cdot x + b \\ l \cdot x^2 + m \cdot x + n = 0 \\
l = 1 + a^2 \\ m = 2 \cdot ( a \cdot ( b - Y_{C} ) - X_{C} ) \\ n = b^2
+ X_{C}^2 + Y_{C}^2 - R^2 - 2 \cdot b \cdot Y_{C} \end{cases} $$
$$ \Delta = m^2 - 4 \cdot l \cdot n $$

Dalsze działania zależą od wartości \(\Delta\):

* Dla \(\Delta < 0\) półprosta nie przecina okręgu.

* Dla \(\Delta = 0\) półprosta przecina okrąg w dokładnie w jednym
punkcie:

$$ abc $$

* Dla \(\Delta > 0\) półprosta przecina okrąg w dokładnie w dwóch
punktach:

$$ abc $$

## Badanie przecięcia dwóch odcinków

abc
