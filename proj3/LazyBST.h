// File: LazyBST.h
// Author: Ujjwal Rehani
// CMSC 341 Chang
// 

#ifndef H_LazyBST
#define H_LazyBST

#include <iostream>
using namespace std;

class LazyBST
{
private:
	struct BSTNode
	{
		int data;
		int height;
		int size;
		BSTNode *left;
		BSTNode *right;

	    BSTNode() { left = right = NULL; }
	    BSTNode(const int e, BSTNode* lt=NULL, BSTNode* rt=NULL)
	    { data = e; height = 0; size = 1; left = lt; right = rt; }
	};

	BSTNode *root;  // root pointer of the tree
	
	void clearBST(BSTNode* p);                             // Delete all nodes in the subtree at p
	BSTNode* copyTree(const BSTNode* sroot);               // Copy a source tree to the current tree
	void insertBST(BSTNode* &p, int key);                  // Insert the node key into subtree p with recursion
	int minValue(BSTNode* p);                              // Find the smallest value under subtree p
	BSTNode* remove(BSTNode* p, int key, bool &end);       // Remove the node key from subtree p with recursion
	void inorder(BSTNode *p);                              // Print inorder of all nodes in subtree p
	int height(BSTNode *p);                                // Calculate the height of every node in subtree at p
	int nodeCount(BSTNode *p);                             // Count the number of nodes for all nodes in subtree at p
	bool findBST(BSTNode* p, int key);                     // find the key node from the subtree at root p
	int BSTToArray(BSTNode *p, int arr[], int pos);        // Convert a BST at node p to an array
	BSTNode* ArrayToBST(int arr[], int start, int end);    // Convert an array to a BST, return a pointer to the rot
	void rebalance(BSTNode* &p);                           // rebalance subtree at node p
public:
	LazyBST();                                             // Default constructor
	LazyBST(const LazyBST& other);                         // Copy constructor
	~LazyBST();                                            // Destructor
	const LazyBST& operator=(const LazyBST& rhs);          // Overload the assignment operator
	void insert(int key);                                  // Insert the key into the tree
	bool remove(int key);                                  // Remove the key from the tree
	bool find(int key);                                    // Find the key node in the tree with a loop implementation
	bool find2(int key);                                   // Find the key node in the tree with the recursion implementation
	void rebalance();                                      // Rebalance the tree
	void inorder();                                        // Print all nodes in inorder in the tree
	bool locate(const char *position, int& key);           // Locate a node and return its key
	

};

#endif
