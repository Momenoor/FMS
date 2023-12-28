#ifndef INDEXE_H
#define INDEXE_H
#include <stdio.h>
#include "struct.h"

// Initialize the file header
void initializeFileHeader(char* filename);

// Increment the header index count
void incrementHeaderIndex(IndexHeader* header, FILE *f);

// Save an index to a file
void saveIndex(char* filename, Index index);

// Load an index from a file
Index loadIndex(char* filename, FILE* f);

// Swap two indices in the list
void swapIndixes(IndexList* a, IndexList* b);

// Sort the index list
void sortIndexList(IndexList* start);

// Place an index in the list
IndexList* placeIndex(IndexList* start, char name[50], int blockNumber, int i);

// Reindex based on client file
IndexList* reindex(char* clientFile, IndexList* start, IndexHeader* header);

// Read the index header from a file
IndexHeader readIndexHeader(char* filename, FILE* file);

// Display an index
void displayIndex(Index* index);

// Display the index list
void displayIndexList(IndexList* start);

// Save a list of indices to a file
void saveIndexList(char* filename, IndexList* list, FILE* f);

#endif // INDEXE_H
