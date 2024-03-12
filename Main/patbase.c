#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define MAXARRAY 20
#define MAXSTR 20


//Alle Variablen die mehrfach vorkommen global definiert um die Funktionen übersichtlicher zu gestalten, da man sie nur einmal callen muss, wenn auch nicht RAM schonend...
struct Patient
{
	char name[MAXSTR];
	char vorname[MAXSTR];
	int messwert;
	int patnr;
};

char vorname[MAXSTR];
char name[MAXSTR];
int messwert;
int patnr;
int anzahl_patienten = 0;
struct Patient patdb[MAXARRAY];

FILE *counter;
FILE *backup;

// Funktionsprototypen
void patient_anlegen();
void patienten_anzeigen();
void db_save();
void db_open();



int main(int argc, char* argv[])
{
	char command='\0';

	while(command != 'q') {
		
		printf("\n\n\nGeben Sie einen Befehl ein:\n");
		printf("(e) Patienten eingeben:\n");
		printf("(a) Patienten anzeigen:\n");
		printf("(s) Datensatz speichern: \n");
		printf("(d) Datensatz oeffnen:\n");
		printf("(q) Ende\n");
		command=getch(); 

		switch(command) {
			case 'e':
				patient_anlegen();
				break;
			case 'a':
				patienten_anzeigen();
				break;
			
			//s für save und d für open benutzt um im "qweasd" Block zu bleiben
			case 's':
				db_save();
				break;
			case 'd':
				db_open();
				break;
		}

	}
	
	return 0;
}

	
//anzahl_patienten ist der Counter für die Anzahl an Einträgen im Array, somit muss für jeden neuen Eintrag auch der COunter steigen um immer in den höchsten unbeschriebenen einzutragen

void patient_anlegen() {
	
	if (anzahl_patienten < 20)
	{
		printf("\nPatientenummer eingeben: ");
		scanf("%d", &patdb[anzahl_patienten].patnr);

		printf("Vornamen des Patienten eingeben: ");
		scanf("%s", &patdb[anzahl_patienten].vorname);

		printf("Nachnamen des Patienten eingeben: ");
		scanf("%s", &patdb[anzahl_patienten].name);

		printf("Messwert eingeben: ");
		scanf("%i", &patdb[anzahl_patienten].messwert);

		anzahl_patienten++;


	}
	else
	{
		//ist aktuell nur ein CATCH falls Array voll ist. Könnte in Zukunft ausgebaut werden mit einer "Eintrag löschen", ist derzeit nicht gefordert...
		printf("\nDer Speicher ist voll, bitte entfernen sie Eintraege, bevor sie neue anlegen koennen.");		
	}



}


//Funktion zum Anzeigen... i ist ein separater Zähler um den Status des Eintrages zu tracken bis "anzahl_patienten", was die gesamte Anzahl der Einträge inne hat, erreicht ist
void patienten_anzeigen(){
		
	for (int i = 0; i < anzahl_patienten; i++)
	{
		//"Datensatz:" ist nur als nettes Extra drin, falls die Löschfunktion jemals hinzugefügt wird
		printf("\n\nDatensatz: %i\nPatientennummer: %i\nVorname: %s\nNachname: %s\nMesswert: %i", i+1, patdb[i].patnr, patdb[i].vorname, patdb[i].name, patdb[i].messwert);	
	}
	
}



void db_open(){
	
	counter = fopen("counter.txt", "r");
	if (counter == NULL){
		printf("\n\nDatei konnte nicht gelesen werden!");}
	else{
		fscanf(counter ,"%i", &anzahl_patienten);
		fclose(counter);
	}

	backup = fopen("backup.bin", "rb");
		if (backup == NULL){
		printf("\n\nDatei konnte nicht gelesen werden!");}
	else{
		fread(&patdb, sizeof(patdb), 1, backup); 
		printf("\n\nDatei eingelesen");
		fclose(backup);
	}

	printf("\n\n%i", anzahl_patienten);
}



void db_save(){

	counter = fopen("counter.txt", "w");
	if (counter == NULL){
		printf("\n\nDatei konnte nicht gespeichert werden!");}
	else{
		fprintf(counter, "%i", anzahl_patienten);
		fclose(counter);
	}


	backup = fopen("backup.bin" ,"wb");
		if (backup == NULL){
		printf("\n\nDatei konnte nicht gespeichert werden!");}
	else{
		fwrite(patdb, sizeof(patdb), 1, backup);
		printf("\n\nDatenbank gespeichert.");
		fclose(backup);
	}
}