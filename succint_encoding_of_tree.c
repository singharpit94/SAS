// C++ program to demonstrate Succinct Tree Encoding and decoding
#include<bits/stdc++.h>
using namespace std;
 
// A Binary Tree Node
struct Node
{
    int key;
    struct Node* left, *right;
};
 
// Utility function to create new Node
Node *newNode(int key)
{
    Node *temp = new Node;
    temp->key  = key;
    temp->left  = temp->right = NULL;
    return (temp);
}
 
// This function fills lists 'struc' and 'data'.  'struc' list
// stores structure information. 'data' list stores tree data
void EncodeSuccinct(Node *root, list<bool> &struc, list<int> &data)
{
    // If root is NULL, put 0 in structure array and return
    if (root == NULL)
    {
        struc.push_back(0);
        return;
    }
 
    // Else place 1 in structure array, key in 'data' array
    // and recur for left and right children
    struc.push_back(1);
    data.push_back(root->key);
    EncodeSuccinct(root->left, struc, data);
    EncodeSuccinct(root->right, struc, data);
}
 
// Constructs tree from 'struc' and 'data'
Node *DecodeSuccinct(list<bool> &struc, list<int> &data)
{
    if (struc.size() <= 0)
        return NULL;
 
    // Remove one item from from structure list
    bool b = struc.front();
    struc.pop_front();
 
    // If removed bit is 1,
    if (b == 1)
    {
         // remove an item from data list
        int key = data.front();
        data.pop_front();
 
        // Create a tree node with the removed data
        Node *root = newNode(key);
 
        // And recur to create left and right subtrees
        root->left = DecodeSuccinct(struc, data);
        root->right = DecodeSuccinct(struc, data);
        return root;
    }
 
    return NULL;
}
 
// A utility function to print tree
void preorder(Node* root)
{
    if (root)
    {
        cout << "key: "<< root->key;
        if (root->left)
            cout << " | left child: " << root->left->key;
        if (root->right)
            cout << " | right child: " << root->right->key;
        cout << endl;
        preorder(root->left);
        preorder(root->right);
    }
}
 
// Driver program
int main()
{
    // Let us construct the Tree shown in the above figure
    Node *root         = newNode(10);
    root->left         = newNode(20);
    root->right        = newNode(30);
    root->left->left   = newNode(40);
    root->left->right  = newNode(50);
    root->right->right = newNode(70);
 
    cout << "Given Tree\n";
    preorder(root);
    list<bool> struc;
    list<int>  data;
    EncodeSuccinct(root, struc, data);
 
    cout << "\nEncoded Tree\n";
    cout << "Structure List\n";
    list<bool>::iterator si; // Structure iterator
    for (si = struc.begin(); si != struc.end(); ++si)
        cout << *si << " ";
 
    cout << "\nData List\n";
    list<int>::iterator di; // Data iIterator
    for (di = data.begin(); di != data.end(); ++di)
        cout << *di << " ";
 
    Node *newroot = DecodeSuccinct(struc, data);
 
    cout << "\n\nPreorder traversal of decoded tree\n";
    preorder(newroot);
 
    return 0;
}
