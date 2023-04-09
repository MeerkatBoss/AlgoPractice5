/**
 * @file binary_tree.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 * 
 * @brief
 *
 * @version 0.1
 * @date 2023-04-09
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef __BINARY_TREE_H
#define __BINARY_TREE_H

#include <stdint.h>

class BinaryTree
{
    struct Node
    {
        uint32_t key;

        Node* left;
        Node* right;
    };

    Node* root;

public:
    BinaryTree() : root(nullptr) {}

    BinaryTree(const BinaryTree& tree) = delete;
    BinaryTree& operator=(const BinaryTree& tree) = delete;

    ~BinaryTree()
    {
        clear_node(root);
    }
    void insert(uint32_t key);
    void erase (uint32_t key);
private:
    void clear_node(Node* node);
    Node* insert_node (Node* parent, uint32_t key);
    Node* erase_node  (Node* parent, uint32_t key);
};

#endif /* binary_tree.h */
