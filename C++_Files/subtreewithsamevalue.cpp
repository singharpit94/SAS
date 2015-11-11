// C++ program to find count of single valued subtrees
#include<bits/stdc++.h>
using namespace std;
 
// A Tree node
struct Node
{
    int data;
    struct Node* left, *right;
};
 
// Utility function to create a new node
Node* newNode(int data)
{
    Node* temp = new Node;
    temp->data = data;
    temp->left = temp->right = NULL;
    return (temp);
}
 
// This function increments count by number of single 
// valued subtrees under root. It returns true if subtree 
// under root is Singly, else false.
bool countSingleRec(Node* root, int &count)
{
    // Return false to indicate NULL
    if (root == NULL)
       return true;
 
    // Recursively count in left and right subtrees also
    bool left = countSingleRec(root->left, count);
    bool right = countSingleRec(root->right, count);
 
    // If any of the subtrees is not singly, then this
    // cannot be singly.
    if (left == false || right == false)
       return false;
 
    // If left subtree is singly and non-empty, but data
    // doesn't match
    if (root->left && root->data != root->left->data)
        return false;
 
    // Same for right subtree
    if (root->right && root->data != root->right->data)
        return false;
 
    // If none of the above conditions is true, then
    // tree rooted under root is single valued, increment
    // count and return true.
    count++;
    return true;
}
 
// This function mainly calls countSingleRec()
// after initializing count as 0
int countSingle(Node* root)
{
    // Initialize result
    int count = 0;
 
    // Recursive function to count
    countSingleRec(root, count);
 
    return count;
}
 
// Driver program to test
int main()
{
    /* Let us construct the below tree
            5
          /   \
        4      5
      /  \      \
     4    4      5 */
    Node* root        = newNode(5);
    root->left        = newNode(4);
    root->right       = newNode(5);
    root->left->left  = newNode(4);
    root->left->right = newNode(4);
    root->right->right = newNode(5);
 
    cout << "Count of Single Valued Subtrees is "
         << countSingle(root);
    return 0;
}
