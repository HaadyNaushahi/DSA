template <class T> class BinarySearchTree : public BinaryTree<T> {
  public:
    BinarySearchTree() : BinaryTree<T>() {}
    BinarySearchTree(const BinarySearchTree &bt) : BinaryTree<T>(bt) {}
    const BinarySearchTree &operator=(const BinarySearchTree &);
    ~BinarySearchTree() {}
    void insert(const T &value);
    void remove(const T &value);
    bool search(const T &value) const;
    bool isEmpty() const;
    void display() const;
    void inorderDisplay() const;
    void preorderDisplay() const;
    void postorderDisplay() const;
    TreeNode<T>* getRoot() const;
    void setRoot(TreeNode<T> *root);
};

template <class T>
void BinarySearchTree<T>::setRoot(TreeNode<T> *newRoot) {
    this->root = newRoot;
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::getRoot() const {
    return this->root;
}

template <class T>
const BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree<T> &bt) {
    if (this != &bt) {
        BinaryTree<T>::operator=(bt);
    }
    return *this;
}

template <class T>
void BinarySearchTree<T>::display() const {
    cout << "Default display (inorder): ";
    inorderDisplay();
}

// helper for in order traversal
template <class T>
void inorderTraversal(TreeNode<T> *root) {
    TreeNode<T> *current = root;
    ArrayStack<TreeNode<T>*> s(100);

    while (current != nullptr || !s.isEmpty()) {
	if (current != nullptr) {
	    s.push(current);
	    current = current->left;
	} else {
	    TreeNode<T>* lastTreeNode;
	    s.pop(lastTreeNode);
	    cout << lastTreeNode->data << " ";
	    current = lastTreeNode->right;
	}
    } 
}

template <class T>
void BinarySearchTree<T>::inorderDisplay() const {
    inorderTraversal(this->root);
}

// helper for pre order traversal
template <class T>
void preorderTraversal(TreeNode<T> *root) {
    TreeNode<T> *current = root;
    ArrayStack<TreeNode<T>*> s(100);

    while (current != nullptr || !s.isEmpty()) {
	if (current != nullptr) {
	    cout << current->data << " ";
	    s.push(current);
	    current = current->left;
	} else {
	    TreeNode<T>* lastTreeNode;
	    s.pop(lastTreeNode);
	    current = lastTreeNode->right;
	}
    } 
}
template <class T>
void BinarySearchTree<T>::preorderDisplay() const {
    preorderTraversal(this->root);
}

// helper for post order traversal
template <class T>
void postorderTraversal(TreeNode<T> *root) {
    ArrayStack<TreeNode<T>*> s1(100);
    ArrayStack<TreeNode<T>*> s2(100);
    s1.push(root);

    while (!s1.isEmpty()) {
	TreeNode<T>* lastTreeNode;
	s1.pop(lastTreeNode);
	s2.push(lastTreeNode);
	if (lastTreeNode->right != nullptr) {
	    s1.push(lastTreeNode->right);
	}
	if (lastTreeNode->left != nullptr) {
	    s1.push(lastTreeNode->left);
	}
    }

    while (!s2.isEmpty()) {
	TreeNode<T>* nodeToPrint;
	s2.pop(nodeToPrint);
	cout << nodeToPrint->data << endl;
    }
}

template <class T>
void BinarySearchTree<T>::postorderDisplay() const {
    postorderTraversal(this->root);
}


template <class T>
TreeNode<T> *removeTreeNode(TreeNode<T>* root, T value) {
    if (root == nullptr) {
	cout << "No node to delete" << endl;
	return nullptr;
    }

    if (root->data == value) {
	if (root->left == nullptr && root->right == nullptr) {
	    delete root;
	    return nullptr;
	} else if (root->left == nullptr && root->right != nullptr) {
	    TreeNode<T>* temp = root;
	    root = root->right;
	    delete temp;
	    return root;
	} else if (root->left != nullptr && root->right == nullptr) {
	    TreeNode<T>* temp = root;
	    root = root->left;
	    delete temp;
	    return root;
	} else {
	    TreeNode<T>* successor;
	    TreeNode<T>* successorParent = root;
	    TreeNode<T>* current = root->right;
	    while (current->left != nullptr) {
		successorParent = current;
		current = current->left;
	    }
	    successor = current;
	    if (successorParent == root) {
		successorParent->right = successor->right;
	    } else {
		successorParent->left = successor->right;
	    }
	    root->data = successor->data;
	    delete successor;
	    return root;
	}
    }

    TreeNode<T>* current = root;
    TreeNode<T>* parent = root;

    while (current != nullptr) {
	if (current->data == value) {
	    break;
	}
	parent = current;
	if (value > current->data) {
	    current = current->right;
	} else {
	    current = current->left;
	}
    } 
    if (current == nullptr) {
	cout << "Value not found" << endl;
	return root;
    }

    if (current->data == value) {
	if (current->left == nullptr && current->right == nullptr) {
	    if (parent->left == current) parent->left = nullptr;
	    else parent->right = nullptr;
	    delete current;
	    return root;
	} else if (current->left == nullptr && current->right != nullptr) {
	    if (parent->left == current) parent->left = current->right;
	    else parent->right = current->right;
	    delete current;
	    return root;
	} else if (current->left != nullptr && current->right == nullptr) {
	    if (parent->left == current) parent->left = current->left;
	    else parent->right = current->left;
	    delete current;
	    return root;
	} else {
	    TreeNode<T>* successorParent = current;
	    TreeNode<T>* currentTreeNode = current->right;
	    while (currentTreeNode->left != nullptr) {
		successorParent = currentTreeNode;
		currentTreeNode = currentTreeNode->left;
	    }
	    TreeNode<T>* successor = currentTreeNode;
	    if (successorParent == current) {
		successorParent->right = successor->right;
	    } else {
		successorParent->left = successor->right;
	    }
	    current->data = successor->data;
	    delete successor;
	    return root;
	}
    }
    return root;
}

template <class T> void BinarySearchTree<T>::remove(const T &value) {
    this->root = removeTreeNode(this->root, value);
} 

template <class T>
bool searchTreeNodes(TreeNode<T> *root, T value) {
    TreeNode<T> *current = root;
    while (current != nullptr) {
	if (current->data == value) {
	    return true;
	}
	if (value > current->data) {
	    current = current->right;
	} else {
	    current = current->left;
	}
    }
    return false;
}

template <class T> bool BinarySearchTree<T>::search(const T &value) const {
    if (this->root == nullptr)
        return false;
    
    return searchTreeNodes(this->root, value);
}

// helper function for insert node 
template <class T>
TreeNode<T>* insertTreeNode(TreeNode<T> *root, T value) {
    TreeNode<T> *current = root;    
    TreeNode<T> *parent = root;    

    if (root == nullptr) {
	current = new TreeNode<T>;
	current->data = value;
	root = current;
	return root;
    }

    while (current != nullptr) {
	parent = current;
	if (value > current->data) {
	    current = current->right;
	} else {
	    current = current->left;
	}
    }
    current = new TreeNode<T>;
    current->data = value;

    if (value > parent->data) {
	parent->right = current;
    } else {
	parent->left = current;
    }
    return root;
}

template <class T> void BinarySearchTree<T>::insert(const T &value) {
    this->root = insertTreeNode(this->root, value);
}

template <class T> bool BinarySearchTree<T>::isEmpty() const {
    return (this->root == nullptr);
}
