template <class T> class BinaryTree {
  protected:
    TreeNode<T> *root;
    void deleteTree();
    void copyTree(const BinaryTree *t);

  public:
    BinaryTree() { root = nullptr; }
    BinaryTree(const BinaryTree &bt) { copyTree(&bt); }
    const BinaryTree &operator=(const BinaryTree &);
    virtual ~BinaryTree() { deleteTree(); }
    virtual void insert(const T &value) = 0;
    virtual void remove(const T &value) = 0;
    virtual bool search(const T &value) const = 0;
    virtual bool isEmpty() const = 0;
    virtual void inorderDisplay() const = 0;
    virtual void preorderDisplay() const = 0;
    virtual void postorderDisplay() const = 0;
    int treeHeight() const; // Returns the height of the binary tree.
    int
    treeNodeCount() const; // Returns the number of nodes in the binary tree.
    int
    treeLeavesCount() const; // Returns the number of leaves in the binary tree
};

template <class T>
const BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T> &bt) {
    if (this != &bt) {
        deleteTree();
        copyTree(&bt);
    }
    return *this;
}

template <class T> void deleteTreeNodes(TreeNode<T> *root) {
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
	TreeNode<T>* nodeToDelete;
	s2.pop(nodeToDelete);
	delete nodeToDelete;
    }
}

template <class T> void BinaryTree<T>::deleteTree() {
    deleteTreeNodes(this->root);
    this->root = nullptr;
}

template <class T> 
TreeNode<T> *copyTreeNodes(TreeNode<T> *root) {
    if (root == nullptr) {
	return nullptr;
    }

    ArrayStack<TreeNode<T>*> s(100);
    ArrayStack<TreeNode<T>*> s2(100);

    TreeNode<T>* newRoot = new TreeNode<T>;
    newRoot->data = root->data;

    s.push(root);
    s2.push(newRoot);

    while (!s.isEmpty()) {
	TreeNode<T>* originalTreeNode;
	s.pop(originalTreeNode);
	TreeNode<T>* copyTreeNode;
	s2.pop(copyTreeNode);

	if (originalTreeNode->left != nullptr) {
	    TreeNode<T>* newTreeNode = new TreeNode<T>;
	    newTreeNode->data = originalTreeNode->data;
	    newTreeNode->right = nullptr;
	    newTreeNode->left = nullptr;
	    copyTreeNode->left = newTreeNode;
	    s.push(originalTreeNode->left);
	    s2.push(newTreeNode);
	} 
	if (originalTreeNode->right != nullptr) {
	    TreeNode<T>* newTreeNode = new TreeNode<T>;
	    newTreeNode->data = originalTreeNode->data;
	    newTreeNode->right = nullptr;
	    newTreeNode->left = nullptr;
	    copyTreeNode->right = newTreeNode;
	    s.push(originalTreeNode->right);
	    s2.push(newTreeNode);
	}
    } 
    return newRoot;
}

template <class T> void BinaryTree<T>::copyTree(const BinaryTree *t) {
    if (t->root == nullptr) {
        this->root = nullptr;
        return;
    }
    this->root = copyTreeNodes(t->root);
}
template <class T> int height(TreeNode<T> *root) {
    if (root == nullptr) {
	return 0;
    }
    ArrayStack<TreeNode<T>*> s(100);
    ArrayStack<int> h(100);
    s.push(root);
    h.push(1); // 1 -> height of the root
    
    int maxHeight = 0;
    int currentHeight = 0;

    while (!s.isEmpty()) {
	TreeNode<T>* lastTreeNode;
	s.pop(lastTreeNode);
	h.pop(currentHeight);
	if (currentHeight > maxHeight) {
	    maxHeight = currentHeight;
	}
	if (lastTreeNode->left != nullptr) {
	    s.push(lastTreeNode->left);
	    h.push(currentHeight + 1);
	}
	if (lastTreeNode->right != nullptr) {
	    s.push(lastTreeNode->right);
	    h.push(currentHeight + 1);
	}
    }
    return maxHeight;
}

template <class T> int BinaryTree<T>::treeHeight() const {
    return height(this->root);
}

template <class T> int nodeCount(TreeNode<T> *root) {
    TreeNode<T> *current = root;
    ArrayStack<TreeNode<T>*> s(100);
    int nodeCount = 0;

    while (current != nullptr || !s.isEmpty()) {
	if (current != nullptr) {
	    s.push(current);
	    current = current->left;
	} else {
	    TreeNode<T>* lastTreeNode;
	    s.pop(lastTreeNode);
	    nodeCount += 1;
	    current = lastTreeNode->right;
	}
    } 
    return nodeCount;
}

template <class T> int BinaryTree<T>::treeNodeCount() const {
    return nodeCount(this->root);
}

template <class T> int leafCount(TreeNode<T> *root) {
    TreeNode<T> *current = root;
    ArrayStack<TreeNode<T>*> s(100);
    int leaves = 0;

    while (current != nullptr || !s.isEmpty()) {
	if (current != nullptr) {
	    s.push(current);
	    current = current->left;
	} else {
	    TreeNode<T>* lastTreeNode;
	    s.pop(lastTreeNode);
	    if (lastTreeNode->right == nullptr && lastTreeNode->left == nullptr) {
		leaves += 1;
	    }
	    current = lastTreeNode->right;
	}
    } 
    return leaves;
}

template <class T> int BinaryTree<T>::treeLeavesCount() const {
    return leafCount(this->root);
}
