#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
/*#ifndef checks whether the given token has been #defined earlier in the file or in an included file; 
if not, it includes the code between it and the closing #else or, if no #else is present, #endif statement. 
#ifndef is often used to make header files idempotent by defining a token once the file has been included 
and checking that the token was not set at the top of that file.
*/

struct list {
	struct listentry* head;
	struct listentry* tail;
};

struct listentry {
	void *data;
	struct listentry *prev;
	struct listentry *next;
};

void list_rm(struct list* l, struct listentry* e) {
if(l->head == NULL){
		return;
	}
	else if(l->head == l->tail){
		l->head = NULL;
		l->tail = NULL;
	}

	else if(l->head == e){
		e->next->prev = NULL;
		l->head = e->next;
		e->next = NULL;
	}
	else if(l->tail == e){
		e->prev->next = NULL;
		l->tail = e->prev;
		e->prev = NULL;
	}
	else{
		e->prev->next = e->next;
		e->next->prev = e->prev;
		e->prev = NULL;
		e->next = NULL;
	}
	free(e);

}    // Remove an item from the list
struct listentry* list_add(struct list* l, void* data) {
	struct listentry* new_element = (struct listentry*)malloc(sizeof(struct listentry));
	new_element->data = data;
	new_element->next = NULL;
	if ((l->head) == NULL) {
        new_element->prev = NULL;
        (l->head) = new_element;
		l->tail = new_element;

    }
	else {
		l->tail->next = new_element;
		new_element->prev = l->tail;
		l->tail = new_element;
	}
	return l->tail;
}  // Add an item to the list
struct list* list_new() {
	struct list* l = (struct list*)malloc(sizeof(struct list));
	l->head = NULL;
	l->tail = NULL;
	return l;
	
}  // Return an initialized listn
int is_empty(struct list* l) {
	if ((l->head) == NULL) { 
		return 1;
	}
	else {
		return 0;
	}
}  // Check if list is empty or not
#endif