#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "fileHandler.h"

void writeJSONToFile(Database* db, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Öffnen der Datei zum Schreiben fehlgeschlagen");
        return;
    }

    fprintf(file, "[\n");
    for (size_t i = 0; i < db->length; i++) {
        Coworker* worker = &db->array[i];
        fprintf(file, "  {\n");
        fprintf(file, "    \"name\": \"%s\",\n", worker->name);
        fprintf(file, "    \"abteilung\": \"%s\",\n", worker->abteilung);
        fprintf(file, "    \"age\": %d,\n", worker->age);
        fprintf(file, "    \"salary\": %.2f\n", worker->salary);
        fprintf(file, "  }%s\n", (i < db->length - 1) ? "," : "");
    }
    fprintf(file, "]\n");

    fclose(file);
}
void readJSONFromFile(Database* db, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Öffnen der Datei zum Lesen fehlgeschlagen");
        return;
    }

    char line[256];
    db->length = 0;
    db->array = NULL;

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "{") == NULL)
            continue;

        Coworker worker;

        if (!fgets(line, sizeof(line), file)) break;
        sscanf(line, " \"name\": \"%[^\"]\",", worker.name);

        if (!fgets(line, sizeof(line), file)) break;
        sscanf(line, " \"abteilung\": \"%[^\"]\",", worker.abteilung);

        if (!fgets(line, sizeof(line), file)) break;
        sscanf(line, " \"age\": %hu,", &worker.age);

        if (!fgets(line, sizeof(line), file)) break;
        sscanf(line, " \"salary\": %f", &worker.salary);

        fgets(line, sizeof(line), file);

        db->length++;
        db->array = realloc(db->array, db->length * sizeof(Coworker));
        db->array[db->length - 1] = worker;
    }

    fclose(file);
}

