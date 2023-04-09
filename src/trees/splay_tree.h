/**
 * @file splay_tree.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 * 
 * @brief
 *
 * @version 0.1
 * @date 2023-04-09
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef __SPLAY_TREE_H
#define __SPLAY_TREE_H

#include <stdint.h>
#include <stddef.h>

class SplayTree
{
    struct Node
    {
        uint32_t key;

        Node* parent;
        Node* left;
        Node* right;
    };

    Node* root;

public:
    SplayTree() : root(nullptr) {}

    SplayTree(const SplayTree& tree) = delete;
    SplayTree& operator=(const SplayTree& tree) = delete;

    ~SplayTree()
    {
        clear_node(root);
    }
    void insert(uint32_t key);
    void erase(uint32_t key);
private:
    void clear_node(Node* node);

    Node* insert_node(Node* parent, Node* node);
    Node* find_node  (Node* node, uint32_t key);

    void splay_node(Node* node);

    void zigzig(Node* parent, Node* grandparent);
    void zigzag(Node* parent, Node* grandparent);

    Node* rotate_left (Node* node);
    Node* rotate_right(Node* node);

    inline Node* get_parent(Node* node)
    {
        return node ? node->parent : nullptr;
    }

    inline Node* get_grandparent(Node* node)
    {
        return get_parent(get_parent(node));
    }

    inline bool is_left_child(Node* node)
    {
        return get_parent(node) && node == node->parent->left;
    }

    inline bool is_right_child(Node* node)
    {
        return get_parent(node) && node == node->parent->right;
    }
};

#endif /* splay_tree.h */
