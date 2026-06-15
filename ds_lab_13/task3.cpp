// SPRING 2026 DATA STRUCTURES SECTION D20 ASSIGNMENT FIVE
// Name of Student: Muhammad Haady Naushahi
// Registration of Student: L1F24BSCS0306
// File task3.cpp contains complete code of task three, that will compile and run

/***** PROBLEM DESCRIPTION *****/
// Task 3: Binary Search Tree String Operations
/*
Implement Binary Search Tree operations on string data including:
1. Read words from file and insert into BST
2. Write BST words to output file in sorted order (in-order traversal)
3. Search for specific words in BST
4. Remove words from BST
5. Insert new words into existing BST
6. Convert case (uppercase ↔ lowercase) for all words in BST
7. Visualize tree structure using Graphviz
All operations demonstrate string handling, tree manipulation, and file I/O with BST data structure.
*/

/***** PROBLEM SOLUTION DESCRIPTION *****/
/*
SOLUTION APPROACH:
---------------------------------------------------
1. CREATE BST FOR STRING STORAGE
   - Initialize empty BST that stores string values
   - Specify filename containing words to load: "words.txt"

2. READ WORDS FROM FILE
   - Open input file for reading
   - Read words one by one from file
   - Insert each word into BST in alphabetical order
   - Close file after reading complete

3. WRITE SORTED WORDS TO OUTPUT FILE
   - Use in-order traversal (Left → Node → Right)
   - In-order traversal naturally produces alphabetically sorted output
   - Write each word on separate line in output file
   - Result: sorted list of all words from BST

4. SEARCH OPERATION
   - Search BST for specific word using binary search
   - Display result: found or not found
   - Example: Search for "phantom"

5. REMOVE OPERATION
   - Remove specified word from BST
   - Maintain BST properties after deletion
   - Reorganize tree structure as needed
   - Example: Remove "ANCHOR"

6. INSERT NEW WORD
   - Add new word to existing BST
   - Maintain alphabetical ordering
   - Example: Insert "Haady"

7. CASE CONVERSION
   - Convert case for all characters in tree
   - Uppercase letters (ASCII 65-90) → add 32 to make lowercase
   - Lowercase letters (ASCII 97-122) → subtract 32 to make uppercase
   - Process all nodes using in-order traversal
   - Update each word's case while preserving BST structure

8. VISUALIZE TREE
   - Generate DOT format representation of tree
   - Use Graphviz to convert DOT to PNG image
   - Display PNG visualization for verification
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "TreeNode.h"
#include "AbstractStack.h"
#include "ArrayStack.h"
#include "BinaryTree.h"
#include "BinarySearchTree.h"
#include "Node.h"
#include "DoublyLinkedList.h"
#include "ConcreteDoublyLinkedList.h"

template <class T>
void to_dot(TreeNode<T> *node, ofstream &out) {
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

/**
 * Generates PNG visualization of tree using Graphviz
 */
template <class T>
void visualize_tree(TreeNode<T> *root, const string &filename = "tree") {
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

/***** GLOBAL FUNCTION PROTOTYPES *****/
void readWordsFromFile(BinarySearchTree<string>& words, string fileName);
void writeWordsToFile(TreeNode<string> *root, ofstream &out);
string convertCase(string word);
void convertCaseInTree(TreeNode<string> *root);


/***** Driver Function Main *****/
int main() {

    // STEP 1: Initialize BST and specify input file
    BinarySearchTree<string> words;
    string fileName = "words.txt";

    // STEP 2: Read all words from file and insert into BST
    readWordsFromFile(words, fileName);
    
    // STEP 3: Optional - Visualize tree after insertion
    // visualize_tree(words.getRoot());
    
    // STEP 4: Write all words to output file in sorted order
    string outputFileName = "output.txt";
    ofstream out(outputFileName);
    writeWordsToFile(words.getRoot(), out);

    // STEP 5: Test search operation
    cout << endl;
    if (words.search("phantom")) {
	cout << "Word found" << endl;
    } else {
	cout << "Word not found" << endl;
    }

    // STEP 6: Remove word from BST
    cout << endl;
    cout << "Removing ANCHOR" << endl;
    words.remove("ANCHOR");
    words.display(); 
    cout << endl;
    // visualize_tree(words.getRoot());

    // STEP 7: Insert new word into BST
    cout << endl;
    cout << "Inserting GOKU" << endl;
    words.insert("GOKU");
    words.display(); 
    cout << endl;
    // visualize_tree(words.getRoot());

    // STEP 8: Convert case for all words in tree
    cout << endl;
    cout << "Converting case for all words: " << endl;
    convertCaseInTree(words.getRoot());
    words.display(); 
    cout << endl;

    return 0;
}

/***** GLOBAL FUNCTION CODE *****/

/**
 * Converts case for single word (uppercase ↔ lowercase)
 */
string convertCase(string word) {
    for (char &s : word) {
	s = (s >= 65 && s <= 90) ? s + 32 : s - 32;
    }
    return word;
}

/**
 * Recursively converts case for all words in BST using in-order traversal
 */
void convertCaseInTree(TreeNode<string> *root) {
    if (root != nullptr) {
	convertCaseInTree(root->left);
	root->data = convertCase(root->data);
	convertCaseInTree(root->right);
    }
}

/**
 * Recursively writes BST words to file in sorted order using in-order traversal
 * In-order: Left → Node → Right produces alphabetically sorted output
 */
void writeWordsToFile(TreeNode<string> *root, ofstream &out) {
    if (root != nullptr) {
	writeWordsToFile(root->left, out);
	out << root->data << endl;
	writeWordsToFile(root->right, out);
    }
}

/**
 * Reads words from file one by one and inserts into BST
 * BST automatically maintains alphabetical ordering
 */
void readWordsFromFile(BinarySearchTree<string>& words, string fileName) {
    ifstream in(fileName);
    string word;

    while (in >> word) {
	words.insert(word);
    }
    in.close();
}
