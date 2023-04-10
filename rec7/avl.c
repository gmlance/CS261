
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
 * This structure represents a single node in a AVL tree.  In addition to containing
 * pointers to its two child nodes (i.e. `left` and `right`), it contains the `key`
 * field representing the data stored at this node.  The `key` field is an
 * integer value that should be used as an identifier for the data in this
 * node.  Nodes in the AVL should be ordered based on this `key` field.
 * It also contains a `height` field that represents the height of the node

 * You should not modify this structure.
 */

struct avl_node
{
    int key;
    int height;
    struct avl_node *left;
    struct avl_node *right;
    struct avl_node *parent;
};

/*
 * This structure represents an entire AVL tree.  It specifically contains a
 * reference to the root node of the tree.
 *
 * You should not modify this structure.
 */
struct avl_tree
{
    struct avl_node* root;
};


/* 
 * Function Prototypes:
 */
int height(struct avl_node *node);
int max(int a, int b);
int getBalance(struct avl_node *node);
void preOrder(struct avl_node *root);

struct avl_tree* avl_create();
void avl_free(struct avl_tree* avl);
void avl_insert(struct avl_tree* avl, int key);
void avl_remove(struct avl_tree* avl, int key);

struct avl_node* _avl_subtree_leftmost_node(struct avl_node* n);
struct avl_node* _avl_subtree_remove(struct avl_node* n, int key);
struct avl_node* _avl_node_create(int key);

// three function that you will be modified in this recitation
struct avl_node* rightRotate(struct avl_node *y);
struct avl_node* leftRotate(struct avl_node *x);
struct avl_node* _avl_subtree_insert(struct avl_node* node, int key);


/*
 * This function should allocate and initialize a new, empty, AVL tree and return
 * a pointer to it.
 */
struct avl_tree* avl_create() {
    struct avl_tree* avl = malloc(sizeof(struct avl_tree));
    assert(avl);
    avl->root = NULL;
    return avl;
}

/*
 * This function should remove a key/value pair with a specified key from a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should remove the first one it encounters (i.e. the one closest to
 * the root of the tree).
 */
void avl_remove(struct avl_tree* avl, int key) {
    assert(avl);
    avl->root = _avl_subtree_remove(avl->root, key);
}

/*
 * This function should insert a new node with key into the AVL tree. 
 */
void avl_insert(struct avl_tree* avl, int key) {
    assert(avl);
    avl->root = _avl_subtree_insert(avl->root, key);
}

/*
 * This function should free the memory associated with a AVL tree.  While this
 * function should up all memory used in the AVL tree itself, it should not free
 * any memory allocated to the pointer values stored in the AVL tree.  This is the
 * responsibility of the caller.
 *
 */
void avl_free(struct avl_tree* avl) {
    assert(avl);
    while (avl->root != NULL) {
        avl_remove(avl, avl->root->key);
    }

    free(avl);
}


 
/* A helper function to get the height of the tree */
int height(struct avl_node *node){
    if (node == NULL)
        return -1;
    return 1+max(height(node->left), height(node->right));
}
 
// A helper function to get maximum of two integers
int max(int a, int b){
    return (a > b)? a : b;
}


/* Get Balance factor of node N */
int getBalance(struct avl_node *node){
    if (node == NULL)
        return -1;
    return height(node->left) - height(node->right);
}

/* A helper function to print preorder traversal of the tree. */
void preOrder(struct avl_node *root){
    if(root != NULL){
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}


/*
 * Helper function to return the leftmost node within a subtree of a AVL tree.
 */
struct avl_node* _avl_subtree_leftmost_node(struct avl_node* n) {
    while (n->left != NULL) {
        n = n->left;
    }
    return n;
}


/*
 * Helper function to remove a given key from a subtree of a BST rooted at
 * a specified node.
 */
struct avl_node* _avl_subtree_remove(struct avl_node* n, int key) {
    if (n == NULL) 
        return NULL;
     
    else if (key < n->key) {
        n->left = _avl_subtree_remove(n->left, key);
        return n;
    } 

    else if (key > n->key) {
        n->right = _avl_subtree_remove(n->right, key);
        return n;
    }


    if (n->left != NULL && n->right != NULL) {
        struct avl_node* in_order_succ = _avl_subtree_leftmost_node(n->right);
        n->key = in_order_succ->key;
        n->right = _avl_subtree_remove(n->right, in_order_succ->key);
        return n;
    } 

    else if (n->left != NULL) {
        struct avl_node* left_child = n->left;
        free(n);
        return left_child;
    } 
    
    else if (n->right != NULL) {
        struct avl_node* right_child = n->right;
        free(n);
        return right_child;
    } 

    else {
        free(n);
        return NULL;
    }
}


 
/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
struct avl_node* _avl_node_create(int key){
    struct avl_node* node = malloc(sizeof(struct avl_node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->height = 0;  // new node is inserted at leaf, height is 0
    return node;
}


/*****************************************************
 *  You need to modify the following three functions
 *****************************************************/

/* A function to right rotate subtree rooted with N */
struct avl_node *rightRotate(struct avl_node *N)
{
    struct avl_node *x = N->left;
    struct avl_node *T2 = x->right;
 
    // Perform rotation
    x->right = N;
    N->left = T2;
 
    // Update heights
    N->height = height(N);
    x->height = height(x);
 
    // Return new root
    return x;
}

/* A function to left rotate subtree rooted with N */
struct avl_node *leftRotate(struct avl_node *x)
{
    struct avl_node *y = x->right;
    struct avl_node *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    //  Update heights
    x->height = height(x);
    y->height = height(y);
 
    // Return new root
    return y;
}


 
/* Recursive function to insert a key in the subtree rooted
 * with node and returns the new root of the subtree.
 */
struct avl_node* _avl_subtree_insert(struct avl_node* node, int key){
    /* normal BST insertion */
    if (node == NULL) return(_avl_node_create(key));
 
    if(key <= node->key){
        if(node->left == NULL){
            node->left = _avl_node_create(key);
            node->left->parent = node;
        }
        else {
           node->left =  _avl_subtree_insert(node->left, key);
            //return node;
        }
    }
    else {
        if(node->right == NULL){
            node->right = _avl_node_create(key);
            node->right->parent = node;
        } else {
            node->right = _avl_subtree_insert(node->right, key);
            //return node;
        }
    }

    // if (key < node->key)
    //     node->left  = _avl_subtree_insert(node->left, key);
    // else if (key > node->key)
    //     node->right = _avl_subtree_insert(node->right, key);
    // else // Equal keys are not allowed in BST
    //     return node;
 
    /* 2. Update height of this ancestor node */
    node->height = height(node);
 
    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance(node);
 
    // If this node becomes unbalanced, then
    // there are 4 cases
 
    // Left Left Case
    if (balance > 1 && node->left != NULL && key < node->left->key)
        return rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && node->right != NULL && key > node->right->key)
        return leftRotate(node);
 
    // Left Right Case
    if (balance > 1 && node->left != NULL && key > node->left->key)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && node->right != NULL && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    /* return the (unchanged) node pointer */
    return node;
}
 
/* main() to test above function*/
int main(){
  
    /* Test case 1:*/
    struct avl_tree *avl1 = avl_create();

    avl_insert(avl1, 10);
    avl_insert(avl1, 20);
    avl_insert(avl1, 30);
    avl_insert(avl1, 40);
    avl_insert(avl1, 50);
    avl_insert(avl1, 25);


  
    /* The constructed AVL Tree would be
            30
           /  \
         20   40
        /  \     \
       10  25    50
    */

    printf("Test case 1: \n"); 
    printf("Preorder traversal: \n");
    printf("Expected: 30 20 10 25 40 50\n");
    printf("Actual:   ");
    preOrder(avl1->root);
    printf("\n\n");


    /* Test case 2:*/
    struct avl_tree *avl2 = avl_create();

    avl_insert(avl2, 64);
    avl_insert(avl2, 96);
    avl_insert(avl2, 32);
    avl_insert(avl2, 16);
    avl_insert(avl2, 80);
    avl_insert(avl2, 24);
    avl_insert(avl2, 48);
    avl_insert(avl2, 8);
    avl_insert(avl2, 40);
    avl_insert(avl2, 88);
  
    /* The constructed AVL Tree would be
             64
           /    \
         24       88
        /  \     /  \
       16  40   80  96
       /   / \
      8  32  48 
    */
    printf("Test case 2: \n"); 
    printf("Preorder traversal: \n");
    printf("Expected: 64 24 16 8 40 32 48 88 80 96\n");
    printf("Actual:   ");
    preOrder(avl2->root);
    printf("\n\n");


    /* Test case 3:*/
    struct avl_tree *avl3 = avl_create();

    avl_insert(avl3, 8);
    avl_insert(avl3, 16);
    avl_insert(avl3, 24);
    avl_insert(avl3, 32);
    avl_insert(avl3, 40);
    avl_insert(avl3, 48);
    avl_insert(avl3, 64);
    avl_insert(avl3, 80);
    avl_insert(avl3, 88);
    avl_insert(avl3, 96);

    /* The constructed AVL Tree would be
             32
           /    \
         16       80
        /  \     /  \
       8   24   48  88
               /  \   \
              40  64  96 
    */

    printf("Test case 3: \n"); 
    printf("Preorder traversal: \n");
    printf("Expected:32 16 8 24 80 48 40 64 88 96\n");
    printf("Actual:  ");
    preOrder(avl3->root);
    printf("\n\n");


    avl_free(avl1);
    avl_free(avl2);
    avl_free(avl3);

    return 0;
}
