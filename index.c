#include "index.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

// Initialize the file header
void initializeFileHeader(char* filename) {
    IndexHeader header;
    FILE* f = fopen(filename, "ab"); // Open the file in binary write mode

    if (f == NULL) {
        printf("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Initialize the header
    header.numIndices = 0;
    header.isUpdated = 0;
    // Write the header to the file
    fwrite(&header, sizeof(header), 1, f);

    fclose(f); // Close the file
}

// Function to read the index header
IndexHeader readIndexHeader(char* filename, FILE* file) {
    IndexHeader header;
    // Position the cursor at the beginning of the file
    fseek(file, 0, SEEK_SET);
    // Read header from the file
    fread(&header, sizeof(header), 1, file);
    return header;
}

// Function to increment the number of indices in the header
void incrementHeaderIndexCount(IndexHeader* header, FILE* f) {
    // Update the header with the number of indices
    header->numIndices++;
    fseek(f, 0, SEEK_SET); // Move to the beginning of the file
    fwrite(header, sizeof(IndexHeader), 1, f);
    // Do not close the file here, ensure to do it elsewhere
}

// Function to save an index
void saveIndex(char* filename, Index index) {
    FILE* f = fopen(filename, "ab"); // Write mode, append at the end
    IndexHeader header;

    if (f == NULL) {
        printf("Error opening file\n");
        exit(EXIT_FAILURE);
    }

    // Read the header
    header = readIndexHeader(filename, f);

    // Write the index to the file
    fwrite(&index, sizeof(index), 1, f);

    // Update the header
    incrementHeaderIndexCount(&header, f);

    // Close the file
    fclose(f);
}

// Function to save a list of indices
void saveIndexList(char* filename, IndexList* list, FILE* f) {
    f = fopen(filename, "ab"); // Write mode, append at the end

    if (f == NULL) {
        printf("Error\n");
        exit(EXIT_FAILURE);
    }

    // Iterate through the list and write each index to the file
    IndexList* current = list;
    int i = 1;
    while (current != NULL) {
        fwrite(&(current->index), sizeof(Index), 1, f);
        printf("Saved index number %d", i);
        i++;
        current = current->next;
    }

    fclose(f); // Close the file
}

// Load an index
Index loadIndex(char* filename, FILE* f) {
    Index index;
    fread(&index, sizeof(index), 1, f);
    return index;
}

// Swap the content of two nodes
void swapIndixes(IndexList* a, IndexList* b) {
    Index temp = a->index;
    a->index = b->index;
    b->index = temp;
}

// Bubble sort to sort the list by 'name' field
void sortList(IndexList* start) {
    int swapped;
    IndexList *ptr;
    IndexList *last = NULL;

    // Base case: empty list or single element
    if (start == NULL || start->next == NULL) {
        return;
    }

    do {
        swapped = 0;
        ptr = start;

        while (ptr->next != last) {
            if (strcmp(ptr->index.name, ptr->next->index.name) > 0) {
                swapIndixes(ptr, ptr->next);
                swapped = 1;
            }
            ptr = ptr->next;
        }
        last = ptr;
    } while (swapped);
}

// Function to display an index
void displayIndex(Index* index) {
    printf("Name: %s\n", index->name);
    printf("Number of addresses: %d\n", index->numAddresses);
    for (int i = 0; i < index->numAddresses; i++) {
        printf("Address %d: Block %d, Position %d\n", i + 1, index->addresses[i].block, index->addresses[i].position+1);
    }
}

// Function to display a linked list
void displayList(IndexList* start) {
    IndexList* current = start;

    while (current != NULL) {
        displayIndex(&(current->index));
        current = current->next;
        printf("\n");
    }
}

// Function to place the index in its correct position, and if the name already exists, it adds the new address
IndexList* placeIndex(IndexList* start, char name[50], int blockNumber, int i) {
    int isIndexed = 0; // Check if the name is already indexed
    IndexList* p; // For traversing the list
    // Index and place in the linked list
    for (p = start; p != NULL; p = p->next) { // Traverse the entire list
        if (strcmp(name, p->index.name) == 0) {  // If the name already exists, just add the new address
            p->index.addresses[p->index.numAddresses].block = blockNumber; // Block address
            p->index.addresses[p->index.numAddresses].position = i;     // Offset in the block array
            // Increment address count
            p->index.numAddresses++;
            // Once the name is found, exit the loop
            isIndexed = 1;
            break;
        }
    }
    // If the name is not found
    if (!isIndexed) {
        // Create a new node
        IndexList* k = malloc(sizeof(IndexList));
        k->index.numAddresses = 1;  // Will have one address
        strcpy(k->index.name, name); // Set the name
        k->index.addresses[0].block = blockNumber;
        k->index.addresses[0].position = i;
        k->next = NULL;  // Add element at the end
        // Add the new element to the end of the list
        if (start == NULL) {
            start = k; // The list is empty, update start
        } else {
            IndexList* last = start;
            while (last->next != NULL) {
                last = last->next;
            }
            last->next = k;
        }
    }
    return start;
}


IndexList* reIndex(char* clientFile, IndexList* start, IndexHeader* header) {
    int blockNumber = 0;  // Keep the block position
    int i;
    ClientBlock block;
    FILE *f = fopen(clientFile, "rb"); // Read mode

    if (f == NULL) {
        printf("Failure");
        exit(EXIT_FAILURE);
    }

    // Read block by block
    while (fread(&block, sizeof(block), 1, f) == 1) {
        blockNumber++;
        for (i = 0; i < block.num; i++) {
            start = placeIndex(start, block.data[i].name, blockNumber, i);
            incrementHeaderIndexCount(header, f);   // Increment the number of indices
        }
    }

    fclose(f);
    return start;
}

IndexList* addOrUpdateIndex(IndexList *head, int reservationCode, int i, int j) {
    IndexNode *current = head;
    while (current != NULL) {
        if (current->entry.id == reservationCode) {
            // Update existing entry
            if (current->entry.numAddresses < MAX_ADDRESSES) {
                current->entry.addresses[current->entry.numAddresses].block = i;
                current->entry.addresses[current->entry.numAddresses].position = j;
                current->entry.numAddresses++;
            }
            return head;
        }
        current = current->next;
    }

    // Add new entry
    IndexNode *newNode = (IndexNode*) malloc(sizeof(IndexNode));
    if (!newNode) return NULL;

    newNode->entry.id = reservationCode;
    newNode->entry.addresses[0].block = block;
    newNode->entry.addresses[0].position = position;
    newNode->entry.numAddresses = 1;
    newNode->next = head;
    return newNode;
}

