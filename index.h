#ifndef INDEX_H
#define INDEX_H

#include <stdio.h>
#include <stdlib.h>

// Forward declaration of the structure
typedef struct IndexList IndexList;

typedef struct {
    int i; // Can represent client ID or other identifiers
    int j; // Can represent reservation ID or other identifiers
} Address;

typedef struct {
    int key;
    Address address;
} Index;

struct IndexList {
    Index item;
    IndexList *next;
};


typedef struct {
    int num_indexes; // Number of indexes
    int updateFlag;  // Flag to indicate if the header is updated
} IndexFileHeader;

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
