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
        return false;
    }
    
    //create Fifo node and Hash Node
    FifoNode* newFifoNode = new FifoNode(searchKey, newItem);
    HashNode* newHashNode = new HashNode(searchKey, newFifoNode); //not sure about constructor
        
    //add both into each data structure
    _hashTable->add(searchKey, newHashNode);
    _fifoCache->insertAtHead(newFifoNode);
    
    return true;
}

//  remove(int)
bool CacheManager::remove(int searchKey){
    //check if item is not in cachemanager using hashtable (lookup is o(1))
    if(!_hashTable->contains(searchKey)){
        return false;
    }

    // //Find node to delete from hashtable
    // Node* nodeToRemove = _hashTable->getItem(searchKey);

    //remove from hashtable
    _hashTable->remove(searchKey);
    //remove from linkedlist


    return true;
}

//  clear()
void CacheManager::clear(){
    //clear doubly linked list
    _fifoCache->deleteList();
    
    //clear hashtable
    _hashTable->clear();
}

bool CacheManager::contains(int value){
    //check if item is in cachemanager
    //implementation is done by DoublyLinkedList
    Node* foundItem = _fifoCache->findNode(value);
    //check we find the item, return true
    return foundItem != nullptr;
}
 