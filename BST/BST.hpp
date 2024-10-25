#ifndef BST_HPP
#define BST_HPP

#include <cstddef>

struct Node 
{
    int val;
    Node* left;
    Node* right;
    Node() : val(0), left(nullptr), right(nullptr) {}
    Node(int x) : val(x), left(nullptr), right(nullptr) {}
    Node(int x, Node *left, Node *right) : val(x), left(left), right(right) {}

};

class BST 
{
public:
    BST();
    BST(int);
    ~BST();
    void insert(int);
    bool search(int) const;
    void NLR(void(*)(int));
    void LNR(void(*)(int));
    void LRN(void(*)(int));
    int getHeight(Node*) const;
    Node* getMax(Node*) const;
    Node* getMin(Node*) const;
    Node* getRoot() const;
    Node* getSuccessor(Node*) const;
    Node* getPredecessor(Node*) const;
    void remove(int);
    void printFromRight() const;

private:
    void destroyTree(Node*);
    Node* insert(Node*, int);
    bool search(Node*, int) const;
    void NLR(Node*, void(*)(int));
    void LNR(Node*, void(*)(int));
    void LRN(Node*, void(*)(int));
    Node* remove(Node*, int);
    void printFromRight(Node*, int) const;

private:
    Node* root;
    size_t size;
};

#endif // BST_HPP