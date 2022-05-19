#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    char getBalance () const;
    void setBalance (char balance);
    void updateBalance(char diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    char balance_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
char AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(char balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(char diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    AVLNode<Key, Value>* traverse(AVLNode<Key, Value>* n, const Key& key) const;


};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    AVLNode<Key, Value>* p = NULL;
    AVLNode<Key, Value>* n = static_cast<AVLNode<Key, Value>*> (this->root_);  // temp node
    AVLNode<Key, Value>* temp = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);

    if (n == NULL){  // empty tree
        n = temp;  // idk
        char zero = 0;
        n->setBalance(zero);
    } 
    // else{
    //     bool equal = false;
    //     bool left = false;
    //     bool right = false;
    //     while(n != NULL){
    //         left = false;
    //         right = false;
    //         if(n->getKey > new_item.first){  // go left
    //             p = n;
    //             n = n->getLeft();
    //             left = true;
    //         }
    //         else if (n->getKey() < new_item.first){  // go right
    //             p = n;
    //             n = n->getRight();
    //             right = true;
    //         } 
    //         else{  // overwrite value
    //             n->setValue(new_item.second);
    //             equal = true;
    //             break;
    //         }
    //     }
    //     if(!equal){
    //         n = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, p);
    //         if(left){
    //             p->setLeft(n);
    //         }
    //         if(right){
    //             p->setRight(n);
    //         }
    //     }
    // }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    // traverse
//     AVLNode<Key, Value>* loc = traverse(key);

//     if(loc == NULL){
//         loc = nullptr;
//         delete loc;
//     }
//     else if(loc.getLeft() == NULL and loc->getRight() == NULL){  // leaf node
//         if(loc->getParent() != NULL){
//             AVLNode<Key, Value>* p = loc->getParent();
//             if(p->getLeft() != NULL){  // update parent of loc
//                 p->setLeft(NULL);
//             }
//             else{ 
//                 p->setRight(NULL);
//             }
//         } 
//         else if(loc == this->root_){
//             this->root_ = NULL;
//         }
//         loc = nullptr;  // delete node
//         delete loc;
//     }
//     else if (loc->getLeft() != NULL and loc->getRight() == NULL){  // one left child
//         nodeSwap(loc, loc->getLeft());  // promote child
//         if(loc->getLeft() != NULL){  // promote left Child
//             AVLNode<Key, Value>* lChild = loc->getLeft();
//             nodeSwap(loc, lChild);
//             lChild->setLeft(NULL);
//         }
//         else if(loc->getRight() != NULL){  // promote right Child
//             AVLNode<Key, Value>* rChild = loc->getRight();
//             nodeSwap(loc, rChild);
//             rChild->setRight(NULL); 
//         }
//         loc = nullptr;   // delete node
//         delete loc;
//     }
//     else if (loc->getLeft() == NULL and loc->getRight() != nullptr){  // one right child
//         nodeSwap(loc, loc->getRight());  // swap
//         if(loc->getLeft() != NULL){  // promote left Child
//             AVLNode<Key, Value>* lChild = loc->getLeft();
//             nodeSwap(loc, lChild);
//             lChild->setLeft(NULL);
//         }
//         else if(loc->getRight() != NULL){  // promote right Child
//             AVLNode<Key, Value>* rChild = loc->getRight();
//             nodeSwap(loc, rChild);
//             rChild->setRight(NULL);
//         }
//         loc = nullptr;   // delete node
//         delete loc;
//     }
//     else{  // two children
//         AVLNode<Key, Value>* pred = predecessor(loc);  // find in-order pred
//         nodeSwap(loc, pred);  // swap
//         if(loc->getParent() != NULL){
//             AVLNode<Key, Value>* p = loc->getParent();
//             if(p->getLeft() == loc){  // update parent of loc
//                 p->setLeft(NULL);
//             }
//             else{ 
//                 p->setRight(NULL);
//             }
//         }
//         delete loc;
//     }
// }

// // remove helper function (not provided)
// template<class Key, class Value>
// AVLNode<Key, Value>*
// AVLTree<Key, Value>::traverse(AVLNode<Key, Value>* n, const Key& key) const{
//     if(n == NULL){
//         return nullptr;
//     }
//     else if (n->getKey() > key){  // go left
//         n = n->getLeft();
//         return traverse(n, key); // recurse - idk
//     }
//     else if (n->getKey() < key){  // go right
//         n = n->getRight();
//         return traverse(n, key); // recurse
//     } 
//     else{
//         return n;
//     }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    char tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
