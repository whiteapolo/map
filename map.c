#include "map.h"
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "avltree.h"

map newMap()
{
	return NULL;
}

map newMapFrom(const char *key, void *data, ...)
{
	map m = newMap();
	mapInsert(&m, key, data);
	va_list ap;
	va_start(ap, data);
	mapInsertAllAp(&m, ap);
	va_end(ap);
	return m;
}

void mapInsert(map *m, const char *key, void *data)
{
	avlInsert(m, key, data);
}

void mapInsertAllAp(map *m, va_list ap)
{
	const char *key = va_arg(ap, const char *);
	void *data = va_arg(ap, void *);

	while (key && data) {
		mapInsert(m, key, data);
		key = va_arg(ap, const char *);
		data = va_arg(ap, void *);
	}
}

// need to be terminated with NULL, NULL
void mapInsertAll(map *m, ...)
{
	va_list ap;
	va_start(ap, m);
	mapInsertAllAp(m, ap);
	va_end(ap);
}


const void *mapFind(const map m, const char *key)
{
	return avlFind(m, key);
}

bool mapIsExists(const map m, const char *key)
{
	return avlIsExists(m, key);
}

void mapRemove(map *m, const char *key, void (*freeData)(void *))
{
	return avlRemove(m, key, freeData);
}

void mapUpdate(map m, const char *key, 
		       void (*freeData)(void *), void *newData)
{
	avlUpdate(m, key, freeData, newData);
}

void mapFree(map m, void (*freeData)(void *))
{
	avlFree(m, freeData);
}

void *memdup(const void *mem, int size)
{
	void *newMem = malloc(size);
	memcpy(newMem, mem, size);
	return newMem;
}
