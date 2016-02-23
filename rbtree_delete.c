#include "rbtree_insert.c"
#include <stdlib.h>

/*
 Perform standard BST delete. When we perform standard delete operation in BST, we always end up deleting a node which is either leaf or has only one child (For an internal node, we copy the successor and then recursively call delete for successor, successor is always a leaf node or a node with one child). So we only need to handle cases where a node is leaf or has one child. Let v be the node to be deleted and u be the child that replaces v (Note that u is NULL when v is a leaf and color of NULL is considered as Black).
 
 2) Simple Case: If either u or v is red, we mark the replaced child as black (No change in black height). Note that both u and v cannot be red as v is parent of u and two consecutive reds are not allowed in red-black tree.
 
 3) If Both u and v are Black.
 3.1) Color u as double black.  Now our task reduces to convert this double black to single black. Note that If v is leaf, then u is NULL and color of NULL is considered as black. So the deletion of a black leaf also causes a double black.
 
 3.2) Do following while the current node u is double black or it is not root. Let sibling of node be s.
 ….(a): If sibling s is black and at least one of sibling’s children is red, perform rotation(s). Let the red child of s be r. This case can be divided in four subcases depending upon positions of s and r.
 …………..(i) Left Left Case (s is left child of its parent and r is left child of s or both children of s are red). This is mirror of right right case shown in below diagram.
 …………..(ii) Left Right Case (s is left child of its parent and r is right child). This is mirror of right left case shown in below diagram.
 …………..(iii) Right Right Case (s is right child of its parent and r is right child of s or both children of s are red)
 
 …………..(iv) Right Left Case (s is right child of its parent and r is left child of s)
 
 …..(b): If sibling is black and its both children are black, perform recoloring, and recur for the parent if parent is black.
 
 
 In this case, if parent was red, then we didn’t need to recur for prent, we can simply make it black (red + double black = single black)
 …..(c): If sibling is red, perform a rotation to move old sibling up, recolor the old sibling and parent. The new sibling is always black (See the below diagram). This mainly converts the tree to black sibling case (by rotation) and  leads to case (a) or (b). This case can be divided in two subcases.
 …………..(i) Left Case (s is left child of its parent). This is mirror of right right case shown in below diagram. We right rotate the parent p.
 …………..(iii) Right Case (s is right child of its parent). We left rotate the parent p.
 
 3.3) If u is root, make it single black and return (Black height of complete tree reduces by 1).
 
 */

node lookup_node(rbtree t, void* key)
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

void* rbtree_lookup(rbtree t, void* key)
{
    node n = lookup_node(t, key);
    return n == NULL ? NULL : n->key;
}

void rbtree_delete(rbtree t, void* key)
{
    node child;
    node n = lookup_node(t, key);
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
