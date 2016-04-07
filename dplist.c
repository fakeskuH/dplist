#include <stdlib.h>
#include <stdio.h>

#include "dplist.h"

#ifdef DEBUG
	#define DEBUG_PRINTF(...) 									\
		do {											\
			printf("\nIn %s - function %s at line %d: ", __FILE__, __func__, __LINE__);	\
			printf(__VA_ARGS__);								\
		} while(0)
#else
	#define DEBUG_PRINTF(...) (void)0
#endif


#define DPLIST_ERR_HANDLER(condition,dplist_errno_value,...)\
	do {						\
		if ((condition))			\
		{					\
		  dplist_errno = dplist_errno_value;	\
		  DEBUG_PRINTF(#condition "failed");	\
		  return __VA_ARGS__;			\
		}					\
		dplist_errno = DPLIST_NO_ERROR;			\
	} while(0)


int dplist_errno;

struct dplist_node {
  dplist_node_t *prev, *next;
  void * value;
};

struct dplist {
  dplist_node_t *head;
  void * (*element_copy)(void * src_element);
  void (*element_free)(void ** element);
  int (*element_compare)(void * x, void * y);
};

void * (*element_copy)(void * element);
void (*element_free)(void ** element);
int (*element_compare)(void * x, void * y);

dplist_t * dpl_create(
                void * (*element_copy)(void * element),
                void (*element_free)(void ** element),
                int (*element_compare)(void * x, void * y)
            ) {
    dplist_t * list;
    list = malloc(sizeof(*list));
    DPLIST_ERR_HANDLER((list==NULL),DPLIST_MEMORY_ERROR,NULL);
    list->head = NULL;
    list->element_copy = element_copy;
    list->element_free = element_free;
    list->element_compare = element_compare;
    return list;
}

void dpl_free(dplist_t ** list) {
    DPLIST_ERR_HANDLER((list == NULL || *list == NULL),DPLIST_INVALID_ERROR);
    dplist_node_t * cNode = (*list)->head;
    element_free = (*list)->element_free;

    while (cNode) {
        dplist_node_t * tNode;
        tNode = cNode;
        cNode = cNode->next;
        element_free((void*)tNode);
    }
    free(*list);
}

dplist_t * dpl_insert_at_index(dplist_t * _list, void * value, int index, bool insert_copy) {
    dplist_node_t * cNode;
    dplist_node_t * iNode;
    DPLIST_ERR_HANDLER((_list == NULL),DPLIST_INVALID_ERROR,NULL);
    cNode = malloc(sizeof(*cNode));
    DPLIST_ERR_HANDLER((cNode == NULL),DPLIST_MEMORY_ERROR,NULL);
    if (insert_copy) {
        cNode->value = element_copy(value);
    } else {
        cNode->value = value;
    }

    if (_list->head == NULL) _list->head = cNode;
    else {
        if (index <= 0) {
            cNode->next = _list->head;
            cNode->prev = NULL;
            _list->head->prev = cNode;
            _list->head = cNode;
        } else if (index >= dpl_size(_list)) {
            iNode = dpl_get_last_reference(_list);
            iNode->next = cNode;
            cNode->prev = iNode;
        } else {
            iNode = dpl_get_reference_at_index(_list,index);
            iNode->prev->next = cNode;
            cNode->prev = iNode->prev;
            cNode->next = iNode;
            iNode->prev = cNode;
        }
    }
    return _list;
}

dplist_t * dpl_remove_at_index(dplist_t * list,int index, bool free_element) {
    dplist_node_t * cNode;
    DPLIST_ERR_HANDLER((list == NULL),DPLIST_INVALID_ERROR,NULL);
    if (list->head == NULL) return NULL;
    else {
        if (index <= 0) {
            cNode = list->head;
            list->head = cNode->next;
            list->head->prev = NULL;
            if (free_element) element_free(&cNode->value);
            free(cNode);
        } else if (index >= dpl_size(list)) {
            dplist_node_t * iNode = dpl_get_last_reference(list);
            iNode->prev->next = NULL;
            if (free_element) element_free(&iNode->value);
            free(iNode);
        } else {
            dplist_node_t * iNode = dpl_get_reference_at_index(list, index);
            iNode->next->prev = iNode->prev;
            iNode->prev->next = iNode->next;
            if (free_element) element_free(&iNode->value);
            free(iNode);
        }
    }
    return list;
}

int dpl_size(dplist_t * list) {
    DPLIST_ERR_HANDLER((list == NULL),DPLIST_INVALID_ERROR,0);
    int size = 0;
    dplist_node_t * iNode;

    iNode = list->head;

    while (iNode) {
        size++;
        iNode = iNode->next;
    }
    return size;
}

dplist_node_t * dpl_get_reference_at_index(dplist_t * list, int index) {
    DPLIST_ERR_HANDLER((list == NULL),DPLIST_INVALID_ERROR,NULL);
    int count;
    dplist_node_t * iNode;

    count = 0;
    iNode = list->head;

    if (index <= 0) return dpl_get_first_reference(list);
    if (index >= dpl_size(list)) return dpl_get_last_reference(list);
    if (iNode == NULL) return (void*)NULL;
    do {
        iNode = iNode->next;
        count++;
        if (count == index) return iNode;
    } while (iNode->next != NULL);
    return NULL;
}

void * dpl_get_element_at_index(dplist_t * list,int index) {
    DPLIST_ERR_HANDLER((list == NULL),DPLIST_INVALID_ERROR,NULL);
    int count;
    dplist_node_t * iNode;
    dplist_node_t * rNode;

    count = 0;
    iNode = list->head;
    rNode = NULL;

    if (index <= 0) {
        rNode = dpl_get_first_reference(list);
        if (!rNode) return (void*)NULL;
        else return rNode->value;
    }
    if (index >= dpl_size(list)) {
        rNode = dpl_get_last_reference(list);
        if (!rNode) return (void*)NULL;
        else return rNode->value;
    }
    if (iNode == NULL) return (void*)NULL;
    do {
        iNode = iNode->next;
        count++;
        if (count == index) return &iNode->value;
    } while (iNode->next != NULL);
    return NULL;
}

int dpl_get_index_of_element(dplist_t * list, void * value) {
    DPLIST_ERR_HANDLER((list == NULL),DPLIST_INVALID_ERROR,(long)NULL);
    dplist_node_t * iNode = list->head;
    int index = 0;

    if (iNode == NULL) return (long)NULL;
    while (iNode->next != NULL) {
        if (element_compare(iNode->value,value) == 0) return index;
        iNode = iNode->next;
        index++;
    }
    return -1;
}

dplist_node_t * dpl_get_last_reference(dplist_t * list) {
    DPLIST_ERR_HANDLER((list == NULL),DPLIST_INVALID_ERROR,NULL);
    dplist_node_t * iNode = list->head;

    if (iNode == NULL) return NULL;
    else {
        while (iNode->next != NULL) iNode = iNode->next;
        return iNode;
    }
}

dplist_node_t * dpl_get_first_reference(dplist_t * list) {
    DPLIST_ERR_HANDLER((list == NULL),DPLIST_INVALID_ERROR,NULL);
    return list->head;
}

dplist_node_t * dpl_get_next_reference(dplist_t * list, dplist_node_t * reference) {
    DPLIST_ERR_HANDLER((list == NULL),DPLIST_INVALID_ERROR,NULL);
    dplist_node_t * iNode;
    iNode = list->head;

    if (!iNode || !reference) return NULL;
    else {
        while (iNode) {
            iNode = iNode->next;
            if (iNode == reference) return iNode->next;
        }
    }
    return NULL;
}

dplist_node_t * dpl_get_previous_reference(dplist_t * list, dplist_node_t * reference) {
    DPLIST_ERR_HANDLER((list == NULL),DPLIST_INVALID_ERROR,NULL);
    dplist_node_t * iNode;
    iNode = list->head;

    if (!iNode || !reference) return NULL;
    else {
        while (iNode) {
            if (iNode == reference) return iNode->prev;
            iNode = iNode->next;
        }
    }
    return NULL;
}
void * dpl_get_element_at_reference(dplist_t * list, dplist_node_t * reference) {
    DPLIST_ERR_HANDLER((list == NULL),DPLIST_INVALID_ERROR,NULL);
    dplist_node_t * iNode;
    iNode = list->head;

    if (!iNode || !reference) return NULL;
    while (iNode) {
        if (iNode == reference) return iNode->value;
        iNode = iNode->next;
    }
    return NULL;
}
dplist_node_t * dpl_get_reference_of_element(dplist_t * list, void * element) {
    DPLIST_ERR_HANDLER((list == NULL),DPLIST_INVALID_ERROR,NULL);
    dplist_node_t * iNode;
    iNode = list->head;

    if (!iNode) return NULL;
    while(iNode) {
        if (element_compare(iNode->value,element) == 0) return iNode;
        iNode = iNode->next;
    }
    return NULL;
}

int dpl_get_index_of_reference(dplist_t * list,dplist_node_t * reference) {
    DPLIST_ERR_HANDLER((list == NULL),DPLIST_INVALID_ERROR,(long)NULL);
    dplist_node_t * iNode;
    iNode = list->head;

    int count = 0;

    if (!iNode) return -1;
    if (!reference) return dpl_size(list);
    while (iNode) {
        if (iNode == reference) return count;
        count++;
        iNode = iNode->next;
    }
    return -1;
}

dplist_t * dpl_insert_at_reference(dplist_t * list, void * element, dplist_node_t * reference, bool insert_copy) {
    DPLIST_ERR_HANDLER((list == NULL),DPLIST_INVALID_ERROR,NULL);
    dplist_node_t * iNode;
    dplist_node_t * nNode;
    dplist_node_t * tNode;
    iNode = list->head;

    if (!iNode) return NULL;
    while (iNode) {
        if (iNode == reference) {
            nNode = malloc(sizeof(*nNode));
            DPLIST_ERR_HANDLER((nNode == NULL),DPLIST_MEMORY_ERROR,NULL);
            tNode = iNode->next;
            iNode->next = nNode;
            nNode->prev = iNode;
            nNode->next = tNode;
            if (insert_copy) nNode->value = element_copy(element);
            else nNode->value = element;
            return list;
        }
        iNode = iNode->next;
    }
    return list;
}

dplist_t * dpl_insert_sorted(dplist_t * list, void * value, bool insert_copy) {
    DPLIST_ERR_HANDLER((list == NULL),DPLIST_INVALID_ERROR,NULL);
    dplist_node_t * iNode;
    dplist_node_t * nNode;
    iNode = list->head;

    if (!iNode) return NULL;
    while (iNode) {
        if (element_compare(value, iNode->value) == -1) {
            iNode = iNode->next;
        } else {
            nNode = malloc(sizeof(*nNode));
            DPLIST_ERR_HANDLER((nNode == NULL),DPLIST_MEMORY_ERROR,NULL);
            if (insert_copy) nNode->value = element_copy(value);
            else nNode->value = value;
            nNode->next = iNode;
            nNode->prev = iNode->prev;
            iNode->prev->next = nNode;
            iNode->prev = nNode;
            return list;
        }
    }
    return list;
}

dplist_t * dpl_remove_at_reference(dplist_t * list, dplist_node_t * reference, bool free_element) {
    DPLIST_ERR_HANDLER((list == NULL),DPLIST_INVALID_ERROR,NULL);
    dplist_node_t * iNode;
    dplist_node_t * rNode;
    iNode = list->head;

    if (!iNode) return list;
    if (!reference) rNode = dpl_get_last_reference(list);
    while (iNode) {
        if (iNode == reference) rNode = iNode;
        iNode = iNode->next;
    }
    if (rNode) {
        if (free_element) element_free(&rNode->value);
        rNode->prev->next = rNode->next;
        if (!rNode->next) rNode->next->prev = rNode->prev;
        free(rNode);
    }
    return list;
}

dplist_t * dpl_remove_element(dplist_t * list, void * value, bool free_element) {
    DPLIST_ERR_HANDLER((list == NULL),DPLIST_INVALID_ERROR,NULL);
    dplist_node_t * iNode;
    iNode = list->head;
    if (!iNode) return NULL;

    while (iNode) {
        if (element_compare(value, iNode->value)== 0) {
            iNode->prev->next = iNode->next;
            if (!iNode->next) iNode->next->prev = iNode->prev;
            if (free_element) element_free(&iNode->value);
            free(iNode);
            return list;
        }
        iNode = iNode->next;
    }
    return list;
}
