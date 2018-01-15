// File: LazyBST.cpp
// Author: Ujjwal Rehani
// CMSC 341 Chang
// 

#include "LazyBST.h"

// clear the subtree 
void LazyBST::clearBST(BSTNode* p)      
{
	if (p == NULL) return;
	clearBST(p->left);
	clearBST(p->right);
	delete p;
}

// Copy a source tree to the current tree
LazyBST::BSTNode* LazyBST::copyTree(const BSTNode* sroot)    
{
    if(sroot == NULL) return NULL;
    BSTNode* newNode = new BSTNode;
    newNode->data = sroot->data;
    newNode->height = sroot->height;
    newNode->size = sroot->size;
    newNode->left = copyTree(sroot->left);
    newNode->right = copyTree(sroot->right);
    return newNode;
}

// insert the key into the subtree p with recursion
void LazyBST::insertBST(BSTNode* &p, int key)   
{
    if (p == NULL) {
       p = new BSTNode(key);
       return;
    }
    rebalance(p);                               // check to see if a rebalance is needed
    
    if (key < p->data)
       insertBST(p->left, key);
    else if (key > p->data)
       insertBST(p->right, key);
    else
        cout << "Duplicated node " << key << " is discarded!" << endl;
}

// Find the smallest value under subtree p
int LazyBST::minValue(BSTNode* p)     
{
    BSTNode* cur = p;
    while (cur->left != NULL)
        cur = cur->left;
    return cur->data;
}

// delete the key from the subtree at p with recursion
LazyBST::BSTNode* LazyBST::remove(BSTNode* p, int key, bool &end)  
{
    if (p == NULL) return p;
 
    rebalance(p);                             // check to see if a rebalance is needed
    
    if (key < p->data)                        // if the key is less than the data in p, move to the left subtree
        p->left = remove(p->left, key, end);    
    else if (key > p->data)                   // if the key is larger than the data in p, move to the right subtree
        p->right = remove(p->right, key, end);
    else                                      // if the key is equal to the data in p, delete the node p
    {
        if (p->left == NULL)                
        {
            BSTNode* pright = p->right;
            delete p;                         // delete the node p
            end = true;                       
            return pright;                    // return the right subtree of p
        }
        else if (p->right == NULL)            
        {
            BSTNode* pleft = p->left;
            delete p;                         // delete the node p
            end = true;                       
            return pleft;                     // return the left subtree of p
        }
 
        // if the node p has two children, find the smallest node in the right subtree, copy the value to p, and delete the smalest node in the right subtree
        int minvalue = minValue(p->right);
        p->data = minvalue;
        p->right = remove(p->right, minvalue, end);
    }
    return p;
}

// do a rebalance at p
void LazyBST::rebalance(BSTNode* &p)	     
{
    if (p->height >= 4) 
    {
        int lSize = 0;
        if (p->left != NULL) lSize = (p->left)->size;
        int rSize = 0;
        if (p->right != NULL) rSize = (p->right)->size;
        if (lSize >= rSize *2 || lSize * 2 <= rSize) 
        {
            int n = p->size;
            //cout << "Rebalance at node " << p->data << " (h=" << p->height << ", s=" << n << ", ls=" << lSize << ", rs=" << rSize << ")" << endl;
            int *array = new int[n];
            BSTToArray(p, array, 0);
            p = ArrayToBST(array, 0, n-1);
            delete array;
        }   
    }
}

// do an inorder at p
void LazyBST::inorder(BSTNode *p)	     
{
    if (p == NULL) return;
    cout << '(';
	inorder(p->left);
	cout << p->data << ':' << p->height << ':' << p->size;
	inorder(p->right);
	cout << ')';
}

// calculate the height of p
int LazyBST::height(BSTNode *p)		    
{
    if (p == NULL) return -1;
	int lh = height(p->left);
	int rh = height(p->right);
	if (lh >= rh)
	   p->height = lh + 1;
	else 
	   p->height = rh + 1;
    return p->height;
}

// calculate the number of nodes in p
int LazyBST::nodeCount(BSTNode *p)		
{
	if (p == NULL) return 0;
	p->size = 1 + nodeCount(p->left) + nodeCount(p->right);
	return p->size;
}

// convert a BST into an array
int LazyBST::BSTToArray(BSTNode *p, int arr[], int pos)       
{
    if (p->left != NULL) {
        pos = BSTToArray(p->left, arr, pos);
    }
    arr[pos++] = p->data;
    if (p->right != NULL) {
        pos = BSTToArray(p->right, arr, pos);
    }
    delete p;
    return pos; 
}

// convert an array into a BST
LazyBST::BSTNode* LazyBST::ArrayToBST(int arr[], int start, int end) 
{
    if (start > end) return NULL;

    int mid = start + (end - start) / 2;
    BSTNode* p = new BSTNode(arr[mid]);

    p->left =  ArrayToBST(arr, start, mid-1);
    p->right = ArrayToBST(arr, mid+1, end);
 
    return p;
}

// Find an item from the subtree with recursion
bool LazyBST::findBST(BSTNode* p, int key) 	
{

	if (p == NULL) return false;
	if (key == p->data) return true;
    if (key < p->data)
       return findBST(p->left, key);
    else
       return findBST(p->right, key);
}

// Default Constructor
LazyBST::LazyBST()                                     
{
    root = NULL;
}

// Copy Constructor
LazyBST::LazyBST(const LazyBST& other){                 
    clearBST(root);
    root = copyTree(other.root);
}

// Destructor
LazyBST::~LazyBST()                                    
{
    clearBST(root);
}

// Overload the assignment operator
const LazyBST& LazyBST::operator=(const LazyBST& rhs)  
{
    if(this != &rhs)
    {
        this->clearBST(root);
        root = copyTree(rhs.root);
    }
    return *this;
}

// Insert the key into the tree
void LazyBST::insert(int key)                        
{
    insertBST(root, key);
    nodeCount(root);
    height(root);
}

// Remove the key from the tree
bool LazyBST::remove(int key)                        
{
    bool end = false;
    root = remove(root, key, end);
    nodeCount(root);
    height(root);
    return end;
}

// Find an item from the tree with loop
bool LazyBST::find(int key) 			            
{	BSTNode *p;
	
	p = root;
	while (p != NULL)
	{	
		if (p->data == key) break;
		if (key < p->data)
		   	 p = p->left;
		else p = p->right;
	}
	if (p == NULL) return false;
	else return true;
}

// Find an item from the tree with recursion
bool LazyBST::find2(int key) 			       
{	
    return findBST(root, key);
}

// Rebalance the tree
void LazyBST::rebalance()                      
{
    rebalance(root);
}

// Print all nodes in inorder in the tree
void LazyBST::inorder()                        
{
    inorder(root);
}

// Locate a node and return its key
bool LazyBST::locate(const char *position, int& key)  
{
    key = -1;
    BSTNode* p = root;
    if (p == NULL) return false;
    
    const char* c = position;
    while (*c != '\0') 
    {
        if (*c == 'L')
        {
            if (p->left == NULL) break;
            p = p->left;
        }
        else if (*c == 'R')
        {
            if (p->right == NULL) break;
            p = p->right;
        }
        else break;
        c++;
    }
    if (*c != '\0') return false;
    key = p->data;
    return true;
}


