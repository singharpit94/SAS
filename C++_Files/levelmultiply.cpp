/* Iterative C++ program to find sum of data of all leaves
   of a binary tree on same level and then multiply sums
   obtained of all levels. */
#include <bits/stdc++.h>
using namespace std;
 
// A Binary Tree Node
struct Node
{
    int data;
    struct Node *left, *right;
};
 
// helper function to check if a Node is leaf of tree
bool isLeaf(Node *root)
{
    return (!root->left && !root->right);
}
 
/* Calculate sum of all leaf Nodes at each level and returns
   multiplication of sums */
int sumAndMultiplyLevelData(Node *root)
{
    // Tree is empty
    if (!root)
        return 0;
 
    int mul = 1;    /* To store result */
 
    // Create an empty queue for level order tarversal
    queue<Node *> q;
 
    // Enqueue Root and initialize height
    q.push(root);
 
    // Do level order traversal of tree
    while (1)
    {
        // NodeCount (queue size) indicates number of Nodes
        // at current lelvel.
        int NodeCount = q.size();
 
        // If there are no Nodes at current level, we are done
        if (NodeCount == 0)
            break;
 
        // Initialize leaf sum for current level
        int levelSum = 0;
 
        // A boolean variable to indicate if found a leaf
        // Node at current level or not
        bool leafFound = false;
 
        // Dequeue all Nodes of current level and Enqueue all
        // Nodes of next level
        while (NodeCount > 0)
        {
            // Process next Node  of current level
            Node *Node = q.front();
 
            /* if Node is a leaf, update sum at the level */
            if (isLeaf(Node))
            {
                 leafFound = true;
                 levelSum += Node->data;
            }
            q.pop();
 
            // Add children of Node
            if (Node->left != NULL)
                q.push(Node->left);
            if (Node->right != NULL)
                q.push(Node->right);
            NodeCount--;
        }
 
        // If we found at least one leaf, we multiply
        // result with level sum.
        if (leafFound)
           mul *= levelSum;
    }
 
    return mul;  // Return result
}
 
// Utility function to create a new tree Node
Node* newNode(int data)
{
    Node *temp = new Node;
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}
 
// Driver program to test above functions
int main()
{
    Node *root = newNode(2);
    root->left = newNode(7);
    root->right = newNode(5);
    root->left->right = newNode(6);
    root->left->left = newNode(8);
    root->left->right->left = newNode(1);
    root->left->right->right = newNode(11);
    root->right->right = newNode(9);
    root->right->right->left = newNode(4);
    root->right->right->right = newNode(10);
 
    cout << "Final product value = "
         << sumAndMultiplyLevelData(root) << endl;
 
    return 0;
}
