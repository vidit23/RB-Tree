#include "rbtree.h"
#include <stdlib.h>

int compare(void* leftp, void* rightp)  // This function compares two number and returns -1, 0, 1
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

node grandparent(node n)    // Returns the granparent of the node
{
    return n->parent->parent;
}

node sibling(node n)    // Returns the parent's other child
{
 	   if (n == n->parent->left)
        return n->parent->right;
    else
        return n->parent->left;
}

node uncle(node n)      // Returns the parents sibling
{
    return sibling(n->parent);
}

color node_color(node n)    // Returns the node's color or if the node is NULL then black
{
    return n == NULL ? BLACK : n->color;
}

void rotate_left(rbtree t, node n)
{
    /*
      y                              x
     / \                            / \
    x  T3                          T1  y
   / \       < - - - - - - -          / \
  T1  T2     Left Rotation           T2  T3
    */
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

void rotate_right(rbtree t, node n)
{
    /*
        y                               x
       / \     Right Rotation          / \
      x   T3   – – – – – – – >        T1  y
     / \                                 / \
    T1  T2                              T2  T3
    */
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

void replace_node(rbtree t, node oldn, node newn)   // Replace the node oldn with newn at its position
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
