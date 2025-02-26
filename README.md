# 3.Übung



## Abgabetermin: 11.01.2024

In dieser Übung sollen Sie eine Animation in C++ mit Qt implementieren. Es
handelt sich um eine Visualisierung der Türme von Hanoi.
Eine alte indische Sage erzählt von einem Tempel in der Stadt Benares, wo Mönche
am Turm des Brahma arbeiten. Ihre Aufgabe ist es, einen Turm von 64 aufeinander-
gestapelten goldenen Scheiben von einem Pflock auf einen anderen Pflock zu trans-
ferieren, wobei sie einen dritten Pflock hilfsweise als Ablage benutzen dürfen. Alle
Scheiben sind kreisrund und haben ein Loch in ihrem Mittelpunkt, wodurch sie auf den
Pflöcken gestapelt werden können. Außerdem haben alle Scheiben unterschiedliche
Durchmesser. Allerdings darf niemals eine größere Scheibe auf eine kleinere gelegt
werden, und es darf immer nur eine Scheibe auf einmal bewegt werden. Der Sage
nach wird bei Beendigung dieser Aufgabe die Welt zu Staub zerfallen und das Univer-
sum im Nichts verschwinden.
Recherchieren Sie, wo nötig, welche Qt-Objekte Sie sinnvollerweise nutzen können.
Versuchen Sie möglichst sauberen Code zu schreiben. Sollten Ihnen die Konzepte des
Clean-Coding noch nicht geläufig sein, machen Sie sich mit den Konzepten vertraut
und versuchen Sie diese bei der Umsetzung der Aufgaben zu berücksichtigen. Im
Laufe Ihres Studiums sind Sie bereits mit Design Patterns in Berührung gekommen.
Es wird nun Zeit, diese auch aktiv umzusetzen. Verwenden Sie, wo sinnvoll, Design
Patterns. Kommentieren Sie Ihre Implementation ausführlich. Jede Funktion sollte mit
einer Beschreibung mit Übergabeparametern, Rückgabeparamtern und einer kurzen
Beschreibung der Funktionalität versehen werden. Informieren Sie sich hierfür über
die Standards in C++.

## Aufgabe 1 

Die Aufgabe sollte rekursiv gelöst werden, wobei die Anzahl n der Scheiben variabel
sein soll. Im Fall einer einzigen Scheibe (Basisfall), ist die Lösung sehr einfach: Es
werden die Scheibe vom linken Stapel genommen und auf den rechten Stapel gesetzt.
Nehmen wir nun an, wir wissen bereits, wie n-1 Scheiben transferiert werden können,
es müssen aber insgesamt n Scheiben versetzt werden. Hierfür müssen nur die n-1
Scheiben auf den mittleren Stapel transferiert werden, die n-te Scheibe auf den rech-
ten Stapel gesetzt, und im Anschluss die n-1 Scheiben vom mittleren Stapel auf den
rechten transferiert werden.
Ein möglicher Pseudocode für das rekursive Vorgehen könnte wie folgt aussehen:
```
funktion bewege (Zahl i, Stab a, Stab b, Stab c) {
    falls (i > 0) {
        bewege(i-1, a, c, b);
        verschiebe oberste Scheibe von a nach c;
        bewege(i-1, b, a, c);
    }
}
```
Schreiben Sie eine oder mehrere C++-Klassen um die Pflöcke und Scheiben zu reprä-
sentieren, sowie die Lage der Scheiben auf den Pflöcken. Die Scheiben sind durch
ihren Durchmesser eindeutig definiert. Sie sollen neben ihrem Durchmesser auch je-
weils eine Farbe besitzen, durch die sie sich sichtbar voneinander unterscheiden. Die
Anzahl der Scheiben soll variabel sein. Zur Visualisierung wird ein Hauptfenster, in
dem die drei Pflöcke und die Scheiben angezeigt werden, sowie die Bewegung der
Scheiben animiert wird benötigt. Der Pflock mit dem Anfangsstapel steht links, der
Zielpflock, auf dem sich der Turm am Ende befinden soll steht rechts, und in der Mitte
befindet sich der Hilfspflock. Im Laufe der Animation wird eine Scheibe nach der an-
deren bewegt, und zwar in einer flüssigen Bewegung. Wählen Sie für die Bewegung
einer Scheibe eine geeignete Funktion, die die Bahn der Bewegung beschreibt, sowie
eine weitere geeignete Funktion, die die Geschwindigkeitsänderung der Scheibe be-
schreibt, so dass die Bewegung kontinuierlich und harmonisch ist. Die Dauer eines
Zuges soll über einen Parameter verändert werden können (d.h. die Geschwindigkeit-
sänderungsfunktion muss stetig verändert werden können). Sinnvoller Weise können
hier bereits entsprechend vorhandene Funktionen von Qt genutzt werden.

Das Hauptfenster sollte über eine Statuszeile verfügen, die anzeigt, wie viele Scheiben
im Spiel sind, wie viele Züge schon erfolgt sind, und ob die Animation startbereit, im
Gange, pausiert oder beendet ist. Es sollte über vier Schalter "Neu", "Start",
"Pause" und "Beenden" zum Neuerzeugen der Startkonfiguration, zum Starten der
Animation, zum Pausieren der Animation und zum Beenden der Animation verfügen.
Schließlich sollte das Fenster noch über ein Menü verfügen, über das ein Einstellungs-
fenster geöffnet werden kann. Die Größe des Hauptfensters soll eine Mindestgröße
nicht unterschreiten, aber sich der Größe der Anzahl der Scheiben und dem Durch-
messer der größten Scheibe anpassen.
Bei Betätigen der Schalter werden folgende Aktionen ausgelöst:
- Neu: Eine neue Startaufstellung der Scheiben wird erstellt und angezeigt

- Start: Die Animation wird gestartet.

- Pause: Eine laufende Animation wird pausiert bzw. eine pausierte Animation
wird weitergeführt; während der Pause blinkt die Anzeige der
Statusleiste

- Beenden: Die Animation wird abgebrochen und das Fenster geschlossen

Das Einstellungsfenster soll es ermöglichen, die Anzahl der Scheiben und die Dauer
eines Zuges der Animation zu verändern.

Überlegen und implementieren Sie eine Objektorientierte Datenstruktur für Ihr Spiel.
Stellen Sie sicher, dass Ihr Programm ordnungsgemäß funktioniert. Wählen Sie die
einzelnen Komponenten, ihr Layout und die Menüführung unter softwareergonomi-
schen Gesichtspunkten

## Aufgabe 2

Erstellen Sie eine Präsentation (Vortragsdauer ca. 10-12 Min) wie Ihre Software
entwickelt wurde und welche Patterns Sie wo, wie und warum verwendet haben.
Beschreiben Sie weiterhin die Architektur und Funktionsweise Ihres Programms und
fügen Sie zur Unterstützung Diagramme (bspw. Klassendiagramme,
Datenflussdiagramme, ...), sowie passende Sichten des 4+1 Sichtenmodells nach
Kruchten bei. Stellen Sie das Ergebnis der Entwicklung (bspw. live oder als Video)
vor. Machen Sie Ihre Entscheidung für die verwendeten Patterns, Diagramme und
Sichten transparent. Teilen Sie die Arbeit an der Präsentation gleichmäßig über alle
Gruppenmitglieder auf und machen Sie kenntlich, wem welches Kapitel/Thema
zuzuschreiben ist. Die Präsentation richtet sich an interessierte Software-
Engineering-Studierende Ihres Jahrgangs (Zielgruppe). Konzentrieren Sie sich in der
Präsentation auf die wesentlichen Aspekte der Entwicklung Ihres Projektes.

Erzeugen Sie eine zip-Datei, die Ihre vollständigen zu diesem Projekt gehörigen
Dateien und Ihre Präsentation enthält, und laden Sie sie auf OLAT zu der
zugehörigen Übung unseres Kurses hoch.

Die Präsentationen werden am 12.01.2024 in der Übungsstunde von Ihnen
präsentiert. (Bei Bedarf auch in der darauffolgenden Übungsstunde). Bringen Sie zur
Präsentation eine ausgedruckte Version der Folien für den Dozenten mit.