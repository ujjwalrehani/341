// Ujjwal Rehani
// CMSC 341
// HashTable.h
//

class HashTable {
    static char * const DELETED ;

public:
    HashTable(int n=101);
    HashTable(const HashTable& other);
    ~HashTable();
    const HashTable& operator=(HashTable& rhs);
    void insert(const char *str);
    bool find(const char *str);
    char * remove(const char *str);
    bool isRehashing();
    int tableSize(int table=0);
    int size(int table=0);
    const char * at(int index, int table=0);
    void dump();
    
private:
    int BS_nextPrime(int lower, int upper, int key);    // Use Binary Search to find the next prime number
    unsigned int hashCode(const char *str);             // Hash Code
    int h(const char *str, int HTSize);                 // Hash Function
    void moveacluster(int code);                        // Move a cluster from old H to current H
    void rehashing();                                   // Incremental Re-Hashing H

    int Threshold;
    int MaxProbing;
    int TableSize;         // Hash table size (capacity)
    int HashSize;          // Number of strings in the Hash table
    char **H;              // the Hash table
    int TableSize_Old;     // Old Hash table size
    int HashSize_Old;      // Number of strings in the Old Hash table
    char **H_Old;          // the Old Hash table
};
