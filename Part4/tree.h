#ifndef TREE_H
#define TREE_H

#include "treenode.h"

// TODO your code goes here:
template<typename T>
class BinarySearchTree {

private:
    unique_ptr<TreeNode<T>> root;

public:
    BinarySearchTree() {}

    void write(ostream & stream) const {
        root->write(stream);
    }

    TreeNode<T>* insert(T data) {
        TreeNode<T>* node = root.get();
        TreeNode<T>* dataNode = new TreeNode<T>(data);

        while (node!=nullptr) {
            if (data < node->data) {
                if (node->leftChild==nullptr) {
                    node->setLeftChild(dataNode);
                    balance(node);
                    return dataNode;
                }
                node = node->leftChild.get();
            } else if (node->data < data) {
                if (node->rightChild==nullptr) {
                    node->setRightChild(dataNode);
                    balance(node);
                    return dataNode;
                }
                node = node->rightChild.get();
            } else {
                balance(node);
                return node;
            }
        }
        root.reset(dataNode); // new root
        return dataNode;
    }

    TreeNode<T>* find(T data) {
        TreeNode<T>* node = root.get();

        while (node!=nullptr) {
            if (data < node->data) {
                if (node->leftChild==nullptr) return nullptr;
                node = node->leftChild.get();
            } else if (node->data < data) {
                if (node->rightChild==nullptr) return nullptr;
                node = node->rightChild.get();
            } else {
                return node;
            }
        }
        return nullptr;
    }

    BinarySearchTree(const BinarySearchTree<T> & other) {
        if (other.root) {
            TreeNode<T>* otherRoot = other.root.get();
            root.reset(copy(otherRoot));
        }
    }

    void operator=(const BinarySearchTree<T> & other) {
        if (other.root) {
            TreeNode<T>* otherRoot = other.root.get();
            root.reset(copy(otherRoot));
        }
    }

    TreeNode<T>* copy(TreeNode<T>* rightNode) {
        if (rightNode) {
            TreeNode<T>* leftNode = new TreeNode<T>();
            leftNode->data = rightNode->data;
            if (rightNode->leftChild!=nullptr) {
                leftNode->setLeftChild(copy(rightNode->leftChild.get()));
            }

            if (rightNode->rightChild!=nullptr) {
                leftNode->setRightChild(copy(rightNode->rightChild.get()));
            }
            //leftNode->setLeftChild(copy(rightNode->leftChild.get()));
            //leftNode->setRightChild(copy(rightNode->rightChild.get()));
            return leftNode;
        }
        return nullptr;
    }

    TreeNodeIterator<T> begin() {
        TreeNode<T>* node = root.get();

        if (node!=nullptr) {
            while (node->leftChild) {
                node = node->leftChild.get();
            }
        }
        return TreeNodeIterator<T>(node);
    }

    TreeNodeIterator<T> end() {
        return nullptr;
    }

    int maxDepth() {
        if (root==nullptr) return 0;
        TreeNode<T>* r = root.get();
        return r->maxDepth();
    }

    int computeBalanceFactor(TreeNode<T>* node) {
        if (node==nullptr) return 0;
        if (node->leftChild && node->rightChild) {
            TreeNode<T>* left = node->leftChild.get();
            TreeNode<T>* right = node->rightChild.get();
            return left->maxDepth() - right->maxDepth();
        } else if (node->leftChild && node->rightChild==nullptr) {
            TreeNode<T>* left = node->leftChild.get();
            return left->maxDepth();
        } else if (node->leftChild==nullptr && node->rightChild) {
            TreeNode<T>* right = node->rightChild.get();
            return -right->maxDepth();
        }
        return 0;
    }

    // definitely better way of doing this!
    void leftRotation(TreeNode<T>* x) {
        TreeNode<T>* y = x->rightChild.get();
        TreeNode<T>* rightY = nullptr;
        TreeNode<T>* newY = new TreeNode<T>(y->data);
        TreeNode<T>* tempX = nullptr;
        TreeNode<T>* z = nullptr;

        if (y->leftChild) z = y->leftChild.get();
        
        tempX = new TreeNode<T>(x->data);
        if (tempX->leftChild) tempX->setLeftChild(x->leftChild.get());
        if (tempX->rightChild) tempX->setRightChild(x->rightChild.get());
        if (y->rightChild) rightY = new TreeNode<T>(y->rightChild.get()->data);

        if (x->parent==nullptr) root.reset(newY); // resets x BUT also y
        else if (x->parent->leftChild.get()==x) x->parent->setLeftChild(newY);
        else x->parent->setRightChild(newY);
        
        x = tempX;
        if (rightY!=nullptr) newY->setRightChild(rightY);
        newY->setLeftChild(x);
    
        if (z!=nullptr) x->setRightChild(z);
    }

    // definitely better way of doing this!
    void rightRotation(TreeNode<T>* x) {
        TreeNode<T>* y = x->leftChild.get();
        TreeNode<T>* leftY = nullptr;
        TreeNode<T>* newY = new TreeNode<T>(y->data);
        TreeNode<T>* tempX = nullptr;
        TreeNode<T>* z = nullptr;

        if (y->rightChild) z = y->rightChild.get();

        tempX = new TreeNode<T>(x->data);
        if (tempX->leftChild) tempX->setLeftChild(x->leftChild.get());
        if (tempX->rightChild) tempX->setRightChild(x->rightChild.get());
        if (y->leftChild) leftY = new TreeNode<T>(y->leftChild.get()->data);

        if (x->parent==nullptr) root.reset(newY); // resets x BUT also y
        else if (x->parent->rightChild.get()==x) x->parent->setRightChild(newY);
        else x->parent->setLeftChild(newY);

        x = tempX;
        if (leftY!=nullptr) newY->setLeftChild(leftY);
        newY->setRightChild(x);
    
        if (z!=nullptr) x->setLeftChild(z);
    }

    void leftRightRotation(TreeNode<T>* node) {
        leftRotation(node->leftChild.get());
        rightRotation(node);
    }

    void rightLeftRotation(TreeNode<T>* node) {
        rightRotation(node->rightChild.get());
        leftRotation(node);
    }

    void balance(TreeNode<T>* node) {
        if (node==nullptr) return;
        if (node->rightChild) {
            if (node->parent==nullptr) return;
            if (computeBalanceFactor(node->parent)==-2 && computeBalanceFactor(node)==-1) {
                leftRotation(node->parent); 
            } else if (computeBalanceFactor(node->parent)==2 && computeBalanceFactor(node)==-1) {
                leftRightRotation(node->parent);
            }
        }  
        if (node->leftChild) {
            if (node->parent==nullptr) return;
            if (computeBalanceFactor(node->parent)==2 && computeBalanceFactor(node)==1) {
                rightRotation(node->parent);
            } else if (computeBalanceFactor(node->parent)==-2 && computeBalanceFactor(node)==1) {
                if (node->parent->leftChild!=nullptr) return;
                rightLeftRotation(node->parent);
            }
        }
    }
};

// do not edit below this line

#endif
