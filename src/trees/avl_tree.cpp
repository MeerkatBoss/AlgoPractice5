#include <cstdlib>

#include "avl_tree.h"

void AVLTree::insert(uint32_t key)
{
    root = insert_node(root, key);
}

void AVLTree::erase(uint32_t key)
{
    root = erase_node(root, key);
}

void AVLTree::clear_node(Node* node)
{
    if (!node) return;
    if (node->left)  clear_node(node->left);
    if (node->right) clear_node(node->right);

    free(node);
}

AVLTree::Node* AVLTree::insert_node(Node* node, uint32_t key)
{
    if (!node)
    {
        Node* new_node = (Node*) calloc(1, sizeof(*new_node));

        new_node->key = key;
        new_node->height = 1;
        new_node->left = nullptr;
        new_node->right = nullptr;

        return new_node;
    }

    if (key <= node->key)
        node->left = insert_node(node->left, key);
    else
        node->right = insert_node(node->right, key);

    return balance_node(node);
}

AVLTree::Node* AVLTree::erase_node(Node* node, uint32_t key)
{
    if (!node) return nullptr;

    if (key < node->key)
    {
        node->left = erase_node(node->left, key);
        return balance_node(node);
    }

    if (key > node->key)
    {
        node->right = erase_node(node->right, key);
        return balance_node(node);
    }
    
    if (!node->left)
    {
        Node* tmp = node->right;
        free(node);
        return tmp;
    }

    if (!node->right)
    {
        Node* tmp = node->left;
        free(node);
        return tmp;
    }

    Node* min_node = node->right;
    while (min_node->left)
        min_node = min_node->left;
    
    node->key = min_node->key;
    node->right = detach_min_node(node->right);

    free(min_node);

    return balance_node(node);
}

AVLTree::Node* AVLTree::detach_min_node(Node* node)
{
    if (!node) return nullptr;

    if (!node->left) return node->right;

    node->left = detach_min_node(node->left);

    return balance_node(node);
}

/*
 * (1)          n                       lr
 *             / \                     / \
 *            l   D         ->        l   n
 *           / \                     /\   /\
 *          A   lr                  A  B C  D
 *             /  \
 *            B    C
 *
 * (2)          n                       l
 *             / \                     / \
 *            l   D         ->       ll    n
 *           / \                    / \   / \
 *         ll   C                  A   B C   D
 *        /  \
 *       A    B
 *
 * (3)          n                       rl
 *             / \                     / \
 *            A   r         ->        n   r
 *               / \                 /\   /\
 *             rl   D               A  B C  D
 *            /  \
 *           B    C
 * (4)          n                       r
 *             / \                     / \
 *            A   r         ->       n    rr
 *               / \                / \   / \
 *              B   rr             A   B C   D
 *                 /  \
 *                C    D
 */
AVLTree::Node* AVLTree::balance_node(Node* node)
{
    if (!node) return node;
    
    node->height = get_updated_height(node);
    long balance = get_balance(node);

    if (balance == -2) // (1) or (2)
    {
        if (get_balance(node->left) == 1)      // (1)
            node->left = rotate_left(node->left);
        return rotate_right(node);             // (1) or (2)
    }
    if (balance == 2)  // (3) or (4)
    {
        if (get_balance(node->right) == -1)    // (3)
            node->right = rotate_right(node->right);
        return rotate_left(node);              // (3) or (4)
    }

    return node;
}

/*
 *          n                     r
 *         / \                   / \
 *        A   r        ->       n   C
 *           / \               / \
 *          B   C             A   B
 */
AVLTree::Node* AVLTree::rotate_left(Node* node)
{
    Node* right = node->right;                      // r
    node->right = right->left;                      // change parent of B
    right->left = node;                             // change parent of n

    right->height = get_updated_height(right);
    node->height  = get_updated_height(node);
    return right;                                   // r is new root
}

/*
 *          n                     l
 *         / \                   / \
 *        l   C        ->       A   n
 *       / \                       / \
 *      A   B                     B   C
 */
AVLTree::Node* AVLTree::rotate_right(Node* node)
{
    Node* left = node->left;                        // l
    node->left = left->right;                       // change parent of B
    left->right = node;                             // change parent of n

    left->height = get_updated_height(left);
    node->height = get_updated_height(node);
    return left;                                    // l is new root
}

