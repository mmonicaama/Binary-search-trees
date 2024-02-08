#include "AVL.hpp"

#include <algorithm>

AVL::AVL()
    : root{nullptr}
    , size{0}
{}

AVL::AVL(int value)
    : root{new Node{value}}
    , size(1)
{}

AVL::~AVL()
{
    destroyTree(root);
}

void AVL::destroyTree(Node* node)
{
    if (!node) {
        return;
    }
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

Node* AVL::left_rotate(Node* node)
{
    Node* res = node->right;
    node->right = res->left;
    res->left = node;
    return res;
}

Node* AVL::right_rotate(Node* node) 
{
    Node* res = node->left;
    node->left = res->right;
    res->right = node;
    return res;
}

Node* AVL::getRoot() const
{
    return root;
}

int AVL::getHeight(Node* node) const
{
    if (!node) {
        return -1;
    }
    return std::max(getHeight(node->left), getHeight(node->right)) + 1;
}

int AVL::getBF(Node* node) const
{
    return getHeight(node->left) - getHeight(node->right);
}

Node* AVL::insert(Node* node, int key) 
{
    if (!node) {
        return new Node{key};
    }
    if (node->val > key) {
        node->left = insert(node->left, key);
    } else if (node->val < key) {
        node->right = insert(node->right, key);
    } else {
        return node;
    }
    
    int bf = getBF(node);
    // RL case
    if (bf < -1 && key < node->right->val) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }
    // RR case
    if (bf < -1 && key > node->right->val) {
        return left_rotate(node);
    }
    // LL case 
    if (bf > 1 && key < node->left->val) {
        return right_rotate(node);
    } 
    // LR case
    if (bf > 1 && key > node->left->val) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    return node;
}

void AVL::insert(int key)
{
    root = insert(root, key);
    ++size;
}

bool AVL::search(Node* node, int key) const
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

bool AVL::search(int key) const
{
    return search(root, key);
}

void AVL::NLR(Node* node, void(*FP)(int))
{
    if (!node) {
        return;
    }
    FP(node->val);
    NLR(node->left, FP);
    NLR(node->right, FP);
}

void AVL::LNR(Node* node, void(*FP)(int))
{
    if (!node) {
        return;
    }
    LNR(node->left, FP);
    FP(node->val);
    LNR(node->right, FP);
}

void AVL::LRN(Node* node, void(*FP)(int))
{
    if (!node) {
        return;
    }
    LRN(node->left, FP);
    LRN(node->right, FP);
    FP(node->val);
}

void AVL::NLR(void(*FP)(int))
{
    NLR(root, FP);
}

void AVL::LNR(void(*FP)(int))
{
    LNR(root, FP);
}

void AVL::LRN(void(*FP)(int))
{
    LRN(root, FP);
}

Node* AVL::getMax(Node* node) const
{
    if (!node) {
        return nullptr;
    } 
    while (node->right != nullptr) {
        node = node->right;
    }
    return node;
}

Node* AVL::getMin(Node* node) const
{
    if (!node) {
        return nullptr;
    } 
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

Node* AVL::getSuccessor(Node* node) const
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

Node* AVL::getPredecessor(Node* node) const
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

Node* AVL::remove(Node* node, int key) 
{
    if (!node) {
        return nullptr;
    }
    
    if (node->val > key) {
        node->left = remove(node->left, key);
    } else if (node->val < key) {
        node->right = remove(node->right, key);
    } else {
        // Node to be deleted found

        // Node with only one child or no child
        if (!node->left || !node->right) {
            Node* tmp = node->left ? node->left : node->right;

            // No child case
            if (!tmp) {
                tmp = node;
                node = nullptr;
            } else {
                // One child case
                *node = *tmp; // Copy the contents of the non-empty child
            }

            delete tmp;
        } else {
            // Node with two children
            Node* successor = getMin(node->right);
            node->val = successor->val;
            node->right = remove(node->right, successor->val);
        }
    }

    // If the tree had only one node then return
    if (!node) {
        return node;
    }

    // Get the balance factor of this node
    int bf = getBF(node);

    // Balance the tree
    // Left Heavy
    if (bf > 1) {
        // Left-Left Case
        if (getBF(node->left) >= 0) {
            return right_rotate(node);
        } else { // Left-Right Case
            node->left = left_rotate(node->left);
            return right_rotate(node);
        }
    }
    // Right Heavy
    if (bf < -1) {
        // Right-Right Case
        if (getBF(node->right) <= 0) {
            return left_rotate(node);
        } else { // Right-Left Case
            node->right = right_rotate(node->right);
            return left_rotate(node);
        }
    }

    return node;
}

void AVL::remove(int key)
{
    root = remove(root, key);
    --size;
}