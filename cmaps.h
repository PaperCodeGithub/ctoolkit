#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Entry {
    char *key;
    void *value;
    struct Entry *next;
} Entry;

typedef struct {
    int size;
    Entry **buckets;
} hashmap;

static unsigned int hash(const char *key, int size) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = (hash * 33) + c;
    }
    return hash % size;
}

hashmap* create_hashmap(int size) {
    hashmap *map = (hashmap*) malloc(sizeof(hashmap));
    map->size = size;
    map->buckets = (Entry**) calloc(size, sizeof(Entry*));
    return map;
}

void hashmap_put(hashmap *map, const char *key, void *value) {
    unsigned int slot = hash(key, map->size);
    Entry *entry = map->buckets[slot];

    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            entry->value = value;
            return;
        }
        entry = entry->next;
    }

    Entry *new_entry = (Entry*) malloc(sizeof(Entry));
    new_entry->key = strdup(key);
    new_entry->value = value;
    new_entry->next = map->buckets[slot];
    map->buckets[slot] = new_entry;
}

void* hashmap_get(hashmap *map, const char *key) {
    unsigned int slot = hash(key, map->size);
    Entry *entry = map->buckets[slot];

    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) return entry->value;
        entry = entry->next;
    }
    return NULL;
}