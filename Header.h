#pragma once
#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <sstream>
#include <algorithm>
#include <functional>

// Класс: узел деревца ~
template <typename T>
class Node {
private:
    T key;
    Node* left;
    Node* right;
    Node* parent;

public:
    Node(T key) : key(key), left(nullptr), right(nullptr) {}

    T getKey() const { return key; }
    Node* getLeft() const { return left; }
    Node* getRight() const { return right; }
    Node* getParent() const { return parent; }

    void setKey(T value) { key = value; }
    void setLeft(Node* l) {
        left = l;
        if (l) l->parent = this;  
    }
    void setRight(Node* r) {
        right = r;
        if (r) r->parent = this;  
    }
    void setParent(Node* p) { parent = p; }  
};

// Класс: бинарное деревце
class BinaryTree {
private:
    Node<int>* root;
    Node<int>* dllHead;
    std::vector<int> inorderTraversal;

    // Вспомогательные методы
    void printTreeRec(Node<int>* node, int level);
    void saveTreeRec(Node<int>* node, int level, std::ofstream& file);
    void inorderToDLL(Node<int>* node, Node<int>*& first, Node<int>*& last);
    void collectInorder(Node<int>* node);
    void clearTree(Node<int>* node);
    Node<int>* buildTreeFromVector(const std::vector<int>& values);
    Node<int>* insertIntoBST(Node<int>* root, int value);

public:
    BinaryTree();
    ~BinaryTree();

    // Ввод дерева
    void createTreeFromInput();
    void createRandomTree();
    void loadTreeFromFile();

    // Создание произвольного бинарного дерева 
    void createBinaryTreeFromInput();
    void createRandomBinaryTree();
    void loadBinaryTreeFromFile();


    // Вывод
    void printTree();
    void saveTreeToFile();

    // задачка 1 - преобразование в двусвязный список
    void convertToDLL();
    void printDLL();
    void saveDLLToFile();
    void clearDLL();

    // задачка 2 - итератор
    void printInorderIterator();
    void saveInorderToFile();

    // задачка 3 - поиск путей с суммой S
    void findAllPaths(Node<int>* node, int S, std::vector<int>& currentPath,
        std::vector<std::vector<int>>& result);
    void findPathsWithSum();
    void savePathsToFile();

    // Проверка
    bool isEmpty() const { return root == nullptr; }
    void clear();
    Node<int>* getRoot() const { return root; }
};

// Класс для проверки бинарного дерева
class TreeValidator {
private:
    bool isBSTUtil(Node<int>* node, int min, int max);
public:
    void isBinarySearchTree(Node<int>* root);
};


// Итератор для обратного обхода 
class InorderIterator {
private:
    Node<int>* current;

    Node<int>* findLeftmost(Node<int>* node) {
        if (!node) return nullptr;
        while (node->getLeft()){
            node = node->getLeft();
        }
        return node;
    }

    Node<int>* findSuccessor(Node<int>* node) {
        if (!node) return nullptr;

        if (node->getRight()) {
            return findLeftmost(node->getRight());
        }

        Node<int>* parent = node->getParent();
        while (parent && node == parent->getRight()) {
            node = parent;
            parent = parent->getParent();
        }
        return parent;
    }

public:
    InorderIterator(Node<int>* root) {
        current = findLeftmost(root);
    }

    bool hasNext() {
        return current != nullptr;
    }

    int next() {
        if (!hasNext()) {
            throw std::runtime_error("Нет больше элементов");
        }

        int value = current->getKey();
        current = findSuccessor(current);
        return value;
    }
};
void solve();

int getNumber();
std::string getLine();

#endif
