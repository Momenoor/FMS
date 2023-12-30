#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "index.h"

/// Create an index
Index createIndex(int key, int i, int j) {
    Index in;
    in.key = key;
    in.address.i = i;
    in.address.j = j;
    return in;
}

// Create a linked list for indexes
IndexList* addIndex(int key, int i, int j, IndexList *head) {
    IndexList *element = (IndexList*)malloc(sizeof(IndexList));
    Index in = createIndex(key, i, j);
    element->item = in;
    element->next = NULL;

    // Check if the list is empty or the key is smaller than the head key
    if(head == NULL || in.key < head->item.key) {
        element->next = head;
        head = element;
        return head;
    } else {
        IndexList *temp = head;
        while(temp->next != NULL && (temp->next->item.key) < in.key) {
            temp = temp->next; // Move to the next element to find the correct position
        }
        element->next = temp->next;
        temp->next = element;
        return head;
    }
}
// Read the header for the index file
IndexFileHeader readIndexFileHeader(FILE *file) {
    IndexFileHeader header;
    rewind(file); // Move the cursor to the beginning
    fread(&header, sizeof(IndexFileHeader), 1, file); // Read the header
    rewind(file); // Reset the cursor to the beginning
    return header;
}

// Write the header to the index file
void writeIndexFileHeader(FILE *file, IndexFileHeader header) {
    rewind(file); // Move the cursor to the beginning
    fwrite(&header, sizeof(IndexFileHeader), 1, file); // Write the header
}

void initializeHeader(char* filename) {
    IndexFileHeader header;
    FILE* f = fopen(filename, "wb"); // Open the file in write-binary mode
    header.num_indexes = 0;
    writeIndexFileHeader(f, header);
    rewind(f);
    fclose(f); // Close the file
}

// Save indexes to the index file
void saveIndex(IndexList **list, const char *filename) {
    IndexList *head = list;
    IndexFileHeader header;
    header.num_indexes = 0;
    while(head != NULL) {
        header.num_indexes++;
        head = head->next;
    }

    header.updateFlag = 1;
    head = list;
    FILE *file;
    file = fopen(filename, "wb+");
    writeIndexFileHeader(file, header);
    fwrite(&header, sizeof(IndexFileHeader), 1, file);
    while(head != NULL) {
        fwrite(&(head->item), sizeof(Index), 1, file);
        head = head->next;
    }
    fclose(file);
}
// Load an index
Index loadIndex(char *filename) {
    Index in;
    FILE *f = fopen(filename, "rb");
    fseek(f, sizeof(IndexFileHeader), SEEK_SET);
    fread(&in, sizeof(Index), 1, f);
    fclose(f);
    printf("%d %d %d", in.key, in.address.i, in.address.j);
    return in;
}
// Path: index.c



