#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"

#include <utility>

// Do not add any #include statements here.  If you have a convincing need for adding a different `#include` please post in the forum on KEATS.

// TODO your code goes here:
#include <initializer_list>

template<typename T>
class LinkedList {

private:
    Node<T>* head;
    Node<T>* tail;
    int count;

public:
    LinkedList()
        : head(nullptr), tail(nullptr), count(0) {
    }

    LinkedList(std::initializer_list<T> list)
        : head(nullptr), tail(nullptr), count(0) {
        
        for (auto &item : list) push_back(item);
    }

    void push_front(T item) {
        Node<T>* node = new Node<T>(item);
        
        if (count==0) {
            head = node;
            tail = node;
        } else {
            node->next = head;
            head->previous = node;
            head = node;
        }
        count++;
    }

    T front() {
        if (count>0) return head->data;
        return 0;
    }

    void push_back(T item) {
        Node<T>* node = new Node<T>(item);

        if (count==0) {
                head = node;
                tail = node;
        } else {
            tail->next = node;
            node->previous = tail;
            tail = node;
        }
        count++;
    }

    T back() {
        if (count>0) return tail->data;
        return 0;
    }

    int size() const {
        return count;
    }

    NodeIterator<T> begin() {
        return NodeIterator<T>(head);
    }

    NodeIterator<T> end() {
        return NodeIterator<T>(nullptr);
    }

    ~LinkedList() {
        Node<T>* node;
        while (head!=nullptr) {
            node = head;
            head = head->next;
            delete node;
        }
    }

    Node<T>* reverseRecursive(Node<T>* node) {
        if (node->next==nullptr) {
            head = node;
            return node;
        }
        Node<T>* nextNode = reverseRecursive(node->next);
        nextNode->next = node;
        node->next = nullptr;
        return node;
    }

    void reverse() {
        if (!head) return;
        reverseRecursive(head);
    }

    NodeIterator<T> insert(NodeIterator<T> &iter, T element) {
        Node<T>* newNode = new Node<T>(element);
        Node<T>* currNode = iter.getCurrent();

        newNode->next = currNode;
        newNode->previous = currNode->previous;

        if (currNode!=head) currNode->previous->next = newNode;
        else head=currNode;

        count++;

        return NodeIterator<T>(newNode);
    }

    NodeIterator<T> erase(NodeIterator<T> iter) {
        Node<T>* eraseNode = iter.getCurrent();
        Node<T>* returnNode = eraseNode->next;

        if (eraseNode == head) {
            head = eraseNode->next;
            head->previous = nullptr;
        }

        if (eraseNode == tail) {
            tail = eraseNode->previous;
            tail->next = nullptr;
            returnNode = nullptr;
        }

        if (eraseNode != head && eraseNode != tail) {
            if (eraseNode->previous != nullptr && eraseNode->next != nullptr) {
                eraseNode->previous->next = eraseNode->next;
                eraseNode->next->previous = eraseNode->previous;
            }
        }

        delete eraseNode;
        count--;

        return NodeIterator<T>(returnNode);
    }

    NodeIteratorReadOnly<T> begin() const {
        return NodeIteratorReadOnly<T>(head);
    }

    NodeIteratorReadOnly<T> end() const {
        return NodeIteratorReadOnly<T>(nullptr);
    }
};



// do not edit below this line

#endif
