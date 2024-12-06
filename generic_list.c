//
// Created by 03sotnikok99 on 12/4/2024.
//


#include "generic_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void generic_list_init(struct generic_list* list) {
    list->head = NULL;
    list->size = 0;
}
void generic_list_destructor(struct generic_list* list ) {
    while(list->size > 0) {
        generic_list_pop(list);
    }
}
void generic_list_pop(struct generic_list* list) {
    if(list == NULL)
        return;
    if(list->head == NULL)
        return;
    struct generic_node* temp = list->head;
    list->head = list->head->next;
    free(temp->data);
    free(temp);
    list->size--;
}
void generic_list_add(struct generic_list* list, void* data, size_t data_size) {
    if(list == NULL)
        return;
    // you need to allocate memory both for a new node to be added and for the data in the node
    struct generic_node* item = (struct generic_node*) calloc(1, sizeof(struct generic_node));
    item->data = malloc(data_size);
    item->data_size = data_size;
    // the whole MAGIC is here
    memmove(item->data, data, data_size);

    if(list->head == NULL) {
        list->head = item;
        list->size++;
        return;
    }
    struct generic_node* temp = list->head;
    while(temp->next != NULL)
        temp = temp->next;
    temp->next = item;
    list->size++;



}
void* generic_list_get_element(struct  generic_list* list, size_t index) {
    if(list == NULL)
        return NULL;
    if(index >= list->size)
        return NULL;
    struct generic_node* temp = list->head;
    int i = 0;
    while(temp->next != NULL && index!=i) {
        temp = temp->next;
        i++;
    }
    return temp->data;

}
size_t generic_list_get_size(struct  generic_list* list, size_t index) {
    if(list == NULL)
        return 0;
    if(index >= list->size)
        return 0;
    struct generic_node* temp = list->head;
    int i = 0;
    while(temp->next != NULL && index!=i) {
        temp = temp->next;
        i++;
    }
    return temp->data_size;
}

// int result = memcmp(ptr1, ptr2, len1);
// 0 if equal, <0 if ptr1 < ptr2, >0 if ptr1 > ptr2
bool generic_list_contains(struct generic_list* list, void* data, size_t data_size) {
    if(list == NULL)
        return 0;
    if(list->head == NULL)
        return 0;
    struct generic_node* temp = list->head;
    while(temp != NULL) {
        if(temp->data_size == data_size) {
            if(memcmp(temp->data, data, data_size) == 0)
                return 1;
        }
        temp = temp->next;
    }
    return 0;
}
void generic_list_remove(struct generic_list* list, size_t index) {
    if (list == NULL || list->head == NULL || index >= list->size)
        return;

    if (index == 0) {
        // Remove the head node
        struct generic_node* temp = list->head;
        list->head = list->head->next;
        if (temp->data) {
            free(temp->data); // Free the data if dynamically allocated
        }
        free(temp); // Free the node itself
        list->size--;
        return;
    }

    struct generic_node* temp = list->head;
    size_t i = 0;

    while (temp->next != NULL) {
        if (i == index - 1) {
            struct generic_node* item = temp->next;
            temp->next = temp->next->next;
            if (item->data) {
                free(item->data); // Free the data if dynamically allocated
            }
            free(item); // Free the node itself
            list->size--;
            return;
        }
        temp = temp->next;
        i++;
    }
}
size_t generic_list_size(struct generic_list* list) {
    if(list == NULL)
        return 0;
    return list->size;
}
bool generic_list_is_empty(struct generic_list* list ) {
    if(list == NULL)
        return true;
    return list->size == 0 ? true : false;
}

void generic_list_print(struct generic_list* list, void (*fptr)(void*)) {
    if(list == NULL)
        return;
    if(list->head ==  NULL)
        return;
    struct generic_node* temp = list->head;
    while(temp!=NULL) {
        fptr(temp->data);
        temp=temp->next;
    }
    printf("\n");
}
void print_int(void* data) {
 printf("%d, ", *(int*)data);
}
void print_float(void* data) {
    printf("%f, ", *(float*)data);
}



void generic_list_load_from_file(struct generic_list* list) {
    if (list == NULL) {
        fprintf(stderr, "List pointer is NULL\n");
        return;
    }

    FILE* fp = fopen("D:/C/uebung5/generic_pointers2    .txt", "r");
    if (fp == NULL) {
        perror("Error occurred while opening the file");
        return;
    }


    generic_list_destructor(list);
    generic_list_init(list);


    size_t size = 0;
    // Read the size of the list
    if (fread(&size, sizeof(size_t), 1, fp) != 1) {
        perror("Error reading list size");
        fclose(fp);
        return;
    }

    for (size_t i = 0; i < size; ++i) {
        size_t data_size = 0;
        if (fread(&data_size, sizeof(size_t), 1, fp) != 1) {
            perror("Error reading data size");
            fclose(fp);
            return;
        }

        void* data = malloc(data_size);
        if (data == NULL) {
            perror("Memory allocation failed");
            fclose(fp);
            return;
        }

        if (fread(data, data_size, 1, fp) != 1) {
            perror("Error reading data");
            free(data);
            fclose(fp);
            return;
        }

        // Add to the list
        generic_list_add(list, data, data_size);
        free(data);
    }

    fclose(fp);
}
// void generic_list_save_in_file(struct generic_list* list) {
//     if(list == NULL)
//         return;
//     FILE* fp = fopen("D:/C/uebung5/generic_pointers.txt", "w+");
//     if(fp == NULL) {
//         perror("Error occurred while opening a file with pointers");
//     }
//     fprintf(fp, "%u\n", list->size);
//     struct generic_node* temp = list->head;
//     while(temp!= NULL) {
//         fprintf(fp, "%p %llu\n", temp->data, temp->data_size);
//         temp = temp->next;
//     }
//     fclose(fp);
//
// }

void generic_list_save_in_file(struct generic_list* list) {
    if(list == NULL)
        return;
    FILE* fp = fopen("D:/C/uebung5/generic_pointers2.txt", "wb");
    if(fp == NULL) {
        perror("Error occurred while opening a file with pointers");
    }
    fwrite(&list->size, sizeof(size_t), 1, fp);
    struct generic_node* temp = list->head;
    while(temp!= NULL) {
        fwrite(&temp->data_size, sizeof(size_t), 1, fp);
        fwrite(temp->data, temp->data_size, 1, fp);
        temp = temp->next;
    }
    fclose(fp);
}


