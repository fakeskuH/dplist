#include <stdio.h>
#include <stdlib.h>
#include "dplist.h"

dplist_t * list = NULL;

void * element_copy(void * element) {
    int * returnVal = malloc(sizeof(int));
    *returnVal = *(int*)element;
    return returnVal;
}

void element_free(void ** element) {
    int * pFree = *element;
    free(pFree);
}

int element_compare(void * x, void * y) {
    int * a = malloc(sizeof(int));
    int * b = malloc(sizeof(int));
    int returnVal = 0;
    *a = *(int*)x;
    *b = *(int*)y;

    if (a<b) returnVal = -1;
    if (a>b) returnVal = 1;
    if (a==b) returnVal = 0;
    return returnVal;
}

int main()
{
    int element = 8;
    dplist_t * list;
    list = dpl_create(element_copy,element_free,element_compare);
    dpl_get_element_at_index(list,0);
    dpl_insert_at_index(list,&element,0,false);
    printf("List size: %d\n",dpl_size(list));
    printf("Get element 0: %d",*(int*)dpl_get_element_at_index(list,0));
    dpl_remove_at_index(list,0,false);

    return 0;
}
