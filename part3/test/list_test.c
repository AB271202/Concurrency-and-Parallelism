#include <stdio.h>
#include "../include/list.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv){
    printf("Testing list!\n");
    struct list* l = list_new();

    int v = 5;
    struct listentry* n = list_add(l, &v);
    int* d = (int *) n->data;
    printf("count %d\n", *d);
    printf("non-empty: %d\n", is_empty(l));

    int v1 = 6;
    struct listentry* n1 = list_add(l, &v1);
    int * d1 = (int*) n1->data;
    printf("count %d\n", *d1);

    list_rm(l, n);
    list_rm(l, n1);

    printf("empty: %d\n", is_empty(l));
    printf("Testing list done!\n\n");
    return 0;
}