#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::ostream;

#include <memory>
using std::unique_ptr;

#include <utility>
using std::pair;

// TODO your code for the TreeNode class goes here:
template<typename T>
class TreeNode {

public:
    T data;
    unique_ptr<TreeNode> leftChild;
    unique_ptr<TreeNode> rightChild;
    TreeNode * parent;

    TreeNode()
        : leftChild(nullptr), rightChild(nullptr) {
    }
    
    TreeNode(T dataIn)
        : data(dataIn), parent(nullptr) {
    }

    void setLeftChild(TreeNode* child) {
        leftChild.reset(child);
        leftChild->parent = this;
    }

    void setRightChild(TreeNode* child) {
        rightChild.reset(child);
        rightChild->parent = this;
    }

    void write(ostream & stream) const {
        if (leftChild) leftChild->write(stream);
        stream << " " << data << " ";
        if (rightChild) rightChild->write(stream);
    }

    int maxDepth() {
        if (leftChild==nullptr && rightChild==nullptr) return 1;

        int leftDepth = 0;
        int rightDepth = 0;
        TreeNode<T>* node = this;

        while (leftChild && node->leftChild) {
            node = node->leftChild.get();
            leftDepth++;
        } 

        node = this; // reset to root

        while (rightChild && node->rightChild) {
            node = node->rightChild.get();
            rightDepth++;
        }
        return rightDepth>leftDepth ? rightDepth+1 : leftDepth+1;
    }
};

template<typename T>
class TreeNodeIterator {
  
public:
    
    TreeNode<T>* current;
    
public:
    
    TreeNodeIterator(TreeNode<T>* currentIn)
        : current(currentIn) {        
    }

    T & operator*() {
        return current->data;
    }

    bool operator==(const TreeNodeIterator & other) {
        return current==other.current;
    }

    bool operator!=(const TreeNodeIterator & other) {
        return current!=other.current;
    }

    void operator++() {
        if (current->rightChild) {
            // traverse down
            current = current->rightChild.get();
            while (current->leftChild) {
                current = current->leftChild.get();
            }
        } else {
            // traverse up
            T startData = current->data;
            current = current->parent;
            while (current->parent && current->data<startData) {
                current = current->parent;
            }
            if (startData > (current->data)) {
                current = nullptr;
            }
        }
    }   
};

// do not edit below this line

#endif
