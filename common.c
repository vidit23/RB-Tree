#include "rbtree.h"
#include <stdlib.h>

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

node grandparent(node n)
{
    return n->parent->parent;
}

node sibling(node n)
{
    if (n == n->parent->left)
        return n->parent->right;
    else
        return n->parent->left;
}

node uncle(node n)
{
    return sibling(n->parent);
}

color node_color(node n)
{
    return n == NULL ? BLACK : n->color;
}

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
