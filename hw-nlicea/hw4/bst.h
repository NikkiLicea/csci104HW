#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node(){
    
}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    static Node<Key, Value>* successor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    // void insertKey(Node<Key, Value>* n, bool left, const std::pair<const Key, Value> &keyValuePair);
    Node<Key, Value>* traverse(Node<Key, Value>* n, const Key& key) const;
    void clear_recurse(Node<Key, Value>* current);
    int height(Node<Key,Value>* n, bool &balanced) const;

protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr) : current_(ptr){
    // TODO - DONE
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() : current_(NULL){
    // TODO - DONE
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const{
    // TODO - DONE
    return current_ == rhs.current_;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const{
    // TODO - DONE
    return current_ != rhs.current_;
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++(){
    // TODO - DONE
    *this = successor(current_);
    return *this;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() {
    // TODO - DONE
    this->root_ = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree(){
    // TODO - DONE
    clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair){
    // TODO - DONE
    Node<Key, Value>* p = NULL;
    Node<Key, Value>* n = this->root_;  // temp node
    Node<Key, Value>* temp = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr);

    if (empty()){  // empty tree
        this->root_ = temp;  // idk
    } 
    else{
        bool equal = false;
        bool left = false;
        bool right = false;
        while(n != NULL){
            left = false;
            right = false;
            if(n->getKey() > keyValuePair.first){  // go left
                p = n;
                n = n->getLeft();
                left = true;
            }
            else if (n->getKey() < keyValuePair.first){  // go right
                p = n;
                n = n->getRight();
                right = true;
            } 
            else{  // overwrite value
                n->setValue(keyValuePair.second);
                equal = true;
                break;
            }
        }
        if(!equal){
            n = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, p);
            if(left){
                p->setLeft(n);
            }
            if(right){
                p->setRight(n);
            }
        }
    }
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key){
    // TODO - DONE - May need to delete loc in else statement?

    // traverse
    Node<Key, Value>* loc = internalFind(key);

    if(loc == NULL){
        loc = nullptr;
        delete loc;
    }
    else if(loc->getLeft() == NULL and loc->getRight() == NULL){  // leaf node
        if(loc->getParent() != NULL){
            Node<Key, Value>* p = loc->getParent();
            if(p->getLeft() != NULL){  // update parent of loc
                p->setLeft(NULL);
            }
            else{ 
                p->setRight(NULL);
            }
        } 
        else if(loc == this->root_){
            this->root_ = NULL;
        }
        loc = nullptr;  // delete node
        delete loc;
    }
    else if (loc->getLeft() != NULL and loc->getRight() == NULL){  // one left child
        nodeSwap(loc, loc->getLeft());  // promote child
        if(loc->getLeft() != NULL){  // promote left Child
            Node<Key, Value>* lChild = loc->getLeft();
            nodeSwap(loc, lChild);
            lChild->setLeft(NULL);
        }
        else if(loc->getRight() != NULL){  // promote right Child
            Node<Key, Value>* rChild = loc->getRight();
            nodeSwap(loc, rChild);
            rChild->setRight(NULL); 
        }
        loc = nullptr;   // delete node
        delete loc;
    }
    else if (loc->getLeft() == NULL and loc->getRight() != nullptr){  // one right child
        nodeSwap(loc, loc->getRight());  // swap
        if(loc->getLeft() != NULL){  // promote left Child
            Node<Key, Value>* lChild = loc->getLeft();
            nodeSwap(loc, lChild);
            lChild->setLeft(NULL);
        }
        else if(loc->getRight() != NULL){  // promote right Child
            Node<Key, Value>* rChild = loc->getRight();
            nodeSwap(loc, rChild);
            rChild->setRight(NULL);
        }
        loc = nullptr;   // delete node
        delete loc;
    }
    else{  // two children
        Node<Key, Value>* pred = predecessor(loc);  // find in-order pred
        nodeSwap(loc, pred);  // swap
        // if(pred->getLeft() != nullptr){  // promote left child
        //     nodeSwap(pred, pred->getLeft());
        // }
        // if(pred->getRight() != nullptr){  // promote right child
        //     nodeSwap(pred, pred->getRight());
        // }
        // pred = nullptr;  // delete node
        // delete pred;
        if(loc->getParent() != NULL){
            Node<Key, Value>* p = loc->getParent();
            if(p->getLeft() == loc){  // update parent of loc
                p->setLeft(NULL);
            }
            else{ 
                p->setRight(NULL);
            }
        }
        delete loc;
    }
}

// remove helper function (not provided)
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::traverse(Node<Key, Value>* n, const Key& key) const{
    if(n == NULL){
        return nullptr;
    }
    else if (n->getKey() > key){  // go left
        n = n->getLeft();
        return traverse(n, key); // recurse - idk
    }
    else if (n->getKey() < key){  // go right
        n = n->getRight();
        return traverse(n, key); // recurse
    } 
    else{
        return n;
    }
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current){
    // TODO - DONE
    if(current->getLeft() != nullptr){  // left ptr exists
        current = current->getLeft();
        while(current->getRight() != nullptr){
            current = current->getRight();
        }
        return current;
    }
    else{  // walk up ancestor chain until you hit root (then no pred)
        // first iteration
        Node<Key, Value>* p = current->getParent();  // parent
        Node<Key, Value>* g = p->getParent();  // grandparent
        if(g->getRight() == p){  // parent is the right child of grandparent
            return g;
        }

        // while(g != this->root_ and g != nullptr){  // idk - confused
        while(g != nullptr){
            Node<Key, Value>* p = g;
            Node<Key, Value>* g = g->getParent();
            if(g->getRight() == p){
                return g;
            }
        }
        return nullptr;  // no predecessor
    }
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current){
    // TODO - DONE
    if(current->getRight() != NULL){  // right ptr exists
        current = current->getRight();  // go to right subtree
        while(current->getLeft() != nullptr){  // find leftmost ptr
            current = current->getLeft();
        }
        return current;
    }
    else{  // walk up ancestor chain until you hit root (then no succ)
        // first iteration
        Node<Key, Value>* p = current->getParent();  // parent
        Node<Key, Value>* g = NULL;  // grandparent
        if(p != NULL){
            g = p->getParent();
        }
        // if(g->getLeft() == p){  // parent is the right child of grandparent
        //     return g;
        // }

        // while(g != root_ and g != nullptr){
        while(g != nullptr){
            if(g->getLeft() == p){  // parent is the right child of grandparent
                return g;
            }
            p = g;
            g = g->getParent();
            // if(g->getLeft() == p){
            //     return g;
            // }
        }
        return nullptr;  // no successor
    }
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear(){
    // TODO - DONE
    clear_recurse(this->root_);
}

// Helper Function for clear()
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear_recurse(Node<Key, Value>* current){
    Node<Key, Value>* temp = current;
    if (temp == nullptr){
        return;
    }
    clear_recurse(current->getLeft());
    clear_recurse(current->getRight());
    current = nullptr;
    delete temp;
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const{
    // TODO - DONE
    Node<Key, Value>* n = this->root_;  // temp node
    if(n == NULL){
        return nullptr;
    }
    while(n->getLeft() != NULL){
        n = n->getLeft();
    }
    return n;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const{
    // TODO - DONE
    Node<Key, Value>* n = this->root_;  // temp node
    if(n == NULL){
        return nullptr;
    }
    Node<Key, Value>* loc = traverse(n, key);
    return loc;
}

/**
 * Return true if the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const{
    // TODO - DONE
    bool balanced = true;
    height(this->root_, balanced);
    return balanced;
}

// Helper Function for isBalanced()
template<typename Key, typename Value>
int BinarySearchTree<Key,Value>::height(Node<Key,Value>* n, bool &balanced) const{
    if (n == nullptr || !balanced) {
        return 0;
    }
 
    int lHeight = height(n->getLeft(), balanced);  // height of the left subtree
    int rHeight = height(n->getRight(), balanced);  // height of the right subtree
 
    if (std::abs(lHeight - rHeight) > 1) {
        balanced = false;
    }
    return std::max(lHeight, rHeight) + 1;
}


template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
