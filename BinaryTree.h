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
public:
    BSTNode<T>* root;

    BinaryTree();
    BinaryTree(const BinaryTree<T>& other);
    BinaryTree<T>& operator=(const BinaryTree<T>& other);
    void add(const T& item);
    bool remove(const T& item);


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
