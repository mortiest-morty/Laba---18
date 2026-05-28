#include "Header.h"

// ==================== Реализация класса: бинарное деревце ====================
BinaryTree::BinaryTree() : root(nullptr), dllHead(nullptr) {}

BinaryTree::~BinaryTree() {
    clear();
}

void BinaryTree::clearTree(Node<int>* node) {
    if (node) {
        clearTree(node->getLeft());
        clearTree(node->getRight());
        delete node;
    }
}

void BinaryTree::clear() {
    clearTree(root);
    root = nullptr;
    dllHead = nullptr;
    inorderTraversal.clear();
}

void BinaryTree::clearDLL() {
    dllHead = nullptr;
}

Node<int>* BinaryTree::insertIntoBST(Node<int>* root, int value) {
    if (!root) {
        return new Node<int>(value);
    }

    if (value < root->getKey()) {
        Node<int>* leftChild = insertIntoBST(root->getLeft(), value);
        root->setLeft(leftChild);
    }
    else if (value > root->getKey()) {
        Node<int>* rightChild = insertIntoBST(root->getRight(), value);
        root->setRight(rightChild);
    }

    return root;
}

Node<int>* BinaryTree::buildTreeFromVector(const std::vector<int>& values) {
    if (values.empty() || values[0] == -1) return nullptr;

    Node<int>* root = new Node<int>(values[0]);
    std::queue<Node<int>*> q;
    q.push(root);

    int i = 1;
    while (!q.empty() && i < values.size()) {
        Node<int>* current = q.front();
        q.pop();

        // Левый ребёнок
        if (i < values.size()) {
            if (values[i] != -1) {
                Node<int>* leftNode = new Node<int>(values[i]);
                current->setLeft(leftNode);
                q.push(leftNode);
            }
            i++;
        }

        // Правый ребёнок
        if (i < values.size()) {
            if (values[i] != -1) {
                Node<int>* rightNode = new Node<int>(values[i]);
                current->setRight(rightNode);
                q.push(rightNode);
            }
            i++;
        }
    }

    return root;
}

void BinaryTree::createTreeFromInput() {
    using namespace std;

    cout << "\n--- Ввод дерева ---\n";
    cout << "Введите числа через пробел:\n";

    string line = getLine();
    while (line.empty()) {
        line = getLine();
    }

    stringstream ss(line);
    vector<int> values;
    int num;
    while (ss >> num) {
        values.push_back(num);
    }

    if (values.empty()) {
        cout << "Ошибка: не введено ни одного числа!\n";
        return;
    }

    clear();

    for (int val : values) {
        root = insertIntoBST(root, val);
    }

    dllHead = nullptr;
    inorderTraversal.clear();
}


void BinaryTree::createRandomTree() {
    using namespace std;

    cout << "\n--- Случайное дерево ---\n";
    cout << "Введите количество узлов: ";
    int nodeCount = getNumber();

    if (nodeCount <= 0) {
        cout << "Ошибка: количество узлов должно быть больше 0\n";
        return;
    }

    srand((unsigned int)time(nullptr));

    vector<int> values;
    for (int i = 0; i < nodeCount; i++) {
        values.push_back(rand() % 100);
    }

    cout << "Сгенерированные значения: ";
    for (int v : values) cout << v << " ";
    cout << endl;

    clear();

    for (int val : values) {
        root = insertIntoBST(root, val);
    }

    dllHead = nullptr;
    inorderTraversal.clear();
}


void BinaryTree::loadTreeFromFile() {
    using namespace std;

    cout << "\n--- Загрузка дерева из файла ---\n";
    cout << "Введите имя файла: ";
    string filename = getLine();

    ifstream file(filename.c_str());
    if (!file.is_open()) {
        cout << "Ошибка открытия файла!\n";
        return;
    }

    string line;
    getline(file, line);
    file.close();

    if (line.empty()) {
        cout << "Файл пуст!\n";
        return;
    }

    stringstream ss(line);
    vector<int> values;
    int num;
    while (ss >> num) {
        values.push_back(num);
    }

    clear();

    for (int val : values) {
        root = insertIntoBST(root, val);
    }

    dllHead = nullptr;
    inorderTraversal.clear();

    cout << "Дерево загружено из файла " << filename << endl;
    dllHead = nullptr;
    inorderTraversal.clear();
}

// ==================== Создание обычного двоичного дерева ====================

void BinaryTree::createBinaryTreeFromInput() {
    using namespace std;

    cout << "\n--- Ввод двоичного дерева  ---\n";
    cout << "Введите числа через пробел:\n";

    string line = getLine();
    while (line.empty()) {
        line = getLine();
    }

    stringstream ss(line);
    vector<int> values;
    int num;
    while (ss >> num) {
        values.push_back(num);
    }

    if (values.empty()) {
        cout << "Ошибка: не введено ни одного числа!\n";
        return;
    }

    clear();
    root = buildTreeFromVector(values);
    dllHead = nullptr;
    inorderTraversal.clear();

    cout << "Двоичное дерево создано!\n";
}

void BinaryTree::createRandomBinaryTree() {
    using namespace std;

    cout << "\n--- Случайное двоичное дерево ---\n";
    cout << "Введите количество узлов: ";
    int nodeCount = getNumber();

    if (nodeCount <= 0) {
        cout << "Ошибка: количество узлов должно быть больше 0\n";
        return;
    }

    srand((unsigned int)time(nullptr));

    vector<int> values;
    for (int i = 0; i < nodeCount; i++) {
        values.push_back(rand() % 100 - 50); 
    }

    clear();

    if (nodeCount > 0) {
        root = new Node<int>(values[0]);
        queue<Node<int>*> q;
        q.push(root);

        int index = 1;
        while (!q.empty() && index < nodeCount) {
            Node<int>* current = q.front();
            q.pop();

            if (index < nodeCount && (rand() % 100 < 70)) {
                Node<int>* leftNode = new Node<int>(values[index++]);
                current->setLeft(leftNode);
                q.push(leftNode);
            }

            if (index < nodeCount && (rand() % 100 < 70)) {
                Node<int>* rightNode = new Node<int>(values[index++]);
                current->setRight(rightNode);
                q.push(rightNode);
            }
        }
    }

    cout << "Сгенерированные значения узлов: ";
    for (int v : values) cout << v << " ";
    cout << endl;
    cout << "Случайное двоичное дерево создано!\n";
}

void BinaryTree::loadBinaryTreeFromFile() {
    using namespace std;

    cout << "\n--- Загрузка двоичного дерева из файла ---\n";
    cout << "Введите имя файла: ";
    string filename = getLine();

    ifstream file(filename.c_str());
    if (!file.is_open()) {
        cout << "Ошибка открытия файла!\n";
        return;
    }

    string line;
    getline(file, line);
    file.close();

    if (line.empty()) {
        cout << "Файл пуст!\n";
        return;
    }

    stringstream ss(line);
    vector<int> values;
    int num;
    while (ss >> num) {
        values.push_back(num);
    }

    clear();
    root = buildTreeFromVector(values);
    dllHead = nullptr;
    inorderTraversal.clear();

    cout << "Двоичное дерево загружено из файла " << filename << endl;
}

void BinaryTree::printTreeRec(Node<int>* node, int level) {
    using namespace std;

    if (!node) return;

    printTreeRec(node->getRight(), level + 1);

    for (int i = 0; i < level; i++) {
        cout << "    ";
    }
    cout << node->getKey() << endl;

    printTreeRec(node->getLeft(), level + 1);
}

void BinaryTree::printTree() {
    using namespace std;

    if (!root) {
        cout << "Дерево пусто!\n";
        return;
    }

    cout << "\n--- Дерево (повернуто на 90°, корень слева) ---\n";
    printTreeRec(root, 0);
}

void BinaryTree::saveTreeRec(Node<int>* node, int level, std::ofstream& file) {
    using namespace std;

    if (!node) return;

    saveTreeRec(node->getRight(), level + 1, file);

    for (int i = 0; i < level; i++) {
        file << "    ";
    }
    file << node->getKey() << endl;

    saveTreeRec(node->getLeft(), level + 1, file);
}

void BinaryTree::saveTreeToFile() {
    using namespace std;

    if (!root) {
        cout << "Дерево пусто. Нечего сохранять!\n";
        return;
    }

    cout << "Введите имя файла для сохранения дерева: ";
    string filename = getLine();

    ofstream file(filename.c_str());
    if (!file.is_open()) {
        cout << "Ошибка открытия файла!\n";
        return;
    }

    saveTreeRec(root, 0, file);
    file.close();
    cout << "Дерево сохранено в файл: " << filename << endl;
}


// ==================== Реализация класса проверок ====================

bool TreeValidator::isBSTUtil(Node<int>* node, int min, int max) {
    if (!node) return true;

    if (node->getKey() < min || node->getKey() > max) return false;

    return isBSTUtil(node->getLeft(), min, node->getKey() - 1) &&
        isBSTUtil(node->getRight(), node->getKey() + 1, max);
}

void TreeValidator::isBinarySearchTree(Node<int>* root) {
    using namespace std;

    if (!root) return;
    if (!isBSTUtil(root, numeric_limits<int>::min(), numeric_limits<int>::max())) {
        cout << " Дерево НЕ является бинарным деревом поиска\n";
    }
}

