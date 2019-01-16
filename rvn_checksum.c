#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
//#include <dos.h>
#include <direct.h>
//#include <dir.h>
#include <io.h>
#include "rvn_checksum.h"


/**     PRINT OUTPUT COLORS

        Name         | Value
                     |
        Black        |   0
        Blue         |   1
        Green        |   2
        Cyan         |   3
        Red          |   4
        Magenta      |   5
        Brown        |   6
        Light Gray   |   7
        Dark Gray    |   8
        Light Blue   |   9
        Light Green  |   10
        Light Cyan   |   11
        Light Red    |   12
        Light Magenta|   13
        Yellow       |   14
        White        |   15
**/


/** START FUNKTION **/
void start(void){

    fflush(stdin);
    // Programm Ueberschrift
    plott_head("RVN Pruefuuuuuuuuung");

    // Zeilenumbruch
    printf("\n");

    // System Ausgabe: Aufruf Hauptmenue
    blue_print("System"," LOG[Rufe Startmenue auf]");

    // Rufe Hauptmenue auf
    start_menu();
}

/** INITIALISIERE RV-NUMMER **/
char* rvn_init(void){
    // Dynamische Speicherallokation auf dem HEAP
    char* rvn = (char*) malloc(sizeof(char)*RVN_SIZE);

    // Pruefe ob System den Speicher freigegeben hat
    if(rvn == NULL){
        // Falls Speicher nicht bekommen, versuche es erneut (Rekursiver Funktionsaufruf)
        return rvn_init();
    }

    // Initialisiere das RVN ARRAY mit ASCII NULLEN [ (int) 0 = (char) 48 ]
    for(int i = 0 ; i < RVN_SIZE ; i++){
        rvn[i] = 48;
    }

    //Debug
    //rvn_print(rvn);

    // Gebe die initialisierte RVN zurueck
    return rvn;
}

/** FUNKTION ZUR AUSGABE DER PROGRAMM UEBERSCHRIFT **/
void plott_head(char* title){

    // Zaehle Anzahl der Buchstaben aus dem uebergebenen String
    int count = 0;
    while(title[count] != '\0'){
        count++;
    }

    // Berechne die Abstaende links und rechts um den String in die Mitte zu setzen
    int width = (int)(TERMINAL_COL_SIZE - count)/2 ;

    // Setze Farbe auf gruen (2) und plotte eine Reihe * -Chars
    SetColor(2);
    for(int i = 0 ; i < TERMINAL_COL_SIZE+2; i++){
        printf("*");
    }
    printf("\n*");
    // Platzhalter - Plotte Leerzeichen
    for(int i = 0 ; i < TERMINAL_COL_SIZE; i++){
        printf(" ");
    }
    printf("*\n*");
    // Setze Ueberschrift in die Mitte
    for(int i = 0 ; i < TERMINAL_COL_SIZE ; i++){
        if(i < width-1 || i > TERMINAL_COL_SIZE-width){
            printf(" ");
        }else if(i == width+1+(sizeof(title)%sizeof(char))){
            printf(" %s ",title);
        }else{
            continue;
        }
    }
    printf("*\n*");
    // Platzhalter
    for(int i = 0 ; i < TERMINAL_COL_SIZE; i++){
        printf(" ");
    }
    printf("*\n");
    // Unterer Rahmen aus * -Chars
    for(int i = 0 ; i < TERMINAL_COL_SIZE+2; i++){
        printf("*");
    }
    // Setze Farbe wieder aus weis (15)
    SetColor(15);

    printf("\n");
}

/** FUNKTION ZUM PLOTTEN DER UEBERSCHRIFT **/
void plott_title(char* title){

    // Zaehle Anzahl der Buchstaben aus dem uebergebenen String
    int count = 0;
    while(title[count] != '\0'){
        count++;
    }

    // Berechne die Abstaende links und rechts um den String in die Mitte zu setzen
    int width = (int)(TERMINAL_COL_SIZE - count)/2 ;

    printf("\n\n");

    // Ausgabe
    for(int i = 0 ; i < TERMINAL_COL_SIZE+2 ; i++){
        // * - Zeichen rechts und links
        if(i < width || i > TERMINAL_COL_SIZE-width){
            printf("*");
        }
        // Setze Titel in die mitte
        else if(i == width+1+(sizeof(title)%sizeof(char))){
            printf(" %s ",title);
        }else{
            // Setze Schleife fort wenn keine if-Anweisung zutrifft (Schritt nicht unbedingt noetig)
            continue;
        }
    }
    printf("\n\n");
}

/** START MENUE FUNKTION **/
void start_menu(void){
    // Hilfsvariable fuer Auswahl
    char c = '*';

    // do-while Schleife: mindestens 1 Mal wird das Menue auf jeden Fall angezeigt
    do{
        // Initialisiere RVN
        char* rvn = rvn_init();
        // Loesche Tastaturpuffer
        fflush(stdin);
        // Plotten des Menuetitels
        plott_title("START MENUE");
        // Plott: Legende
        printf("\n\t[1] - Rentenversicherungsnummer pruefen\n\t[2] - Rentenversicherungsdaten aus RV-Nummer ausgeben lassen\n\t[q] - Programm beenden\n\n");
        // Benutzer eingabe: gruen
        green_print("Auswahl"," ");
        // Einlesen des Chars und abspeichern in HV c
        scanf("%c", &c);
        // Loesche Tastaturpuffer
        fflush(stdin);

        // Aufruf je nach Auswahl
        switch(c){
        case '1':
            // RVN einlesen
            plott_title("RVN EINLESEN");
            blue_print("System"," LOG[Rufe RVN_READ(*) auf]");
            rvn_read(rvn);
            // Ab hier sind alle Pruefungen erfolgreich beendet und die RVN Prueffunktion kann aufgerufen werden
            blue_print("System"," LOG[Rufe RVN_CHECKSUM(*) auf]");
            rvn_checksum(rvn);
            // RVN Daten ausgeben
            plott_title("RVN PRUEFUNG ABGESCHLOSSEN");
            blue_print("System"," LOG[Rufe RVN_DATAOUTPUT(*) auf]");
            rvn_dataOutput(rvn);
            break;
        case '2':
            // RVN einlesen
            plott_title("RVN EINLESEN");
            blue_print("System"," LOG[Rufe RVN_READ(*) auf]");
            rvn_read(rvn);
            // RVN Daten ausgeben
            plott_title("RVN DATEN");
            blue_print("System"," LOG[Rufe RVN_DATAOUTPUT(*) auf]");
            rvn_dataOutput(rvn);
            break;
        case 'q':
        case 'Q':
            c = 'q';
            break;
        // Pruefe ob Eingabe korrekt
        default:
            error_print("ERROR"," Falsche Eingabe");
            break;
        }

        printf("\n");
        fflush(stdin);

        // RVN nicht mehr benoetigt - Speicher freigeben
        free(rvn);
    }while(c != 'q');
}

/** FUNKTION ZUM EINLESEN DER RVN **/
void rvn_read(char* rvn){
    blue_print("System"," LOG[Starte RVN_READ(*)]\n");

    // Ausgabe: Initialisierung
    blue_print("System"," Ihre 11 stellige Rentenversicherungsnummer sollte wie folgt aussehen:");
    printf("\n\n\t\t\t  BEREICH   |       GEBURTSDATUM      |   NACHNAME  | GESCHLECHT \n\t\t\t[X_1] [X_2] | [T] [T] [M] [M] [J] [J] | [Buchstabe] | [Y_1] [Y_2]\n\n");
    blue_print("System"," Bitte geben Sie hier ihre 11 stellige Rentenversicherungsnummer zur Ueberpruefung ein:\n");
    green_print("Eingabe"," ");

    // Loesche Tastaturpuffer
    fflush(stdin);

    // Schleife zur Eingabe der einzelnen Charakter, umgeht das \0 Ende-String-Zeichen , RVN besteht so aus tatsaechlichen 12 Char
    for(int i = 0 ; i < RVN_SIZE ; i++){
        // Einlesen der Character
        scanf("%c",&rvn[i]);

        // Abbrechen mit q
        if(rvn[0] == 'q'){
            error_print("ERROR"," System abort");
            error_print("System"," Programm wird neugestartet");

            fflush(stdin);
            // Rekursiver Aufruf der Funktion
            return start();
            break;
        }

        // Pruefe ob RVN zu kurz
        if(i < RVN_SIZE-1 && rvn[i] == '\n'){
            error_print("ERROR"," !!! ACHTUNG - EINGABE ZU KURZ !!!");
            error_print("System"," Bitte RVN erneut eingeben.");

            fflush(stdin);
            // Rekursiver Aufruf der Funktion
            return rvn_read(rvn);
        }
    }

    // Loesche Tastaturpuffer
    fflush(stdin);

    // Pruefe ob an der Buchstabenposition (8) auch ein Buchstabe steht, A=65 (ASCII)
    if(rvn[RVN_LETTER_POS] < 65){
        error_print("ERROR"," !!! ACHTUNG - EINGABE FALSCH !!!");
        error_print("System"," Bitte RVN erneut eingeben.");

        // Rekursiver Aufruf der Funktion
        return rvn_read(rvn);
    }

    //DEBUG
    //rvn_print(rvn);

    blue_print("System"," LOG[Beende RVN_READ(*)]");
}

/*int *rvn_toInteger(char* rvn){
    int* rvnValues = rvn_init();

    for(int i = 0 ; i < RVN_SIZE && i != RVN_LETTER_POS ; i++){
        rvnValues[i] = rvn[i]-48;
    }

    rvnValues[RVN_LETTER_POS] = (rvn[RVN_LETTER_POS]-64)/10;
    rvnValues[RVN_LETTER_POS+1] = (rvn[RVN_LETTER_POS]-64)%10;
    rvnValues[RVN_LETTER_POS+2] = rvn[RVN_LETTER_POS+1]-48;
    rvnValues[RVN_LETTER_POS+3] = rvn[RVN_LETTER_POS+2]-48;

    //debug
    rvn_print(rvnValues);

    return rvnValues;
}*/

/** AUSGABE FUNKTION FUER RVN NUMMER **/
void rvn_print(char* rvn){

    blue_print("System", " Ihre 11 stellige Rentenversicherungsnummer:");
    printf("\n\n  BEREICH   |       GEBURTSDATUM      |   NACHNAME  | GESCHLECHT | PRUEFZIFFER \n\n  ");
    for(int i = 0 ; i < RVN_SIZE ; i++){
        printf("  %c",rvn[i]);
        if(i == 1){
            printf("    |  ");
        }else if(i == 7){
            printf("     |    ");
        }else if(i == 8){
            printf("      |  ");
        }else if(i == 10){
            printf("    |  ");
        }
    }

    /*
    // Ausgabe als Integer Variable
    printf("\n  ");
    for(int i = 0 ; i < RVN_SIZE ; i++){
        printf(" %i",rvn[i]);
        if(i == 1){
            printf("    |  ");
        }else if(i == 7){
            printf("     |    ");
        }else if(i == 8){
            printf("      |  ");
        }else if(i == 10){
            printf("    |  ");
        }
    }
    */
    printf("\n");
}

/** RVN PRUEFFUNKTION **/
void rvn_checksum(char* rvn){
    blue_print("System"," LOG[Starte RVN_CHECKSUM(*)]\n");

    // significand: bestehend aus den Gewichtungskonstanten
    const int significand[RVN_SIZE] = {2,1,2,5,7,1,2,1,21,2,1};
    // Pruefziffer
    int* checkDigit = (int*) malloc(sizeof(int));
    // Hilfsvariable zur Prozentrechnung fuer die Ausgabe des Fortschrittes
    float pct = 1.0;

    blue_print("System"," Starte RVN Prueffunktion\n");

    // mit 0 initalisieren
    *checkDigit = 0;

    // Berechnung bis zum vorletzten Wert, da dieser nicht in die Berechnung miteinfliesst und fuer die Pruefziffer zur Verfuegung steht
    for(int i = 0 ; i < RVN_SIZE-1 ; i++){
        // Pruefe ob Buchstabe
        if(i==RVN_LETTER_POS){
            // Ziehe vom ASCII Wert 64 ab um auf dem Buchstabenzaehler zu landen (A=65.. -64, A = 1. Buchstabe)
            *checkDigit += (significand[i]/10)*((rvn[i]-64)/10);
            *checkDigit += (significand[i]%10)*((rvn[i]-64)%10);
        }else{
            // Ziehe vom ASCII Wert 48 ab um auf 0 zu landen (0=48.. -48, 0 = 0)
            *checkDigit += significand[i]*(rvn[i]-48);
        }
        // Zeige Fortschritt in der Ausgabe an
        SetColor(3);
        printf("$ System ");
        SetColor(15);
        printf("> Pruefung zu %.2f %% abgeschlossen\r",pct=((float)(i+1)/(float)(RVN_SIZE-1))*100);
    }
    printf("\n");

    // Rechne die Summe Modulo 10 um die Pruefziffer zu erhalten
    *checkDigit = *checkDigit%10;

    // Setze die Pruefziffer an die 12. Ziffernstelle
    rvn[RVN_SIZE-1] = *checkDigit+48;

    //DEBUG
    //rvn_print(rvn);

    // dynamischen Speicher freigeben
    free(checkDigit);

    blue_print("System"," LOG[Beende RVN_CHECKSUM(*)]\n");
}

/** RVN DATEN AUSGABE **/
void rvn_dataOutput(char* rvn){
    blue_print("System"," LOG[Starte RVN_OUTPUT(*)]\n");
    // Ausgabe RVN Komplett
    blue_print("System"," Ihre Daten zur Rentenversicherungsnummer\n");
    rvn_print(rvn);

    // Ausgabe der Pruefziffer
    blue_print("System"," Ihre Pruefziffer lautet: ");
    printf("%c\n", rvn[RVN_SIZE-1]);

    // Ausgabe des Geburtsdatums im DATUM Format (TT.MM.JJJJ)
    blue_print("System"," Geburtsdatum: ");
    for(int i = 2 ; i < 8 ; i++){
        printf("%c",rvn[i]);
        if(i == 3){
            printf(".");
        }else if(i == 5){
            printf(".");
        }
    }
    printf("\n");

    // Geburtsjahr ins Integerformat bringen und zu 1900 addieren
    int alter_jahr = 1900 + ((rvn[6]-48)*10) + (rvn[7]-48);
    blue_print("System", " Alter: ");
    // Ausgabe: Aktuelles Jahr minus dem Geburtsjahr
    printf("%d", CURRENT_YEAR - alter_jahr);

    blue_print("System"," LOG[Beende RVN_OUTPUT(*)]\n");
}

/** Siehe: https://stackoverflow.com/questions/29574849/how-to-change-text-color-and-console-color-in-codeblocks **/
void SetColor(int ForgC){
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    //We use csbi for the wAttributes word.
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        //Mask out all but the background attribute, and add in the forgournd color
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}

void error_print(const char* errorTag, const char* errorMessage){

        SetColor(4);
        printf("\n$ %s ",errorTag);
        SetColor(15);
        printf(">%s\n",errorMessage);
}

void green_print(const char* greenTag, const char* greenMessage){

        SetColor(2);
        printf("\n$ %s ",greenTag);
        SetColor(15);
        printf(">%s",greenMessage);
}

void blue_print(const char* blueTag, const char* blueMessage){

        SetColor(3);
        printf("\n$ %s ",blueTag);
        SetColor(15);
        printf(">%s",blueMessage);
}
