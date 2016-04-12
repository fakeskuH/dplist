#ifndef DPLIST_H
#define DPLIST_H

#define DPLIST_NO_ERROR 0
#define DPLIST_MEMORY_ERROR 1 // error due to mem alloc failure
//#define DPLIST_EMPTY_ERROR 2  //error due to an operation that can't be executed on an empty list
#define DPLIST_INVALID_ERROR 3 //error due to a list operation applied on a NULL list

extern int dplist_errno;

typedef enum { false, true } bool;

typedef struct dplist dplist_t;
typedef struct dplist_node dplist_node_t;

dplist_t * dpl_create(
                void * (*element_copy)(void * element),
                void (*element_free)(void ** element),
                int (*element_compare)(void * x, void * y)
            );
void dpl_free(dplist_t ** _list);
dplist_t * dpl_insert_at_index(dplist_t * list, void * value, int index, bool insert_copy);
dplist_t * dpl_remove_at_index(dplist_t * list,int index, bool free_element);
int dpl_size(dplist_t * list);
dplist_node_t * dpl_get_reference_at_index(dplist_t * list,int index);
void * dpl_get_element_at_index(dplist_t * list, int index);
int dpl_get_index_of_element(dplist_t * list,void * value);
dplist_node_t * dpl_get_first_reference(dplist_t * list);
dplist_node_t * dpl_get_last_reference(dplist_t * list);
dplist_node_t * dpl_get_next_reference(dplist_t * list, dplist_node_t * reference);
dplist_node_t * dpl_get_previous_reference(dplist_t * list, dplist_node_t * reference);
void * dpl_get_element_at_reference(dplist_t * list, dplist_node_t * reference);
dplist_node_t * dpl_get_reference_of_element(dplist_t * list, void * value);
int dpl_get_index_of_reference(dplist_t * list, dplist_node_t * reference);
dplist_t * dpl_insert_at_reference(dplist_t * list, void * value,dplist_node_t * reference, bool insert_copy);
dplist_t * dpl_insert_sorted(dplist_t * list, void * value, bool insert_copy);
dplist_t * dpl_remove_at_reference(dplist_t * list,dplist_node_t * reference,bool free_element);
dplist_t * dpl_remove_element(dplist_t * list, void * value, bool free_element);
void dpl_printlist(dplist_t * list);

#endif // DPLIST_H
