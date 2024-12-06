//
// Created by 03sotnikok99 on 12/4/2024.
//

#ifndef GENERIC_LIST_H
#define GENERIC_LIST_H
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "generic_node.h"

// there is a helper data structure to store the size of the list
// and navigate between elements more easily

// how the elements are stored is that each node stores both its value, or in other words, its sequence of bits
// and its size in bits, so how many bits this concrete node needs to store this value
// so to use an element of the list, you need both its size and value
// you need the size its size to "depoint" correctly

struct generic_list {
    struct generic_node* head;
    size_t size;
};


void generic_list_init(struct generic_list*);
void generic_list_load_from_file(struct generic_list*);
void generic_list_save_in_file(struct generic_list*);

void generic_list_destructor(struct generic_list* );
void generic_list_add(struct generic_list*, void* data, size_t data_size);
void* generic_list_get_element(struct  generic_list*, size_t index);
size_t generic_list_get_size(struct  generic_list*, size_t index);
bool generic_list_contains(struct generic_list*, void* data, size_t data_size);
void generic_list_remove(struct generic_list*, size_t index);
size_t generic_list_size(struct generic_list*);
bool generic_list_is_empty(struct generic_list* );
void generic_list_pop(struct generic_list*);
void generic_list_print(struct generic_list*, void (*fptr)(void*));
void print_int(void*);
void print_float(void*);




// a. Add – Fügt ein Element am Ende der Liste hinzu.
// b. Get – Gibt ein Element an einer bestimmten Position zurück.
// c. Contains – Überprüft, ob ein Element in der Liste gespeichert ist und gibt die
// Position zurück.
// d. Remove – Entfernt das Element an der angegebenen Position.
// e. IsEmpty – Überprüft, ob die Liste leer ist.
// f. Size – Überprüft, wie viele Elemente in der Liste gespeichert sind.

#endif //GENERIC_LIST_H
