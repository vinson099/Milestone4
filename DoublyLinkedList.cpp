/**
 * @file DoublyLinkedList.cpp
 * @brief This file contains the implementation of the DoublyLinkedList class.
 *
 * @author ChatGPT used to provide an example of file,class and methods header
 * @author Franco Barra and Vinson Thai
 * @date 10/03/24
 */

#include <vector>
#include "DoublyLinkedList.hpp"


/**
 * Default constructor for a new instance of DoublyLinkedList.
 *
 * <p>
 * This construtor initializes the head and tail pointer of the list to null.
 * Which indicates that the list is currently empty
 *
 *@return void This constructor does not return a value
 *
 */
DoublyLinkedList::DoublyLinkedList(): head(nullptr), tail(nullptr){}

/**
 * Inserts a new node at the head of the DoublyLinkedList.
 *
 * <p>
 * This method checks if the list is empty. If it is, the new node becomes
 * both the head and the tail of the list. If the list is not empty, the new
 * node is added at the beginning, and the previous head node's previous pointer
 * is updated to point to the new node
 * 
 *@param newNode A node pointer to the node to be inserted at the head of the list.
 *@return void This method does not return a value.
 *
 */
void DoublyLinkedList::insertAtHead(Node* newNode){
    // check if list is empty.
    if(head == nullptr){
        head = newNode;
        tail = newNode;
    }
    // add the new node at the beginning of the list
    else{
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

/**
 * Inserts new node at the tail of the DoublyLinkedList.
 *
 * <p>
 * This method checks if the list is empty. If it is, the new node becomes
 * the new head and tail of the list. If the list is not empty, the new
 * node is added at te end, and the previous tail node's next pointer is updated to point to the new node
 *
 *@param newNode A node pointer to the node to be inserted at the tail of the list.
 *@return void This method does not return a value.
 *
 */
void DoublyLinkedList::insertAtTail(Node* newNode){
    // if list is empty, new node becomes the new head and tail of the list
    if(head == nullptr){
        head = newNode;
        tail = newNode;
    }
    // if list is not empty, new node is added a the end of the list
    else{
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
}

/**
 * Searches for a node in the DoublyLinkedList that contains the given value
 *
 *<p>
 * This method iterates through the list starting from the head and
 * checks each node's data. If the a node with the specefied value is found,
 * a pointer to that node is returned. If no matching node is found, the method returns null.
 *
 *@param value The value to search for in the list
 *@return current A pointer to the node containing the specified value, or nullptr if no node exist in the list.
 */

Node* DoublyLinkedList::findNode(int value){
    Node* current = head;
    
    // iterates through the list searching for node's data that matches the given value
    while(current != nullptr){
        if(current->key == value){
            return current;
        }
        current = current->next;
    }
    
    // if no match, return nullprt
    return nullptr;
}

/**
 * Deletes a specified node from the DoublyLinkedList.
 *
 * <p>
 * This method does not check wheter the node exist within the list.
 * It assumes node exist in the list. It removes a node from the list and adjust the
 * pointers accordingly. If the node is the head, the head pointer is updated.
 * If the node is the tail, the tail pointer is updated. If the node is in the middle,
 * it is disconnected from the list, and the 2 adjecent nodes are connected. Then
 * the node is deleted. If node is null, the method does nothing.
 *
 *@param existingNode A pointer to the node to be deleted from the list.
 *@return void The method does not return a value.
 */
void DoublyLinkedList::deleteNode(Node* existingNode){
    //if node is null, return
    if(existingNode == nullptr){
        return;
    }
    // if node = head, move head pointer to next node
    else if(existingNode == head){
        head = existingNode->next;
        head->prev = nullptr;
    }
    // if node = tail, move tail pointer to previous node
    else if(existingNode == tail){
        tail = existingNode->prev;
        tail->next = nullptr;
    }
    // if node is in the middle/body of the list, disconnet specify node from the list and connect the 2 adjacent nodes
    else{
        existingNode->prev->next = existingNode->next;      // duplicate code
        existingNode->next->prev = existingNode->prev;
    }
    //delete node
    delete existingNode;
}

/**
 * Moves specified node to the head of the DoublyLinkedList.
 *
 * <p>
 *  This method moves a specified node from any position in the list to the head. If the node
 *  does not exist or is the head, the method does nothing.
 *  If node is the tail, the tail poiter is updated. If node is in the body of the list,
 *  it is disconnected from the list by updating the two pointers of the adjacent nodes.
 *
 * @param existingNode A pointer to the node to be moved to the head of the list.
 * @return void This method does not return a value.
 */
void DoublyLinkedList::moveToHead(Node* existingNode){
    //checks if node is null or if node is already head node
    if(existingNode == nullptr || head == existingNode){
        return;
    }
    // if node = tail, move tail pointer to previous node
    else if(existingNode == tail){
        tail = existingNode->prev;
        tail->next = nullptr;
    }
    // if node is in the middle/body of the list, disconnet specify node from the list and connect the 2 adjacent nodes
    else{
        existingNode->prev->next = existingNode->next;      // duplicate code
        existingNode->next->prev = existingNode->prev;
    }
    // Adds node to the head of the list and makes necessary connections between nodes
    existingNode->prev = nullptr;   // sets prev to null
    existingNode->next = head;      // connects existingNode to node pointed by head
    head->prev = existingNode;      // connects old head prev to existingNode
    head = existingNode;            // sets head pointer to existingNdde
}

/**
 * Moves specified node to the tail of the DoublyLinkedList.
 *
 * <p>
 *  This method moves a specified node from any position in the list to the tail. If the node
 *  does not exist or is the tail, the method does nothing.
 *  If node is the head, the head poiter is updated. If node is in the body of the list,
 *  it is disconnected from the list by updating the two pointers of the adjacent nodes.
 *
 * @param existingNode A pointer to the node to be moved to the tail of the list.
 * @return void This method does not return a value.
 */
void DoublyLinkedList::moveToTail(Node* existingNode){
    //checks if node is null or if node is already tail node
    if(existingNode == nullptr || tail == existingNode){
        return;
    }
    // if node = head, move head pointer to next node
    else if(existingNode == head){
        head = existingNode->next;
        head->prev = nullptr;
    }
    // if node is in the middle/body of the list, disconnet specify node from the list and connect the 2 adjacent nodes
    else{
        existingNode->prev->next = existingNode->next;      // duplicate code
        existingNode->next->prev = existingNode->prev;
    }
    // Adds node to the tail of the list and makes necessary connections between nodes
    existingNode->next = nullptr;   // sets next to null
    existingNode->prev = tail;      // connects existingNode to node pointed by tail
    tail->next = existingNode;      // connects old tail next to existingNode
    tail = existingNode;            // sets tail pointer to existingNode
}


/**
 * Deletes the head node of the DoublyLinkedList.
 *
 * <p>
 * This method removess the head node from the list. If the list is empty,
 * the method does nothing. A pointer to the node to be deleted is created
 * and the head is updated to point to the next node. If the updated head is not empty,
 * its prev pointer is updated to nullptr. If the list is empty, the tail is updated to
 * nullptr. The original head node is deleted.
 *
 *@return void This method does not return a value.
 */
void DoublyLinkedList::deleteHeadNode(){
    if(head == nullptr){
        return;
    }
    Node* nodeToDelete = head;
    head = head->next;
    
    if(head != nullptr){
        head->prev = nullptr;
    }
    else{
        tail = nullptr;
    }
    delete nodeToDelete;
    
}

/**
 * Deletes the tail node of the DoublyLinkedList.
 *
 * <p>
 * This method removess the tail node from the list. If the list is empty,
 * the method does nothing. A pointer to the node to be deleted is created
 * and the tail is updated to point to the previous node. If the updated tail is not empty,
 * its nect pointer is updated to nullptr. If the list is empty, the head is updated to
 * nullptr. The original tail node is deleted.
 *
 *@return void This method does not return a value.
 */
void DoublyLinkedList::deleteTailNode(){
    if(tail == nullptr){
        return;
    }
    Node* nodeToDelete = tail;
    tail = tail->prev;
    if(tail != nullptr){
        tail->next = nullptr;
    }
    else{
        head = nullptr;
    }
    delete nodeToDelete;
}

/**
 * Deletes all the nodes in the DoublyLinkedList.
 *
 * <p>
 * This method uses a while loop to iterate through the list, starting at the head and
 * deletes each node one by one until the entire list is cleared. After all nodes
 * are deleted, the head and tail pointers are set to nullptr.
 *
 * @return void this method does not return a value
 */
void DoublyLinkedList::deleteList(){
    Node* current = head;
    
    while(current != nullptr){
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
    tail = nullptr;
    //std::cout << "list deleted" << std::endl;
}


Node* DoublyLinkedList::getHead(){
    return head;
}

// modified .hpp. added isEmpty()
bool DoublyLinkedList::isEmpty(){
    return head == nullptr;
}


//modified for cache manager
Node* DoublyLinkedList::getTail(){
    return tail;
}
