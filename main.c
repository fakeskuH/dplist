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

    if (*a<*b) returnVal = -1;
    if (*a>*b) returnVal = 1;
    if (*a==*b) returnVal = 0;
    return returnVal;
}

int main()
{
    int element = 8;
    dplist_node_t * iNode;
    dplist_node_t * rNode;
    int * rElement;

    dplist_t * list;
    list = dpl_create(element_copy,element_free,element_compare);

    dpl_insert_at_index(list,&element,0,true);
    element = 5;
    dpl_insert_at_index(list,&element,0,true);
    element = 1;
    dpl_insert_at_index(list,&element,0,true);
    printf("List: %d %d %d\n",*(int*)dpl_get_element_at_index(list,0),*(int*)dpl_get_element_at_index(list,1),*(int*)dpl_get_element_at_index(list,2));
    element = 5;
    /*iNode = dpl_get_reference_of_element(list,&element);
    dpl_remove_at_reference(list,iNode,true);*/
    dpl_remove_element(list,&element,true);
    element = 2;
    dpl_insert_sorted(list,&element,true);
    printf("List: %d %d %d %d\n",*(int*)dpl_get_element_at_index(list,0),*(int*)dpl_get_element_at_index(list,1),*(int*)dpl_get_element_at_index(list,2),*(int*)dpl_get_element_at_index(list,3));
    return 0;
}
