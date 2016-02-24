#include "rbtree.h"
#include <stdlib.h>

/**
 * @brief This function compares two number.
 * It returns -1(first<second), 0(both equal), 1(second<first)
 * @param leftp the first argument.
 * @param rightp the second argument.
 */
int compare(void* leftp, void* rightp)
{
    int left = (int)leftp;
    int right = (int)rightp;
    if(left < right)
        return -1;
    else if (left > right)
        return 1;
    else
        return 0;
}

/**
 * @brief Returns the granparent of the node.
 * Parent's parent
 * @param n is the argument.
 */
node grandparent(node n)
{
    return n->parent->parent;
}

/**
 * @brief Returns the sibling.
 * Parent's other child
 * @param n is the argument.
 */
node sibling(node n)
{
 	   if (n == n->parent->left)
        return n->parent->right;
    else
        return n->parent->left;
}

/**
 * @brief Returns the parents sibling.
 * Parent's parent's other child
 * @param n is the argument.
 */
node uncle(node n)
{
    return sibling(n->parent);
}

/**
 * @brief Returns the node's color or if the node is NULL then black.
 * @param n is the argument.
 */
color node_color(node n)
{
    return n == NULL ? BLACK : n->color;
}

/**
 * @brief Perform standard L rotation.
 * \n      y                              x
 * \n     / \                            / \
 * \n    x  T3                          T1  y
 * \n   / \       < - - - - - - -          / \
 * \n  T1  T2     Left Rotation           T2  T3
 * @param t is the tree root
 * @param n is the node to rotate across.
 */
void rotate_left(rbtree t, node n)
{
    node r = n->right;
    replace_node(t, n, r);
    n->right = r->left;
    if (r->left != NULL)
    {
        r->left->parent = n;
    }
    r->left = n;
    n->parent = r;
}

/**
 * @brief Perform standard R rotation.
 * \n    y                               x
 * \n   / \     Right Rotation          / \
 * \n  x   T3   – – – – – – – >        T1  y
 * \n / \                                / \
 * \nT1  T2                            T2  T3
 * @param t is the tree root
 * @param n is the node to rotate across.
 */
void rotate_right(rbtree t, node n)
{

    node l = n->left;
    replace_node(t, n, l);
    n->left = l->right;
    if (l->right != NULL)
    {
        l->right->parent = n;
    }
    l->right = n;
    n->parent = l;
}

/**
 * @brief Replace a node with another.
 * @param t is the tree root
 * @param oldn is the node to be replaced.
 * @param newn is the node which takes it place.
 */
void replace_node(rbtree t, node oldn, node newn)
{

    if (oldn->parent == NULL)
    {
        t->root = newn;
    }
    else
    {
        if (oldn == oldn->parent->left)
            oldn->parent->left = newn;
        else
            oldn->parent->right = newn;
    }
    if (newn != NULL)
    {
        newn->parent = oldn->parent;
    }
}
