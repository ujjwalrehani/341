// Ujjwal Rehani
// CMSC 341
// HashTable.cpp
// 
//

#include <iostream>
#include <iomanip>
#include <string.h>
#include <stdexcept>
#include <stdlib.h>

#include "HashTable.h"
#include "primes.h"
using namespace std ;

char * const HashTable::DELETED  = (char *) 1 ;

int HashTable::BS_nextPrime(int lower, int upper, int key)
{
       int position;
       position = ( lower + upper) / 2;

       while((primes[position] != key) && (lower <= upper))
       {
           if (primes[position] < key)
               lower = position + 1;    
           else                                                
               upper = position - 1;     
           position = (lower + upper) / 2;
       }
       if (lower <= upper)
           return key;
       else
           return primes[lower];
}

unsigned int HashTable::hashCode(const char *str) {  // Generate the hash code of the str

   unsigned int val = 0 ;
   const unsigned int thirtyThree = 33 ;  // magic number from textbook

   int i = 0 ;
   while (str[i] != '\0') {
      val = val * thirtyThree + str[i] ;
      i++ ;
   }
   return val ;
}

int HashTable::h(const char *str, int HTSize) {     // Hash Function
    return hashCode(str)%HTSize; 
}

void HashTable::moveacluster(int code) {   // move a cluster from old H to current H
    int pos, pos1;
    //cout << "move code = " << code << endl;
    if  (HashSize_Old * 100  <= TableSize_Old * 3) {   // if the number of items in the old table has dropped below 3%?
                      
        for (int k = 0; k < TableSize_Old; k++) {      // if yes, copy the remaining in the old HT to the new HT
            if (H_Old[k] != NULL && H_Old[k] != DELETED) {
                pos = h(H_Old[k], TableSize);          // find the slot in the new HT
                int i =1;
                while (H[pos] != NULL && H[pos] != DELETED) {
                    if (strcmp(H[pos], H_Old[k]) == 0) break;  
                    pos = (pos + 1) % TableSize;            
                    i++;
                }
                if (H[pos] == NULL || H[pos] == DELETED)  {
                    H[pos] = H_Old[k];
                    HashSize++;
                    HashSize_Old--;
                }
            }
        }
        delete H_Old;
        TableSize_Old = 0;
        HashSize_Old = 0;
        H_Old = NULL;
    } else {          // if no, only copy the clster to the new HT
        pos1 = code;
        if (H_Old[pos1] != NULL) {
            while (H_Old[pos1] != NULL)
                pos1 = (pos1 - 1) % TableSize_Old;
            pos1 = (pos1 + 1) % TableSize_Old;
        }
        int home, pos;
        while (H_Old[pos1] != NULL) {
            if (H_Old[pos1] != DELETED) {
                pos = home = h(H_Old[pos1], TableSize);
                int i =1;
                while (H[pos] != NULL && H[pos] != DELETED) {
                    if (strcmp(H[pos], H_Old[pos1]) == 0) break;   
                    pos = (home + i) % TableSize;     
                    i++;
                }
                if (H[pos] == NULL || H[pos] == DELETED) {
                    H[pos] = H_Old[pos1];
                    HashSize++;
                    HashSize_Old--;
                }
            }
            H_Old[pos1] = NULL;
            pos1 = (pos1 + 1) % TableSize_Old;
        }
    }
    if (HashSize_Old <= 0) {
        delete H_Old;
        TableSize_Old = 0;
        H_Old = NULL;
    }
}

void HashTable::rehashing() {   // Rehashing
    if (H_Old == NULL) {                // if there is no old H
        H_Old = H;                      // move the current H as the old H
        TableSize_Old = TableSize;
        HashSize_Old = HashSize;
        
        int n = HashSize_Old * 4;       // Make the new H size be 4 times of the number of string in the old H
        TableSize = BS_nextPrime(0, numPrimes-1, n);   // find the next prime that is larger than n
        HashSize = 0;
        H = new char*[TableSize];       // create the new H
        for (int i=0; i<TableSize; i++)
            H[i] = NULL;
        
    } else {            // if there is already a rehashing, merge the current H and the old H as the new H
        char **H3;
        int TS3;
        int HS3;
        int n = (HashSize + HashSize_Old) * 4;   // new H size is 4 times of the number of string in the current H and old H
        TS3 = BS_nextPrime(0, numPrimes-1, n);   // find the next prime that is larger than n
        HS3 = 0;
        int pos;
        H3 = new char*[TS3];             // create the new H
        for (int i=0; i<TS3; i++)
            H3[i] = NULL;
            
        for (int k = 0; k < TableSize; k++) {   // move the current H to the new H
            if (H[k] != NULL && H[k] != DELETED) {
                pos = h(H[k], TS3);       // find H[k]'s slot in the new H
                int i =1;
                while (H3[pos] != NULL) {
                    if (strcmp(H3[pos], H[k]) == 0) break;  
                    pos = (pos + 1) % TS3;            
                    i++;
                }
                if (H3[pos] == NULL)  {
                    H3[pos] = H[k];
                    HS3++;
                }
            }
        }
        delete H;
        for (int k = 0; k < TableSize_Old; k++) {   // move the old H to the new H
            if (H_Old[k] != NULL && H_Old[k] != DELETED) {
                pos = h(H_Old[k], TS3);  // find H_Old[k]'s slot in the new H
                int i =1;
                while (H3[pos] != NULL) {
                    if (strcmp(H3[pos], H_Old[k]) == 0) break;  
                    pos = (pos + 1) % TS3;            
                    i++;
                }
                if (H3[pos] == NULL)  {
                    H3[pos] = H_Old[k];
                    HS3++;
                }
            }
        }
        delete H_Old;
        H_Old = NULL;
        TableSize_Old = 0;
        HashSize_Old = 0;
        
        H = H3;           // move the new H3 as the current H
        TableSize = TS3;
        HashSize = HS3;
    }
}

HashTable::HashTable(int n) {           // default constructor
    if (n > 199999)
        throw std::out_of_range("Hash Table size > 199,999!");
    
    Threshold = 2;      // set threshold as 2 (if the load factor of the table exceeds 0.5), avoid doing division operation
    MaxProbing = 10;
    
    TableSize = BS_nextPrime(0, numPrimes-1, n);
    HashSize = 0;
    H = new char*[TableSize];
    for (int i=0; i<TableSize; i++)
        H[i] = NULL;
    TableSize_Old = 0;
    HashSize_Old = 0;
    H_Old = NULL;
}

HashTable::HashTable(const HashTable& other) {
    /*for (int i=0; i<TableSize; i++) {      // release the hash table if has
        if (H[i] != NULL && H[i] != DELETED)
            free(H[i]); 
    }
    delete H;
    if (H_Old != NULL) {
        for (int i=0; i<TableSize_Old; i++) {  // if rehashing, release the old hash table
            if (H_Old[i] != NULL && H_Old[i] != DELETED)
                free(H_Old[i]);
        }
        delete H_Old;
    }*/
    
    Threshold = other.Threshold;
    MaxProbing = other.MaxProbing;
    TableSize = other.TableSize;
    HashSize = other.HashSize;
    H = new char*[TableSize];
    for (int i=0; i<TableSize; i++) {
        if (other.H[i] == NULL || other.H[i] == DELETED)
            H[i] = other.H[i];
        else
            H[i] = strdup(other.H[i]);
    }
    TableSize_Old = other.TableSize_Old;
    HashSize_Old = other.HashSize_Old;
    H_Old = NULL;
    if (other.H_Old != NULL) {
        H_Old = new char*[TableSize_Old];
        for (int i=0; i<TableSize_Old; i++) {
            if (other.H_Old[i] == NULL || other.H_Old[i] == DELETED)
                H_Old[i] = other.H_Old[i];
            else
                H_Old[i] = strdup(other.H_Old[i]);
        }
    }
}

HashTable::~HashTable() {                // destructor
    for (int i=0; i<TableSize; i++)      // release the hash table
        if (H[i] != NULL && H[i] != DELETED) free(H[i]); 
    delete H;
    if (H_Old != NULL) {
        for (int i=0; i<TableSize_Old; i++)      // if it is rehashing, release the old hash table
            if (H_Old[i] != NULL && H_Old[i] != DELETED) free(H_Old[i]); 
        delete H_Old;
    }
}

const HashTable& HashTable::operator=(HashTable& rhs) {
    if(this != &rhs)
    {
        for (int i=0; i<TableSize; i++)       // release the hash table if has
            if (H[i] != NULL && H[i] != DELETED) free(H[i]); 
        delete H;
        if (H_Old != NULL) {
            for (int i=0; i<TableSize_Old; i++)   // if rehashing, release the old hash table
                if (H_Old[i] != NULL && H_Old[i] != DELETED) free(H_Old[i]); 
            delete H_Old;
        }
        
        Threshold = rhs.Threshold;
        MaxProbing = rhs.MaxProbing;
        TableSize = rhs.TableSize;
        HashSize = rhs.HashSize;
        H = new char*[TableSize];
        for (int i=0; i<TableSize; i++) {
            if (rhs.H[i] == NULL || rhs.H[i] == DELETED)
                H[i] = rhs.H[i];
            else
                H[i] = strdup(rhs.H[i]);
        }
        TableSize_Old = rhs.TableSize_Old;
        HashSize_Old = rhs.HashSize_Old;
        H_Old = NULL;
        if (rhs.H_Old != NULL) {
            H_Old = new char*[TableSize_Old];
            for (int i=0; i<TableSize_Old; i++) {
                if (rhs.H_Old[i] == NULL || rhs.H_Old[i] == DELETED)
                    H_Old[i] = rhs.H_Old[i];
                else
                    H_Old[i] = strdup(rhs.H_Old[i]);
            }
        }
    }
    return *this;
}

void HashTable::insert(const char *str) {
     
    int home, pos;
    if (H_Old != NULL) {
        home = h(str, TableSize_Old);
        if (H_Old[home] != NULL)
            moveacluster(home);
    }
    pos = home = h(str, TableSize);
    int i = 1;
    while (H[pos] != NULL && H[pos] != DELETED)  // if the current slot is occupied,
    {
        if (strcmp(H[pos], str) == 0) break;     // if the string is already in H, break the look, and not to add it again
        pos = (pos + 1) % TableSize;            // Linear probing
        i++;
    }
    if (H[pos] == NULL || H[pos] == DELETED)     // if find an available slot, add the string to the H
    {
        H[pos] = strdup(str);
        HashSize++;
    }
        
    if (HashSize * Threshold > TableSize || i >= MaxProbing) // if the load factor of the table exceeds 0.5 or probing is 10 or over
    {   rehashing();                         // do rehasing
        if (H_Old != NULL) moveacluster(home);
    }
}

bool HashTable::find(const char *str) {
    int home, pos;
    if (H_Old != NULL) {
        home = h(str, TableSize_Old);
        if (H_Old[home] != NULL)
            moveacluster(home);
    }
    pos = home = h(str, TableSize);
    int i = 1;
    while (H[pos] != NULL && (H[pos] == DELETED || strcmp(H[pos], str) != 0)) {
        pos = (pos + 1) % TableSize;
        i++;
    }
    bool ret = false;
    if (H[pos]!=NULL && strcmp(H[pos], str) == 0) 
        ret = true;

    if (HashSize * Threshold > TableSize || i >= MaxProbing) // if the load factor of the table exceeds 0.5 or probing is 10 or over
    {   rehashing();                         // do rehasing
        if (H_Old != NULL) moveacluster(home);
    }
    
    return ret;
}

char * HashTable::remove(const char *str) {
    int home, pos;
    char *pt;
    
    if (H_Old != NULL) {
        home = h(str, TableSize_Old);
        if (H_Old[home] != NULL)
            moveacluster(home);
    }
    
    pos = home = h(str, TableSize);
    int i = 1;
    while (H[pos] != NULL && (H[pos] == DELETED || strcmp(H[pos], str) != 0)) {
        pos = (pos + 1) % TableSize;
        i++;
    }
    
    pt = NULL;
    if (H[pos] != NULL) {
        pt = H[pos];
        H[pos] = DELETED;
        HashSize--;
    }
    
    if (HashSize * Threshold > TableSize || i >= MaxProbing) // if the load factor of the table exceeds 0.5 or probing is 10 or over
    {   rehashing();                         // do rehasing
        if (H_Old != NULL) moveacluster(home);
    }
    
    return pt;
}

bool HashTable::isRehashing() {
    if (H_Old == NULL)
        return false;
    else
        return true;
}

int HashTable::tableSize(int table) {
    if (table == 0)
        return TableSize;
    else
        return TableSize_Old;
}

int HashTable::size(int table) {
    if (table == 0)
        return HashSize;
    else
        return HashSize_Old;
}

const char * HashTable::at(int index, int table) {
    if (table == 0) {
        if (index < 0 || index >= TableSize)
            throw std::out_of_range("Index is out of range!");
        return H[index];
    } else {
        if (index < 0 || index >= TableSize_Old)
            throw std::out_of_range("Index is out of range!");
        return H_Old[index];
    }
}

void HashTable::dump() {
    int tn = 1;
    if (H_Old != NULL) {
        cout << "HashTable #" << tn << ": size = " << HashSize_Old << ", tableSize = " << TableSize_Old << endl;
        for (int i=0; i<TableSize_Old; i++)
        {
            cout << "H" << tn << "[" << setw(3) << i << "] = ";
            if (H_Old[i] != NULL) {
                if (H_Old[i] == DELETED)
                    cout << "DELETED";
                else
                    cout << H_Old[i] << " (" << h(H_Old[i], TableSize_Old) << ")"; 
            }
            cout << endl;
        }
        tn++;
        cout << endl;
    }
    cout << "HashTable #" << tn << ": size = " << HashSize << ", tableSize = " << TableSize << endl;
    for (int i=0; i<TableSize; i++)
    {
        cout << "H" << tn << "[" << setw(3) << i << "] = ";
        if (H[i] != NULL) {
            if (H[i] == DELETED)
                cout << "DELETED";
            else
                cout << H[i] << " (" << h(H[i],  TableSize) << ")"; 
        }
        cout << endl;
    }
    
}
