//
//  HashNode.cpp
//  week_11
//
//  Created by Franco Barra and Vinson Thai on 11/13/24.
//

#include <stdio.h>
#include "HashNode.hpp"

/**
 * This constructor initalizes a HashNode with the given key
 *
 * @return void This constructor does not return a value
 */
HashNode::HashNode(int value) : Node(value), cacheNode(nullptr){}

/**
 * Modified constructor for Hashtable
 *
 * <p>
 * This constructor initalizes a HashNode with the given key and points to the associated fifoNode within the cachemanager
 *
 * @return void This constructor does not return a value
 */
HashNode::HashNode(int value, Node* newCacheNode) : Node(value), cacheNode(newCacheNode){}

/**
 * Helper method for HashNode to find the associated fifoNode 
 *
 * @return void This method returns a pointer to the fifoNode associated with the current hashNode
 */
Node* HashNode::getCacheNode(){
    return cacheNode;
}
