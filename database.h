#ifndef DATABASE_H
#define DATABASE_H

#include <stdio.h>
#include <stdlib.h>

#define NAME_LEN 30

typedef struct {
        char name[NAME_LEN];
        char abteilung[NAME_LEN];
        unsigned short age;
        float salary;
} Coworker;

typedef struct {
        Coworker* array;
        size_t length;
} Database;

Database initDatabase();
void addCoworker(Database* db);
void deleteCoworker(Database* db);
void editCoworker(Database* db);
void printCoworker(Database* db, size_t index);
void printCoworkerByName(Database* db);
void printAllCoworkers(Database* db);
void freeDatabase(Database* db);

#endif