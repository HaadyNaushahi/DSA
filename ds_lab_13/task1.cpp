// SPRING 2026 DATA STRUCTURES SECTION D20 ASSIGNMENT FIVE
// Name of Student: Muhammad Haady Naushahi
// Registration of Student: L1F24BSCS0306
// File t1.cpp contains complete code of task one, that will compile and run

#include <iostream>
using namespace std;
#include "TreeNode.h"
#include "AbstractStack.h"
#include "ArrayStack.h"
#include "BinaryTree.h"
#include "BinarySearchTree.h"

int main() {

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

    bst.display();
    cout << endl;

    bst.remove(19);
    bst.display();
    cout << endl;

    if (bst.search(8)) {
	cout << "Value found" << endl;
    } else {
	cout << "Value not found" << endl;
    }

    cout << "Tree leaves count: ";
    cout << bst.treeLeavesCount() << endl;

    cout << "Tree height: ";
    cout << bst.treeHeight() << endl;

    bst.treeNodeCount();

    return 0;
}
