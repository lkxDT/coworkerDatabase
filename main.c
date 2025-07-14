#include <stdio.h>
#include "database.h"
#include "fileHandler.h"

int main() {
        Database db = initDatabase();
        int choice;
        printf("Willkommen zur Mitarbeiter-Datenbank!\n\n");
        while(1) {
                printf("1. Mitarbeiter hinzufügen\n");
                printf("2. Mitarbeiter löschen\n");
                printf("3. Mitarbeiterdaten nach Name anzeigen\n");
                printf("4. Alle Mitarbeiterdaten anzeigen\n");
                printf("5. Edit Coworker\n");
                printf("6. Datenbank in JSON-Datei speichern\n");
                printf("7. Datenbank aus JSON-Datei laden\n");                
                printf("8. Beenden\n\n");
                printf("Wählen Sie eine Option: ");
                scanf("%d", &choice);
                if(choice == 1) {
                        addCoworker(&db);
                } else if(choice == 2) {
                        deleteCoworker(&db);
                } else if(choice == 3) {
                        printCoworkerByName(&db);
                } else if(choice == 4) {
                        printAllCoworkers(&db);
                } else if(choice == 5) {
                        editCoworker(&db);
                } else if(choice == 6) {
                        char filename[100];
                        printf("Geben Sie den Dateinamen zum Speichern an: ");
                        scanf("%s", filename);
                        writeJSONToFile(&db, filename);
                        printf("Datenbank unter %s gespeichert.\n", filename);
                } else if(choice == 7) {
                        char filename[100];
                        printf("Geben Sie den Dateinamen zum Laden an: ");
                        scanf("%s", filename);
                        readJSONFromFile(&db, filename);
                        printf("Datenbank aus %s geladen.\n", filename);
                
                } else if(choice == 8) {
                        break;
                } else {
                        printf("Ungültige Auswahl, bitte versuchen Sie es erneut.\n");
                }
        }


        // Free allocated memory
        freeDatabase(&db);
        printf("Exiting the Coworker Database. Goodbye!\n");
        return 0;
}