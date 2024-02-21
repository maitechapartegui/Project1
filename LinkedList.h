#pragma once
#include<iostream>
#include <vector>
using namespace std;

template<typename T>
class LinkedList{
public:
    struct Node{
        T data;
        Node* next;
        Node* prev;
        Node();
        Node(T data);
    };

    //Constructors/Destructors
    LinkedList();
    LinkedList(const LinkedList &d);
    LinkedList& operator=(const LinkedList& d);
    ~LinkedList();

    // Adding information to container
    void AddHead(const T& data);
    void AddTail(const T& data);
    void AddNodesHead(T* array, int sizeArray);
    void AddNodesTail(T* array, int sizeArray);
    void InsertAfter(Node* node, T value);
    void InsertBefore(Node* node, T value);
    void InsertAt(T value, int index);

    //Accessors
    unsigned int NodeCount();
    Node* getHead();
    Node* getTail();
    Node* GetNode(int index) const;
    Node* GetNode(int index);
    Node* Find(T data) const;
    vector<typename LinkedList<T>::Node*> FindAll(vector<Node*>& nodes, T value);

    //Displays
    void PrintForward();
    void PrintReverse();
    void PrintForwardRecursive(Node* startingNode);
    void PrintReverseRecursive(Node* startingNode);

    //Operators
    T operator[](int index) const;
    T operator[](int index);
    bool operator==(LinkedList<T>& listA);

    //Removal functions
    bool RemoveHead();
    bool RemoveTail();
    int Remove(T value);
    bool RemoveAt(int index);
    void Clear();

private:
    Node* head;
    Node* tail;
    unsigned int size;
};

// Node struct definitions
template<typename T>
LinkedList<T>::Node::Node(){
    data = NULL;
    next = nullptr;
    prev = nullptr;
}

template<typename T>
LinkedList<T>::Node::Node(T data){
    this->data = data;
    next = nullptr;
    prev = nullptr;
}

// Constructors and Destructors
template<typename T>
LinkedList<T>::LinkedList(){
    size = 0;
    head = nullptr;
    tail = nullptr;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &d) {
    size = d.size;
    head = nullptr;
    tail = nullptr;

    Node* temp = d.head;
    while(temp != nullptr){
        Node* newNode = new Node(temp->data);
        if(head == nullptr){
            head = newNode;
            tail = newNode;
        }
        else{
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        temp = temp->next;
    }
}


template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T> &d){
    // delete mem from old list
    if (this != &d) {
        Node* temp = head;
        while (temp != nullptr) {
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
    }

    size = d.size;
    head = nullptr;
    tail = nullptr;

    // copy over new list
    Node* temp = d.head;
    while(temp != nullptr){
        Node* newNode = new Node(temp->data);
        if(head == nullptr){
            head = newNode;
            tail = newNode;
        }
        else{
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        temp = temp->next;
    }
    return *this;
}

template<typename T>
LinkedList<T>::~LinkedList(){
    Node* temp = head;
    for(unsigned int i = 0; i < size; i++){
        Node* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }
}

// Adding Functions
template<typename T>
void LinkedList<T>::AddHead(const T& data){
    if(size == 0){
        Node* newNode = new Node(data);
        head = newNode;
        tail = newNode;
    }
    else{
        Node* newNode = new Node(data);
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    size++;
}

template<typename T>
void LinkedList<T>::AddTail(const T &data) {
    if(size == 0){
        Node* newTail = new Node(data);
        head = newTail;
        tail = newTail;
    }
    else{
        Node* newTail = new Node(data);
        newTail->prev = tail;
        tail->next = newTail;
        tail = newTail;
    }
    size++;
}
template<typename T>
void LinkedList<T>::AddNodesHead(T* array, int sizeArray) {
    for(unsigned int i = sizeArray; i > 0; i--){
        Node* newNode = new Node(array[i - 1]);
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
        size++;
    }

}

template<typename T>
void LinkedList<T>::AddNodesTail(T* array, int sizeArray) {
    for(unsigned int i = 0; i < sizeArray; i++){
        Node* newNode = new Node(array[i]);
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
        size++;
    }
}

template<typename T>
void LinkedList<T>:: InsertAfter(Node* node, T value){
    Node* newNode = new Node(value);

    if(node == tail){
        tail = newNode;
    }
    else{
        newNode->prev = node;
        newNode->next = node->next;

        node->next = newNode;
        node->next->prev = newNode;
    }

    size++;
}

template<typename T>
void LinkedList<T>::InsertBefore(Node* node, T value){
    Node* newNode = new Node(value);

    if (node->prev == nullptr) {
        head = newNode;
        newNode->next = node;
        node->prev = newNode;
    }
    else{
        node->prev->next = newNode;
        newNode->prev = node->prev;

        node->prev = newNode;
        newNode->next = node;
    }
    size++;
}

template<typename T>
void LinkedList<T>::InsertAt(T value, int index){
    if(index > size){
        throw out_of_range("Index is out of range.");
    }

    else if (index == size) {
        AddTail(value);
    }

    else if(index == 0){
        AddHead(value);
    }

    else{
        Node* temp = head;

        for(unsigned int i = 0; i <= index; i++) {
            if (i == index){
                InsertBefore(temp, value);
            }
            temp = temp->next;
        }
    }
}

// Accessors
template<typename T>
unsigned int LinkedList<T>::NodeCount() {
    return size;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::getHead() {
    return head;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::getTail() {
    return tail;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(T data) const{
    Node* temp = head;

    for(unsigned int i = 0; i < size; i++){
        if(temp->data == data){
            break;
        }
        else {
            temp = temp->next;
        }
    }
    return temp;
}
template<typename T>
vector<typename LinkedList<T>::Node*> LinkedList<T>::FindAll(vector<Node*>& nodes, T value){
    Node* temp = head;

    for(unsigned int i = 0; i < size; i++){
        if(temp->data == value){
            nodes.push_back(temp);
            temp = temp->next;
        }
        else{
            temp = temp->next;
        }
    }
    return nodes;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(int index) const{
    Node* temp = head;

    if(index >= size){
        throw out_of_range("Index is out of range.");
    }

    else if(index == 0){
        return head;
    }

    else if(index == size - 1){
        return tail;
    }

    else{
        for(unsigned int i = 0; i == index - 1; i++) {
            temp = temp->next;
        }
    }
    return temp;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(int index){
    Node* temp = head;

    if(index >= size){
        throw out_of_range("Index is out of range.");
    }
    else if(index == 0){
        return head;
    }

    else if(index == size - 1){
        return tail;
    }

    else{
        for(unsigned int i = 0; i <= index - 1; i++) {
            temp = temp->next;
        }
    }
    //cout << "Deleting " << temp->data << endl;
    return temp;
}

// Displays
template<typename T>
void LinkedList<T>::PrintForward() {
    Node* temp = head;

    for(unsigned int i = 0; i < size; i++){
        cout << temp->data << endl;
        temp = temp->next;
    }
}

template<typename T>
void LinkedList<T>::PrintReverse(){
    Node* temp = tail;

    for(unsigned int i = 0; i < size; i++){
        cout << temp->data << endl;
        temp = temp->prev;
    }
}

template<typename T>
void LinkedList<T>:: PrintForwardRecursive(Node* startingNode){
    if(startingNode != nullptr){
        cout << startingNode->data << endl;
        PrintForwardRecursive(startingNode->next);
    }
}

template<typename T>
void LinkedList<T>:: PrintReverseRecursive(Node* startingNode){
    if(startingNode != nullptr){
        cout << startingNode->data << endl;
        PrintReverseRecursive(startingNode->prev);
    }
}

//Operators
template<typename T>
T LinkedList<T>::operator[](int index) const{
    Node* temp = head;

    if(index == 0){
        return temp->data;
    }
    else{
        for(unsigned int i = 0; i == index - 1; i++){
            temp = temp->next;
        }
    }
    return temp->data;
}

template<typename T>
T LinkedList<T>::operator[](int index){
    Node* temp = head;

    if(index >= size){
        throw out_of_range("Index is out of range.");
    }
    else{
        if(index == 0){
            return temp->data;
        }
        else{
            for(unsigned int i = 0; i == index - 1; i++){
                temp = temp->next;
            }
        }
    }
    return temp->data;
}

template<typename T>
bool LinkedList<T>::operator==(LinkedList<T>& listA){
    if(this->size != listA.size){
        return false;
    }
    Node* nodeA = this->head;
    Node* nodeB = listA.head;

    while(nodeA == nodeB){
        nodeA = nodeA->next;
        nodeB = nodeB->next;
    }
    return true;
}


//Removal functions
template<typename T>
bool LinkedList<T>::RemoveHead(){
    if(size == 0){
        return false;
    }

    else if(size == 1){
        delete head;
        head = nullptr;
        tail = nullptr;
        size--;
        return true;
    }

    else{
        Node* temp = head->next;
        temp->prev = nullptr;
        delete head;
        head = temp;
        size--;
        return true;
    }
}

template<typename T>
bool LinkedList<T>::RemoveTail(){
    if(size == 0){
        return false;
    }

    else if(size == 1){
        delete tail;
        head = nullptr;
        tail = nullptr;
        size--;
        return true;
    }

    else{
        Node* temp = tail->prev;
        temp->next = nullptr;
        delete tail;
        tail = temp;
        size--;
        return true;
    }
}

template<typename T>
int LinkedList<T>::Remove(T value){
    int removedNodeCount = 0;
    Node* temp = head;

    while(temp != nullptr){
        Node* next = temp->next;

        if(temp->data == value){
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
            removedNodeCount++;
            size--;
        }

        temp = next;
    }

    return removedNodeCount;
}


template<typename T>
bool LinkedList<T>:: RemoveAt(int index){
    if(index == 0){
        RemoveHead();
    }

    else if(index == size - 1){
        RemoveTail();
    }

    else if(index >= size){
        return false;
    }

    else{
        Node* temp = GetNode(index);
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
        size--;
        return true;
    }

    return false;
}
template<typename T>
void LinkedList<T>::Clear(){
    Node* temp = head;

    if(size == 1){
        RemoveHead();
    }

    else{
        while (size > 0) {
            RemoveHead();
        }
    }
    size = 0;
}
