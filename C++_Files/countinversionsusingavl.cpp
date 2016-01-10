// An AVL Tree based C++ program to count inversion in an array
#include<bits/stdc++.h>
using namespace std;

// An AVL tree node
struct Node
{
    int key, height;
    struct Node *left, *right;
    int size; // size of the tree rooted with this Node
};

// A utility function to get height of the tree rooted with N
int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

// A utility function to size of the tree of rooted with N
int size(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->size;
}

/* Helper function that allocates a new Node with the given key and
    NULL left and right pointers. */
struct Node* newNode(int key)
{
    struct Node* node = new Node;
    node->key   = key;
    node->left   = node->right  = NULL;
    node->height = node->size = 1;
    return(node);
}

// A utility function to right rotate subtree rooted with y
struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    // Update sizes
    y->size = size(y->left) + size(y->right) + 1;
    x->size = size(x->left) + size(x->right) + 1;

    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    // Update sizes
    x->size = size(x->left) + size(x->right) + 1;
    y->size = size(y->left) + size(y->right) + 1;

    // Return new root
    return y;
}

// Get Balance factor of Node N
int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Inserts a new key to the tree rotted with Node. Also, updates
// *result (inversion count)
struct Node* insert(struct Node* node, int key, int *result)
{
    /* 1.  Perform the normal BST rotation */
    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
    {
        node->left  = insert(node->left, key, result);

        // UPDATE COUNT OF GREATE ELEMENTS FOR KEY
        *result = *result + size(node->right) + 1;
    }
    else
        node->right = insert(node->right, key, result);

    /* 2. Update height and size of this ancestor node */
    node->height = max(height(node->left),
                       height(node->right)) + 1;
    node->size = size(node->left) + size(node->right) + 1;

    /* 3. Get the balance factor of this ancestor node to
          check whether this node became unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are
    // 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

// The following function returns inversion count in arr[]
int getInvCount(int arr[], int n)
{
  struct Node *root = NULL;  // Create empty AVL Tree

  int result = 0;   // Initialize result

  // Starting from first element, insert all elements one by
  // one in an AVL tree.
  for (int i=0; i<n; i++)

     // Note that address of result is passed as insert
     // operation updates result by adding count of elements
     // greater than arr[i] on left of arr[i]
     root = insert(root, arr[i], &result);

  return result;
}

// Driver program to test above
int main()
{
    int arr[] = {8, 4, 2, 1};
    int n = sizeof(arr)/sizeof(int);
    cout << "Number of inversions count are : "
         << getInvCount(arr,n);
    return 0;
}
