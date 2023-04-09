#include <cstdlib>

#include "treap.h"

void Treap::insert(uint32_t key)
{
    Node* node = (Node*) calloc(1, sizeof(*node));

    node->key = key;
    node->priority = distrib(gen);
    node->left = nullptr;
    node->right = nullptr;

    Node *left = nullptr, *right = nullptr;

    split_node(root, key, &left, &right);

    left = merge_nodes(left, node);
    root = merge_nodes(left, right);
}

void Treap::erase(uint32_t key)
{
    root = erase_node(root, key);
}

void Treap::clear_node(Node* node)
{
    if (!node) return;
    if (node->left)  clear_node(node->left);
    if (node->right) clear_node(node->right);

    free(node);
}

Treap::Node* Treap::erase_node(Node* node, uint32_t key)
{
    if (!node) return nullptr;

    if (key == node->key)
    {
        Node* merged = merge_nodes(node->left, node->right);
        free(node);
        return merged;
    }

    if (key < node->key) node->left  = erase_node(node->left,  key);
    else                 node->right = erase_node(node->right, key);

    return node;
}

Treap::Node* Treap::merge_nodes(Node* left, Node* right)
{
    if (!left)  return right;
    if (!right) return left;
    
    if (left->priority > right->priority)
    {
        left->right = merge_nodes(left->right, right);
        return left;
    }
    else
    {
        right->left = merge_nodes(left, right->left);
        return right;
    }
}

void  Treap::split_node(Node* source, uint32_t key,
                  Node** dest_left, Node** dest_right)
{
    if (!source)
    {
        *dest_left = nullptr;
        *dest_right = nullptr;
        return;
    }

    if (key < source->key)
    {
        split_node(source->left, key, dest_left, &source->left);
        *dest_right = source;
        return;
    }
    else
    {
        split_node(source->right, key, &source->right, dest_right);
        *dest_left = source;
        return;
    }
}

