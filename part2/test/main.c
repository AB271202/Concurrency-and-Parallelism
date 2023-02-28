#include <stdio.h>
#include "../include/hm.h"
#include "../include/list.h"
#include <stdlib.h>
#include <string.h>
#include "../include/mythread.h"

void readFile(void *);

struct hashmap_s hashmap;

int printer(struct hashmap_element_s *const e) {
    int* count = (int*) e->data;
    // printf("key %s\n", e->key);
	// printf(", count %d\n", *count);
	// printf("key ");
	// // fputs(e->key,stdout);
	// printf(", count %d\n",*count);
	printf("key %s, count %d\n", e->key, *count);
    return 0;
}

static void f2 (char* word) {
    printf("Inside f2 %s\n", word);
    acquire_bucket(&hashmap, word);
    int* c = (int*) hashmap_get(&hashmap, word); 
    int* c1 = (int*) malloc(sizeof(int));
    *c1 = 1;
    if(c != NULL) {
        for(int i = 0; i < *c; i ++) {
            mythread_yield();
        }
        *c1 = *c + 1;
    }
	//free(c); //I added this
    printf("Inside f2: c1 %d\n", *c1);
    hashmap_put(&hashmap, word, c1); //This word vanishes after f2 runnung is over; must allocate dynamically in hashmap_put
    release_bucket(&hashmap, word);
    puts("finish f2");
}

void readFile(void *args) {
    	// Perform following steps
    	// 1. Read a word from the file
    	// 2. Acquire lock on relevent hashmap bucket
    	// 3. Get count of word from hashmap. Let value returened by hashmap be x.
    	// 4. Yield thread
    	// 5. Set new count of the word as x+1.
    	// 6. Release lock
	    // 7. Repeat for all words in the file.
		char *filename = (char*)args;
	    FILE *fp = fopen(filename,"r");
	    if(fp==NULL)
	        return;
	    char ch;
	    int i=0;
	    char arr[25];
	    int val =-1;
	    while((ch = fgetc(fp))!=EOF) {
	        if(ch!=' ' && ch!='\n' && ch!='\t' && ch!='\0' && ch!='\r') {
	            arr[i] = ch;
	            i++;
	        } else {
	            arr[i] = 0;
	            f2(arr);
	            for(int j=0;j<25;j++)
	                arr[j]='\0';
	            i=0;
	        }
	    }
}

int main(int argc, char** argv) {
    hashmap_create(&hashmap);
    printf("Testing threads!\n");
    mythread_init();
    for(int i=1;i<argc;i++) {

        mythread_create(readFile, (void *) argv[i]); // creates contexts of same function readFile with different arguments
		// readFile(argv[i]);
	
	}
    mythread_join();
	printf("Iterating now\n");
    hashmap_iterator(&hashmap, printer);
    printf("Testing threads done!\n\n");
}
