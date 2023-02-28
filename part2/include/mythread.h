#ifndef THREAD_H
#define THREAD_H

#include<stdio.h>
#include<stdlib.h>
#include<ucontext.h>
#include<signal.h>
#include<sys/time.h>
#include<unistd.h>

void mythread_init();      // Initialize threads list
ucontext_t* mythread_create(void func(void*), void* arg);  // Create a new thread
void mythread_join();  // Waits for other thread to complete. It is used in case of dependent threads.
void mythread_yield();  // Perform context switching here

struct lock {
	ucontext_t* ctx;
};
struct lock* lock_new();   // return an initialized lock object
void lock_acquire(struct lock* lk);   // Set lock. Yield if lock is acquired by some other thread.
int lock_release(struct lock* lk);   // Release lock

#endif
