Hallo Andreas,
hier findest du die Beschreibung zu meiner Abgabe der Portfolioaufgaben.

Wenn du das Spiel startest, hast du eine Auswahl, welche Teilaufgabe compiled werden soll.
Per Mausklick kannst du auswählen, was du willst.

Das Projekt wurde mit CMake und Raylib verwirklicht (Christoph gab sein OK dafür). Hierfür wurde das Raylib Template von GitHub verwendet:
https://github.com/AdrianPfaff/raylibstarter-lite

Demnach muss man in Visual Studio CMake installiert haben, 
sollte es nicht automatisch schon drauf sein.


Aufgabe 1a:
Verschiedene Tiles:
	Start 		- Handtuch	(hier spawnt der Spieler)
	Passierbar 	- Sand		(hier kann er drüber laufen)
	Blockiert 	- Sandburg	(hier kann er nicht drüber laufen)
	Rutschig	- Eiscreme	(hier rutscht der Spieler ein Feld weiter)
	Reset		- Krabbe	(hier wird der Spieler zum Start zurückgeworfen)
	Ziel		- Wasser	(hier ist das Ziel)

In der Headerdatei ist das wichtigste der zweidimensionale Vector (std::vector<std::vector(Tile)> map) mit dem Bezeichner map. Dieser Vektor wird mit Tiles als Elemente befüllt.

Im Konstruktor der Scene "Aufgabe1a" werden erst alle Tiles als passierbar markiert, dann wird der Start und das Ziel festgelegt und danach werden die restlichen Tiles 
zufällig verteilt. Ausnahme: der mittlere Weg ist immer passierbar.


Aufgabe 1b:
Das ist so ziemlich die Aufgabe 1a, bloß mit teilweise zufällig generierter map.


Aufgabe 1c:
Hier besteht derselbe Map-Aufbau wie in 1a-b, jedoch werden fünf items auf leeren Tiles platziert. Es wurde darauf geachtet, dass auf einem Tile nicht mehrere Items platziert werden können.

In dem Item Ordner wurde für diese Aufgabe die ItemBase.h hinzugefügt und Cap.h/Cap.cpp als konkrete Itemklasse.
Die ItemBase Klasse wurde für die raylib-Funktionen mit einer Draw()-Funktion und den Variablen Texture2D und Vector2 erweitert.