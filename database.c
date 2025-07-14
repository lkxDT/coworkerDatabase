#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "database.h"
#define NAME_LEN 30


Coworker initWorker(char name[NAME_LEN], char abteilung[NAME_LEN], int age, float salary) {
        Coworker temp;
        strcpy(temp.name, name);

        strcpy(temp.abteilung, abteilung);

        temp.age = age;

        temp.salary = salary;
        return temp;
}

Coworker readCoworker() {
        char name[NAME_LEN];
        char abteilung[NAME_LEN];
        int age;
        float salary;
        
        printf("Geben Sie den Namen ein: ");
        scanf("%s", &name);
        printf("Geben Sie den Abteilungsamen ein: ");
        scanf("%s", &abteilung);
        printf("Geben Sie das Alter des Mitarbeiters ein: ");
        scanf("%d", &age);
        printf("Geben Sie das Gehalt ein: ");
        scanf("%f", &salary);

        return initWorker(name, abteilung, age, salary);
}



Database initDatabase() {
        Database db;
        db.array = NULL;
        db.length = 0;
        return db;
}

void addCoworker(Database* db) {
        db->length++;
        db->array = realloc(db->array, db->length * sizeof(Coworker));
        db->array[db->length-1] = readCoworker();
        printf("Mitarbeiter hinzugefügt bei Index %d.\n\n", db->length-1);
}

long getIndexForName(Database* db, char word[NAME_LEN]) {
        for(int i = 0; i < db->length; i++) {
                if(!strcmp(word, db->array[i].name)){
                        return i;
                }
        }
        return -1;
}

void removeCoworkerOnIndex(Database* db, size_t index) {
        if(index >= db->length){
                printf("Fehlgeschlagen: Index größer als Array\n");
                return;
        }
        for(int i = index; i < db->length-1; i++) {
                db->array[i] = db->array[i+1];
        }
        db->length--;
        db->array = realloc(db->array, db->length * sizeof(Coworker));
}

void removeCoworker(Database* db, char word[NAME_LEN]) {
        long indexOfName = getIndexForName(db, word);
        if(indexOfName == -1) {
                printf("Fehlgeschlagen: Kein Mitarbeiter mit Namen gefunden. \n");
                return;
        }
        removeCoworkerOnIndex(db, (size_t)indexOfName);
        printf("Erfolgreich entfernt\n");
}

void deleteCoworker(Database* db) {
        if(db->length == 0) {
                printf("Keine Mitarbeiter in der Datenbank\n");
                return;
        }
        char name[NAME_LEN];
        printf("Geben Sie den Namen des Mitarbeiters an, den Sie entfernen möchten: ");
        scanf("%s", name);
        removeCoworker(db, name);
}

void editCoworker(Database* db) {
        char word[NAME_LEN];
        printf("Geben Sie den Namen des Mitarbeiters an, den Sie entfernen möchten: ");
        scanf("%s", word);
        long indexOfName = getIndexForName(db, word);
        if(indexOfName == -1) {
                printf("Fehlgeschlagen: Kein Mitarbeiter mit Namen gefunden. \n");
                return;
        }
        Coworker newWorker = readCoworker();
        db->array[indexOfName] = newWorker;
        printf("Mitarbeiter erfolgreich geändert.\n");
}

void printCoworker(Database* db, size_t index) {
        
        printf("\nMitarbeiter Index: %d\n",(int)index );
        printf("Name: %s\n", db->array[index].name);
        printf("Abteilung: %s\n", db->array[index].abteilung);
        printf("Alter: %d\n", db->array[index].age);
        printf("Gehalt: %f\n", db->array[index].salary);
}

void printCoworkerByName(Database* db) {
        char name[NAME_LEN];
        printf("Geben Sie den Namen des Mitarbeiters an: ");
        scanf("%s", name);
        long indexOfName = getIndexForName(db, name);
        if(indexOfName == -1) {
                printf("Fehlgeschlagen: Kein Mitarbeiter mit Namen gefunden. \n");
                return;
        }
        printCoworker(db, (size_t)indexOfName);
}

void printAllCoworkers(Database* db) {
        if(db->length == 0) {
                printf("Keine Mitarbeiter in der Datenbank\n");
                return;
        }
        for(int i = 0; i < db->length; i++) {
                printCoworker(db, (size_t)i);
        }
}

void freeDatabase(Database* db) {
        free(db->array);
        db->array = NULL;
        db->length = 0;
}
