template <class T>
class BinaryTree
{
protected:
  Node<T> * root;
  void deleteTree();
  void copyTree(const BinaryTree<T>*);
  Node<T>* copyNodes(const Node<T> *root);
public:
  BinaryTree() {root = nullptr;}
  BinaryTree(const BinaryTree & bt) {copyTree(bt);}
  const BinaryTree & operator = (const BinaryTree & );
  virtual ~BinaryTree(){deleteTree();}
  virtual void insert(const T & value) = 0; 
  virtual void remove(const T & value) = 0;
  virtual bool search(const T & value) const = 0;   
  virtual bool isEmpty() const= 0; 
  void inorderDisplay() const= 0;
  void preorderDisplay() const= 0;
  void postorderDisplay() const= 0;
  int treeHeight() const;  //Returns the height of the binary tree.
  int treeNodeCount() const;   //Returns the number of nodes in the binary tree.
  int treeLeavesCount() const;  //Returns the number of leaves in the binary tree
};

template <class T>
Node<T>* copyNodes(const Node<T> *root) {
    if (root == nullptr) return nullptr;

    Node<T> *newNode = new Node<T>;
    newNode->data = root->data;
    newNode->left = copyNodes(root->left);
    newNode->right = copyNodes(root->right);

    return newNode;
}

template <class T>
void BinaryTree<T>::copyTree(const BinaryTree<T> *bst) {
    if (bst == nullptr) {
	root == nullptr;
	return;
    }
    this->root = copyNodes(bst->root);
}

template <class T>
void BinaryTree<T>::insert(const T & value) {
    
}
template <class T>
void BinaryTree<T>::remove(const T & value) {

}
template <class T>
bool BinaryTree<T>::search(const T & value) const {

}
template <class T>
bool BinaryTree<T>::isEmpty() const {

}
template <class T>
void BinaryTree<T>::inorderDisplay() const {
    if (root != nullptr) {
	inorderDisplay();
	cout << root->data << " ";
	inorderDisplay();
    }
}
template <class T>
void BinaryTree<T>::preorderDisplay() const {

}
template <class T>
void BinaryTree<T>::postorderDisplay() const {

}
template <class T>
int BinaryTree<T>::treeHeight() const {

}
template <class T>
int BinaryTree<T>::treeNodeCount() const {

}
template <class T>
int BinaryTree<T>::treeLeavesCount() const {

}
