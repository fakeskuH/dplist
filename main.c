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
    test1();
    test2();
    test3();
    test4();
    return 0;
}

void test1() {
    int element = 1;
    int insertAtIndex = 2;

    printf("-------- TEST 1 ---------\n");

    dplist_t * list;
    list = dpl_create(element_copy,element_free,element_compare);

    dpl_insert_at_index(list,&element,0,true);
    dpl_insert_at_index(list,&insertAtIndex,1,false);
    printf("Element: %d\nElement: %d\n",*(int*)dpl_get_element_at_index(list,0),*(int*)dpl_get_element_at_index(list,1));
    printf("Size: %d\n",dpl_size(list));
    dpl_free(&list);
    printf("\n\n");
}

void test2() {
    int element = 1;
    int insertAtIndex = 2;

    printf("-------- TEST 2 ---------\n");

    dplist_t * list;
    list = dpl_create(element_copy,element_free,element_compare);

    dpl_insert_at_index(list,&element,0,true);
    dpl_insert_at_index(list,&insertAtIndex,1,false);
    printf("Element: %d\nElement: %d\n",*(int*)dpl_get_element_at_index(list,0),*(int*)dpl_get_element_at_index(list,1));
    printf("Size: %d\n",dpl_size(list));
    dpl_remove_at_index(list,1,false);
    printf("Size: %d\n",dpl_size(list));
    dpl_remove_at_index(list,0,true);
    printf("Size: %d\n",dpl_size(list));
    dpl_free(&list);
    printf("\n\n");
}

void test3() {
    int element = 1;
    int insertAtIndex = 2;

    printf("-------- TEST 3 ---------\n");

    dplist_t * list;
    list = dpl_create(element_copy,element_free,element_compare);

    dpl_insert_at_index(list,&element,0,true);
    dpl_insert_at_index(list,&insertAtIndex,1,false);
    dpl_printlist(list);
    printf("Size: %d\n",dpl_size(list));
    printf("Value 1 found at index: %d\n",dpl_get_index_of_element(list,&element));
    printf("Value 2 found at index: %d\n\n",dpl_get_index_of_element(list,&insertAtIndex));
    dpl_remove_at_index(list,0,true);
    dpl_printlist();
    printf("Size: %d\n",dpl_size(list));
    printf("Value 2 found at index: %d\n\n",dpl_get_index_of_element(list,&insertAtIndex));
    dpl_remove_at_index(list,0,false);
    dpl_printlist();
    printf("Size: %d\n",dpl_size(list));
    printf("Value 2 found at index: %d\n",dpl_get_index_of_element(list,&insertAtIndex));

    dpl_free(&list);
    printf("\n\n");
}

void test4() {
    int element = 1;
    int insertAtIndex = 2;

    printf("-------- TEST 4 ---------\n");

    dplist_t * list;
    list = dpl_create(element_copy,element_free,element_compare);

    dpl_insert_at_index(list,&element,0,true);
    dpl_insert_at_index(list,&insertAtIndex,1,false);
    dpl_printlist(list);
    printf("Size: %d\n",dpl_size(list));

    dpl_free(&list);
    printf("\n\n");
}

