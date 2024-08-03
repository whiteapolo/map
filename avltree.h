#ifndef AVLTREE_H
#define AVLTREE_H

#include <stdbool.h>

typedef struct avlNode {
	struct avlNode *left;
	struct avlNode *right;
	char *key;
	void *data;
	int height;
} avlNode;

bool avlIsExists(const avlNode *root, const char *key);

const void *avlFind(const avlNode *root, const char *key);

void avlInsert(avlNode **root, const char *key, void *data);

void avlRemove(avlNode **root, const char *key, void (*freeData)(void *));

void avlUpdate(avlNode *root, const char *key, 
		       void (*freeData)(void *), void *newData);

void avlFree(avlNode *root, void (*freeData)(void *));

#endif
