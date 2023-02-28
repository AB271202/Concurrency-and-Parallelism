#include "../include/mythread.h"
#include "../include/list.h"
#include <pthread.h>
#include <sched.h>

struct ucontext_t main_ctx;
struct list *l;
void mythread_init() {
	l = list_new();
}

void* mythread_create(void func(void*), void* arg){
	pthread_t* t = (pthread_t*) malloc(sizeof(pthread_t));
	pthread_create(t, NULL, func, arg);
	list_add(l, t);
	return t;
}

void mythread_yield(){
	// pthread_yield(); does not work on some systems
	sched_yield();
}

void mythread_join() {
	struct listentry* le = l->head;
	while(le != NULL) {
		pthread_t* t = (pthread_t*) le->data;
		pthread_join(*t, NULL);
		le = le->next;
	}
}

struct lock* lock_new() {
	struct lock* lk = (struct lock*) malloc(sizeof(struct lock));
	lk->c = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(lk->c, NULL);
	return lk;
}

void lock_acquire(struct lock* lk) {
	pthread_mutex_lock(lk->c);
}

int lock_release(struct lock* lk) {
	pthread_mutex_unlock(lk->c);
}