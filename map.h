#ifndef MAP_H
#define MAP_H

#include <stdarg.h>
#include "avltree.h"

#define $(element) (&((typeof(element)){element}))
#define DUP_VAL(value) memdup($(value), sizeof(value))

typedef avlNode *map;

map newMap();

// need to be terminated with NULL, NULL
map newMapFrom(const char *key, void *data, ...);

void mapInsert(map *m, const char *key, void *data);

// need to be terminated with NULL, NULL
void mapInsertAllAp(map *m, va_list ap);

// need to be terminated with NULL, NULL
void mapInsertAll(map *m, ...);

const void *mapFind(const map m, const char *key);

bool mapIsExists(const map m, const char *key);

void mapRemove(map *m, const char *key, void (*freeData)(void *));

void mapFree(map m, void (*freeData)(void *));

void mapUpdate(map m, const char *key,
		       void (*freeData)(void *), void *newData);

// util
void *memdup(const void *mem, int size);

#endif
