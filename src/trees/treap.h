/**
 * @file treap.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 * 
 * @brief
 *
 * @version 0.1
 * @date 2023-04-09
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef __TREAP_H
#define __TREAP_H

#include <stdint.h>
#include <climits>
#include <random>

class Treap
{
    struct Node
    {
        uint32_t key;
        int priority;

        Node* left;
        Node* right;
    };
    Node* root;

    // Cannot use rand() because it will mess testing up
    std::mt19937 gen;
    std::uniform_int_distribution<> distrib;

public:
    Treap() : root(nullptr), gen(std::random_device()()), distrib(0, INT_MAX) {}
    
    Treap(const Treap& treap) = delete;
    Treap& operator=(const Treap& treap) = delete;

    ~Treap()
    {
        clear_node(root);
    }

    void insert(uint32_t key);
    void erase(uint32_t key);
    
private:
    void clear_node(Node* node);

    Node* erase_node(Node* node, uint32_t key);

    Node* merge_nodes(Node* left, Node* right);
    void  split_node (Node* source, uint32_t key,
                      Node** dest_left, Node** dest_right);

};

#endif /* treap.h */
