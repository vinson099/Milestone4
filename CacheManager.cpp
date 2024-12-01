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
    if(_hashTable->getItem(searchKey) != nullptr){
        //create Fifo node and Hash Node
//        Node* newNode = new FifoNode(searchKey, newItem);
//        Node* node = new HashNode(searchKey, newNode);
        
        
        
        
        
        
    }
    
    
    return true;
}
