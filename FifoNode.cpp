//
//  FifoNode.cpp
//  week_11
//
//  Created by Franco Barra on 11/13/24.
//

#include <stdio.h>
#include "FifoNode.hpp"

FifoNode::FifoNode(int value) : Node(value), dataValues(nullptr){}


/**
 * Constructor for the FifoNode
 *
 * <p>
 * This constructor initalizes a FifoNode given a key and a pointer to a Data object
 *
 * @return void This constructor does not return a value
 */
FifoNode::FifoNode(int value, Data* cacheData) : Node(value), dataValues(cacheData){}


/**
 * Constructor for the Data
 *
 * <p>
 * This constructor initalizes the data passed in and creates a Data object 
 *
 * @return void This constructor does not return a value
 */
Data::Data(int keyValue, std::string fullName, std::string address, std::string city, std::string state, std::string zip)
    : key(keyValue), fullName(fullName), address(address), city(city), state(state), zip(zip) {
    // Any additional initialization if necessary
}


