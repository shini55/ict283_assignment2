#include <iostream>
#include "BinarySearchTree.h"

// Utility function for printing traversal
void printInorder(int& value)
{
    std::cout << value << " ";
}

void printPreorder(int& value)
{
    std::cout << value << " ";
}

void printPostorder(int& value)
{
    std::cout << value << " ";
}

int main()
{
    BinarySearchTree<int> bst;

    // Test 1: Insert elements into the tree
    std::cout << "Inserting integers:" << std::endl;
    bst.Insert(10);
    bst.Insert(20);
    bst.Insert(5);
    bst.Insert(30);
    bst.Insert(50);
    bst.Insert(7);

    // Test 2: Inorder Traversal
    std::cout << "Inorder Traversal: ";
    bst.InorderTraversal(printInorder);
    std::cout << std::endl;
    std::cout << std::endl;

    // Test 3: Search for existing and non-existing values
    // Test Search function with a single value
    int valueToSearch = 10;  // The value we want to search for

    if (bst.Search(valueToSearch))
    {
        std::cout << "Found " << std::endl;
        std::cout << std::endl;
    }
    else
    {
        std::cout << "Not Found" << std::endl;
        std::cout << std::endl;
    }

    // Test 4: Delete node (
    std::cout << "Deleting 5" << std::endl;
    bst.DeleteNode(5);

    std::cout << "Inorder Traversal after deleting 5: "<< std::endl;
    bst.InorderTraversal(printInorder);
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "PostOrder Traversal after deleting 5: "<< std::endl;
    bst.PostorderTraversal(printPostorder);
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "PreOrder Traversal after deleting 5: "<< std::endl;
    bst.PreorderTraversal(printPreorder);
    std::cout << std::endl;
    std::cout << std::endl;



    return 0;
}
