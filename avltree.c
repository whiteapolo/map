#include "avltree.h"
#include <endian.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b)
{
	return a > b ? a : b;
}

avlNode *makeNode(const char *key, void *data)
{
	avlNode *n = malloc(sizeof(avlNode));
	n->key = strdup(key);
	n->data = data;
	n->height = 1;
	n->left = NULL;
	n->right = NULL;
	return n;
}

int getHeight(avlNode *node)
{
	if (node == NULL)
		return 0;
	return node->height;
}

void updateHeight(avlNode *node)
{
	node->height = 1 + max(getHeight(node->right), getHeight(node->left));
}

int getBalanceFactor(avlNode *node)
{
	if (node == NULL)
		return 0;
	return getHeight(node->left) - getHeight(node->right);
}

avlNode *getMinNode(avlNode *root)
{
	while (root->left != NULL)
		root = root->left;
	return root;
}

void leftRotate(avlNode **root)
{
	avlNode *newRoot = (*root)->right;
	avlNode *tmp = newRoot->left;

	newRoot->left = *root;
	(*root)->right = tmp;

	updateHeight(newRoot->left);
	updateHeight(newRoot);

	*root = newRoot;
}

void rightRotate(avlNode **root)
{
	avlNode *newRoot = (*root)->left;
	avlNode *tmp = newRoot->right;

	newRoot->right = *root;
	(*root)->left = tmp;

	updateHeight(newRoot->right);
	updateHeight(newRoot);

	*root = newRoot;
}

void leftRightRotate(avlNode **root)
{
	leftRotate(&(*root)->left);
	rightRotate(root);
}

void rightLeftRotate(avlNode **root)
{
	rightRotate(&(*root)->right);
	leftRotate(root);
}

const avlNode *findAvlNode(const avlNode *root, const char *key)
{
	int cmpRes;
	while (root && (cmpRes = strcmp(key, root->key))) {
		if (cmpRes > 0)
			root = root->right;
		else
			root = root->left;
	}
	return root;
}

bool avlIsExists(const avlNode *root, const char *key)
{
	return findAvlNode(root, key) != NULL;
}

const void *avlFind(const avlNode *root, const char *key)
{
	const avlNode *node = findAvlNode(root, key);
	if (node != NULL)
		return node->data;
	return NULL;
}

void avlInsert(avlNode **root, const char *key, void *data)
{
	if (*root == NULL)
		return (void)(*root = makeNode(key, data));

	else if (strcmp(key, (*root)->key) > 0)
		avlInsert(&(*root)->right, key, data);

	else
		avlInsert(&(*root)->left, key, data);


	updateHeight(*root);
	int bf = getBalanceFactor(*root);
	int cmpRes = strcmp(key, (*root)->key);


	if (bf > 1 && cmpRes < 0)
		rightRotate(root);

	else if (bf < -1 && cmpRes > 0)
		leftRotate(root);

	else if (bf > 1 && cmpRes > 0)
		leftRightRotate(root);

	else if (bf < -1 && cmpRes < 0)
		rightLeftRotate(root);
}

void avlRemove(avlNode **root, const char *key, void (*freeData)(void *))
{
	if (*root == NULL) {
		return;

	} else if (strcmp(key, (*root)->key) > 0) {
		return avlRemove(&((*root)->right), key, freeData);

	} else if (strcmp(key, (*root)->key) < 0) {
		return avlRemove(&((*root)->left), key, freeData);

	} else {
		if (freeData)
			freeData((*root)->data);

		if ((*root)->left == NULL) {
			avlNode *tmp = (*root)->right;
			free((*root)->key);
			free(*root);
			*root = tmp;
			return;
		} else if ((*root)->right == NULL) {
			avlNode *tmp = (*root)->left;
			free((*root)->key);
			free(*root);
			*root = tmp;
			return;
		}

		avlNode *succesor = getMinNode((*root)->right);

		free((*root)->key);
		(*root)->key = strdup(succesor->key);
		(*root)->data = succesor->data;

		avlRemove(&((*root)->right), succesor->key, NULL);
	}

	updateHeight(*root);
	int bf = getBalanceFactor(*root);

	if (bf > 1 && getBalanceFactor((*root)->left) >= 0)
		rightRotate(root);

	else if (bf < -1 && getBalanceFactor((*root)->right) <= 0)
		leftRotate(root);

	else if (bf > 1 && getBalanceFactor((*root)->left) < 0)
		leftRightRotate(root);

	else if (bf < -1 && getBalanceFactor((*root)->right) > 0)
		rightLeftRotate(root);

	return;
}

void avlUpdate(avlNode *root, const char *key, void (*freeData)(void *), void *newData)
{
	avlNode *node = (avlNode *)findAvlNode(root, key);

	if (node == NULL)
		return;

	if (freeData)
		freeData(node->data);

	node->data = newData;
}

void avlFree(avlNode *root, void (*freeData)(void *))
{
	if (root == NULL)
		return;

	free(root->key);

	if (freeData != NULL)
		freeData(root->data);

	avlFree(root->left, freeData);
	avlFree(root->right, freeData);

	free(root);
}
