/**
 * @file avl_tree.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 * 
 * @brief
 *
 * @version 0.1
 * @date 2023-04-09
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef __AVL_TREE_H
#define __AVL_TREE_H

#include <stdint.h>
#include <stddef.h>

class AVLTree
{
    struct Node
    {
        uint32_t key;

        size_t height;
        Node* left;
        Node* right;
    };
    
    Node* root;
public:
    AVLTree() : root(nullptr) {} 

    AVLTree(const AVLTree& tree) = delete;
    AVLTree& operator=(const AVLTree& tree) = delete;

    ~AVLTree()
    {
        clear_node(root);
    }
    void insert(uint32_t key);
    void erase(uint32_t key);
private:
    void clear_node(Node* node);

    Node* insert_node(Node* node, uint32_t key);
    Node* erase_node(Node* node, uint32_t key);

    Node* detach_min_node(Node* node);
    Node* balance_node(Node* node);
    Node* rotate_left (Node* node);
    Node* rotate_right(Node* node);

    inline size_t get_height(const Node* node)
    {
        return node ? node->height : 0;
    }

    inline long get_balance(const Node* node)
    {
        if (!node) return 0;
        return (long) get_height(node->right) - (long) get_height(node->left);
    }
    
    inline size_t get_updated_height(const Node* node)
    {
        if (!node) return 0;
        
        size_t  left_height = get_height(node->left );
        size_t right_height = get_height(node->right);

        return 1 + (left_height > right_height
                        ? left_height
                        : right_height);
    }

};

#endif /* avl_tree.h */
