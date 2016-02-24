#include "common.c"
#include <stdlib.h>

/*
	During insertion, we see to it that none of the five rules of Red-Black Trees are violated. The Five Rules are: 
	
	1. Each node is either red or black.

	2. The root node is black.

	3. All leaves are black and contain no data. Since we represent these empty leaves using NULL, this property is implicitly assured by always treating NULL as black.

	4. Every red node has two children, and both are black (or equivalently, the parent of every red node is black).

	5. All paths from any given node to its leaf nodes contain the same number of black nodes.
Properties 4 and 5 together guarantee that no path in the tree is more than about twice as long as any other path, which guarantees that it has O(log n) height.
*/

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


void rbtree_insert(rbtree t, void* key) /* Insertion as is done in a Normal Binary Search Tree. */ 
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

void insert_case1(rbtree t, node n) /* Make the root BLACK */
{
    if (n->parent == NULL)
        n->color = BLACK;
    else
        insert_case2(t, n);
}

void insert_case2(rbtree t, node n) /* If parent color is RED, move to insert_case3 */
{
    if (node_color(n->parent) == BLACK)
        return;
    else
        insert_case3(t, n);
}

void insert_case3(rbtree t, node n) /* If uncle is RED as well, both parent and uncle are made BLACK along with making the granparent RED. insert_case1 is followed on the granparent node */
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
        insert_case4(t, n); /* If parent is RED and uncle is BLACK, go to insert_case4 */
    }
}

/* Rotation cases are shown below */ 

void insert_case4(rbtree t, node n) {
    if (n == n->parent->right && n->parent == grandparent(n)->left)	//    x                x
    {									//   /                /
        rotate_left(t, n->parent);					//  y	rotated to   z
        n = n->left;							//   \              /
    }									//    z            y
    else if (n == n->parent->left && n->parent == grandparent(n)->right)//  x              x
    {									//   \              \
        rotate_right(t, n->parent);					//    y rotated to   z
        n = n->right;							//   /                \
    }									//  z                  y
    insert_case5(t, n);
}

void insert_case5(rbtree t, node n) {                      		//     x
    n->parent->color = BLACK;						//    /               z
    grandparent(n)->color = RED;					//   z   rotated to  / \
    if (n == n->parent->left && n->parent == grandparent(n)->left)	//  /               y   x
    {									// y
        rotate_right(t, grandparent(n));				
    }									// x
    else								//  \                 z
    {									//   z   rotated to  / \
        rotate_left(t, grandparent(n));					//    \             x   y
    }									//     y 
}									
