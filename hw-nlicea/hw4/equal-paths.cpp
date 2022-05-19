#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int height(Node* n, bool &balanced){
    if (n == nullptr || !balanced) {
        return 0;
    }
 
    int lHeight = height(n->left, balanced);  // height of the left subtree
    int rHeight = height(n->right, balanced);  // height of the right subtree
 
    if (std::abs(lHeight - rHeight) > 1) {
        balanced = false;
    }
    if(lHeight > rHeight){
        return lHeight + 1;
    }
    return rHeight + 1;
}

bool equalPaths(Node * root){
    // Add your code below
    bool balancedL = true;
    bool balancedR = true;

    if(root == NULL){
        return true;
    }

    int lHeight = height(root->left, balancedL);
    int rHeight = height(root->right, balancedR);

    if(!((lHeight == 0 and rHeight == 1) or (lHeight == 1 and rHeight == 0)) and std::abs(lHeight - rHeight) >= 1){
        return false;
    }
    return true;
}


