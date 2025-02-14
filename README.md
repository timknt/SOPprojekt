# Greppy - Ein leistungsstarkes Suchwerkzeug

## Beschreibung
Greppy ist ein leistungsfähiges Kommandozeilen-Tool zur Textsuche in Dateien und Verzeichnissen. Es unterstützt verschiedene Optionen zur Steuerung der Suche, einschließlich rekursiver Suche, Groß-/Kleinschreibung, Zählmodus und mehr.

## Features
- Unterstützung für rekursive Suche
- Case-Insensitive-Modus
- Maximalanzahl an Treffern konfigurierbar
- Zählen von Übereinstimmungen
- Ausgabe in verschiedenen Formaten

## Installation
### Voraussetzungen
- C-Compiler (z. B. GCC oder Clang)
- CMake (für die Erstellung des Build-Systems)

### Build-Anleitung
1. Repository klonen:
   ```sh
   git clone <REPOSITORY-URL>
   cd greppy
   ```
2. CMake-Build erstellen:
   ```sh
   mkdir build && cd build
   cmake ..
   make
   ```
3. Das Programm ist nun ausführbar:
   ```sh
   ./greppy <Suchbegriff> <Datei/Verzeichnis>
   ```

## Nutzung
Das Programm kann mit verschiedenen Optionen aufgerufen werden:
```sh
./greppy [OPTIONEN] <SUCHBEGRIFF> <DATEI/VERZEICHNIS>
```

### Wichtige Optionen
- `-r` : Rekursive Suche in Unterverzeichnissen
- `-i` : Suche ohne Berücksichtigung der Groß-/Kleinschreibung
- `-c` : Anzahl der Treffer zählen
- `-m <N>` : Maximale Anzahl an Treffern festlegen
- `-q` : Keine Ausgabe (nur Exit-Code)

### Beispielaufrufe
- Suche nach "error" in `log.txt`:
  ```sh
  ./greppy error log.txt
  ```
- Rekursive Suche nach "TODO" in `src/`:
  ```sh
  ./greppy -r TODO src/
  ```
- Anzahl der Vorkommen von "debug" zählen:
  ```sh
  ./greppy -c debug log.txt
  ```

## Lizenz
Dieses Projekt steht unter der MIT-Lizenz. Weitere Informationen sind in der `LICENSE`-Datei zu finden.

## Autor
Entwickelt von Adrian Stelter, Tim Knüttel und Jakob Hämmelmann.

