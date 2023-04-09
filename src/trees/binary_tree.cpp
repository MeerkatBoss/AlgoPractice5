#include <cstdlib>

#include "binary_tree.h"

void BinaryTree::insert(uint32_t key)
{
    root = insert_node(root, key);
}

void BinaryTree::erase(uint32_t key)
{
    root = erase_node(root, key);
}

void BinaryTree::clear_node(Node* node)
{
    if (!node) return;
    if (node->left)  clear_node(node->left);
    if (node->right) clear_node(node->right);

    free(node);
}

BinaryTree::Node* BinaryTree::insert_node(Node* parent, uint32_t key)
{
    if (!parent)
    {
        Node* new_node = (Node*) calloc(1, sizeof(*new_node));
        new_node->key = key;
        new_node->left = nullptr;
        new_node->right = nullptr;

        return new_node;
    }
    
    if (key <= parent->key)
        parent->left = insert_node(parent->left, key);
    else
        parent->right = insert_node(parent->right, key);

    return parent;
}

BinaryTree::Node* BinaryTree::erase_node(Node* parent, uint32_t key)
{
    if (!parent) return nullptr;

    if (parent->key < key)
    {
        parent->left = erase_node(parent->left, key);
        return parent;
    }
    if (parent->key > key)
    {
        parent->right = erase_node(parent->right, key);
        return parent;
    }

    if (!parent->left)
    {
        Node* tmp = parent->right;
        free(parent);
        return tmp;
    }

    if (!parent->right)
    {
        Node* tmp = parent->left;
        free(parent);
        return tmp;
    }

    Node* min_node = parent->right;
    Node* min_parent = parent;
    
    while (min_node->left)
    {
        min_parent = min_node;
        min_node = min_node->left;
    }
    
    parent->key = min_node->key;

    if (min_parent != parent)
        min_parent->left = min_node->right;
    else
        min_parent->right = min_node->right;

    free(min_node);

    return parent;
}
