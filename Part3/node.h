#ifndef NODE_H
#define NODE_H

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

// Do not add any #include statements here.  If you have a convincing need for adding a different `#include` please post in the forum on KEATS.

// TODO your code for the Node class goes here:
// (Note the 'NodeIterator' class will report lots of errors until Node exists
template<typename T>
class Node {

private:

public:
    T data;
    Node* next;
    Node* previous;

    Node(T dataIn)
        : data(dataIn), next(nullptr), previous(nullptr) {
    }
};


template<typename T>
class NodeIterator {
  
private:
    Node<T>* current;
    
public:
    NodeIterator(Node<T>* currentIn)
        : current(currentIn) {        
    }

    T & operator*() {
        return current->data;
    }

    // TODO: complete the code for NodeIterator here
    
    // prefix
    NodeIterator operator++() {
        current = current->next;
        return *this;
    }

    // postfix
    NodeIterator operator++(int) {
        current = current->next;
        NodeIterator result = *this;
        ++(*this);
        return result;
    }
    
    bool operator==(NodeIterator<T> other) {
        return other.current == current;
    }

    bool operator!=(NodeIterator<T> other) {
        return other.current != current;
    }

    Node<T>* getCurrent() {
        return current;
    }
};

template<typename T>
class NodeIteratorReadOnly {
  
private:
    Node<T>* current;
    
public:
    NodeIteratorReadOnly(Node<T>* currentIn)
        : current(currentIn) {        
    }

    T & operator*() {
        return current->data;
    }
    
    // prefix
    NodeIteratorReadOnly<T> operator++() {
        current = current->next;
        return *this;
    }

    // postfix
    NodeIteratorReadOnly<T> operator++(int) {
        current = current->next;
        NodeIteratorReadOnly result = *this;
        ++(*this);
        return result;
    }
    
    bool operator==(const NodeIteratorReadOnly<T> other) {
        return other.current == current;
    }

    bool operator!=(const NodeIteratorReadOnly<T> other) {
        return other.current != current;
    }

    Node<T>* getCurrent() {
        return current;
    }
};

// do not edit below this line

#endif
