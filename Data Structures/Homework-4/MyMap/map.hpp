#pragma once
#include <iostream>
#include <stdexcept>


template <typename K, typename V>
class Map {
private:
    struct Node {
        K key;
        V value;
        Node* left;
        Node* right;

        Node(const K& key, const V& value)
            : key(key), value(value), left(nullptr), right(nullptr) {}
    };

    Node* root;
    size_t nodeCount;

    void copyTree(Node*& thisR, Node* otherR) {
        if (otherR) {
            thisR = new Node(otherR->key, otherR->value);
            copyTree(thisR->left, otherR->left);
            copyTree(thisR->right, otherR->right);
        }
    }

    void deleteTree(Node* node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

    Node* findNode(const K& key, Node* node) const {
        if (!node) return nullptr;
        if (key == node->key) return node;
        if (key < node->key) return findNode(key, node->left);
        return findNode(key, node->right);
    }

    Node*& findMin(Node*& node) {
        return node->left ? findMin(node->left) : node;
    }

    Node*& findMax(Node*& node) {
        return node->right ? findMax(node->right) : node;
    }

    bool insertNode(const K& key, V&& value, Node*& node) {
        if (!node) {
            node = new Node(key, std::forward<V>(value));
            return true;
        }
        if (key == node->key) return false;
        if (key < node->key) return insertNode(key, std::forward<V>(value), node->left);
        return insertNode(key, std::forward<V>(value), node->right);
    }

    bool eraseNode(const K& key, Node*& node) {
        if (!node) return false;
        if (key == node->key) {
            Node* temp = node;
            if (!node->left) {
                node = node->right;
            } else if (!node->right) {
                node = node->left;
            } else {
                Node*& minNode = findMin(node->right);
                node->key = minNode->key;
                node->value = minNode->value;
                temp = minNode;
                minNode = minNode->right;
            }
            delete temp;
            return true;
        }
        if (key < node->key) return eraseNode(key, node->left);
        return eraseNode(key, node->right);
    }

public:
    Map() : root(nullptr), nodeCount(0) {}

    Map(const Map& other) : root(nullptr), nodeCount(0) {
        copyTree(this->root, other.root);
    }

    Map(Map&& other) noexcept : root(other.root), nodeCount(other.nodeCount) {
        other.root = nullptr;
        other.nodeCount = 0;
    }

    Map& operator=(const Map& other) {
        if (this != &other) {
            clear();
            copyTree(this->root, other.root);
        }
        return *this;
    }

    Map& operator=(Map&& other) noexcept {
        if (this != &other) {
            clear();
            root = other.root;
            nodeCount = other.nodeCount;
            other.root = nullptr;
            other.nodeCount = 0;
        }
        return *this;
    }

    ~Map() {
        clear();
    }

    bool empty() const {
        return root == nullptr;
    }

    size_t size() const {
        return nodeCount;
    }

    V& at(const K& key) {
        Node* node = findNode(key, root);
        if (!node) throw std::out_of_range("No key");
        return node->value;
    }

    const V& at(const K& key) const {
        Node* node = findNode(key, root);
        if (!node) throw std::out_of_range("No key");
        return node->value;
    }

    V* find(const K& key) {
        Node* node = findNode(key, root);
        return node ? &node->value : nullptr;
    }

    const V* find(const K& key) const {
        Node* node = findNode(key, root);
        return node ? &node->value : nullptr;
    }

    V& operator[](const K& key) {
        Node* node = findNode(key, root);
        if (!node) {
            insertNode(key, V{}, root);
            nodeCount++;
            node = findNode(key, root);
        }
        return node->value;
    }

    template <typename U>
    void insert(const K& key, U&& value) {
        if (insertNode(key, std::forward<U>(value), root)) {
            nodeCount++;
        } else {
            throw std::runtime_error("Key already exists");
        }
    }

    bool erase(const K& key) {
        if (eraseNode(key, root)) {
            nodeCount--;
            return true;
        }
        return false;
    }

    void clear() {
        deleteTree(root);
        root = nullptr;
        nodeCount = 0;
    }
};
