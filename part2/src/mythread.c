#define _XOPEN_SOURCE 600
#define MEM 64000
#ifndef THREAD_H
#define THREAD_H
#include "../include/list.h"
#include<stdio.h>
#include<stdlib.h>
#include<ucontext.h>
#include<signal.h>
#include<sys/time.h>
#include<unistd.h>


// void print_ctx(ucontext_t *ctx) {
// 	printf("uc_link: %p\n", ctx->uc_link);
// 	printf("uc_stack.ss_sp: %p, uc_stack.ss_size: %ld, uc_stack.ss_flags: %d\n", 
// 		ctx->uc_stack.ss_sp, ctx->uc_stack.ss_size, ctx->uc_stack.ss_flags);
// 	// print_mctx(ctx->uc_mcontext);
// }

struct list* l; 
static ucontext_t ctx0;
struct listentry* currentpointer;
void mythread_init(){
	l=list_new();
	// list_add(l,&ctx0);
}      // Initialize threads list
// void ctxlistprint(){
// 	struct listentry* cur = l->head;
// 	int size=1;
// 	while(cur->next!=NULL) {size++;cur=cur->next;}
// 	cur=l->head;
// 	printf("%d", size);
// 	for(int i=0; i<size; i++){
// 		print_ctx(cur->data);
// 		printf("\n");
// 		cur=cur->next;
// 	}
// }
ucontext_t* mythread_create(void func(void*), void* arg){
	//printf("HEREEEEEEEEE\n");
	ucontext_t * ctx= (ucontext_t*)malloc(sizeof(ucontext_t));
	char* st=(char*)malloc(8192*sizeof(char));
	//char st[8192];
			
	getcontext(ctx);
    ctx->uc_stack.ss_sp = st;
    ctx->uc_stack.ss_size = sizeof st;
	ctx->uc_link = &ctx0;
    makecontext(ctx, (void (*)(void))func, 1, arg);
	
	list_add(l,ctx);

	//ctxlistprint();
	// printf("%d\n",(l->head)->next==NULL);
	// printf("counter\n");
	return ctx;
}  // Create a new thread

void mythread_join(){

	struct listentry* var = l->head;
	
		
	while(var != NULL){
	    //printf("start_loop\n");
		// currentpointer=var;
		//printf("here in loop 2");
		swapcontext(&ctx0,(var->data));
		//printf("Return to join")
		//printf("here in loop1"); Context returns here after the function finishes
		//printf("mid_loop\n");
		list_rm(l,l->head);
		//printf("removed\n");
		var = (l->head);

// 		var = (var-> next);	
		// printf("%d\n",var==NULL);
		// printf("end_loop\n");
	}
	
}  // Waits for other thread to complete. It is used in case of dependent threads.

void mythread_yield(){
	//printf("Yield called\n");
	// if (currentpointer->next!=NULL){
	// 	ucontext_t * tmp = currentpointer->data;
	// 	currentpointer=currentpointer->next;
	// 	swapcontext(tmp, currentpointer->data);
	// }	
	// else{
	// 	ucontext_t * tmp = currentpointer->data;
	// 	currentpointer=l->head;
	// 	swapcontext(tmp, currentpointer->data);
	// }
	//printf("Hi");
	//printf("mythread_yield %d\n",l->head->next != NULL);
	if (l->head->next != NULL){
		struct listentry * tmp = l->head;
		l->head=l->head->next;
		list_add(l,tmp->data);
		swapcontext(tmp->data, l->head->data);
		//printf("return to yield\n");
		free(tmp);
	}
	else{
		return;
	}

}  // Perform context switching here

struct lock {
	ucontext_t* ctx;
};
struct lock* lock_new(){ 
	struct lock* newlock=(struct lock*)malloc(sizeof(struct lock));
	newlock->ctx=NULL;
	return newlock;
}   // return an initialized lock object
void lock_acquire(struct lock* lk){
	while (lk->ctx!=NULL){
		//printf("Can't acquire!\n");
		mythread_yield();
		//printf("RETURNED HERE\n");
		
	}
	
		lk->ctx = l->head->data;


}   // Set lock. Yield if lock is acquired by some other thread.
int lock_release(struct lock* lk){
	lk->ctx =NULL;
	return 0;
}   // Release lock

#endif