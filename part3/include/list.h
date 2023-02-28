/**
 * @file list.h
 * @brief A double-linked list implementation.
*/

#ifndef LIST_H
#define LIST_H

/**
 * @struct list
 * @brief A list data structure that contains a head and tail pointer to its entries.
*/
struct list {
    struct listentry* head; /**< A pointer to the first entry in the list. */
    struct listentry* tail; /**< A pointer to the last entry in the list. */
};

/**
 * @struct listentry
 * @brief A list entry that contains a data pointer and pointers to the previous and next entries in the list.
*/
struct listentry {
    void *data; /**< A pointer to the data stored in this entry. */
    struct listentry *prev; /**< A pointer to the previous entry in the list. */
    struct listentry *next; /**< A pointer to the next entry in the list. */
};

/**
 * @brief Removes the given entry from the list.
 * Also free the space captured by the entry.
 * @param l The list from which to remove the entry.
 * @param e The entry to be removed.
*/
void list_rm(struct list *l, struct listentry *e);

/**
 * @brief Adds a new entry with the given data to the list.
 * @param l The list to which the entry should be added.
 * @param data The data to be stored in the new entry.
 * @return A pointer to the new entry.
*/
struct listentry *list_add(struct list *l, void *data);

/**
 * @brief Creates a new empty list.
 * @return A pointer to the new list.
*/
struct list *list_new();

/**
 * @brief Checks whether the given list is empty.
 * @param l The list to check.
 * @return 1 if the list is empty, 0 otherwise.
*/
int is_empty(struct list *l);

#endif
