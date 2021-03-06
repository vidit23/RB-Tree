enum rbtree_node_color { RED, BLACK };
/**
* @brief Definition of each node in the tree
*/
typedef struct rbtree_node_t {
    void* key;                          /*!< Stores the value */
    struct rbtree_node_t* left;         /*!< Pointer to left child */
    struct rbtree_node_t* right;        /*!< Pointer to right child */
    struct rbtree_node_t* parent;       /*!< Pointer to nodes parent */
    enum rbtree_node_color color;       /*!< Stores the color of the node */
} *rbtree_node;

/**
* @brief The pointer to the root of the tree
*/
typedef struct rbtree_t {
    rbtree_node root;                   /*!< Root of the Red-Black Tree */
} *rbtree;

rbtree rbtree_create();
void* rbtree_lookup(rbtree t, void* key);
void rbtree_insert(rbtree t, void* key);
void rbtree_delete(rbtree t, void* key);
typedef rbtree_node node;
typedef enum rbtree_node_color color;


static node grandparent(node n);
static node sibling(node n);
static node uncle(node n);
static void verify_properties(rbtree t);
static color node_color(node n);


static node new_node(void* key, color node_color, node left, node right);
static node lookup_node(rbtree t, void* key);
static void rotate_left(rbtree t, node n);
static void rotate_right(rbtree t, node n);

//the cases for insertion and deletion (the conditions tobe checked)

static void replace_node(rbtree t, node oldn, node newn);
static void insert_case1(rbtree t, node n);
static void insert_case2(rbtree t, node n);
static void insert_case3(rbtree t, node n);
static void insert_case4(rbtree t, node n);
static void insert_case5(rbtree t, node n);
static node maximum_node(node root);
static void delete_case1(rbtree t, node n);
static void delete_case2(rbtree t, node n);
static void delete_case3(rbtree t, node n);
static void delete_case4(rbtree t, node n);
static void delete_case5(rbtree t, node n);
static void delete_case6(rbtree t, node n);
