//
//  CacheManager.cpp
//  week_11
//
//  Created by Franco Barra on 11/14/24.
//

#include <stdio.h>
#include "CacheManager.hpp"

CacheManager::CacheManager(size_t capacity) : _maxSize(capacity), _curSize(0), _fifoCache(new DoublyLinkedList()), _hashTable(new HashTable()){}


/**
 * @return Returns a pointer to a the hashtable within the cachemanager
 */
HashTable* CacheManager::getTable(){
    return _hashTable;
}

/**
 * @return Returns a pointer to a the doubly linked list within the cachemanager
 */
DoublyLinkedList* CacheManager::getFifoList(){
    return _fifoCache;
}

/**
 * Returns a node with the given key, and moves the node to the front of the FifoList
 *
 * @param key The identifier for the HashNode we are trying to find
 * @return Returns a pointer to a hashnode within the cachemanager's hashtable
 */
Node* CacheManager::getItem(int key){
    // gets the hash node associated with the key
    HashNode* retrieved = _hashTable->getItem(key);

    // moves the node to the head when accessed
    Node* retrievedCache = retrieved->getCacheNode();
    _fifoCache->moveToHead(retrievedCache);
    
    return retrieved;
}

/**
 * Returns the amount of nodes within CacheManager
 *
 * @return Returns an integer that represents the size of CacheManager
 */
size_t CacheManager::getSize(){
    return _curSize;
}

/**
 * Tells us if the cacheManager is empty or not
 *
 * @return Returns a boolean of if both the hashTable and fifoCache are empty
 */
bool CacheManager::isEmpty(){
    return _hashTable->isEmpty() && _fifoCache->isEmpty();
}

/**
 * Returns the amount of nodes within CacheManager
 *
 * @return Returns an integer that represents the size of CacheManager
 */
size_t CacheManager::getNumberOfItems(){
    return _curSize;
}

/**
 * Adds a new node to the cacheManager
 *
 * <p>
 * This method checks if the item is already in the cachemanager, and updates the fifoList to have 
 * the node at the head. If the cache is at max capacity, we will delete the last item from the fifo 
 * list and the associated hashNode to make space for the new node. Then we will create a new fifoNode
 * and hashNode and add them to the cache.
 *
 * @param searchKey The key that will be associated to the hashNode when it is created
 * @param newItem The data that the fifoNode will hold
 * @return Returns true if the new node is added successfully 
 */
bool CacheManager::add(int searchKey, Data* newItem){
    
    // first case. check if newItem already exist by using searchKey.
    // check in Hash table. look up is O(1)
    HashNode* existingHashNode = _hashTable->getItem(searchKey);
    if(existingHashNode != nullptr){
        Node* existingFifoNode = existingHashNode->getCacheNode();
        _fifoCache->moveToHead(existingFifoNode);
        return false;
    }
    
    if(_curSize == _maxSize ){
        //get tail of fifo list
        //get key from tail
        Node* fifoNodeToDelete = _fifoCache->getTail();
        int key = fifoNodeToDelete->getKey();
        
        // use key to find node in hashtable and delete
        //HashNode* hashNodeToDelete = _hashTable->getItem(key);
        _hashTable->remove(key);
        _fifoCache->deleteTailNode();
        
    }
    
    //create Fifo node and Hash Node
    FifoNode* newFifoNode = new FifoNode(searchKey, newItem);
    HashNode* newHashNode = new HashNode(searchKey, newFifoNode); 
        
    //add both into each data structure
    _hashTable->add(searchKey, newHashNode);
    _fifoCache->insertAtHead(newFifoNode);
    
    //update current size of cachemanager
    _curSize++;

    
    return true;
}

/**
 * Removes a node from the cacheManager
 *
 * <p>
 * This method searches if the node we want to delete exists within the cache. 
 * If it exists, we will remove it by retrieving the hashNode and the fifoNode 
 * associated with it. Then we delete both of them and decrement our size.
 *
 * @param searchKey The key value of the node we want to delete
 * @return Returns true if a node with the given parameter is deleted
 */
bool CacheManager::remove(int searchKey){
    
    // look for hashNode in hash table using searchKey
    HashNode* hashNodeToRemove = _hashTable->getItem(searchKey);
    
    // if node exist
    if(hashNodeToRemove != nullptr){
        // Remove from fifo list
        Node* fifoNodeToRemove = hashNodeToRemove->getCacheNode();
        _fifoCache->deleteNode(fifoNodeToRemove);
        
        //remove from hashtable
        _hashTable->remove(searchKey);
        
        //update current size
        _curSize--;
        return true;
    }


    return false;
}

/**
 * Clears the Cachemanager
 *
 * <p>
 * Will call the deleteList function for the doubly linked list, and clear function for the hashtable. Then resets the size to zero
 *
 * @param value The value we are looking for within each node
 */
void CacheManager::clear(){
    //clear doubly linked list
    _fifoCache->deleteList();
    
    //clear hashtable
    _hashTable->clear();
    
    //clear size
    _curSize = 0;
}


/**
 * Checks to see if CacheManager contains a value, and if it does, move it to the front
 *
 * <p>
 * This method uses the fifoCache to search for a value, returns whether or not the node was found after traversal. 
 *
 * @param value The value we are looking for within each node
 * @return Returns true if a node with the given value is found
 */
bool CacheManager::contains(int value){
    //check if item is in cachemanager
    //implementation is done by DoublyLinkedList
    Node* foundItem = _fifoCache->findNode(value);

    //check we find the item, move it to the front and return true
    _fifoCache->moveToHead(foundItem);
    return foundItem != nullptr;
}
 
