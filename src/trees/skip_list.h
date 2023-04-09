/**
 * @file skip_list.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 * 
 * @brief
 *
 * @version 0.1
 * @date 2023-04-09
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef __SKIP_LIST_H
#define __SKIP_LIST_H

#include <stdint.h>
#include <random>

class SkipList
{
    struct Node
    {
        uint32_t key;

        Node* next;
        Node* down;
    };

    Node* root;
    std::mt19937 gen;
    std::bernoulli_distribution coin;

public:
    SkipList() : root(nullptr), gen(std::random_device()()), coin(0.5) {}

    SkipList(const SkipList& list) = delete;
    SkipList& operator=(const SkipList& list) = delete;

    ~SkipList()
    {
        clear();
    }

    void insert(uint32_t key);
    void erase(uint32_t key);

private:

    void clear(void);

    Node* insert_node(Node* node, uint32_t key);
    void  erase_node (Node* node, uint32_t key);
};

#endif /* skip_list.h */
