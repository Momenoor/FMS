#ifndef INDEX_H
#define INDEX_H

#include <stdio.h>
#include "struct.h"

// Function prototypes
Index createIndex(int key, int i, int j);
IndexList* addIndex(int key, int i, int j, IndexList *head);
IndexFileHeader readIndexFileHeader(FILE *file);
void writeIndexFileHeader(FILE *file, IndexFileHeader header);
void initializeHeader(char* filename);
void saveIndex(IndexList **list,const  char *filename);
Index loadIndex(char *filename);
// Include additional function prototypes here if needed

#endif // INDEX_H
