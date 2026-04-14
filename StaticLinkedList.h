#pragma once

#define MAX_LIST 100
#define EMPTY -1

typedef struct {
	int data;
	int next;
} Node;

typedef struct {
	Node elements[MAX_LIST];
	int head;
	int available;
	int size;
} StaticLinkedList;

void initialize(StaticLinkedList *list);
int getIndex(StaticLinkedList *list);
void freeIndex(StaticLinkedList *list, int index);
bool isEmpty(StaticLinkedList *list);
bool isFull(StaticLinkedList *list);
bool insertPos(StaticLinkedList *list, int data, int pos);
bool insertFirst(StaticLinkedList *list, int data);
bool insertLast(StaticLinkedList *list, int data);
bool removePos(StaticLinkedList *list, int pos);
bool removeFirst(StaticLinkedList *list);
bool removeLast(StaticLinkedList *list);
int search(StaticLinkedList *list, int data);
int get(StaticLinkedList *list, int pos);
void print(StaticLinkedList *list);

