//map的纯c实现
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct KeyValue {
    char* key;
    char* value;
    struct KeyValue* next;
} KeyValue;

typedef struct Map {
    KeyValue** table;
    size_t size;
} Map;

Map* createMap(size_t size) {
    Map* map = (Map*)malloc(sizeof(Map));
    map->table = (KeyValue**)malloc(sizeof(KeyValue*) * size);
    for (size_t i = 0; i < size; i++) {
        map->table[i] = NULL;
    }
    map->size = size;
    return map;
}

unsigned long hash(const char* key) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

void insert(Map* map, const char* key, const char* value) {
    unsigned long index = hash(key) % map->size;
    KeyValue* newPair = (KeyValue*)malloc(sizeof(KeyValue));
    newPair->key = strdup(key);
    newPair->value = strdup(value);
    newPair->next = map->table[index];
    map->table[index] = newPair;
}

char* search(Map* map, const char* key) {
    unsigned long index = hash(key) % map->size;
    KeyValue* pair = map->table[index];
    while (pair != NULL) {
        if (strcmp(pair->key, key) == 0) {
            return pair->value;
        }
        pair = pair->next;
    }
    return NULL;
}

void freeMap(Map* map) {
    for (size_t i = 0; i < map->size; i++) {
        KeyValue* pair = map->table[i];
        while (pair != NULL) {
            KeyValue* temp = pair;
            pair = pair->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }
    free(map->table);
    free(map);
}

int main() {
    Map* map = createMap(10);
    insert(map, "name", "Alice");
    insert(map, "age", "30");
    printf("Name: %s\n", search(map, "name"));
    printf("Age: %s\n", search(map, "age"));
    freeMap(map);
    return 0;
}
