template <class T>
class BinarySearchTree: public BinaryTree<T>
{
public:
  BinarySearchTree():BinaryTree<T>() {}
  BinarySearchTree(const BinarySearchTree & bt): BinaryTree<T>(bt){}
  const BinarySearchTree & operator = (const BinarySearchTree & );
  ~BinarySearchTree(){}
  void insert(const T & value); 
  void remove(const T & value) ;
  bool search(const T & value) const ;   
  bool isEmpty() const; 
  void display() const;
};

