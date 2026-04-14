#pragma once

#include<stdbool.h>

#define max(a,b) (((a) > (b)) ? (a) : (b))

typedef struct Node {
	int key;
	int height;
	struct Node* left;
	struct Node* right;
} Node;

typedef struct Avl {
	Node* root;
	int count;
} Avl;

// ADT
Avl* create();
bool isEmpty(Avl* avl);
int size(Avl* avl);
void insert(Avl* avl, int key);
bool search(Avl* avl, int key);
bool delete(Avl* avl, int key);
void print(Avl* avl);