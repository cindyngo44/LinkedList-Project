#pragma once
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class LinkedList{
public:
    struct Node{ //nested class that contains data stored in list, 1 or more ptrs to other nodes
        T data;
        Node *next;
        Node *prev; //if doubly-linked use it

        Node();
    };
    //Constructors/Destruction
    LinkedList();
    LinkedList(const LinkedList<T>& list);
    ~LinkedList();

    //Behaviors
    void PrintForward() const;
    void PrintReverse() const;
    void PrintForwardRecursive(const Node* node) const;
    void PrintReverseRecursive(const Node* node) const;

    //Accessors
    unsigned int NodeCount() const;
    void FindAll(vector<Node*>& outData, const T& value) const;
    const Node* Find(const T& data) const;
    Node* Find(const T& data);
    const Node* GetNode(unsigned int index) const;
    Node* GetNode (unsigned int index);
    Node* Head();
    const Node* Head() const;
    Node* Tail();
    const Node* Tail() const;



    //Insertion
    void AddHead(const T& data);
    void AddTail(const T& data);
    void AddNodesHead(const T* data, unsigned int count);
    void AddNodesTail(const T* data, unsigned int count);
    void InsertAfter(Node* node, const T& data);
     void InsertBefore(Node* node, const T& data);
     void InsertAt(const T& data, unsigned int index);


    //Removal
    bool RemoveHead();
    bool RemoveTail();
    unsigned int Remove(const T&data);
    bool RemoveAt(unsigned int index);
    void Clear();


    //Operators
    const T& operator[](unsigned int index) const;
    T& operator[](unsigned int index);
    bool operator==(const LinkedList<T>& rhs) const;
    LinkedList<T>& operator=(const LinkedList<T>& rhs);


private:
    unsigned int nodeCount;
    Node *head; //ptr to first node in list
    Node *tail; //ptr to last node in the list. *May or may not be used (doubly linked)

};
//node constructor
template<typename T>
LinkedList<T>::Node::Node() {
    next = nullptr;
    prev = nullptr;
}
//linked list default constructor
template<typename T>
LinkedList<T>::LinkedList() {
    nodeCount = 0;
    tail = nullptr;
    head = nullptr;
}
//copy constructor
//pass in the data from other object into this
template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &list) {
    //ptrCounter starts at list head
    Node* ptrCounter = list.head;
    nodeCount = 0;
    //while ptrCounter does not = nullptr it will iterate through
    while(ptrCounter != nullptr){
        T tempData = ptrCounter->data;

        this->AddTail(tempData);

        ptrCounter = ptrCounter->next;
    }
}
//assignment op
template<typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs) {
    //allocate space
    if(nodeCount != 0){
        Clear();
    }
    //ptrCounter starts at list head
    Node* ptrCounter = rhs.head;
    nodeCount = 0;
    //while ptrCounter does not = nullptr it will iterate through
    while(ptrCounter != nullptr){
        T tempData = ptrCounter->data;

        this->AddTail(tempData);

        ptrCounter = ptrCounter->next;
    }
    return *this;
}
//destructor
template<typename T>
LinkedList<T>::~LinkedList() {
    //iterate through pointers and delete
    Node *deleteNodes = head;
    Node *iteration;

    while(deleteNodes != nullptr){
        //keep track of iteration separately and delete deleteNodes
        //then set deleteNodes to next iteration until nullptr is released thus no more ptrs
        iteration = deleteNodes->next;
        delete deleteNodes;
        deleteNodes = iteration;
    }
    //reset current LinkedList variables
    nodeCount = 0;
    tail = nullptr;
    head = nullptr;
}

template<typename T>
void LinkedList<T>::Clear() {
//iterate through pointers and delete
    Node *deleteNodes = head;
    Node *iteration;

    while(deleteNodes != nullptr){
        //keep track of iteration separately and delete deleteNodes
        //then set deleteNodes to next iteration until nullptr is released thus no more ptrs
        iteration = deleteNodes->next;
        delete deleteNodes;
        deleteNodes = iteration;
    }
    //reset current LinkedList variables
    nodeCount = 0;
    tail = nullptr;
    head = nullptr;
}
//print from head
template<typename T>
void LinkedList<T>::PrintForward() const {
    //print data the head, then move on to next node which is the next ptr until hitting null
    Node *printHead = head;
    while(printHead != nullptr){
        cout << printHead->data << endl;
        printHead = printHead->next;
    }
}
//print from tail, reverse of PrintForward
template<typename T>
void LinkedList<T>::PrintReverse() const {
    Node *printTail = tail;
    while(printTail != nullptr){
        cout << printTail->data << endl;
        printTail = printTail->prev;
    }
}
//return node count
template<typename T>
unsigned int LinkedList<T>::NodeCount() const {
    return nodeCount;
}
//create new node at the front of the list
template<typename T>
void LinkedList<T>::AddHead(const T &data) {
    //HEAD = FRONT = INDEX 0
    Node *newNode = new Node();
    //if no nodes in list, then first node's head/tail ptrs are to nullptr
    // while LinkedList's head/tail are to newNode for the next possible new node
    if(nodeCount == 0){
        newNode->data = data;
        head = newNode;
        tail = newNode;
    }
        //null/new head/prev/ (newNode) -next-> _____ tail
    else{
        //newNode data is set, its nextptr = the old head
        //the old head's prevPtr will be newNode
        //new head = newly added newNode
        newNode->data = data;
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    //new node added
    nodeCount++;
}
//create new node at end of list (like AddHead but reverse)
template<typename T>
void LinkedList<T>::AddTail(const T &data) {
    //TAIL = BACK = SIZE OF LIST
    Node *newNode = new Node(); //new node created
    //if no nodes in list, then first node's head/tail ptrs are to nullptr
    // while LinkedList's head/tail are to newNode for the next possible new node
    if(nodeCount == 0){
        newNode->data = data;
        head = newNode;
        tail = newNode;
    }
        // head _____ <-prev- (newNode) null/new tail/next
    else{
        //newNode data is set, its prev ptr = old tail
        //old tail's next ptr will be newNode
        //new tail = newly added newNode
        newNode->data = data;
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    //new node added
    nodeCount++;
}
//given array of values, insert a node for each of those at the beginning of the list, maintaining orig order
template<typename T>
void LinkedList<T>::AddNodesHead(const T *data, unsigned int count) {
    //supposed to be inverse because adding from head
    for(int i = count - 1; i >= 0; i--){
        AddHead(data[i]);
    }
}
//Ditto except adding to the ends
template<typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int count) {
    int j = count;
    for(int i = 0; i < j; i++){
        AddTail(data[i]);
    }
}
//find all nodes which match the passed in parameter value
//store a pointer to that node in the passed in vector
template<typename T>
void LinkedList<T>::FindAll(vector<Node *> &outData, const T &value) const {
    Node *searchNode = head;
    Node *iteration;

    while(searchNode != nullptr){
        iteration = searchNode->next;
        if(searchNode->data == value){
            outData.push_back(searchNode);
        }
        searchNode = iteration;
    }
}
//find first node with the matching data value
//return ptr to node, else no matching nullptr
template<typename T>
const typename LinkedList<T>::Node *LinkedList<T>::Find(const T &data) const {
    bool found= false;
    Node *searchNode = head;
    Node *iteration;

    while(searchNode != nullptr){
        iteration = searchNode->next;
        if(searchNode->data == data){
            found = true;
            return searchNode;
        }
        searchNode = iteration;
    }
    if(!found){
        return nullptr;
    }
}

template<typename T>
typename LinkedList<T>::Node *LinkedList<T>::Find(const T &data) {
    Node *searchNode = head;
    Node *iteration;

    while(searchNode != nullptr){
        iteration = searchNode->next;
        if(searchNode->data == data){
            return searchNode;
        }
        searchNode = iteration;
    }
    return nullptr;
}
//given a index, return a pointer to the node at that index
//throws exception out_of_range if index is out of range
template<typename T>
const typename LinkedList<T>::Node *LinkedList<T>::GetNode(unsigned int index) const {
    Node *searchNode = head;

    if(index >= nodeCount){
        throw out_of_range("");
    }
    for (int i = 0; i <= index - 1; i ++){
        searchNode = searchNode->next;
    }
    return searchNode;
}

template<typename T>
typename LinkedList<T>::Node *LinkedList<T>::GetNode(unsigned int index) {
    Node *searchNode = head;

    if(index >= nodeCount){
        throw out_of_range("");
    }
    for (int i = 0; i <= index - 1; i ++){
        searchNode = searchNode->next;
    }
    return searchNode;
}

template<typename T>
typename LinkedList<T>::Node *LinkedList<T>::Head() {
    return head;
}

template<typename T>
const typename LinkedList<T>::Node *LinkedList<T>::Head() const {
    return head;
}

template<typename T>
typename LinkedList<T>::Node *LinkedList<T>::Tail() {
    return tail;
}

template<typename T>
const typename LinkedList<T>::Node *LinkedList<T>::Tail() const {
    return tail;
}

template<typename T>
const T &LinkedList<T>::operator[](unsigned int index) const {
    Node *searchNode = head;

    if(index >= nodeCount){
        throw out_of_range("");
    }
    for (unsigned int i = 0; i == index - 1; i ++){
        searchNode = searchNode->next;
    }
    return searchNode->data;
}

template<typename T>
T &LinkedList<T>::operator[](unsigned int index) {
    Node *searchNode = head;

    if(index >= nodeCount){
        throw out_of_range("");
    }
    for (int i = 0; i == index - 1; i ++){
        searchNode = searchNode->next;
    }
    return searchNode->data;
}
//Given pointer to node
template<typename T>
void LinkedList<T>::InsertAfter(LinkedList::Node *node, const T &data) {
    //new node with passed in value after indicated node
    //(node) <-prev (node2) next-> (node->next/node3)
    //inserted^
    Node *node2 = new Node();
    Node *node3 = node->next;
    node2->data = data;
    node2->next = node3;
    node2->prev = node;
    nodeCount++;

    //fix node and node->next
    node->next = node2;
    node3->prev = node2;
}
//Ditto except insert it before
template<typename T>
void LinkedList<T>::InsertBefore(LinkedList::Node *node, const T &data) {
    //new node with passed in value after indicated node
    //(node3/node->prev) <-prev (node2) next-> (node)
    //inserted^
    Node * node2 = new Node();
    Node *node3 = node->prev;
    node2->data = data;
    node2->next = node;
    node2->prev = node3;
    nodeCount++;

    //fix node and node->next
    node->prev = node2;
    node3->next = node2;

}
//Inserts a new node to store the first parameter at the index-th location
//index = 3, new node should have 3 nodes before it
//throws an out of range if given invalid index
template<typename T>
void LinkedList<T>::InsertAt(const T &data, unsigned int index) {
    if(index > nodeCount){
        throw out_of_range("");
    }
    // ______node1 <-prev <insertNode> next->  node2______
    Node *ptrCounter = head;
    //if at the beginning
    if (index == 0){
        //mirrors AddHead
        this->AddHead(data);
    }
    //if at end
    else if (index == nodeCount){
        //mirrors AddTail
        this->AddTail(data);
    }
    //else somewhere in the middle
    else{
        //count to index
        //insert after the said index with the data
        for(unsigned int i = 0; i != index; i++){
            ptrCounter = ptrCounter->next;
        }
        this->InsertAfter(ptrCounter->prev, data);
    }
}

template<typename T>
bool LinkedList<T>::operator==(const LinkedList<T> &rhs) const {
    bool match = true;
    int index = 0;
    //while ptrCounter does not = nullptr it will iterate through
    for(Node* ptrCounter = rhs.head;ptrCounter != nullptr;){
        T rhsData = rhs[index];
        T thisData = this->operator[](index);

        if(rhsData == thisData){
            match = true;
        }
        else{
            match = false;
        }
        if (!match){
            break;
        }
        index++;
        ptrCounter = ptrCounter->next;
    }
    return match;
}
//takes in a pointer node (starting) then recursively visits each node that follows in forward order
//and prints their values
//must be implemented with recursion
template<typename T>
void LinkedList<T>::PrintForwardRecursive(const LinkedList::Node *node) const {
    if (node->next == nullptr){
        cout << node->data << endl;
    }
    else{
        cout << node->data << endl;
        this->PrintForwardRecursive(node->next);
    }
}
//same but backwards
template<typename T>
void LinkedList<T>::PrintReverseRecursive(const LinkedList::Node *node) const {
    if (node->prev == nullptr){
        cout << node->data << endl;
    }
    else{
        cout << node->data << endl;
        this->PrintReverseRecursive(node->prev);
    }
}
//remove first node in the list, return whether or not it was successful
template<typename T>
bool LinkedList<T>::RemoveHead() {
    //empty list
    if(nodeCount == 0){
        return false;
    }
    //one node in list -> empty list
    else if (nodeCount == 1){
        Clear();
        return true;
    }
    //more than one node
    else{
        //new head will be the what was next to current head
        //new head's prev ptr will be null
        //delete current head and replace with new head
        Node *currHead = head;
        Node *newHead = currHead->next;
        newHead->prev = nullptr;
        head = newHead;
        delete currHead;

        nodeCount--;
        return true;
    }
}

template<typename T>
bool LinkedList<T>::RemoveTail() {
    //empty list
    if(nodeCount == 0){
        return false;
    }
    //one node in list -> empty list
    else if(nodeCount == 1){
        Clear();
        return true;
    }
        //more than one node
        // _ <-prev- _________
    else{
        //new tail will be the what was prev to current tail
        //new tail's next ptr will be null
        //delete current tail and replace with new tail
        Node *currTail = tail;
        Node *newTail = currTail->prev;
        newTail->next = nullptr;
        tail = newTail;
        delete currTail;

        nodeCount--;
        return true;
    }
}
//remove all nodes containing values matching the parameter
//return how many instances were removed
template<typename T>
unsigned int LinkedList<T>::Remove(const T &data) {
    //similar to find all instances
    //just have to remove them
    Node *searchNode = head;
    Node *iteration;
    int removed = 0;

    while(searchNode != nullptr){
        iteration = searchNode->next;
        if(searchNode->data == data){
            removed++;
            Node *removedNode = searchNode;
            Node *beforeRemove = removedNode->prev;
            Node *afterRemove = removedNode->next;

            beforeRemove->next = afterRemove;
            afterRemove->prev = beforeRemove;
            delete removedNode;
        }
        searchNode = iteration;
    }
    return removed;
}

template<typename T>
bool LinkedList<T>::RemoveAt(unsigned int index) {
    //index out of range
    if(index >= nodeCount){
        return false;
    }
    //empty list
    else if(nodeCount == 0){
        return false;
    }
    //one node in list -> empty list
    else if(nodeCount == 1){
        Clear();
        return true;
    }
    //removal of index 0 aka RemoveHead
    else if(index == 0){
        this->RemoveHead();
        return true;
    }
    //removal of last index aka RemoveTail
    else if(index == nodeCount){
        this->RemoveTail();
        return true;
    }
    //removal somewhere in the middle
    else {
        Node *removedNode = head;
        for(unsigned int i = 0; i != index; i++){
            removedNode = removedNode->next;
        }
        Node *beforeRemove = removedNode->prev;
        Node *afterRemove = removedNode->next;

        nodeCount--;
        beforeRemove->next = afterRemove;
        afterRemove->prev = beforeRemove;
        delete removedNode;
        return true;
    }
}


