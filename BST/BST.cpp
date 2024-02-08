#include "BST.hpp"

#include <algorithm>
#include <limits.h>

BST::BST()
    : root{nullptr}
    , size{0}
{}

BST::BST(int value) 
    : root{new Node{value}}
    , size{1}
{}

BST::~BST()
{
    destroyTree(root);
}

void BST::destroyTree(Node* node) 
{
    if (!node) {
        return;
    }
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

Node* BST::insert(Node* node, int key)
{
    if (!node) {
        node = new Node{key};
    }
    if (node->val > key) {
        node->left = insert(node->left, key);
    } else if (node->val < key) {
        node->right = insert(node->right, key);
    }
    return node;
}

void BST::insert(int key)
{
    root = insert(root, key);
    ++size;
}

bool BST::search(Node* node, int key) const
{
    if (!node) {
        return false;
    }
    if (node->val == key) {
        return true;
    } else if (key < node->val) {
        return search(node->left, key);
    } else {
        return search(node->right, key);
    }
}

bool BST::search(int key) const
{
    return search(root, key);
}

void BST::NLR(Node* node, void(*FP)(int))
{
    if (!node) {
        return;
    }
    FP(node->val);
    NLR(node->left, FP);
    NLR(node->right, FP);
}

void BST::LNR(Node* node, void(*FP)(int))
{
    if (!node) {
        return;
    }
    LNR(node->left, FP);
    FP(node->val);
    LNR(node->right, FP);
}

void BST::LRN(Node* node, void(*FP)(int))
{
    if (!node) {
        return;
    }
    LRN(node->left, FP);
    LRN(node->right, FP);
    FP(node->val);
}

void BST::NLR(void(*FP)(int))
{
    NLR(root, FP);
}

void BST::LNR(void(*FP)(int))
{
    LNR(root, FP);
}

void BST::LRN(void(*FP)(int))
{
    LRN(root, FP);
}

int BST::getHeight(Node* node) const
{
    if (!node) {
        return -1;
    }
    return std::max(getHeight(node->left), getHeight(node->right)) + 1;
}

Node* BST::getMax(Node* node) const
{
    if (!node) {
        return nullptr;
    } 
    while (node->right != nullptr) {
        node = node->right;
    }
    return node;
}

Node* BST::getMin(Node* node) const
{
    if (!node) {
        return nullptr;
    } 
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

Node* BST::getRoot() const
{
    return root;
}

Node* BST::getSuccessor(Node* node) const
{
    if (!node) {
        return nullptr;
    }
    if (node->right) {
        return getMin(node->right);
    }

    Node* successor = nullptr;
    Node* ancestor = root;

    while (node != ancestor) {
        if (node->val < ancestor->val) {
            successor = ancestor;
            ancestor = ancestor->left;
        } else {
            ancestor = ancestor->right;
        }
    }

    return successor;
}

Node* BST::getPredecessor(Node* node) const
{
    if (!node) {
        return nullptr;
    }
    if (node->left) {
        return getMax(node->left);
    }
    
    Node* predecessor = nullptr;
    Node* ancestor = root;

    while (node != ancestor) {
        if (node->val > ancestor->val) {
            predecessor = ancestor;
            ancestor = ancestor->right;
        } else {
            ancestor = ancestor->left;
        }
    }

    return predecessor;
}

Node* BST::remove(Node* node, int key)
{
    if (!node) {
        return nullptr;
    }
    if (node->val < key) {
        node->right = remove(node->right, key);
        return node;
    } 
    if (node->val > key) {
        node->left = remove(node->left, key);
        return node;
    }
    if (!node->left) {
        Node* tmp = node->right;
        delete node;
        return tmp;
    } else if (!node->right) {
        Node* tmp = node->left;
        delete node;
        return tmp;
    }
    Node* successor = getMin(node->right);
    node->val = successor->val;
    node->right = remove(node->right, successor->val);
    return node;
}

void BST::remove(int key)
{
    root = remove(root, key);
    --size;
}