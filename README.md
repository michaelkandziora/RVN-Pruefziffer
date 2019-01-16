## RVN-Pruefziffer

Ein kleines C-Programm zur Überprüfung der Deutschen Rentenversicherungsnummer

Beinhaltet:
- Berechnung der Prüfziffer
- Berechnung des Alters aus den Daten der RVN


# Aufbau der 12 stelligen RVN

Bereichs- | Geburtsdatum | 1.Buchstb- | Geschlecht      | Prüfziffer
nummer    |              | Nachname   | M 00-49 W 50-99 | 
//---------------------------------------------------------------------
 X_1  X_2 |  T T M M J J |     C      |    Y_1 Y_2      |    P
 
 # Berechnung der Prüfziffer
 
 Die RVN wird von links nach rechts mit folgenden Konstanten gewichtet:
 
   2  1  2  5  7  1  2  1  2  1  2  1
   
 Produkte aus rvn[i] * konstante[i] aufsummiert und MODULO 10 ergibt die Prüfziffer
 
 
# Programmablauf
 
Das Programm startet mit dem Hauptmenü, es werden 3 Auswahlmöglichkeiten angeboten.
 
  1. Berechne Prüfziffer
  2. Berechne Daten aus RVN
  3. Beende das Programm mit 'q' oder 'Q'
  
Berechne Prüfziffer:

  Rufe RVN-Eingabe-Funktion auf (inkl. Validierungsschritten)
  Rufe RVN-CheckSum-Funktion auf (errechnet die Prüfziffer und speichert diese an der Stelle 12 ab)
  Rufe RVN-Output-Funktion auf (Gibt die eingegebene RVN inkl. der berechneten Prüfziffer aus + Geburtsdatum + Alter)

Berechne Daten aus RVN:
  
  Rufe RVN-Eingabe-Funktion auf (inkl. Validierungsschritten)
  Rufe RVN-Output-Funktion auf (Gibt die eingegebene RVN inkl. der berechneten Prüfziffer aus + Geburtsdatum + Alter)
  
# Programminformationen

Die RVN wird per dynamische Speicherallokation auf dem HEAP erstellt.



~ Dokumentation Ende 
