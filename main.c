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
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
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
    dpl_printlist(list);
    printf("Size: %d\n",dpl_size(list));
    printf("Value 2 found at index: %d\n\n",dpl_get_index_of_element(list,&insertAtIndex));
    dpl_remove_at_index(list,0,false);
    dpl_printlist(list);
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
    printf("Value '%d' read from node at index 0.\n",*(int*)dpl_get_element_at_index(list,0));
    printf("Value '%d' read from node at index 1.\n",*(int*)dpl_get_element_at_index(list,1));
    dpl_remove_at_index(list,1,false);
    dpl_printlist(list);
    printf("Value '%d' read from node at index 1.\n",*(int*)dpl_get_element_at_index(list,1));
    printf("Value '%d' read from node at index -7.\n",*(int*)dpl_get_element_at_index(list,-7));

    dpl_free(&list);
    printf("\n\n");
}

void test5() {
    int element = 1;
    int element2 = 2;
    int refVal = 0;

    void * refNode;

    printf("-------- TEST 5 ---------\n");

    dplist_t * list;
    list = dpl_create(element_copy,element_free,element_compare);

    dpl_insert_at_index(list,&element,0,true);
    dpl_insert_at_index(list,&element2,1,false);
    dpl_printlist(list);
    printf("Size: %d\n",dpl_size(list));

    printf("Found value '%d' stored in reference index 0.\n",*(int*)dpl_get_element_at_reference(list,dpl_get_reference_at_index(list,0)));
    printf("Found value '%d' stored in reference index 1.\n",*(int*)dpl_get_element_at_reference(list,dpl_get_reference_at_index(list,1)));
    printf("Found value '%d' stored in reference index -7.\n",*(int*)dpl_get_element_at_reference(list,dpl_get_reference_at_index(list,-7)));
    printf("Found value '%d' stored in reference index 3.\n",*(int*)dpl_get_element_at_reference(list,dpl_get_reference_at_index(list,3)));

    printf("Found value '%d' stored in first reference.\n",*(int*)dpl_get_element_at_reference(list,dpl_get_first_reference(list)));
    printf("Found value '%d' stored in last reference.\n",*(int*)dpl_get_element_at_reference(list,dpl_get_last_reference(list)));
    refNode = dpl_get_first_reference(list);
    refVal = *(int*)dpl_get_element_at_reference(list,dpl_get_next_reference(list,refNode));
    printf("Found value '%d' stored in next (first+1) reference.\n",refVal);
    refVal = *(int*)dpl_get_element_at_reference(list,dpl_get_previous_reference(list,refNode));
    printf("Found value '%d' stored in previous (first-1) reference.\n",refVal);
    refNode = dpl_get_last_reference(list);
    refVal = *(int*)dpl_get_element_at_reference(list,dpl_get_previous_reference(list,refNode));
    printf("Found value '%d' stored in previous (last-1) reference.\n",refVal);
    refVal = *(int*)dpl_get_element_at_reference(list,dpl_get_next_reference(list,refNode));
    printf("Found value '%d' stored in next (last+1) reference.\n",refVal);


    dpl_free(&list);
    printf("\n\n");
}

void test6() {

    int element = 1;
    int element2 = 2;
    int refVal = 0;

    void * refNode;

    printf("-------- TEST 6 ---------\n");

    dplist_t * list;
    list = dpl_create(element_copy,element_free,element_compare);

    dpl_insert_at_index(list,&element,0,true);
    dpl_insert_at_index(list,&element2,1,false);
    dpl_printlist(list);
    printf("Size: %d\n",dpl_size(list));

    refNode = dpl_get_reference_at_index(list,0);
    refVal = *(int*)dpl_get_element_at_reference(list,refNode);
    printf("Found value '%d' at reference with index 0.\n",refVal);
    refNode = dpl_get_reference_at_index(list,1);
    refVal = *(int*)dpl_get_element_at_reference(list,refNode);
    printf("Found value '%d' at reference with index 1.\n",refVal);
    printf("Reference with index 1 is found at index '%d'.\n",dpl_get_index_of_reference(list,refNode));
    printf("Reference with index NULL is found at index '%d'.\n",dpl_get_index_of_reference(list,NULL));
    printf("Unknown reference is found at index '%d'.\n",dpl_get_index_of_reference(list,(void*)0x888888));
    printf("Element with value '%d' has reference at index '%d'.\n",*(int*)dpl_get_element_at_index(list,0),dpl_get_index_of_reference(list,dpl_get_reference_of_element(list,dpl_get_element_at_index(list,0))));
    printf("Element with value '%d' has reference at index '%d'.\n",*(int*)dpl_get_element_at_index(list,1),dpl_get_index_of_reference(list,dpl_get_reference_of_element(list,dpl_get_element_at_index(list,1))));
    int testVal = 99;
    printf("Unknown element found at reference with index '%d'.\n",dpl_get_index_of_reference(list,dpl_get_reference_of_element(list,&testVal)));

    dpl_free(&list);
    printf("\n\n");
}

void test7() {
    int element = 1;
    int element2 = 2;
    int element3 = 3;

    void * refNode;

    printf("-------- TEST 7 ---------\n");

    dplist_t * list;
    list = dpl_create(element_copy,element_free,element_compare);

    dpl_insert_at_index(list,&element,0,true);
    dpl_insert_at_index(list,&element2,1,false);
    dpl_printlist(list);
    printf("Size: %d\n",dpl_size(list));

    refNode = dpl_get_reference_at_index(list,0);
    dpl_insert_at_reference(list,&element3,refNode,true);
    dpl_printlist(list);
    printf("Size: %d\n",dpl_size(list));
    refNode = dpl_get_reference_of_element(list,&element3);
    printf("Newly inserted element found at '%d'.\n",dpl_get_index_of_element(list,&element3));
    printf("Newly inserted reference found at '%d'.\n",dpl_get_index_of_reference(list,refNode));
    dpl_free(&list);
    printf("\n\n");
}

void test8() {
    int element = 1;
    int element2 = 2;
    int element3 = 3;

    void * refNode;

    printf("-------- TEST 8 ---------\n");

    dplist_t * list;
    list = dpl_create(element_copy,element_free,element_compare);

    dpl_insert_at_index(list,&element,0,true);
    dpl_insert_at_index(list,&element2,1,false);
    dpl_printlist(list);
    printf("Size: %d\n",dpl_size(list));

    refNode = dpl_get_reference_at_index(list,1);
    dpl_remove_at_reference(list,refNode,false);
    dpl_printlist(list);
    printf("Size: %d\n",dpl_size(list));
    dpl_remove_at_reference(list,refNode,false);
    dpl_printlist(list);
    printf("Size: %d\n",dpl_size(list));
    printf("Removed node found at index '%d'.\n",dpl_get_index_of_reference(list,refNode));

    dpl_free(&list);
    printf("\n\n");
}

void test9() {
    int element = 1;
    int element2 = 2;
    int element3 = 3;

    void * refNode;

    printf("-------- TEST 9 ---------\n");

    dplist_t * list;
    list = dpl_create(element_copy,element_free,element_compare);

    dpl_insert_at_index(list,&element,0,true);
    dpl_insert_at_index(list,&element2,1,false);
    dpl_printlist(list);
    printf("Size: %d\n",dpl_size(list));

    refNode = dpl_get_reference_at_index(list,1);
    dpl_remove_element(list,&element2,false);
    dpl_printlist(list);
    printf("Size: %d\n",dpl_size(list));
    printf("Reference found at index '%d'.\n",dpl_get_index_of_reference(list,refNode));

    dpl_free(&list);
    printf("\n\n");
}

void test10() {
    int element = 1;
    int element2 = 2;
    int element3 = 3;
    int element4 = -1;

    void * refNode;

    printf("-------- TEST 10 ---------\n");

    dplist_t * list;
    list = dpl_create(element_copy,element_free,element_compare);

    dpl_insert_at_index(list,&element,0,true);
    dpl_insert_at_index(list,&element2,1,false);
    dpl_printlist(list);
    printf("Size: %d\n",dpl_size(list));

    dpl_insert_sorted(list,&element3,true);
    dpl_printlist(list);
    printf("Size: %d\n",dpl_size(list));
    dpl_insert_sorted(list,&element4,true);
    dpl_printlist(list);
    printf("Size: %d\n",dpl_size(list));

    dpl_free(&list);
    printf("\n\n");
}
