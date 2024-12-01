#pragma once
#include "BSTNode.h"
#include <stdexcept>
#include <iostream>

template <typename K, typename V>
class TreeMap {
private:
    class KeyValue {
    public:
        K key;
        V value;

        KeyValue() = default;
        KeyValue(K k, V v) : key(k), value(v) {}

        bool operator<(const KeyValue& other) const {
            return key < other.key;
        }
        bool operator>(const KeyValue& other) const {
            return key > other.key;
        }
        bool operator==(const KeyValue& other) const {
            return key == other.key;
        }
        bool operator!=(const KeyValue& other) const {
            return !(*this == other);
        }
    };

    BSTNode<KeyValue>* root;

    void clearNode(BSTNode<KeyValue>* node) {
        if (node == nullptr) return;
        clearNode(node->getLeft());
        clearNode(node->getRight());
        delete node;
    }

    V& getNodeValue(BSTNode<KeyValue>* node, const K& key) {
        if (node == nullptr) {
            throw std::logic_error("Key not found");
        }
        if (key == node->getItem().key) {
            return node->getItem().value;
        } else if (key < node->getItem().key) {
            return getNodeValue(node->getLeft(), key);
        } else {
            return getNodeValue(node->getRight(), key);
        }
    }

    BSTNode<KeyValue>* getNode(BSTNode<KeyValue>* node, const KeyValue& keyValue) const {
        if (node == nullptr) return nullptr;
        if (keyValue == node->getItem()) {
            return node;
        }
        if (keyValue < node->getItem()) {
            return getNode(node->getLeft(), keyValue);
        }
        return getNode(node->getRight(), keyValue);
    }

    void addNode(BSTNode<KeyValue>*& node, const KeyValue& kv) {
        if (node == nullptr) {
            node = new BSTNode<KeyValue>(kv);
        } else if (kv < node->getItem()) {
            addNode(node->getLeft(), kv);
        } else if (kv > node->getItem()) {
            addNode(node->getRight(), kv);
        }
    }
public:
    TreeMap() : root(nullptr) {}

    void clear() {
        clearNode(root);
        root = nullptr;
    }

    bool containsKey(const K& key) {
        KeyValue tempKey(key, V());
        return getNode(root, tempKey) != nullptr;
    }

    V& get(const K& key) {
        KeyValue tempKey(key, V());
        BSTNode<KeyValue>* node = getNode(root, tempKey);
        if (node == nullptr) {
            throw std::logic_error("Key not found");
        }
        return node->getItem().value;
    }

    void put(const K& key, const V& value) {
        KeyValue kv(key, value);
        addNode(root, kv);
    }
int size() {
        return root ? root->count() : 0;
    }

    bool removeKey(const K& key) {
        KeyValue tempKey(key, V());
        return removeNode(root, tempKey);
    }

    bool removeNode(BSTNode<KeyValue>*& node, const KeyValue& keyValue) {
        if (node == nullptr) return false;
        if (keyValue == node->getItem()) {
            if (node->getLeft() == nullptr && node->getRight() == nullptr) {
                delete node;
                node = nullptr;
                return true;
            }

        } else if (keyValue < node->getItem()) {
            return removeNode(node->getLeft(), keyValue);
        } else {
            return removeNode(node->getRight(), keyValue);
        }
        return false;
    }

    ~TreeMap() {
        clear();
    }
};

