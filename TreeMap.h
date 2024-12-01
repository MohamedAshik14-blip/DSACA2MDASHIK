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


};
