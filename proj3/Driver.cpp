// File: Driver.cpp
// Author: Ujjwal Rehani
// CMSC 341 Chang

#include <iostream>
#include <stdexcept>
using namespace std ;

#include "LazyBST.h"

const int depthLimit = 30 ;

bool sanityCheck(LazyBST& T, char pos[], int depth, int& key, int& height, int& size, bool report=true) {

   int leftKey, rightKey ;
   int leftHeight=-1, rightHeight=-1 ;
   int leftSize=0, rightSize=0 ;
   bool hasLeft, hasRight ;


   // Try to catch bad BST with cycles
   //
   if (depth >= depthLimit) {
      throw out_of_range("Depth limit reached. Something looks wrong!\n") ;
   }


   // Is does current position have a node?
   //
   if ( ! T.locate(pos, key) ) return false ;


   // Add extra '\0' so pos string can be extended
   //
   pos[depth+1] = '\0' ;


   // Recursively checks left subtree.
   //
   pos[depth] = 'L' ;
   hasLeft= sanityCheck(T, pos, depth+1, leftKey, leftHeight, leftSize, report) ;


   // Recursively checks right subtree.
   //
   pos[depth] = 'R' ;
   hasRight= sanityCheck(T, pos, depth+1, rightKey, rightHeight, rightSize, report) ;


   pos[depth] = '\0' ;  // restores pos[]


   // Compute current node's height and size
   //
   height = 1 + ( (leftHeight > rightHeight) ? leftHeight : rightHeight ) ; 
   size = 1 + leftSize + rightSize ;


   // Check key ordering for left child
   //
   if (hasLeft && leftKey >= key) {
      cerr << "\nIn position " << pos 
           << " (key=" << key << ",height=" << height << ",size=" << size << ")"
           << " left child's key not less than current node's key:"
	   << leftKey << " " << key << endl ;
   }


   // Check key ordering for right child
   //
   if (hasRight && rightKey <= key) {
      cerr << "\nIn position " << pos 
           << " (key=" << key << ",height=" << height << ",size=" << size << ")"
           << " right child's key not greater than current node's key:"
	   << rightKey << " " << key << endl ;
   }


   // Check relative sizes of left and right subtrees.
   // Note: leftSize == 2* rightSize (or vice versa) is not an error
   //    because it is up to the next insert or remove to fix.
   //
   if (height > 3) {
      if (leftSize > 2 * rightSize) {
	 cerr << "\nIn position " << pos 
              << " (key=" << key << ",height=" << height << ",size=" << size << ")"
	      << " left subtree too big: "
	      << leftSize << " " << rightSize << endl ;
      }
      if (rightSize > 2 * leftSize) {
	 cerr << "\nIn position " << pos 
              << " (key=" << key << ",height=" << height << ",size=" << size << ")"
	      << " right subtree too big: "
	      << leftSize << " " << rightSize << endl ;
      }

   }


   // Give stats for current node, if so desired.
   //

   if (report) {
      cout << "\n Node report on position " << pos << " :" << endl ;
      cout << "   key = " << key 
	   << "   height = " << height 
	   << "   size = " << size 
	   << endl ;

      if (hasLeft) {
	 cout << "   left child key = " << leftKey << endl ;
      } else {
	 cout << "   no left child\n" ;
      }

      if (hasRight) {
	 cout << "   right child key = " << rightKey << endl ;
      } else {
	 cout << "   no right child\n" ;
      }
   }

   return true ;
}

int main() {

   LazyBST T ;

   T.insert(70) ;
   T.inorder() ; cout << endl ;

   T.insert(30) ;
   T.inorder() ; cout << endl ;

   T.insert(110) ;

   T.inorder() ; cout << endl ;

	T.insert(14) ;

   T.insert(7) ;
   T.insert(25) ;
   
   int n;
   
   n = 14 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ;  
   
   n = 19 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
   n = 101 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
   n = -32 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ;
   
    T.insert(3) ; T.insert(32) ; 
   T.insert(9) ; T.insert(18) ; 
   
    T.insert(3) ; T.insert(32) ; 
   T.insert(9) ; T.insert(18) ; 
   
   
   n = 3  ;
   cout << "Find " << n << endl ;
   if ( T.find(n) ) { 
      cout << "found = " << n << endl ;
   } else {
      cout << "did not find = " << n << endl ;
   }
   cout << endl;
   
   n = 21  ;
   cout << "Remove " << n << endl ;
   if ( T.remove(n) ) { 
      cout << n << " removed\n" ;
   } else {
      cout << n << " not found\n" ;
   }
   T.inorder() ; cout << endl ;
   
   LazyBST T1 ;

   T1.insert(14) ;

   T1.insert( 7) ;
   T1.insert(25) ;

   T1.insert( 3) ; T1.insert(32) ; 
   T1.insert( 9) ; T1.insert(18) ; 

   T1.insert( 1) ; T1.insert(44) ;
   T1.insert(12) ; T1.insert(15) ; 
   T1.insert( 4) ; T1.insert(29) ; 
   T1.insert(10) ; T1.insert(21) ;
   
    cout << "Original T1:         " ;
   T1.inorder() ; cout << endl ;

   // Use copy constructor
   LazyBST *Tptr = new LazyBST(T1) ;

   cout << "Copied T1:           " ;
   Tptr->inorder() ; cout << endl; 
   
   LazyBST T2 ;

   T2.insert(50) ;
   T2.insert(25) ; T2.insert(75) ;
   // T2.inorder() ; cout << endl ;

   T2 = *Tptr ;
   cout << "Second copy:         " ;
   T2.inorder() ; cout << endl ; 

   cout << "Delete first copy...\n" ;
   delete Tptr ;

   cout << "Recheck original:    " ;
   T1.inorder() ; cout << endl ;
   cout << "Recheck second copy: " ;
   T2.inorder() ; cout << endl ; 
   
   T.inorder() ; cout << endl ;

   int key = 9999 ;
   bool ans ;
   const char *str ;

   ans = T.locate(str="", key=-1) ;
   cout << str << ": " << ans << " " << key << endl ;

   ans = T.locate(str="LL", key=-1) ;
   cout << str << ": " << ans << " " << key << endl ;

   ans = T.locate(str="LLR", key=-1) ;
   cout << str << ": " << ans << " " << key << endl ;

   ans = T.locate(str="RLLR", key=-1) ;
   cout << str << ": " << ans << " " << key << endl ;

   char pos[depthLimit] ;
   pos[0] = '\0' ;
   int height, size ;

   // Do check
   //
   cout << "First a small test...\n" ;
   sanityCheck(T,pos,0,key,height,size) ;
   cout << "\n\nSmall tree has root with key=" << key
        << ", height=" << height 
	<< ", size=" << size 
	<< endl; 
   
   


}