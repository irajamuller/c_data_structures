#include <stdbool.h>
#include <stdio.h>

#include "StaticLinkedList.h"

void initialize(StaticLinkedList *list) {
	list->head = EMPTY;
	list->available = 0;
	list->size = 0;
	for (int i = 0; i < MAX_LIST - 1; i++)
		list->elements[i].next = i + 1;

	list->elements[MAX_LIST - 1].next = EMPTY;
}

int getIndex(StaticLinkedList *list) {
	int result = list->available;
	if (result != EMPTY)
		list->available = list->elements[result].next;
	return result;
}

void freeIndex(StaticLinkedList *list, int index) {
	list->elements[index].next = list->available;
	list->available = index;
}

bool isEmpty(StaticLinkedList *list) { 
	return list->head == EMPTY; 
}

bool isFull(StaticLinkedList *list) { 
	return list->available == EMPTY; 
}

bool insertPos(StaticLinkedList *list, int data, int pos) {
	if (isFull(list) || pos < 0 || pos > list->size) {
		return false;
	}

	int newIndex = getIndex(list);
	list->elements[newIndex].data = data;
	// Inserção na primeira posição
	if (pos == 0) {
		list->elements[newIndex].next = list->head;
		list->head = newIndex;
	} else {
		// Inserção nas demais posições
		int previous = list->head;
		for (int i = 0; i < pos - 1; i++) {
			previous = list->elements[previous].next;
		}

		list->elements[newIndex].next = list->elements[previous].next;
		list->elements[previous].next = newIndex;
	}
	list->size++;

	return true;
}

bool insertFirst(StaticLinkedList *list, int data) {
	return insertPos(list, data, 0);
}

bool insertLast(StaticLinkedList *list, int data) {
	return insertPos(list, data, list->size);
}

bool removePos(StaticLinkedList *list, int pos) {
	if (isEmpty(list) || pos < 0 || pos >= list->size)
		return false;
	int toDelete;

	if (pos == 0) {
		toDelete = list->head;
		list->head = list->elements[toDelete].next;
	} else {
		int previous = list->head;
		for (int i = 0; i < pos - 1; i++) {
			previous = list->elements[previous].next;
		}
		toDelete = list->elements[previous].next;
		list->elements[previous].next = list->elements[toDelete].next;
	}

	freeIndex(list, toDelete);
	list->size--;
	return true;
}

bool removeFirst(StaticLinkedList *list) { return removePos(list, 0); }

bool removeLast(StaticLinkedList *list) {
	return removePos(list, list->size - 1);
}

int search(StaticLinkedList *list, int data) {
	int current = list->head;
	int index = 0;
	while (current != EMPTY) {
		if (list->elements[current].data == data) {
			return index;
		}
		current = list->elements[current].next;
		index++;
	}
	return EMPTY;
}

int get(StaticLinkedList *list, int pos) {
	if (isEmpty(list) || pos < 0 || pos >= list->size)
		return EMPTY;

	int current = list->head;
	for (int i = 0; i < pos; i++) {
		current = list->elements[current].next;
	}
	return list->elements[current].data;
}

void print(StaticLinkedList *list) {
	int current = list->head;
	while (current != EMPTY) {
		printf("%d\n", list->elements[current].data);
		current = list->elements[current].next;
	}
}

int main() {
	StaticLinkedList list;
	initialize(&list);

	for (int i = 0; i < 10; i++) {
		insertLast(&list, i + 1);
	}
	print(&list);

	removePos(&list, 5);
	print(&list);
	removeFirst(&list);
	print(&list);
	removeLast(&list);
	print(&list);

	int toFind = 5;
	printf("Posição do elemento %d é %d\n", toFind, search(&list, toFind));

	int toFindByIndex = 3;
	printf("Elemento da posição %d é %d\n", toFindByIndex,
		   get(&list, toFindByIndex));

	return 0;
}
