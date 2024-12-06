//
//  HashTable.cpp
//  week_9
//
//  Created by Franco Barra and Vinson Thai on 10/24/24.
//

#include <stdio.h>
#include <vector>
#include "HashTable.hpp"

/**
 * Default constructor for Hashatable
 *
 * <p>
 * This constructor initalizes and array of pointer of type HashNode. The array is initialize to a fix size and sets each entry to nullptr
 *
 * @return void This constructor does not return a value
 */

HashTable::HashTable(){
    // doing this will set a garbage value (not nullptr) for each entry
    // Learned from ChatGPT
    table = new HashNode*[_HASH_TABLE_SIZE];
    // Initialize each entry to nullptr
    for (int i = 0; i < _HASH_TABLE_SIZE; i++) {
        table[i] = nullptr; 
    }

    numberOfItems = 0;
}

/**
 * Returns an array (table) of HashNode pointers
 *
 *@return Returns a pointer to the array of HashNode pointers
 */

HashNode** HashTable::getTable() {
    return (table);
}

/**
 * Returns the size of the array (table)
 *
 * @return Returns the fix size of the array (table)
 */

int HashTable::getSize(){
    return _HASH_TABLE_SIZE;
}

/**
 * Checks if the hash table is empty
 *
 * @return Returns true if the hash table is empty, false otherwise
 */

bool HashTable::isEmpty(){
    
    return numberOfItems == 0;
}

/**
 * Returns the number of items in the Hash table
 *
 * @return numberOfItems Returns the number of items in the hash table
 */

int HashTable::getNumberOfItems(){
    return numberOfItems;
}

/**
 * Adds a new item to the hash table
 *
 * <p>
 * This method uses a hash function with moodule to create an index. Then the index is use to find the entry in the table and checks if the entry is empty. If empty, a pointer to the node is added at the index. If not empty, a doubly linked list is used to add at the head of the list
 *
 * @param searchKey The key to determine the bucket index
 * @param newItem The hashnode to insert in the hash table
 * @return Returns true if the items are succesfully added
 */
bool HashTable::add(int searchKey, HashNode* newItem){
    int tableIndex = searchKey % _HASH_TABLE_SIZE;
    HashNode* currentNode = table[tableIndex];
    
    if(table[tableIndex] == nullptr){
        //if table entry is empty
        table[tableIndex] = newItem;
    }
    else{
        //adds at the head of the bucket
        currentNode->prev = newItem;
        newItem->next = currentNode;
        table[tableIndex] = newItem;
        // adds at the tail
//        while(currentNode->next != nullptr){
//            currentNode = currentNode->next;
//        }
//        currentNode->next = newItem;
//        newItem->prev = currentNode;
        
    }
    numberOfItems++;
    return true;
}

/**
 * Removes the most recent node from the hash table with the given key
 *
 * <p>
 * This methods uses the hash funciton to find the entry in the table. Then uses the
 *  key to traverse the doubly link list, until it finds the node. If node is found,
 *  the node is deleted and the adjecent nodes are linked together
 *
 * @param searchKey The key to determine the bucket in the list
 * @return Returns true if the node was removed successfully, false otherwise
 */
bool HashTable::remove(int searchKey){
    int tableIndex = searchKey % _HASH_TABLE_SIZE;
    HashNode* currentNode = table[tableIndex];
    
    while(currentNode != nullptr && currentNode->key != searchKey){
        currentNode = static_cast<HashNode*>(currentNode->next);
    }
    
    // check if searchKey was found in bucket
    if(currentNode == nullptr){
        return false;
    }
    // check if searchKey is found at head, updates the list by removing the head
    // and table[i] points to new head
    if(currentNode->prev == nullptr){
        table[tableIndex] = static_cast<HashNode*>(currentNode->next);
        if(table[tableIndex] != nullptr){
            table[tableIndex]-> prev = nullptr;
        }
    }
    // check if searchKey is found at tail
    else if(currentNode->next == nullptr){
        currentNode->prev->next = nullptr;
        //delete currentNode;
    }
    // check if searchKey is found in the body of list
    else{
        currentNode->prev->next = currentNode->next;
        currentNode->next->prev = currentNode->next;
        //delete currentNode;
    }
    delete currentNode;
    numberOfItems--;
    return true;
    
    
}

/**
 * Clears all the items from the hash table, deleting each node
 *
 * <p>
 * This method uses a for loop to check each entry in the hash table.
 * If the entry is not null, a while loop is used to traverse the list and delete
 * each node. The numberOfItems is set to 0.
 *
 */
void HashTable::clear(){
    HashNode* current = nullptr;
    HashNode* nodeToDelete = nullptr;
    for(int i = 0; i < _HASH_TABLE_SIZE; i++){
        if(table[i] != nullptr){
            current = table[i];
            while(current != nullptr){
                nodeToDelete = current;
                current = static_cast<HashNode*>(current->next);
                delete nodeToDelete;
            }
        }
        table[i] = nullptr;
    }
    numberOfItems = 0;
}

/**
 * Returns a pointer to the hash node with the given key
 *
 * <p>
 * This methods uses the hash funciton to find the entry in the table.
 * It then uses a while loop to traverse the bucket and find the node with
 * the given key
 *
 * @param searchKey The key to determine the bucket in the key
 * @return currentNode Returns a pointer to the node
 */
HashNode* HashTable::getItem(int searchKey){
    // get the hash bucket and the current node to traverse the bucket
    int tableIndex = searchKey % _HASH_TABLE_SIZE;
    HashNode* currentNode = table[tableIndex];

    // traverse bucket
    while(currentNode != nullptr){
        // if current searchKey exists in our hashtable
        if(searchKey == currentNode -> key){
            return currentNode;
        }
        currentNode = static_cast<HashNode*>(currentNode -> next);
    }

    // if we cant find the key
    return nullptr;
}


/**
 * Checks if an item with the specified key exists in the hash table.
 *
 * @param searchKey The key of the item to search for.
 * @return True if the item exists; false otherwise.
 */
bool HashTable::contains(int searchKey){
    // get the hash bucket and the current node to traverse the bucket
    int tableIndex = searchKey % _HASH_TABLE_SIZE;
    HashNode* currentNode = table[tableIndex];
    
    // traverse bucket
    while(currentNode != nullptr){
        // if current searchKey exists in our hashtable
        if(searchKey == currentNode -> key){
            return true;
        }
        currentNode = static_cast<HashNode*>(currentNode -> next);
    }
    
    // if we cant find the key
    return false;
}
