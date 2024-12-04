//
//  CacheManager.cpp
//  week_11
//
//  Created by Franco Barra on 11/14/24.
//

#include <stdio.h>
#include "CacheManager.hpp"

CacheManager::CacheManager(size_t capacity) : _maxSize(capacity), _curSize(0), _fifoCache(new DoublyLinkedList()), _hashTable(new HashTable()){}


// getTable
HashTable* CacheManager::getTable(){
    return _hashTable;
}

// getFifoList
DoublyLinkedList* CacheManager::getFifoList(){
    return _fifoCache;
}

// getItem
Node* CacheManager::getItem(int key){
    return _hashTable->getItem(key);
}

// getSize
size_t CacheManager::getSize(){
    return _curSize;
}

// isEmpty
bool CacheManager::isEmpty(){
    return _hashTable->isEmpty() && _fifoCache->isEmpty();
}

// getNumberOfItems
size_t CacheManager::getNumberOfItems(){
    return _curSize;
}

// add(searchKey, newItem)
bool CacheManager::add(int searchKey, Data* newItem){
    
    // first case. check if newItem already exist by using searchKey.
    // check in Hash table. look up is O(1)
    HashNode* existingHashNode = _hashTable->getItem(searchKey);
    //Node* existingFifoNode = existingHashNode->getCacheNode();    // accessing hashNode's cacheNode here creates bug. access it after checking existingHashNode is not null
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
    HashNode* newHashNode = new HashNode(searchKey, newFifoNode); //not sure about constructor
        
    //add both into each data structure
    _hashTable->add(searchKey, newHashNode);
    _fifoCache->insertAtHead(newFifoNode);
    
    //update current size of cachemanager
    _curSize++;

    
    return true;
}

//  remove(int)
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

//  clear()
void CacheManager::clear(){
    //clear doubly linked list
    _fifoCache->deleteList();
    
    //clear hashtable
    _hashTable->clear();
    
    //clear size
    _curSize = 0;
}

bool CacheManager::contains(int value){
    //check if item is in cachemanager
    //implementation is done by DoublyLinkedList
    Node* foundItem = _fifoCache->findNode(value);
    //check we find the item, return true
    return foundItem != nullptr;
}
 
