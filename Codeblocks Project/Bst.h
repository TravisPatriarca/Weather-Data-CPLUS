//#include "Node.h"
#include <iostream>

#ifndef BST_H
#define BST_H

template <class T>
class Bst
{
    /**
     * @brief Node structure
     *
     * Stores lNode and rNode pointers as well as Node data.
     *
     */
    struct Node {
        Node *lNode = nullptr; ///left node pointer
        Node *rNode = nullptr; ///right node pointer
        T data; ///node data
    };

    public:
        Bst();
        Bst(const Bst &tree); ///copy constructor
        /**
         * @brief overloads assignment operator
         *
         * Copies one tree to another
         *
         * @param Bst<T>& tree
         * @return Bst&
         */
        const Bst& operator=(const Bst<T>& tree);
        ~Bst();
        /**
         * @brief in order traversal public
         *
         *  Calls inOrder passing through the root.
         *
         * @param function pointer void (*func)
         * @return void
         */
        void inOrderTraversal(void (*func) (T&)) const;
        /**
         * @brief pre order traversal public
         *
         *  Calls preOrder passing through the root.
         *
         * @param function pointer void (*func)
         * @return void
         */
        void preOrderTraversal(void (*func) (T&)) const;
        /**
         * @brief post order traversal public
         *
         *  Calls postOrder passing through the root.
         *
         * @param function pointer void (*func)
         * @return void
         */
        void postOrderTraversal(void (*func) (T&)) const;
        /**
         * @brief deletes the tree
         *
         *  Calls destroy on root
         *
         * @return void
         */
        void deleteTree();
        /**
         * @brief inserts data into tree
         *
         * calls insertData starting at root
         *
         * @param const T&
         * @return void
         */
        void insert(const T& insertItem);

        /**
         * @brief inserts data into tree
         *
         * calls insertData starting at root
         *
         * @param const T&
         * @return void
         */
        bool search(const T& searchData);

        /**
         * @brief get a given data element
         *
         * gets given data starting at root
         *
         * @param const T&
         * @return T&
         */
        T& get(const T& dataItem);


    private:
        /**
         * @brief get a given data element
         *
         * gets given data at node
         *
         * @param Node* &, const T&
         * @return T&
         */
        T& getData(Node* &n, const T& dataItem);
        /**
         * @brief inserts data into node
         *
         * @param Node *n, Node *newNode
         * @return void
         */
        void insertData(Node* &n,const T &newNode);
        /**
         * @brief in order traversal
         *
         * Traverses tree left node, this node, right node
         *
         * @param Node *n
         * @return void
         */
        void inOrder(Node *n, void (*func) (T& item)) const;
        /**
         * @brief pre order traversal
         *
         * Traverses tree this node, left node, right node
         *
         * @param Node *n
         * @return void
         */
        void preOrder(Node *n, void (*func) (T& item)) const;
        /**
         * @brief post order traversal
         *
         * Traverses tree left node, right node, this node
         *
         * @param Node *n
         * @return void
         */
        void postOrder(Node *n, void (*func) (T& item)) const;
        /**
         * @brief destroys node
         *
         * Destroys node and it's attached nodes using recursion
         *
         * @param Node *n
         * @return void
         */
        void destroy(Node *n);

        /**
         * @brief searches node
         *
         * find if data exists within a node
         *
         * @param Node *n, T searchData
         * @return bool
         */
        bool searchNode(Node *n, T searchData);

        /**
         * @brief copies a tree
         *
         * copies from one tree to another
         *
         * @param Node* &copyTreeRoot, Node* otherTreeRoot
         * @return void
         */
        void copyTree(Node* &copyTreeRoot, Node* otherTreeRoot);

        Node *root; ///root pointer node of the tree
};

template <class T>
Bst<T>::Bst()
: root(nullptr)
{
}

template <class T>
Bst<T>::Bst(const Bst<T>& tree)
{
    if (tree.root == nullptr) //if root is not set
        root = nullptr;
    else
        copyTree(root, tree.root); //copy tree
}

template <class T>
Bst<T>::~Bst()
{
    destroy(root);
}

template <class T>
const Bst<T>& Bst<T>::operator=(const Bst<T>& tree)
{
    if (this != &tree) //if current tree is not the new tree
    {
        if (root != nullptr)
            destroy(root);

        if (tree.root == nullptr)
            root = nullptr;
        else
            copyTree(root, tree.root); //copy tree
    }

    return *this;
}

template <class T>
void Bst<T>::copyTree(Node* &copiedTreeRoot, Node* otherTreeRoot)
{
    if (otherTreeRoot == nullptr)
        copiedTreeRoot = nullptr;
    else
    {
        copiedTreeRoot = new Node;
        copiedTreeRoot->data = otherTreeRoot->data;
        copyTree(copiedTreeRoot->lNode, otherTreeRoot->lNode);
        copyTree(copiedTreeRoot->rNode, otherTreeRoot->rNode);
    }
}

template <class T>
T& Bst<T>::get(const T& dataItem)
{
    return getData(root, dataItem);
}

template <class T>
T& Bst<T>::getData(Node* &n, const T& dataItem)
{
    if (dataItem == n->data)
    {
        return n->data;
    }
    else
        if (dataItem < n->data) // if searchData is < nodes data
        {
            if (n->lNode != nullptr) // if left node does not exists
            {
                return getData(n->lNode, dataItem); // search data in left node
            }
        }
        else
        {
            if (n->rNode != nullptr) //if right node exists
            {
                return getData(n->rNode, dataItem); // search data in right node
            }
        }
}

template <class T>
void Bst<T>::insert(const T& insertItem)
{
    insertData(root, insertItem);
}

template <class T>
void Bst<T>::insertData(Node* &n, const T& insertItem)
{
    if (n==nullptr)
    {
        Node *newNode;
        newNode = new Node;
        newNode->data = insertItem;
        n = newNode;
    }
    else
    {
        if (n->data > insertItem)
        {
            insertData(n->lNode, insertItem);
        }
        else
            if (n->data < insertItem)
            {
                insertData(n->rNode, insertItem);
            }
    }
}

template <class T>
void Bst<T>::inOrderTraversal(void (*func) (T&)) const
{
    inOrder(root, *func);
}

template <class T>
void Bst<T>::preOrderTraversal(void (*func) (T&)) const
{
    preOrder(root, *func);
}

template <class T>
void Bst<T>::postOrderTraversal(void (*func) (T&)) const
{
    postOrder(root, *func);
}

template <class T>
void Bst<T>::inOrder(Node *n, void (*func) (T& item)) const
{
    if (n != nullptr) // if node exists
    {
        inOrder(n->lNode, *func); // go to left node
        (*func) (n->data); // print current node data
        inOrder(n->rNode, *func); // go to right node

    }
}

template <class T>
void Bst<T>::preOrder(Node *n, void (*func) (T& item)) const
{
    if (n != nullptr) // if node exists
    {
        (*func) (n->data); // print current node data
        preOrder(n->lNode, *func); // go to left node
        preOrder(n->rNode, *func); // go to right node

    }
}

template <class T>
void Bst<T>::postOrder(Node *n, void (*func) (T& item)) const
{
    if (n != nullptr) // if node exists
    {
        postOrder(n->lNode, *func); // go to left node
        postOrder(n->rNode, *func);  // go to right node
        (*func) (n->data); // print current node data

    }
}

template <class T>
void Bst<T>::deleteTree()
{
    destroy(root);
}

template <class T>
void Bst<T>::destroy(Node *n)
{
    if (n != nullptr) // if node exists
    {
        destroy(n->lNode); // destroy left node
        destroy(n->rNode); // destroy right node
        delete n; // delete this node pointer
        n = nullptr; // set pointer to null
    }
}

template <class T>
bool Bst<T>::search(const T& searchData)
{
    if (root == nullptr)
    {
        return false;
    }
    else
    {
       return searchNode(root, searchData);
    }
}

template <class T>
bool Bst<T>::searchNode(Node *n, T searchData)
{
    if (searchData == n->data)
    {
        return true;
    }
    else
        if (searchData < n->data) // if searchData is < nodes data
        {
            if (n->lNode == nullptr) // if left node does not exists
            {
                return false;
            }
            else
            {
                return searchNode(n->lNode, searchData); // search data in left node
            }
        }
        else
        {
            if (n->rNode == nullptr) //if right node exists
            {
                return false;
            }
            else
            {
                return searchNode(n->rNode, searchData); // search data in right node
            }
        }
}
#endif // BST_H
