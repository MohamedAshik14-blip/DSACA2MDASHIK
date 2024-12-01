#pragma once
#include <iostream>

template <class T>
class BSTNode {
private:
    T item;
    BSTNode* left;
    BSTNode* right;

public:
    BSTNode(const T& newItem)
            : item(newItem), left(nullptr), right(nullptr) {}

    T& getItem() { return item; }
    const T& getItem() const { return item; }
    void setItem(const T& newItem) { item = newItem; }

    BSTNode* getLeft() const { return left; }
    void setLeft(BSTNode* newLeft) { left = newLeft; }

    BSTNode* getRight() const { return right; }
    void setRight(BSTNode* newRight) { right = newRight; }

    void add(const T& newItem) {
        if (newItem < item) {
            if (left == nullptr) {
                left = new BSTNode(newItem);
            } else {
                left->add(newItem);
            }
        } else if (newItem > item) {
            if (right == nullptr) {
                right = new BSTNode(newItem);
            } else {
                right->add(newItem);
            }
        }
    }

    bool remove(const T& newItem) {
        if (newItem < item) {
            return left != nullptr && left->remove(newItem);
        } else if (newItem > item) {
            return right != nullptr && right->remove(newItem);
        } else { 
          
            if (left == nullptr && right == nullptr) {
                delete this;
                return true;
            }
            if (left == nullptr || right == nullptr) {
                BSTNode* child = left ? left : right;
                item = child->item;
                left = child->left;
                right = child->right;
                delete child;
                return true;
            }
        }
        return false;
    }

 int count() const {
        int count = 1;
        if (left != nullptr) count += left->count();
        if (right != nullptr) count += right->count();
        return count;
    }

    ~BSTNode() {
        delete left;
        delete right;
    }
};
