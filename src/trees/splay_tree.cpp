#include <cstdlib>

#include "splay_tree.h"

void SplayTree::insert(uint32_t key)
{
    Node* node = (Node*) calloc(1, sizeof(*node));

    node->key = key;
    node->parent = nullptr;
    node->left = nullptr;
    node->right = nullptr;

    insert_node(root, node);
    splay_node(node);

    root = node;
}

void SplayTree::erase(uint32_t key)
{
    Node* deleted = find_node(root, key);

    if (!deleted) return;

    splay_node(deleted);
    
    Node* left = deleted->left;
    Node* right = deleted->right;

    free(deleted);

    if (left) left->parent = nullptr;
    if (right) right->parent = nullptr;

    if (!left)
    {
        root = right;
        return;
    }
    if (!right)
    {
        root = left;
        return;
    }

    Node* left_max = left;

    while (left_max->right)
        left_max = left_max->right;

    splay_node(left_max);
    left_max->right = right;
    right->parent = left_max;

    root = left_max;
}

void SplayTree::clear_node(Node* node)
{
    if (!node) return;
    if (node->left)  clear_node(node->left);
    if (node->right) clear_node(node->right);

    free(node);
}

SplayTree::Node* SplayTree::insert_node(Node* parent, Node* node)
{
    if (!parent) return node;
    
    if (node->key <= parent->key)
    {
        parent->left = insert_node(parent->left,  node);
        parent->left->parent = parent;
    }
    else
    {
        parent->right = insert_node(parent->right, node);
        parent->right->parent = parent;
    }

    return parent;   
}

SplayTree::Node* SplayTree::find_node(Node* node, uint32_t key)
{
    if (!node) return nullptr;

    if (key == node->key) return node;

    if (key < node->key) return find_node(node->left,  key);
    else                 return find_node(node->right, key);
}

void SplayTree::splay_node(Node* node)
{
    Node* grandparent = nullptr;

    while ((grandparent = get_grandparent(node)))
    {
        Node* parent = node->parent;
        
        if (is_left_child(node) == is_left_child(parent))
            zigzig(parent, grandparent);
        else
            zigzag(parent, grandparent);
    }

    if (is_left_child (node))
        rotate_right(node->parent);
    if (is_right_child(node))
        rotate_left (node->parent);
}

/*
 *        g            n
 *       / \          / \
 *      p   D        A   p
 *     / \      ->      / \
 *    n   C            B   g
 *   / \                  / \
 *  A   B                C   D
 */
void SplayTree::zigzig(Node* parent, Node* grandparent)
{
    if (is_left_child(parent))
    {
        rotate_right(grandparent);
        rotate_right(parent);
    }
    else
    {
        rotate_left(grandparent);
        rotate_left(parent);
    }
}

/*
 *        g             _n_
 *       / \           /   \
 *      p   D         p     g
 *     / \      ->   / \   / \
 *    A   n         A   B C   D
 *       / \
 *      B   C
 */
void SplayTree::zigzag(Node* parent, Node* grandparent)
{
    if (is_left_child(parent))
    {
        rotate_left (parent);
        rotate_right(grandparent);
    }
    else
    {
        rotate_right(parent);
        rotate_left (grandparent);
    }
}

/*
 *          n                     r
 *         / \                   / \
 *        A   r        ->       n   C
 *           / \               / \
 *          B   C             A   B
 */
SplayTree::Node* SplayTree::rotate_left(Node* node)
{
    Node* right = node->right;                      // r
    node->right = right->left;                      // change parent of B
    if (node->right) node->right->parent = node;

    if (is_left_child(node))                        // report changes to
        node->parent->left = right;                 // parent of node
    if (is_right_child(node))
        node->parent->right = right;
    right->parent = node->parent;

    right->left = node;                             // change parent of n
    node->parent = right;

    return right;                                   // r is new root
}

/*
 *          n                     l
 *         / \                   / \
 *        l   C        ->       A   n
 *       / \                       / \
 *      A   B                     B   C
 */
SplayTree::Node* SplayTree::rotate_right(Node* node)
{
    Node* left = node->left;                        // l
    node->left = left->right;                       // change parent of B
    if (node->left) node->left->parent = node;

    if (is_left_child(node))                        // report changes to
        node->parent->left = left;                  // parent of n
    if (is_right_child(node))
        node->parent->right = left;
    left->parent = node->parent;

    left->right = node;                             // change parent of n
    node->parent = left;

    return left;                                    // l is new root
}

