/*! \mainpage Main Page
 *
 * \section intro_sec Introduction
 *
 * This is the doxy documentation of the part3 of the assignement
 * finding the word count in the given files using the <a href="https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&cad=rja&uact=8&ved=2ahUKEwjx1_TO4aH9AhVIzXMBHWt6C_YQFnoECAkQAQ&url=https%3A%2F%2Fen.wikipedia.org%2Fwiki%2FPthreads&usg=AOvVaw2wvsRWMPWZ6QcSFt_O8wOpL">pthread.h</a>  library.
 *
 * For more information you can look at Classes and Files  tab. 
 *
 */
/**
 * @file mythread.h
 * @brief This is the header file for a simple user-level thread library.
*/
#ifndef THREAD_H
#define THREAD_H

#include<stdio.h>
#include<stdlib.h>
#include<ucontext.h>
#include<signal.h>
#include<sys/time.h>
#include<unistd.h>

/**
 * @brief Initializes the thread library.
 *	This function initializes the thread library, including setting up necessary
 *	data structures and signal handlers. This function should be called before
 *	any other thread functions are used.
*/
void mythread_init();

/**
 * @brief Creates a new thread.
 * This function creates a new thread with the given function and argument.
 * @param func The function that the new thread will execute.
 * @param arg The argument to pass to the new thread's function.
 * @return A pointer to the new thread.
*/
void* mythread_create(void func(void*), void* arg);

/**
 * @brief Joins with a thread.
 * This function waits for the specified thread to finish execution.
 * And then start the other thead.
*/
void mythread_join();

/**
 * @brief Yields the current thread.
 * This function yields the current thread, allowing other threads to run
 * without the completion of the current thread.
*/
void mythread_yield();

/**
 * @brief A lock structure.
 * This structure represents a lock that can be used to synchronize access to
 * shared resources.
*/
struct lock {
    void* c;
};

/**
 * @brief Creates a new lock.
 * This function creates a new lock and returns a pointer to it.
 * @return A pointer to the new lock.
*/
struct lock* lock_new();

/**
 * @brief Acquires a lock.
 * This function acquires the specified lock(by making NULL it's context). If the lock 
 * is already held byanother thread, the calling thread is blocked
 * (i.e. mythread_yield is called) until the lock becomes available.
 * @param lk The lock which is to be acquired.
*/
void lock_acquire(struct lock* lk);

/**
 * @brief Releases a lock.
 * This function releases the specified lock. If other threads are waiting on
 * the lock, one of them will be unblocked and will acquire the lock.
 * @param lk The lock to release.
 * @return 0 if successful, or an error code if an error occurred.
*/
int lock_release(struct lock* lk);
#endif