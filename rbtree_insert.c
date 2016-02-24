#include "common.c"
#include <stdlib.h>

/**
 * \n During insertion, we see to it that none of the five rules of Red-Black Trees are violated. 
 * \n The Five Rules are: 
 * \n 1. Each node is either red or black.
 * \n 2. The root node is black.
 * \n 3. All leaves are black and contain no data. Since we represent these empty leaves using NULL, this property is implicitly assured by always treating NULL as black.
 * \n 4. Every red node has two children, and both are black (or equivalently, the parent of every red node is black).
 * \n 5. All paths from any given node to its leaf nodes contain the same number of black nodes.
Properties 4 and 5 together guarantee that no path in the tree is more than about twice as long as any other path, which guarantees that it has O(log n) height.
 * \n
 * \n @brief Function to initialize and create the tree	
*/
rbtree rbtree_create()
{
    rbtree t = malloc(sizeof(struct rbtree_t));
    t->root = NULL;
    return t;
}

/**
 * \n @brief Function to create a node within the Red-Black Tree
 * \n The key value is provided along with its color, left and right child
 * \n @param key stores the value in the node (Datatype void is used so that in can be typecast with any other datatype)
 * \n @node_color maintains the color of the node
 * \n @left points to the left child of the inserted node
 * \n @right points to the right child of the inserted node
*/
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

/**
 * \n @brief Insertion is done following the rules of a Normal Binary Search Tree
 */
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

/**
 * \n @brief This function makes the root node black (Property 1)
*/
void insert_case1(rbtree t, node n)
{
    if (n->parent == NULL)
        n->color = BLACK;
    else
        insert_case2(t, n);
}

/**
 * \n @brief This function checks if the parent node is RED. If so, moves into @see insert_case3
*/
void insert_case2(rbtree t, node n)
{
    if (node_color(n->parent) == BLACK)
        return;
    else
        insert_case3(t, n);
}

/*
 * \n @brief This function changes the parent and uncle to BLACK, along with grandparent to RED if the uncle is initially RED. This is followed by @see insert_case1 on the grandparent node
 * \n @brief If parent is RED and uncle is BLACK, the function moves to @see insert_case4 
*/
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

/**
 * \n @brief Rotation cases are LR and RL are dealt with @see insert_case4
 * \n
 * \n @see rotate_left does the following (For LR):
 * \n
 * \n    x                x
 * \n   /                /
 * \n  y   rotated to   z
 * \n   \              /
 * \n    z            y
 * \n
 * \n @see rotate_right does the following (For RL):
 * \n
 * \n  x              x
 * \n   \              \
 * \n    y rotated to   z
 * \n   /                \
 * \n  z                  y
*/ 
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

/**
 * \n @brief Rotation cases are LL and RR are dealt with @see insert_case4
 * \n
 * \n @see rotate_left does the following (For LL):
 * \n
 * \n      x
 * \n     /               z
 * \n    z   rotated to  / \
 * \n   /               y   x
 * \n  y
 * \n
 * \n @see rotate_right does the following (For RR):
 * \n
 * \n  x
 * \n   \                 z
 * \n    z   rotated to  / \
 * \n    \             x   y
 * \n     y
*/ 

void insert_case5(rbtree t, node n)
{
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
