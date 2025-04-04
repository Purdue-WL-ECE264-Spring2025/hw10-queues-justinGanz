#include "linked_list.h"
#include <stdlib.h>

// Helper function to create a new node
struct list_node *new_node(size_t value) {
    struct list_node *node = malloc(sizeof(struct list_node));
    if (!node) {
        return NULL;  // Handle memory allocation failure
    }
    node->value = value;
    node->next = NULL;
    return node;
}

// Insert a value at the head of the linked list
void insert_at_head(struct linked_list *list, size_t value) {
    struct list_node *new = new_node(value);
    if (!new) {
        return;  // Handle memory allocation failure
    }
    new->next = list->head;
    list->head = new;
}

// Insert a value at the tail of the linked list
void insert_at_tail(struct linked_list *list, size_t value) {
    struct list_node *new = new_node(value);
    if (!new) {
        return;  // Handle memory allocation failure
    }
    
    if (list->head == NULL) {
        list->head = new;
        return;
    }
    
    struct list_node *temp = list->head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new;
}

// Remove and return the value at the head of the linked list
size_t remove_from_head(struct linked_list *list) {
    if (list->head == NULL) {
        return 0;  // Return 0 if the list is empty (or handle as an error)
    }
    
    struct list_node *temp = list->head;
    size_t value = temp->value;
    list->head = temp->next;
    free(temp);
    
    return value;
}

// Remove and return the value at the tail of the linked list
size_t remove_from_tail(struct linked_list *list) {
    if (list->head == NULL) {
        return 0;  // Return 0 if the list is empty (or handle as an error)
    }
    
    if (list->head->next == NULL) {
        // Only one node in the list
        size_t value = list->head->value;
        free(list->head);
        list->head = NULL;
        return value;
    }
    
    struct list_node *temp = list->head;
    while (temp->next && temp->next->next != NULL) {
        temp = temp->next;
    }
    
    size_t value = temp->next->value;
    free(temp->next);
    temp->next = NULL;
    
    return value;
}

// Free all nodes in the linked list
void free_list(struct linked_list list) {
    struct list_node *temp = list.head;
    while (temp != NULL) {
        struct list_node *next = temp->next;
        free(temp);
        temp = next;
    }
}


// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}