#pragma once

#include <stack>
#include <vector>
#include <assert.h>

using namespace std;

struct listNode {
  listNode* next;
  int value;
};

void printList(listNode* head) {
    while(head != NULL) {
        cout << head->value << " ";
        head = head->next;
    }
    cout << endl;
}

void deleteList(listNode** headRef) {
	if(*headRef == NULL) {
		return;
	}
    listNode* head = *headRef;
	deleteList(&(head->next));
	delete (*headRef);
	*headRef = NULL;
}
//(OK) 3. delete list
void deleteList1(listNode** headRef) {
	listNode* current = *headRef;
	listNode* next;
	while(current != NULL) {
		next = current->next;
		delete current;
		current = next;
	}
	*headRef = NULL;
}

void push(listNode** headRef, int value) {
    listNode* newNode = new listNode();
    newNode->value = value;
    newNode->next = *headRef;
    *headRef = newNode;
}

//(OK) 4. pop from head
int pop(listNode** headRef) {	
	listNode* head = *headRef;
	assert(head != NULL);
	listNode* next = head->next;
	int value = head->value;
	delete head;
	*headRef = next;
	return value;
}

//5.
void InsertNth(listNode** headRef, int n, int value) {
	listNode* head = * headRef;
	listNode** ref = headRef;
	while(n > 0) {
		assert(head != NULL);
		ref = &(head->next);
		head = head->next;		
	}
	listNode* newNode = new listNode();
	newNode->value = value;
	newNode->next = head;
	*ref = newNode;
	return;
}

//6.
void SortedInsert(struct listNode** headRef, listNode* newNode) {
	//node after the insertion
	listNode* current = *headRef;
	//ref to the point of insertion
	listNode** ref = headRef;
	while(current != NULL) {
		if(current->value > newNode->value) {
			break;
		}
		else {
			ref = &(current->next);
			current = current->next;
		}
	}
	//insert
	*ref = newNode;
	newNode->next = current;
}

//7. sort using SortedInsert
void SortUsingSortedInsert(listNode** headRef) {
	listNode* head = NULL;
	listNode* current = *headRef;
	listNode* next;
	while(current != NULL) {
		next = current->next;
		SortedInsert(&head, current);
		current = next;
	}
    //printList(head);
	*headRef = head;	
}

void Append(listNode** aRef, listNode** bRef) {
	//append point
	listNode* aHead = *aRef;
	listNode* bHead = *bRef;
	*bRef = NULL;
	if(aHead == NULL) {
		*aRef = *bRef;
	}
	while(aHead->next != NULL) {
		aHead = aHead->next;
	}
	aHead->next = bHead;
}

void FrontBackSplit(listNode* source, listNode** frontRef, listNode** backRef) {

}

void makeTestList(listNode** headRef) {
    push(headRef, 2);
    push(headRef, 5);
    push(headRef, 3);
    push(headRef, 1);
    push(headRef, 9);
}

void Reverse(listNode** headRef) {
    listNode* prev = NULL;
    listNode* current = *headRef;
    
    while(current != NULL) {
        listNode* next = current->next;
        current->next = prev;
        prev = current;
        current = next;        
    }

    *headRef = prev;
}

void ReverseR(listNode** headRef) {
    listNode* head = *headRef;
    if(head == NULL || head->next == NULL) {
        return;
    }
    listNode* next = head->next;
    listNode* newHead = next;
    ReverseR(&newHead);
    *headRef = newHead;
    //new tail
    next->next = head;
    head->next = NULL;
}