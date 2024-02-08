#include <iostream>
#include "BST.hpp"

void print(int val)
{
    std::cout << val << " ";
}

int main()
{
    BST myTree;

    myTree.insert(5);
    myTree.insert(3);
    myTree.insert(7);
    myTree.insert(2);
    myTree.insert(4);

    int valueToSearch = 4;
    if (myTree.search(valueToSearch)) {
        std::cout << valueToSearch << " found in the BST." << std::endl;
    } else {
        std::cout << valueToSearch << " not found in the BST." << std::endl;
    }

    valueToSearch = 6;
    if (myTree.search(valueToSearch)) {
        std::cout << valueToSearch << " found in the BST." << std::endl;
    } else {
        std::cout << valueToSearch << " not found in the BST." << std::endl;
    }

    myTree.LNR(print);
    std::cout << std::endl;

    Node* root = myTree.getRoot();

    std::cout << myTree.getHeight(root) << std::endl;

    std::cout << "MAX : " << myTree.getMax(root)->val << std::endl;
    std::cout << "MIN : " << myTree.getMin(root)->val << std::endl;

    if (myTree.getSuccessor(root)) {
        std::cout << "Successor of root : " << myTree.getSuccessor(root)->val << std::endl;
    } else {
        std::cout << "Doesn't have successor.\n";
    }
    
    if (myTree.getSuccessor(root->left)) {
        std::cout << "Successor of 3 : " << myTree.getSuccessor(root->left)->val << std::endl;
    } else {
        std::cout << "Doesn't have successor.\n";
    }

    if (myTree.getSuccessor(root->right)) {
        std::cout << "Successor of 7 : " << myTree.getSuccessor(root->right)->val << std::endl;
    } else {
        std::cout << "Doesn't have successor.\n";
    }


    if (myTree.getPredecessor(root)) {
        std::cout << "Predecessor of root : " << myTree.getPredecessor(root)->val << std::endl;
    } else {
        std::cout << "Doesn't have predecessorr.\n";
    }
    
    if (myTree.getPredecessor(root->left)) {
        std::cout << "Predecessor of 3 : " << myTree.getPredecessor(root->left)->val << std::endl;
    } else {
        std::cout << "Doesn't have predecessor.\n";
    }

    if (myTree.getPredecessor(root->right)) {
        std::cout << "Predecessor of 7 : " << myTree.getPredecessor(root->right)->val << std::endl;
    } else {
        std::cout << "Doesn't have predecessor.\n";
    }
    
    myTree.remove(7);
    myTree.LNR(print);
    std::cout << std::endl;

    return 0;
}