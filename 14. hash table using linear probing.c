#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

// Define the hash table structure
typedef struct {
    int key;
    int value;
    int isOccupied; // 1 if the slot is occupied, 0 if it is empty
} HashTableEntry;

typedef struct {
    HashTableEntry entries[TABLE_SIZE];
} HashTable;

// Hash function
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

// Initialize hash table
void initHashTable(HashTable *table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table->entries[i].isOccupied = 0;
    }
}

// Insert key-value pair into the hash table using linear probing
void insert(HashTable *table, int key, int value) {
    int index = hashFunction(key);
    int originalIndex = index;

    // Linear probing
    while (table->entries[index].isOccupied && table->entries[index].key != key) {
        index = (index + 1) % TABLE_SIZE;
        if (index == originalIndex) {
            printf("Hash table is full!\n");
            return;
        }
    }

    table->entries[index].key = key;
    table->entries[index].value = value;
    table->entries[index].isOccupied = 1;
}

// Search for a key in the hash table
int search(HashTable *table, int key) {
    int index = hashFunction(key);
    int originalIndex = index;

    // Linear probing
    while (table->entries[index].isOccupied) {
        if (table->entries[index].key == key) {
            return table->entries[index].value;
        }
        index = (index + 1) % TABLE_SIZE;
        if (index == originalIndex) {
            break;
        }
    }

    return -1; // Key not found
}

// Delete a key-value pair from the hash table
void delete(HashTable *table, int key) {
    int index = hashFunction(key);
    int originalIndex = index;

    // Linear probing
    while (table->entries[index].isOccupied) {
        if (table->entries[index].key == key) {
            table->entries[index].isOccupied = 0;
            printf("Deleted key %d\n", key);
            return;
        }
        index = (index + 1) % TABLE_SIZE;
        if (index == originalIndex) {
            break;
        }
    }

    printf("Key %d not found\n", key);
}

// Print the hash table
void printHashTable(HashTable *table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table->entries[i].isOccupied) {
            printf("Index %d: Key %d, Value %d\n", i, table->entries[i].key, table->entries[i].value);
        } else {
            printf("Index %d: Empty\n", i);
        }
    }
}

// Main function to test the hash table
int main() {
    HashTable table;
    initHashTable(&table);

    insert(&table, 1, 100);
    insert(&table, 2, 200);
    insert(&table, 11, 300); // This will collide with index 1
    insert(&table, 22, 400); // This will collide with index 2

    printf("Hash Table after inserts:\n");
    printHashTable(&table);

    printf("Searching for key 11: %d\n", search(&table, 11));
    printf("Searching for key 3: %d\n", search(&table, 3));

    delete(&table, 11);
    printf("Hash Table after deleting key 11:\n");
    printHashTable(&table);

    return 0;
}
