//
//  Node.cpp
//  week_11
//
//  Created by Franco Barra on 11/12/24.
//

#include <stdio.h>
#include "Node.hpp"

Node::Node(int keyValue): key(keyValue), prev(nullptr), next(nullptr){}
Node::~Node() {}

//note
// modified code.Added method to get key
int Node::getKey(){
    return key;
}
