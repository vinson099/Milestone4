//
//  FifoNode.cpp
//  week_11
//
//  Created by Franco Barra on 11/13/24.
//

#include <stdio.h>
#include "FifoNode.hpp"

FifoNode::FifoNode(int value) : Node(value), dataValues(nullptr){}

// Note
// new constructor
FifoNode::FifoNode(int value, Data* cacheData) : Node(value), dataValues(cacheData){}

Data::Data(int keyValue, std::string fullName, std::string address, std::string city, std::string state, std::string zip)
    : key(keyValue), fullName(fullName), address(address), city(city), state(state), zip(zip) {
    // Any additional initialization if necessary
}


