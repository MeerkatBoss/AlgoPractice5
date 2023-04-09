#include <cstdlib>

#include "skip_list.h"

void SkipList::insert(uint32_t key)
{
    Node* new_node = insert_node(root, key);

    if (new_node)
    {
        Node* new_root = (Node*) calloc(1, sizeof(*new_root));
        new_root->down = root;
        new_root->next = new_node;

        root = new_root;
    }
}

void SkipList::erase(uint32_t key)
{
    erase_node(root, key);
    
    if (!root->next)
    {
        Node* tmp = root->down;
        free(root);
        root = tmp;
    }
}
 
void SkipList::clear(void)
{
    while (root)
    {
        Node* next_row = root->down;

        while (root)
        {
            Node* next = root->next;
            free(root);
            root = next;
        }

        root = next_row;
    }
}

SkipList::Node* SkipList::insert_node(Node* node, uint32_t key)
{
    if (!node)
    {
        Node* new_node = (Node*) calloc(1, sizeof(*new_node));

        new_node->key = key;

        return new_node;
    }

    while (node->next && node->next->key <= key)
        node = node->next;

    Node* new_node = insert_node(node->down, key);

    if (!new_node) return nullptr;
    
    new_node->next = node->next;
    node->next = new_node;

    if (coin(gen)) return nullptr;

    Node* result = (Node*) calloc(1, sizeof(*result));

    result->key  = key;
    result->down = new_node;
    
    return result;
}

void SkipList::erase_node(Node* node, uint32_t key)
{
    if (!node) return;
    
    while (node->next && node->next->key < key)
        node = node->next;

    if (node->next && node->next->key == key)
    {
        Node* deleted = node->next;

        node->next = node->next->next;

        free(deleted);
    }

    erase_node(node->down, key);
}

