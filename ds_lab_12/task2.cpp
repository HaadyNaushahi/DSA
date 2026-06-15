// SPRING 2026 DATA STRUCTURES SECTION D20 ASSIGNMENT FIVE
// Name of Student: Muhammad Haady Naushahi
// Registration of Student: L1F24BSCS0306
// File task2.cpp contains complete code of task two, that will compile and run

/***** PROBLEM DESCRIPTION *****/
// Task 2: Binary Search Tree Operations
/*
Implement various Binary Search Tree (BST) operations including:
1. Swap subtrees at each node
2. Count single parent nodes (nodes with only one child)
3. Convert BST to a sorted doubly linked list using in-order traversal
4. Split a BST into left and right subtrees
5. Find a subtree by searching for a specific value
All operations should work on a BST of integers and demonstrate tree manipulation and traversal techniques.
*/

/***** PROBLEM SOLUTION DESCRIPTION *****/
/*
SOLUTION APPROACH:
---------------------------------------------------
1. CREATE BST WITH TEST DATA
   - Insert 10 values into BST: 15, 6, 23, 3, 10, 19, 28, 1, 8, 14
   - This creates a complete BST structure for testing

2. SWAP SUBTREES OPERATION (Recursive)
   - For each node in the tree:
     a. Temporarily store left subtree
     b. Replace left subtree with right subtree
     c. Replace right subtree with temporary stored left subtree
     d. Recursively perform swap on both new left and right subtrees
   - Performs complete mirror/flip of the BST

3. COUNT SINGLE PARENT NODES (Recursive)
   - Traverse entire tree
   - At each node, check if it has exactly one child (XOR condition)
   - Count such nodes and add counts from left and right subtrees
   - Return total count of single parent nodes

4. CONVERT BST TO DOUBLY LINKED LIST (In-Order Traversal)
   - Use in-order traversal (Left → Node → Right)
   - Insert each node's data into doubly linked list in order
   - Result is a sorted doubly linked list representation of BST

5. SPLIT BST OPERATION
   - Detach left subtree and store in leftRoot pointer
   - Detach right subtree and store in rightRoot pointer
   - Remove connections from root to isolate subtrees
   - Returns two independent subtrees

6. FIND SUBTREE BY VALUE (Recursive Search)
   - Search for target value in tree using DFS
   - If found at current node, return pointer to that subtree
   - If not found, recursively search left subtree first
   - Then recursively search right subtree
   - Return pointer to subtree rooted at target node or nullptr

HELPER FUNCTIONS:
- to_dot(): Converts BST structure to DOT format for graph visualization
- visualize_tree(): Generates PNG visualization of BST using Graphviz
*/

#include <iostream>
using namespace std;
#include <fstream>
#include "TreeNode.h"
#include "AbstractStack.h"
#include "ArrayStack.h"
#include "BinaryTree.h"
#include "BinarySearchTree.h"
#include "Node.h"
#include "DoublyLinkedList.h"
#include "ConcreteDoublyLinkedList.h"

/***** GLOBAL FUNCTION PROTOTYPES *****/
void swapSubTrees(TreeNode<int>* root);
int singleParent(TreeNode<int>* root);
void convert2List(TreeNode<int>* root, ConcreteDoublyLinkedList<int>& ll);
void split(TreeNode<int>* root, TreeNode<int>*& leftRoot, TreeNode<int>*& rightRoot);
TreeNode<int>* subTree(TreeNode<int>* root, int value);

void to_dot(TreeNode<int> *node, ofstream &out) {
    if (!node)
        return;
    out << "  " << node->data << ";\n";
    if (node->left) {
        out << "  " << node->data << " -> " << node->left->data << ";\n";
        to_dot(node->left, out);
    }
    if (node->right) {
        out << "  " << node->data << " -> " << node->right->data << ";\n";
        to_dot(node->right, out);
    }
}
void visualize_tree(TreeNode<int> *root, const string &filename = "tree") {
    ofstream out(filename + ".dot");
    out << "digraph BST {\n";
    out << "  node [shape=circle];\n";
    to_dot(root, out);
    out << "}\n";
    out.close();

    string cmd = "dot -Tpng " + filename + ".dot -o " + filename +
        ".png && xdg-open " + filename + ".png";
    system(cmd.c_str());
}

/***** Driver Function Main *****/
// PLEASE SEE,
// PLEASE UNCOMMENT THE CODE FOR EACH STEP AS RUNNING EVERY TASK AT ONCE IS NOT A GOOD IDEA
int main() {

    // STEP 1: Create Binary Search Tree and insert test values
    BinarySearchTree<int> bst;
    bst.insert(15);
    bst.insert(6);
    bst.insert(23);
    bst.insert(3);
    bst.insert(10);
    bst.insert(19);
    bst.insert(28);
    bst.insert(1);
    bst.insert(8);
    bst.insert(14);

    // Get root pointer for tree operations
    TreeNode<int>* root = bst.getRoot();

    // Display separator
    cout << endl;

    // STEP 2: Optional - Visualize original tree
    // visualize_tree(root);
    // bst.display();

    // STEP 3: Optional - Test swapSubTrees operation
    // swapSubTrees(root);
    // visualize_tree(root);
    // bst.display();

    cout << endl;

    // STEP 4: Optional - Count and display single parent nodes
    // cout << "Number of single parents: " << singleParent(root) << endl;

    // STEP 5: Convert BST to doubly linked list and display
    ConcreteDoublyLinkedList<int> ll;
    convert2List(root, ll);
    ll.display();
    

    // STEP 6: Optional - Test split operation and visualize subtrees
    // TreeNode<int>* rightNode;
    // TreeNode<int>* leftNode;
    //
    // split(bst.getRoot(), leftNode, rightNode);
    //
    // BinarySearchTree<int> leftSubTree;
    // BinarySearchTree<int> rightSubTree;
    //
    // leftSubTree.setRoot(leftNode);
    // rightSubTree.setRoot(rightNode);
    //
    // visualize_tree(leftSubTree.getRoot());

    // STEP 7: Optional - Find and visualize subtree containing specific value
    // TreeNode<int>* subTreeFromValue = subTree(bst.getRoot(), 6);
    // visualize_tree(subTreeFromValue);

    return 0;
}

/***** GLOBAL FUNCTION CODE *****/

/**
 * FUNCTION: swapSubTrees
 * PURPOSE: Recursively swaps left and right subtrees at each node
 */
void swapSubTrees(TreeNode<int>* root) {
    // BASE CASE: If node is null, return
    if (root != nullptr) {
	// Temporarily store left subtree pointer
	TreeNode<int> *temp = root->left;
	
	root->left = root->right;
	root->right = temp;

	swapSubTrees(root->left);
	swapSubTrees(root->right);
    }
}

/**
 * FUNCTION: singleParent
 * PURPOSE: Counts all nodes with exactly one child
 */
int singleParent(TreeNode<int>* root) {
    if (root == nullptr) {
	return 0;
    }
    
    int count = 0;
    
    if ((root->left == nullptr && root->right != nullptr) ||
    (root->left != nullptr && root->right == nullptr)) {
	count = 1;
    }
    
    return count + singleParent(root->left) + singleParent(root->right);
}

/**
 * FUNCTION: convert2List
 * PURPOSE: Converts BST to sorted doubly linked list using in-order traversal
 */
void convert2List(TreeNode<int>* root, ConcreteDoublyLinkedList<int>& ll) {
    if (root != nullptr) {
	convert2List(root->left, ll);
	
	ll.insertAtLast(root->data);
	
	convert2List(root->right, ll);
    }    
}

/**
 * FUNCTION: split
 * PURPOSE: Splits BST by detaching left and right subtrees from root
 */
void split(TreeNode<int>* root, TreeNode<int>*& leftRoot, TreeNode<int>*& rightRoot) {
    if (root == nullptr) return;
    
    leftRoot = root->left;
    
    rightRoot = root->right;
    
    root->left = nullptr;
    root->right = nullptr;
}

/**
 * FUNCTION: subTree
 * PURPOSE: Finds and returns pointer to subtree containing target value
 */
TreeNode<int>* subTree(TreeNode<int>* root, int value) {
    if (root == nullptr) return nullptr;
    
    if (root->data == value) return root;
    
    TreeNode<int> * result = subTree(root->left, value);
    
    if (result != nullptr) return result;
    
    return subTree(root->right, value);
}
