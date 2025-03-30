#ifndef BINARYSEARCHTREE_H_INCLUDED
#define BINARYSEARCHTREE_H_INCLUDED

/**
 * @brief A structure representing a node in a binary search tree.
 *
 * @tparam T The type of data stored in the node.
 */

template <class T>
struct Node
{
    T m_info;
    Node<T> *m_left;
    Node<T> *m_right;
};

/**
 * @brief A class representing a Binary Search Tree (BST).
 *
 * This class provides methods to insert, search, delete, and traverse nodes in the tree.
 *
 * @tparam T The type of data stored in the tree nodes.
 */

template <class T>
class BinarySearchTree
{
public:

    /**
     * @brief Default constructor for BinarySearchTree.
     *
     * Initializes an empty binary search tree.
     */
    BinarySearchTree();

      /**
     * @brief Destructor for BinarySearchTree.
     *
     * Deallocates all nodes in the tree.
     */
    ~BinarySearchTree();

    /**
     * @brief Copy constructor for BinarySearchTree.
     *
     * Creates a deep copy of the given binary search tree.
     *
     * @param otherTree The binary search tree to copy.
     */
    BinarySearchTree(const BinarySearchTree& otherTree);

      /**
     * @brief Assignment operator for BinarySearchTree.
     *
     * Copies the contents of the given binary search tree into the current tree.
     *
     * @param otherTree The binary search tree to copy.
     * @return A reference to the current tree.
     */
    BinarySearchTree& operator=(const BinarySearchTree& otherTree);

     /**
     * @brief Inserts a new item into the binary search tree.
     *
     * @param item The item to insert.
     */

    void Insert(const T& item);

    /**
     * @brief Searches for a target item in the binary search tree.
     *
     * @param target The item to search for.
     * @return true if the item is found, false otherwise.
     */
    bool Search(const T& target) const;

      /**
     * @brief Deletes a node with the specified target from the tree.
     *
     * @param target The item to delete.
     */
    void DeleteNode(const T& target);

       /**
     * @brief Deletes all nodes in the tree.
     *
     * This method is called to remove all nodes in the tree.
     */

    void DeleteTree(); // Public method


     /**
     * @brief Performs an inorder traversal of the tree.
     *
     * @param visit A pointer to a function that processes each node's data.
     */

    // Traversal methods
    void InorderTraversal(void (*visit)(T&)) const;


    /**
     * @brief Performs a preorder traversal of the tree.
     *
     * @param visit A pointer to a function that processes each node's data.
     */
    void PreorderTraversal(void (*visit)(T&)) const;


     /**
     * @brief Performs a postorder traversal of the tree.
     *
     * @param visit A pointer to a function that processes each node's data.
     */
    void PostorderTraversal(void (*visit)(T&)) const;

private:
    Node<T> *m_root;/**< Pointer to the root node of the tree */


      /**
     * @brief Helper method for performing inorder traversal.
     *
     * @param current The current node to process.
     * @param visit A pointer to a function that processes each node's data.
     */
    void Inorder(Node<T>* current, void (*visit)(T&)) const;

     /**
     * @brief Helper method for performing preorder traversal.
     *
     * @param current The current node to process.
     * @param visit A pointer to a function that processes each node's data.
     */
    void Preorder(Node<T>* current, void (*visit)(T&)) const;

     /**
     * @brief Helper method for performing postorder traversal.
     *
     * @param current The current node to process.
     * @param visit A pointer to a function that processes each node's data.
     */
    void Postorder(Node<T>* current, void (*visit)(T&)) const;

     /**
     * @brief Helper method for inserting a new node into the tree.
     *
     * @param newNode The node to insert.
     * @param current The current node to compare against.
     */

    void Insert(Node<T>* newNode, Node<T>*& current);

     /**
     * @brief Helper method for searching for a target item in the tree.
     *
     * @param current The current node to compare against.
     * @param target The target item to search for.
     * @return true if the target is found, false otherwise.
     */
    bool Search(Node<T>* current, const T& target) const;

     /**
     * @brief Helper method for deleting a node from the tree.
     *
     * @param current The current node to check.
     * @param target The item to delete.
     */
    void DeleteFromTree(Node<T>*& current,const T& target);

     /**
     * @brief Helper method for destroying the entire tree.
     *
     * @param current The current node to delete.
     */
    void Destroy(Node<T>*& current);

     /**
     * @brief Helper method for copying a tree.
     *
     * @param current The current node to copy.
     * @return A pointer to the newly created tree.
     */
    Node<T>* CopyTree(Node<T>* current) const;


};

// Constructor
template <class T>
BinarySearchTree<T>::BinarySearchTree()
{
    m_root= nullptr;
}
// Destructor
template <class T>
BinarySearchTree<T>::~BinarySearchTree()
{
    DeleteTree();
}

// Copy Constructor
template <class T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree& otherTree)
{
    m_root = CopyTree(otherTree.m_root);
}

// Assignment Operator
template <class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree& otherTree)
{
    if (this != &otherTree)
    {
        DeleteTree();
        m_root = CopyTree(otherTree.m_root);
    }
    return *this;
}

// Public Insert Method
template <class T>
void BinarySearchTree<T>::Insert(const T& item)
{
    Node<T> *newNode = new Node<T>;

    newNode->m_info = item;
    newNode->m_left = nullptr;
    newNode->m_right = nullptr;

    if (m_root == nullptr)
    {
        m_root = newNode;

    }
    else
    {

        Insert(newNode, m_root);
    }
}

// Private Insert Method
template <class T>
void BinarySearchTree<T>::Insert(Node<T>* newNode, Node<T>*& current)
{
    if (current == nullptr)
    {
        current = newNode;
    }
    else if (newNode->m_info < current->m_info)
    {
        Insert(newNode, current->m_left);
    }
    else if (newNode->m_info > current->m_info)
    {
        Insert(newNode, current->m_right);
    }
    else
    {
        delete newNode; // Handle duplicate insertion
    }


}

// Public Search Method
template <class T>
bool BinarySearchTree<T>::Search(const T& target) const
{
    return Search(m_root, target);
}

// Private Recursive Search Method
template <class T>
bool BinarySearchTree<T>::Search(Node<T>* current, const T& target) const
{
    if (current == nullptr)
    {
        return false;
    }
    else if (current->m_info == target)
    {
        return true;
    }
    else if (target < current->m_info)
    {
        return Search(current->m_left, target);
    }
    else
    {
        return Search(current->m_right, target);
    }
}

// Public DeleteNode Method
template <class T>
void BinarySearchTree<T>::DeleteNode(const T& target)
{
    DeleteFromTree(m_root, target);
}

// Private DeleteFromTree Method
template <class T>
void BinarySearchTree<T>::DeleteFromTree(Node<T>*& current, const T& target)
{
    Node<T>* trailCurrent = nullptr;
    Node<T>* temp = nullptr;

    if (current == nullptr) {
        return;
    }

    if (target < current->m_info) {
        DeleteFromTree(current->m_left, target);
    } else if (target > current->m_info) {
        DeleteFromTree(current->m_right, target);
    } else {
        // Node to be deleted found

        if (current->m_left == nullptr && current->m_right == nullptr) {
            // Case 1: No children
            temp = current;
            current = nullptr;
            delete temp;
        } else if (current->m_left == nullptr) {
            // Case 2: One child (right)
            temp = current;
            current = current->m_right;
            delete temp;
        } else if (current->m_right == nullptr) {
            // Case 3: One child (left)
            temp = current;
            current = current->m_left;
            delete temp;
        } else {
            // Case 4: Two children
            // Find the maximum node in the left subtree (inorder predecessor)
            Node<T>* currentMaxLeft = current->m_left;
            trailCurrent = nullptr;

            while (currentMaxLeft->m_right != nullptr) {
                trailCurrent = currentMaxLeft;
                currentMaxLeft = currentMaxLeft->m_right;
            }

            // Copy the max-left value into the node to be "deleted"
            current->m_info = currentMaxLeft->m_info;

            // Adjust pointers to remove the duplicate node
            if (trailCurrent == nullptr) {
                // If currentMaxLeft is directly current->m_left
                current->m_left = currentMaxLeft->m_left;
            } else {
                trailCurrent->m_right = currentMaxLeft->m_left;
            }

            delete currentMaxLeft;
        }
    }
}

// Public DeleteTree Method
template <class T>
void BinarySearchTree<T>::DeleteTree()
{
    Destroy(m_root);
    m_root = nullptr;
}

// Private Destroy Method (Renamed from DeleteTree)
template <class T>
void BinarySearchTree<T>::Destroy(Node<T>*& current)
{
    if (current != nullptr)
    {
        Destroy(current->m_left);
        Destroy(current->m_right);
        delete current;
        current = nullptr;
    }
}

// CopyTree Method
template <class T>
Node<T>* BinarySearchTree<T>::CopyTree(Node<T>* current) const
{
    if (current == nullptr)
    {
        return nullptr;
    }
    else
    {
        Node<T>* newNode = new Node<T>;
        newNode->m_info = current->m_info;
        newNode->m_left = CopyTree(current->m_left);
        newNode->m_right = CopyTree(current->m_right);
        return newNode;
    }

}

template <class T>
void BinarySearchTree<T>::InorderTraversal(void (*visit)(T&)) const
{
    Inorder(m_root, *visit);
}

template <class T>
void BinarySearchTree<T>::PreorderTraversal(void (*visit)(T&)) const
{
    Preorder(m_root, *visit);
}

template <class T>
void BinarySearchTree<T>::PostorderTraversal(void (*visit)(T&)) const
{
    Postorder(m_root, *visit);
}

template <class T>
void BinarySearchTree<T>::Inorder(Node<T>* current, void (*visit)(T&)) const
{
    if (current != nullptr)
    {
        Inorder(current->m_left, *visit);
        visit(current->m_info);
        Inorder(current->m_right, *visit);
    }
}

template <class T>
void BinarySearchTree<T>::Preorder(Node<T>* current, void (*visit)(T&)) const
{
    if (current != nullptr)
    {
        visit(current->m_info);
        Preorder(current->m_left, *visit);
        Preorder(current->m_right, *visit);
    }
}

template <class T>
void BinarySearchTree<T>::Postorder(Node<T>* current, void (*visit)(T&)) const
{
    if (current != nullptr)
    {
        Postorder(current->m_left, *visit);
        Postorder(current->m_right, *visit);
        visit(current->m_info);
    }
}


#endif // BINARYSEARCHTREE_H_INCLUDED
