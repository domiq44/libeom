//
//  LinkedList.c
//  hdelibc
//
//  Created by Eric Meehan on 1/31/21.
//

#include <stdlib.h>
#include <stdio.h>

#include "LinkedList.h"



/* PRIVATE METHODS */

struct Node * create_node(void *data, int size);
void destroy_node(struct Node *node_to_destroy);



/* PUBLIC MEMBER METHODS */
struct Node * iterate(struct LinkedList *linked_list, int index);
void insert(struct LinkedList *linked_list, int index, void *data, int size);
void remove_node(struct LinkedList *linked_list, int index);
void * retrieve(struct LinkedList *linked_list, int index);



/* CONSTRUCTORS */
struct LinkedList linked_list_constructor()
{
    struct LinkedList new_list;
    new_list.head = NULL;
    new_list.length = 0;
    
    new_list.insert = insert;
    new_list.remove = remove_node;
    new_list.retrieve = retrieve;
    
    return new_list;
}

void linked_list_destructor(struct LinkedList *linked_list)
{
    for (int i = 0; i < linked_list->length; i++)
    {
        linked_list->remove(linked_list, 0);
    }
}



/* PRIVATE METHODS */

// The create_node function creates a new node to add to the chain by allocating space on the heap and calling the node constructor.
struct Node * create_node(void *data, int size)
{
    // Allocate space.
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    // Call the constructor.
    *new_node = node_constructor(data, size);
    return new_node;
}

// The destroy_node function removes a node by deallocating it's memory address.  This simply renames the node destructor function.
void destroy_node(struct Node *node_to_destroy)
{
    node_destructor(node_to_destroy);
}

// The iterate function traverses the list from beginning to end.
struct Node * iterate(struct LinkedList *linked_list, int index)
{
    // Confirm the user has specified a valid index.
    if (index < 0 || index >= linked_list->length)
    {
        printf("Index out of bound..");
        exit(9);
    }
    // Create a cursor node for iteration.
    struct Node *cursor = linked_list->head;
    // Step through the list until the desired index is reached.
    for (int i = 0; i < index; i++)
    {
        cursor = cursor->next;
    }
    return cursor;
}



/* PUBLIC METHODS */

// The insert function puts a new node in the chain.
void insert(struct LinkedList *linked_list, int index, void *data, int size)
{
    // Create a new node to be inserted.
    struct Node *node_to_insert = create_node(data, size);
    // Check if this node will be the new head of the list.
    if (index == 0)
    {
        // Define the Node's next.
        node_to_insert->next = linked_list->head;
        // Re-define the List's head.
        linked_list->head = node_to_insert;
    }
    else
    {
        // Find the item in the list immediately before the desired index.
        struct Node *cursor = iterate(linked_list, index - 1);
        // Set the Node's next.
        node_to_insert->next = cursor->next;
        // Set the cursor's next to the new node.
        cursor->next = node_to_insert;
        
    }
    // Increment the list length.
    linked_list->length += 1;
}

// The remove function removes a node from the linked list.
void remove_node(struct LinkedList *linked_list, int index)
{
    // Check if the item being removed is the head.
    if (index == 0)
    {
        // Collect the node to be removed.
        struct Node *node_to_remove = linked_list->head;
        // Define the new head of the list.
        linked_list->head = node_to_remove->next;
        // Remove the desired node.
        destroy_node(node_to_remove);
    }
    else
    {
        // Find the item in the list before the one that is going to be removed.
        struct Node *cursor = iterate(linked_list, index - 1);
        // Use the cursor to define the node to be removed.
        struct Node *node_to_remove = cursor->next;
        // Update the cursor's next to skip the node to be removed.
        cursor->next = node_to_remove->next;
        // Remove the node.
        destroy_node(node_to_remove);
    }
    // Decrement the list length.
    linked_list->length -= 1;
}

// The retrieve function is used to access data in the list.
void * retrieve(struct LinkedList *linked_list, int index)
{
    // Find the desired node and return its data.
    struct Node *cursor = iterate(linked_list, index);
    return cursor->data;
}
