#pragma once
#include "BSTNode.h"
#include <vector>
#include <iostream>
#include <stdexcept>

template <class T>
class BinaryTree {
private:
    void addItemToArray(BSTNode<T>* node, int& pos, T* arr);
    void deleteSubTree(BSTNode<T>* node);
    void addKeysToSet(BSTNode<T>* node, std::set<T>& keySet);
public:
    BSTNode<T>* root;

    BinaryTree();
    BinaryTree(const BinaryTree<T>& other);
    BinaryTree<T>& operator=(const BinaryTree<T>& other);
    void add(const T& item);
    bool remove(const T& item);
    void clear();
    int count();
    T& get(const T& item);
    T* toArray();
    void printInOrder();
    void printInOrder(BSTNode<T>* node);
    void printPreOrder();
    void printPreOrder(BSTNode<T>* node);
    void printPostOrder();
    void printPostOrder(BSTNode<T>* node);
 std::set<T> keySet();
    T& operator[](const T& key);
    ~BinaryTree();


};


template <class T>
BinaryTree<T>::BinaryTree() {
    root = nullptr;
}


template <class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& other) {
    root = nullptr;
    if (other.root != nullptr) {
        root = new BSTNode<T>(*other.root);
    }
}


template <class T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& other) {
    if (this == &other) return *this;
    clear();
    if (other.root != nullptr) {
        root = new BSTNode<T>(*other.root);
    }
    return *this;
}


template <class T>
void BinaryTree<T>::add(const T& item) {
    if (root == nullptr) {
        root = new BSTNode<T>(item);
    } else {
        root->add(item);
    }
}


template <class T>
bool BinaryTree<T>::remove(const T& item) {
    BSTNode<T>* parent = nullptr;
    BSTNode<T>* node = root;


    while (node != nullptr && node->getItem() != item) {
        parent = node;
        if (item < node->getItem()) {
            node = node->getLeft();
        } else {
            node = node->getRight();
        }
    }

    if (node == nullptr) return false;


    if (node->getLeft() == nullptr || node->getRight() == nullptr) {
        BSTNode<T>* newChild = (node->getLeft() != nullptr) ? node->getLeft() : node->getRight();

        if (parent == nullptr) {
            root = newChild;
        } else if (parent->getLeft() == node) {
            parent->setLeft(newChild);
        } else {
            parent->setRight(newChild);
        }

        delete node;
    } else {

        BSTNode<T>* smallestParent = node;
        BSTNode<T>* smallest = node->getRight();

        while (smallest->getLeft() != nullptr) {
            smallestParent = smallest;
            smallest = smallest->getLeft();
        }

        node->setItem(smallest->getItem());

        if (smallestParent->getLeft() == smallest) {
            smallestParent->setLeft(smallest->getRight());
        } else {
            smallestParent->setRight(smallest->getRight());
        }

        delete smallest;
    }

    return true;
}


template <class T>
T& BinaryTree<T>::get(const T& item) {
    BSTNode<T>* current = root;
    while (current != nullptr) {
        if (current->getItem() == item) {
            return current->getItem();
        } else if (item < current->getItem()) {
            current = current->getLeft();
        } else {
            current = current->getRight();
        }
    }
    throw std::logic_error("Item not found");
}


template <class T>
void BinaryTree<T>::addItemToArray(BSTNode<T>* node, int& pos, T* arr) {
    if (node != nullptr) {
        addItemToArray(node->getLeft(), pos, arr);
        arr[pos++] = node->getItem();
        addItemToArray(node->getRight(), pos, arr);
    }
}

template <class T>
T* BinaryTree<T>::toArray() {
    int size = count();
    T* arr = new T[size];
    int pos = 0;
    addItemToArray(root, pos, arr);
    return arr;
}

template <class T>
void BinaryTree<T>::clear() {
    deleteSubTree(root);
    root = nullptr;
}

template <class T>
void BinaryTree<T>::deleteSubTree(BSTNode<T>* node) {
    if (node != nullptr) {
        deleteSubTree(node->getLeft());
        deleteSubTree(node->getRight());
        delete node;
    }
}


template <class T>
int BinaryTree<T>::count() {
    return (root == nullptr) ? 0 : root->count();
}

template <class T>
void BinaryTree<T>::printInOrder() {
    printInOrder(root);
    std::cout << std::endl;
}

template <class T>
void BinaryTree<T>::printInOrder(BSTNode<T>* node) {
    if (node != nullptr) {
        printInOrder(node->getLeft());
        std::cout << node->getItem() << " ";
        printInOrder(node->getRight());
    }
}


template <class T>
void BinaryTree<T>::printPreOrder() {
    printPreOrder(root);
    std::cout << std::endl;
}

template <class T>
void BinaryTree<T>::printPreOrder(BSTNode<T>* node) {
    if (node != nullptr) {
        std::cout << node->getItem() << " ";
        printPreOrder(node->getLeft());
        printPreOrder(node->getRight());
    }
}


template <class T>
void BinaryTree<T>::printPostOrder() {
    printPostOrder(root);
    std::cout << std::endl;
}

template <class T>
void BinaryTree<T>::printPostOrder(BSTNode<T>* node) {
    if (node != nullptr) {
        printPostOrder(node->getLeft());
        printPostOrder(node->getRight());
        std::cout << node->getItem() << " ";
    }
}
template <class T>
std::set<T> BinaryTree<T>::keySet() {
    std::set<T> keys;
    addKeysToSet(root, keys);
    return keys;
}


template <class T>
void BinaryTree<T>::addKeysToSet(BSTNode<T>* node, std::set<T>& keySet) {
    if (node != nullptr) {
        addKeysToSet(node->getLeft(), keySet);
        keySet.insert(node->getItem());
        addKeysToSet(node->getRight(), keySet);
    }
}


template <class T>
T& BinaryTree<T>::operator[](const T& key) {
    return get(key);
}

template <class T>
BinaryTree<T>::~BinaryTree() {
    clear();
}


