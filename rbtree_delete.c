#include "rbtree_insert.c"
#include <stdlib.h>

node lookup_node(rbtree t, void* key, compare_func compare)
{
    node n = t->root;
    while (n != NULL)
    {
        int comp_result = compare(key, n->key);
        if (comp_result == 0)
        {
            return n;
        }
        else if (comp_result < 0)
        {
            n = n->left;
        }
        else
        {
            n = n->right;
        }
    }
    return n;
}

void* rbtree_lookup(rbtree t, void* key, compare_func compare)
{
    node n = lookup_node(t, key, compare);
    return n == NULL ? NULL : n->key;
}

void rbtree_delete(rbtree t, void* key, compare_func compare)
{
    node child;
    node n = lookup_node(t, key, compare);
    if (n == NULL)
        return;
    if (n->left != NULL && n->right != NULL)
    {
        node pred = maximum_node(n->left);
        n->key   = pred->key;
        n = pred;
    }


    child = n->right == NULL ? n->left  : n->right;
    if (node_color(n) == BLACK)
    {
        n->color = node_color(child);
        delete_case1(t, n);
    }
    replace_node(t, n, child);
    if (n->parent == NULL && child != NULL)
        child->color = BLACK;
    free(n);
}

static node maximum_node(node n)
{
    while (n->right != NULL)
    {
        n = n->right;
    }
    return n;
}

void delete_case1(rbtree t, node n)
{
    if (n->parent == NULL)
        return;
    else
        delete_case2(t, n);
}

void delete_case2(rbtree t, node n)
{
    if (node_color(sibling(n)) == RED)
    {
        n->parent->color = RED;
        sibling(n)->color = BLACK;
        if (n == n->parent->left)
            rotate_left(t, n->parent);
        else
            rotate_right(t, n->parent);
    }
    delete_case3(t, n);
}

void delete_case3(rbtree t, node n)
{
    if (node_color(n->parent) == BLACK && node_color(sibling(n)) == BLACK && node_color(sibling(n)->left) == BLACK && node_color(sibling(n)->right) == BLACK)
    {
        sibling(n)->color = RED;
        delete_case1(t, n->parent);
    }
    else
        delete_case4(t, n);
}

void delete_case4(rbtree t, node n)
{
    if (node_color(n->parent) == RED && node_color(sibling(n)) == BLACK && node_color(sibling(n)->left) == BLACK && node_color(sibling(n)->right) == BLACK)
    {
        sibling(n)->color = RED;
        n->parent->color = BLACK;
    }
    else
        delete_case5(t, n);
}

void delete_case5(rbtree t, node n)
{
    if (n == n->parent->left && node_color(sibling(n)) == BLACK && node_color(sibling(n)->left) == RED && node_color(sibling(n)->right) == BLACK)
    {
        sibling(n)->color = RED;
        sibling(n)->left->color = BLACK;
        rotate_right(t, sibling(n));
    }
    else if (n == n->parent->right && node_color(sibling(n)) == BLACK && node_color(sibling(n)->right) == RED && node_color(sibling(n)->left) == BLACK)
    {
        sibling(n)->color = RED;
        sibling(n)->right->color = BLACK;
        rotate_left(t, sibling(n));
    }
    delete_case6(t, n);
}

void delete_case6(rbtree t, node n)
{
    sibling(n)->color = node_color(n->parent);
    n->parent->color = BLACK;
    if (n == n->parent->left)
    {

        sibling(n)->right->color = BLACK;
        rotate_left(t, n->parent);
    }
    else
    {

        sibling(n)->left->color = BLACK;
        rotate_right(t, n->parent);
    }
}
