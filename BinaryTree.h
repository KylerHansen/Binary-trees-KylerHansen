#ifndef BINARY_TREE_H
#define BINARY_TREE_H

using std::cout;
using std::endl;


template <class Type>
struct Node {
    Type item;
    Node<Type>* left;
    Node<Type>* right;
};

template <class Type>
class BinaryTree
{
public:
    BinaryTree();
    ~BinaryTree();
    void insert(Type item);
    void preOrder();
    void inOrder();
    void postOrder();
    int nodeCount();
    Node<Type>* find(Type item);
    Node<Type>* findRightMostNode(Node<Type>* find);
    void remove(Type item);
    int  height();
    int leavesCount();
    BinaryTree(const BinaryTree<Type>& b);


protected:
    Node<Type>* root;

private:
    void destroy(Node<Type>* curr);
    void insert(Type item, Node<Type>* curr);
    void preOrder(Node<Type>* curr);
    void postOrder(Node<Type>* curr);
    void inOrder(Node<Type>* curr);
    int nodeCount(Node<Type>* curr);
    int leavesCount(Node<Type>* curr, int& count);
    Node<Type>* find(Type item, Node<Type>* curr);
    Node<Type>* remove(Type item, Node<Type>* curr);
    int height(int level, Node<Type>* curr);
    BinaryTree<Type>& operator=(const BinaryTree<Type>&);
    Node<Type>* copyNode(Node<Type>* ptr);
};

template <class Type>
BinaryTree<Type>::BinaryTree() {
    root = nullptr;
}

template <class Type>
BinaryTree<Type>::~BinaryTree() {
    destroy(root);
}

template <class Type>
void BinaryTree<Type>::destroy(Node<Type>* curr) {
    if (curr != nullptr) {
        destroy(curr->left);
        destroy(curr->right);
        delete curr;
    }
}

template <typename Type> //copy constructor
BinaryTree<Type>::BinaryTree(const BinaryTree<Type>& b) {
    root = copyNode(b.root);
}

template <typename Type>  //assignment operator
BinaryTree<Type>& BinaryTree<Type>::operator=(const BinaryTree<Type>&) {
    return BinaryTree(*this);
}

template <typename Type> //copy constructor helper
Node<Type>* BinaryTree<Type>::copyNode(Node<Type>* ptr) {
    if (ptr == nullptr) {
        return nullptr;
    }
    auto ptrCopy = new Node<Type>;
    //Node<Type>* ptrCopy = nullptr;
    ptrCopy->item = ptr->item;
    ptrCopy->left = copyNode(ptr->left);
    ptrCopy->right = copyNode(ptr->right);

    return ptrCopy;
}


template <class Type>
void BinaryTree<Type>::insert(Type item) {
    if (root == nullptr) {
        root = new Node<Type>;
        root->item = item;
        root->left = nullptr;
        root->right = nullptr;
    }
    else {
        insert(item, root);
    }

}

template <class Type>
void BinaryTree<Type>::insert(Type item, Node<Type>* curr) {
    if (item < curr->item) {
        if (curr->left == nullptr) {
            auto tmp = new Node<Type>;
           // Node<Type>* tmp = nullptr;
            tmp->item = item;
            tmp->right = nullptr;
            tmp->left = nullptr;
            curr->left = tmp;
        }
        else {
            insert(item, curr->left);
        }
    }
    else {
        if (curr->right == nullptr) {
            auto tmp = new Node<Type>;
            //Node<Type>* tmp = nullptr;
            tmp->item = item;
            tmp->right = nullptr;
            tmp->left = nullptr;
            curr->right = tmp;
        }
        else {
            insert(item, curr->right);
        }
    }
}


template <class Type>
void BinaryTree<Type>::preOrder() {
    cout << "Pre-Order: ";
    preOrder(root);
}
template <class Type>
void BinaryTree<Type>::preOrder(Node<Type>* curr) {
    if (curr != nullptr) {
        cout << curr->item << " ";
        preOrder(curr->left);
        preOrder(curr->right);
    }
}

template <class Type>
void BinaryTree<Type>::inOrder() {
    cout << "In-Order: ";
    inOrder(root);
}
template <class Type>
void BinaryTree<Type>::inOrder(Node<Type>* curr) {
    if (curr != nullptr) {
        inOrder(curr->left);
        cout << curr->item << " ";
        inOrder(curr->right);
    }

}

template <class Type>
void BinaryTree<Type>::postOrder() {
    cout << "Post-Order: ";
    postOrder(root);
}
template <class Type>
void BinaryTree<Type>::postOrder(Node<Type>* curr) {
    if (curr) {
        preOrder(curr->left);
        preOrder(curr->right);
        cout << curr->item << " ";
    }
}


template <class Type>
int BinaryTree<Type>::nodeCount() {
    return nodeCount(root);;
}

template <class Type>
int BinaryTree<Type>::nodeCount(Node<Type>* curr) {
    if (curr) {  //if currnode exists
        return 1 + nodeCount(curr->left) + nodeCount(curr->right);
    }
    return 0;
}

template <class Type>
int BinaryTree<Type>::leavesCount() {
    int count = 0;
    leavesCount(root, count);
    return count;
}

template <class Type>
int BinaryTree<Type>::leavesCount(Node<Type>* curr, int& count) {

    if (curr != nullptr) {
        if (curr->left == nullptr && curr->right == nullptr) {
            return count = count + 1;
        }
        if (curr->left != nullptr) {
            leavesCount(curr->left, count);
        }
        if (curr->right != nullptr) {
            leavesCount(curr->right, count);
        }
    }
    return count;
}


template <class Type>
Node<Type>* BinaryTree<Type>::find(Type item) {
    return find(item, root);
}


template <class Type>
Node<Type>* BinaryTree<Type>::find(Type item, Node<Type>* curr) {
    if (curr != nullptr) {
        if (curr->item == item) {
            return curr;
        }
        if (item < curr->item) {
            return find(item, curr->left);
        }
        if (item > curr->item) {
            return find(item, curr->right);
        }

    }
    return nullptr;
}


template <class Type>
Node<Type>* BinaryTree<Type>::findRightMostNode(Node<Type>* curr) {
    if (curr != nullptr) {
        if (curr->right == nullptr) {
            return curr;
        }
        else {
            return findRightMostNode(curr->right);
        }
    }

    return nullptr;
}

template <class Type>
void BinaryTree<Type>::remove(Type item) {
    remove(item, root);
}


template <class Type>
Node<Type>* BinaryTree<Type>::remove(Type item, Node<Type>* curr) {
    //Find the node you wish to delete
   // auto toRemove = new Node<Type>;
    Node<Type>* toRemove = nullptr;
    toRemove = find(item, curr);

    if (toRemove->left == nullptr) {// If the left pointer is null, replace the node with the right branch
        //auto tmp = new Node<Type>;
        Node<Type>* tmp = nullptr;
        tmp = toRemove->right;
        toRemove->item = tmp->item;
        tmp = nullptr;
    }
    else if (toRemove->right == nullptr) { //else If the right pointer is null, replace the node with the left branch
        //auto tmp = new Node<Type>;
        Node<Type>* tmp = nullptr;
        tmp = toRemove->left;
        toRemove->item = tmp->item;
        tmp = nullptr;
    }
    else { //Otherwise, replace the node's value with the value in the rightmost node of the left branch and remove the rightmost node on the left branch.

        //auto rightNode = new Node<Type>;  //create node to store the rightmost node of the left branch
        Node<Type>* rightNode = nullptr;
        rightNode = findRightMostNode(toRemove->left); //find the rightmost node of the left branch
        toRemove->item = rightNode->item; //set the value of the found node to the value of the rightmost node of the left branch.
        rightNode = nullptr; //remove the right most node;
    }

    return nullptr;
}

template <class Type>
int BinaryTree<Type>::height() {
    return height(0, root);
}
template <class Type>
int BinaryTree<Type>::height(int level, Node<Type>* curr) {
    if (curr != nullptr) {
        if (curr->left) { //if it exists
            return level = 1 + height(level, curr->left);
        }
        if (curr->right) {
            return level = 1 + height(level, curr->right);
        }
    }
    return 1;
}

#endif // BINARY_TREE_H