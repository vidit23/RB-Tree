#include "common.c"
#include <stdlib.h>

rbtree rbtree_create()
{
    rbtree t = malloc(sizeof(struct rbtree_t));
    t->root = NULL;
    return t;
}

node new_node(void* key , color node_color, node left, node right)
{
    node result = malloc(sizeof(struct rbtree_node_t));
    result->key = key;
    result->color = node_color;
    result->left = left;
    result->right = right;
    if (left  != NULL)
        left->parent = result;
    if (right != NULL)
        right->parent = result;
    result->parent = NULL;
    return result;
}


void rbtree_insert(rbtree t, void* key)
{
    node inserted_node = new_node(key, RED, NULL, NULL);
    if (t->root == NULL)
    {
        t->root = inserted_node;
    }
    else
    {
        node n = t->root;
        while (1)
        {
            int comp_result = compare(key, n->key);
            if (comp_result == 0)
            {
                free (inserted_node);
                return;
            }
            else if (comp_result < 0)
            {
                if (n->left == NULL)
                {
                    n->left = inserted_node;
                    break;
                }
                else
                {
                    n = n->left;
                }
            }
            else
            {

                if (n->right == NULL)
                {
                    n->right = inserted_node;
                    break;
                }
                else
                {
                    n = n->right;
                }
            }
        }
        inserted_node->parent = n;
    }
    insert_case1(t, inserted_node);
}

void insert_case1(rbtree t, node n)
{
    if (n->parent == NULL)
        n->color = BLACK;
    else
        insert_case2(t, n);
}

void insert_case2(rbtree t, node n)
{
    if (node_color(n->parent) == BLACK)
        return;
    else
        insert_case3(t, n);
}

void insert_case3(rbtree t, node n)
{
    if (node_color(uncle(n)) == RED)
    {
        n->parent->color = BLACK;
        uncle(n)->color = BLACK;
        grandparent(n)->color = RED;
        insert_case1(t, grandparent(n));
    }
    else
    {
        insert_case4(t, n);
    }
}

void insert_case4(rbtree t, node n) {
    if (n == n->parent->right && n->parent == grandparent(n)->left)
    {
        rotate_left(t, n->parent);
        n = n->left;
    }
    else if (n == n->parent->left && n->parent == grandparent(n)->right)
    {
        rotate_right(t, n->parent);
        n = n->right;
    }
    insert_case5(t, n);
}

void insert_case5(rbtree t, node n) {
    n->parent->color = BLACK;
    grandparent(n)->color = RED;
    if (n == n->parent->left && n->parent == grandparent(n)->left)
    {
        rotate_right(t, grandparent(n));
    }
    else
    {

        rotate_left(t, grandparent(n));
    }
}
