#include <iostream>
#include <map>
#include <vector>
using namespace std;

struct Node {
  Node *right, *left;
  int key;
};
// Deepest Common BST Ancestor -- Find the deepest node
// that is a common ancestor of keys k1 and k2 if they
// were in a BST. Return NULL if the tree is empty.
Node* deepestCommonAncestor(Node* root, int k1, int k2){
  if(root == NULL){
    return NULL;
  }
  else if(k1 < root->key && k2 < root->key){
    return deepestCommonAncestor(root->left, k1, k2);
  }
  else if(k1 > root->key && k2 > root->key){
    return deepestCommonAncestor(root->right, k1, k2);
  }
  else{
    return root;
  }
}