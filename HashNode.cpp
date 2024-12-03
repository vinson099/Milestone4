//
//  HashNode.cpp
//  week_11
//
//  Created by Franco Barra on 11/13/24.
//

#include <stdio.h>
#include "HashNode.hpp"

HashNode::HashNode(int value) : Node(value), cacheNode(nullptr){}

HashNode::HashNode(int value, Node* newCacheNode) : Node(value), cacheNode(newCacheNode){}

Node* HashNode::getCacheNode(){
    return cacheNode;
}
