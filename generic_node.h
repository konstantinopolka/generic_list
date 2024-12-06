//
// Created by 03sotnikok99 on 12/4/2024.
//

#ifndef GENERIC_NODE_H
#define GENERIC_NODE_H

struct generic_node {
    struct generic_node* next;
    size_t data_size;
    void* data;

};



#endif //GENERIC_NODE_H
