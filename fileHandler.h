#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include "database.h"

void writeJSONToFile(Database* db, const char* filename);
void readJSONFromFile(Database* db, const char* filename);

#endif