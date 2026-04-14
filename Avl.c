/*
Referência utilizada: https://algs4.cs.princeton.edu/code/edu/princeton/cs/algs4/AVLTreeST.java.html
*/
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

#include "Avl.h"

Avl* create() {
	Avl* avl = malloc(sizeof(Avl));
	avl->root = NULL;
	avl->count = 0;	

	return avl;
}

bool isEmpty(Avl* avl) {
	return avl->count == 0;
}

int size(Avl* avl) {
	return avl->count;
}

Node* createNode(int key) {
	Node* newNode = malloc(sizeof(Node));
	newNode->key = key;
	newNode->height = 0;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

// Funções para balanceamento
int getHeight(Node* node) {
	return node ? node->height : -1;
}

int getBalanceFactor(Node* node) {
	return getHeight(node->left) - getHeight(node->right);
}

Node* doRightRotation(Node* k2) {
	Node* k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;

	k2->height = 1 + max(getHeight(k2->left), getHeight(k2->right));
	k1->height = 1 + max(getHeight(k1->left), getHeight(k1->right));

	return k1;
}

Node* doLeftRotation(Node* k1) {
	Node* k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;

	k1->height = 1 + max(getHeight(k1->left), getHeight(k1->right));
	k2->height = 1 + max(getHeight(k2->left), getHeight(k2->right));

	return k2;
}

Node* doBalance(Node* node) {
	if (getBalanceFactor(node) < -1) {
		if (getBalanceFactor(node->right) > 0) 
			node->right = doRightRotation(node->right);
		node = doLeftRotation(node);
	} else if (getBalanceFactor(node) > 1) {
		if (getBalanceFactor(node->left) < 0) 
			node->left = doLeftRotation(node->left);
		node = doRightRotation(node);
	}
	return node;
}

Node* insertNode(Node* node, int key) {
	if (node == NULL) 
		return createNode(key);
	else if (key < node->key) 
		node->left = insertNode(node->left, key);
	else if (key > node->key) 
		node->right = insertNode(node->right, key);
	
	// Balanceamento
	node->height = 1 + max(getHeight(node->left), getHeight(node->right));
	return doBalance(node);
}

void insert(Avl* avl, int key) {
	avl->root = insertNode(avl->root, key);
	avl->count++;
}

void printTree(Node* node, int level) {
	if (node == NULL) 
        return;

	printTree(node->right, level + 1);
    printf("\n");
    for (int i = 0; i < level; i++) {
        printf("    "); 
    }
    printf("%d", node->key);
    printTree(node->left, level + 1);
}

void print(Avl* avl) {
	printTree(avl->root, 0);
}

bool searchNode(Node* node, int key) {
	if (node == NULL) {
		return false;
	} else if (key == node->key) {
		return true;
	} else if (key > node->key) {
		return searchNode(node->right, key);
	} else {
		return searchNode(node->left, key);
	}
}

bool search(Avl* avl, int key) {
	return searchNode(avl->root, key);
}

Node* deleteNode(Node* node, int key) {
    if (node == NULL) return node;

    if (key < node->key) {
        node->left = deleteNode(node->left, key);
    } else if (key > node->key) {
        node->right = deleteNode(node->right, key);
    } else {
		// Caso 1 e 2
        if (node->left == NULL || node->right == NULL) {
            Node* temp = node->left ? node->left : node->right;
            // Caso 1: folha
			if (temp == NULL) { 
                temp = node;
                node = NULL;
            // Caso 2: um filho
			} else { 
				// Copia o conteúdo do filho para o atual (exclusão por cópia)
                *node = *temp; 
            }
            free(temp);
        } else {
            // Caso 3: dois filhos
			// Pega-se o antecessor (menor chave da subárvore à esquerda)
			Node* current = node->left;
			while (current->right != NULL)
				current = current->right;

            node->key = current->key;
			// Será o caso 1 ou 2
            node->left = deleteNode(node->left, current->key);
        }
    }
    if (node == NULL) 
		return node;

	// Balanceamento
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    return doBalance(node);
}

// Exclusão por cópia 
bool delete(Avl* avl, int key) {
	if (search(avl, key)) { 
        avl->root = deleteNode(avl->root, key);
        avl->count--;
        return true;
    }
    return false;	
}

void freeNodes(Node* node) {
    if (node == NULL) return;
    freeNodes(node->left);
    freeNodes(node->right);
    free(node); 
}

void destroy(Avl* avl) {
    if (avl == NULL) return;
    freeNodes(avl->root); 
    free(avl);           
}

void main() {
	// Inicialização da AVL
	Avl* avl = create();

	// Inserção de elementos (degenerada)
	insert(avl, 1);
	insert(avl, 2);
	insert(avl, 3);
	insert(avl, 4);
	insert(avl, 5);
	insert(avl, 6);
	insert(avl, 7);

	print(avl);

	// Buscas
	printf("\n\nPESQUISAS\n");
	printf("search(%d): %d\n", 7, search(avl, 7));
	printf("search(%d): %d\n", 20, search(avl, 20));

	// Exclusão
	printf("\nEXCLUSÕES\n");
	printf("delete(%d) caso 1: \n", 1, delete(avl, 1));
	print(avl);
	printf("\ndelete(%d) caso 2: %d\n", 2, delete(avl, 2));
	print(avl);
	printf("\ndelete(%d) caso 3: %d\n", 6, delete(avl, 6));
	print(avl);

	// Vazia
	printf("\n\nUTILITÁRIAS\n");
	printf("isEmpty() %d\n", isEmpty(avl));
	// Número de elementos
	printf("size(): %d\n", size(avl));

	destroy(avl);
}