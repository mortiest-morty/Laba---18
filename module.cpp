#include "Header.h"

// ======================= ПРОВЕРКА ВВОДА =======================
int getNumber() {
    using namespace std;

    int value;
    while (true) {
        cin >> value;
        if (cin.fail()) {
            cout << "Ошибка! Введите число: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

std::string getLine() {
    using namespace std;

    string input;
    getline(cin, input);
    return input;
}


// ==================== Задачка 1 ====================
void BinaryTree::inorderToDLL(Node<int>* node, Node<int>*& first, Node<int>*& last) {
    if (!node) return;

    inorderToDLL(node->getLeft(), first, last);

    if (last) {
        last->setRight(node);
        node->setLeft(last);
    }
    else {
        first = node;
    }
    last = node;

    inorderToDLL(node->getRight(), first, last);
}

// преобразование дерева в список
void BinaryTree::convertToDLL() {
    using namespace std;

    if (!root) {
        cout << "Дерево пусто!\n";
        return;
    }

    Node<int>* first = nullptr;
    Node<int>* last = nullptr;
    inorderToDLL(root, first, last);

    if (first) first->setLeft(nullptr);
    if (last) last->setRight(nullptr);

    dllHead = first;
}

// вывод списка в консоль
void BinaryTree::printDLL() {
    using namespace std;

    if (!dllHead) {
        cout << "Список пуст!\n";
        return;
    }

    cout << "\n--- Двусвязный список ---\n";
    Node<int>* curr = dllHead;
    cout << "Список: ";
    while (curr) {
        cout << curr->getKey() << " ";
        curr = curr->getRight();
    }
    cout << endl;
}

// вывод списка в файл
void BinaryTree::saveDLLToFile() {
    using namespace std;

    if (!dllHead) {
        cout << "Список пуст!\n";
        return;
    }

    cout << "Введите имя файла для сохранения списка: ";
    string filename = getLine();

    ofstream file(filename.c_str());
    if (!file.is_open()) {
        cout << "Ошибка открытия файла!\n";
        return;
    }

    Node<int>* curr = dllHead;
    while (curr) {
        file << curr->getKey() << " ";
        curr = curr->getRight();
    }
    file.close();
    cout << "Список сохранён в файл: " << filename << endl;
}


// ==================== Задачка 2 ====================
void BinaryTree::collectInorder(Node<int>* node) {
    if (!node) return;
    collectInorder(node->getLeft());
    inorderTraversal.push_back(node->getKey());
    collectInorder(node->getRight());
}

void BinaryTree::printInorderIterator() {
    using namespace std;

    if (!root) {
        cout << "Дерево пусто!\n";
        return;
    }

    InorderIterator it(root);

    cout << "Обход итератором (лево-корень-право): ";
    while (it.hasNext()) {
        cout << it.next() << " ";
    }
    cout << endl;
}

void BinaryTree::saveInorderToFile() {
    using namespace std;

    if (!root) {
        cout << "Дерево пусто!\n";
        return;
    }

    inorderTraversal.clear();
    collectInorder(root);

    cout << "Введите имя файла для сохранения обхода: ";
    string filename = getLine();

    ofstream file(filename.c_str());
    if (!file.is_open()) {
        cout << "Ошибка открытия файла!\n";
        return;
    }

    for (int val : inorderTraversal) {
        file << val << " ";
    }
    file.close();
    cout << "Обход сохранён в файл: " << filename << endl;
}

// ==================== Задачка 3 ====================
// Вспомогательная функция для поиска всех путей 
void BinaryTree::findAllPaths(Node<int>* node, int S, std::vector<int>& currentPath,
    std::vector<std::vector<int>>& result) {
    using namespace std;

    if (!node) return;

    currentPath.push_back(node->getKey());

    // Проверяем все подпути, заканчивающиеся в текущем узле
    int sum = 0;
    for (int i = currentPath.size() - 1; i >= 0; i--) {
        sum += currentPath[i];
        if (sum == S) {
            // Нашли путь от i до конца
            vector<int> path;
            for (size_t j = i; j < currentPath.size(); j++) {
                path.push_back(currentPath[j]);
            }
            // ДОБАВЛЯЕМ ВСЕГДА, даже если такой путь уже был
            result.push_back(path);
        }
    }

    // Рекурсивно обходим детей
    findAllPaths(node->getLeft(), S, currentPath, result);
    findAllPaths(node->getRight(), S, currentPath, result);

    currentPath.pop_back();
}

void BinaryTree::findPathsWithSum() {
    using namespace std;

    if (!root) {
        cout << "Дерево пусто. Сначала создайте дерево!\n";
        return;
    }

    cout << "Введите искомую сумму S: ";
    int S = getNumber();

    vector<int> currentPath;
    vector<vector<int>> paths;
    findAllPaths(root, S, currentPath, paths);

    cout << "\n--- ВСЕ пути с суммой " << S << " ---\n";
    if (paths.empty()) {
        cout << "Пути не найдены\n";
        return;
    }

    // Выводим все пути (включая повторяющиеся)
    cout << "Найдено " << paths.size() << " путей (включая повторяющиеся):\n";
    for (size_t i = 0; i < paths.size(); i++) {
        cout << "Путь " << i + 1 << ": ";
        for (int val : paths[i]) {
            cout << val << " ";
        }
        cout << endl;
    }
}

void BinaryTree::savePathsToFile() {
    using namespace std;

    if (!root) {
        cout << "Дерево пусто. Сначала создайте дерево!\n";
        return;
    }

    cout << "Введите искомую сумму S: ";
    int S = getNumber();

    vector<int> currentPath;
    vector<vector<int>> paths;

    findAllPaths(root, S, currentPath, paths);

    cout << "Введите имя файла для сохранения путей: ";
    string filename = getLine();

    ofstream file(filename.c_str());
    if (!file.is_open()) {
        cout << "Ошибка открытия файла!\n";
        return;
    }

    if (paths.empty()) {
        file << "Пути с суммой " << S << " не найдены\n";
    }
    else {
        file << "Найдено " << paths.size() << " путей (включая повторяющиеся) с суммой " << S << ":\n";
        for (size_t i = 0; i < paths.size(); i++) {
            file << "Путь " << i + 1 << ": ";
            for (int val : paths[i]) {
                file << val << " ";
            }
            file << endl;
        }
    }
    file.close();
    cout << "Пути сохранены в файл: " << filename << endl;
}

// ==================== Меню ====================
void showMainMenu() {
    using namespace std;

    cout << "\n============== ^-^ Главная менюшка  ^-^ ==============\n\n";
    cout << "1 - задачка 1: Преобразование бин дерева в двусвязный список\n";
    cout << "2 - задачка 2: Итератор (лево-корень-право)\n";
    cout << "3 - задачка 3: Поиск путей с заданной суммой\n";
    cout << "0 - Выход\n\n";
    cout << "Ваш выбор: ";
}
void showTreeFun1Menu() {
    using namespace std;

    cout << "\n(*-*) ============ задачка 1 ============ (*-*)\n\n";
    cout << "1 - Создать дерево\n";
    cout << "2 - Вывести дерево\n";
    cout << "3 - Преобразовать дерево в двусвязный список\n";
    cout << "4 - Вывести двусвязный список\n";
    cout << "5 - Сохранить список в файл\n";
    cout << "0 - Назад\n\n";
    cout << "Ваш выбор: ";
}

void showCreateTreeMenu() {
    using namespace std;

    cout << "\n-------- Способы создания дерева --------\n\n";
    cout << "1 - Ввод с консоли\n";
    cout << "2 - Сгенерировать случайное дерево\n";
    cout << "3 - Загрузить из файла\n";
    cout << "0 - Назад\n\n";
    cout << "Ваш выбор: ";
}

void showPrintTreeMenu() {
    using namespace std;

    cout << "\n-------- Способы вывода дерева --------\n\n";
    cout << "1 - вывод дерева в консоль\n";
    cout << "2 - Сохранить дерево в файл\n";
    cout << "0 - Назад\n\n";
    cout << "Ваш выбор: ";
}

void showTreeFun3Menu() {
    using namespace std;

    cout << "\n(*-*) ============ задачка 2 ============ (*-*)\n\n";
    cout << "1 - Создать дерево\n";
    cout << "2 - Вывести дерево\n";
    cout << "3 - Вывести обход итератором\n";
    cout << "4 - Сохранить обход в файл\n";
    cout << "0 - Назад\n\n";
    cout << "Ваш выбор: ";
}

void showTreeFun12Menu() {
    using namespace std;

    cout << "\n(*-*) ============ задачка 3 ============ (*-*)\n\n";
    cout << "1 - Ввод дерева\n";
    cout << "2 - Вывод дерева\n";
    cout << "3 - Найти путь с суммой S\n";
    cout << "4 - сохранить путь в файл\n";
    cout << "0 - Назад\n\n";
    cout << "Ваш выбор: ";
}

void solve() {
    using namespace std;

    int choice, subChoice, actionChoice;

    while (true) {
        showMainMenu();
        choice = getNumber();

        system("cls");

        switch (choice) {
        case 1: { 
            BinaryTree tree;
            while (true) {
                showTreeFun1Menu();
                actionChoice = getNumber();

                switch (actionChoice) {
                case 1: // Создать дерево
                    while (true) {
                        showCreateTreeMenu();
                        subChoice = getNumber();
                        switch (subChoice) {
                        case 1: tree.createTreeFromInput(); goto exit_create1;
                        case 2: tree.createRandomTree(); goto exit_create1;
                        case 3: tree.loadTreeFromFile(); goto exit_create1;
                        case 0: goto exit_create1;
                        default: cout << "Да блин ошибка на ошибке!\n";
                        }
                    }
                exit_create1:
                    break;

                case 2: // Вывести дерево
                    while (true) {
                        showPrintTreeMenu();
                        subChoice = getNumber();
                        switch (subChoice) {
                        case 1: tree.printTree(); goto exit_print1;
                        case 2: tree.saveTreeToFile(); goto exit_print1;
                        case 0: goto exit_print1;
                        default: cout << "Выбирать нормально надо!\n";
                        }
                    }
                exit_print1:
                    break;

                case 3: // Преобразовать в список
                    tree.convertToDLL();
                    break;

                case 4: // Вывести список
                    tree.printDLL();
                    break;

                case 5: // Сохранить список  в файл
                    tree.saveDLLToFile();
                    break;

                case 0:
                    goto exit_fun1;

                default:
                    cout << "Фигню не пиши!\n";
                }
            }
        exit_fun1:
            break;
        }

        case 2: { 
            BinaryTree tree;
            while (true) {
                showTreeFun3Menu();
                actionChoice = getNumber();

                switch (actionChoice) {
                case 1: // Создать дерево
                    while (true) {
                        showCreateTreeMenu();
                        subChoice = getNumber();
                        switch (subChoice) {
                        case 1: tree.createTreeFromInput(); goto exit_create3;
                        case 2: tree.createRandomTree(); goto exit_create3;
                        case 3: tree.loadTreeFromFile(); goto exit_create3;
                        case 0: goto exit_create3;
                        default: cout << "Ну, хватит писать неправильна!\n";
                        }
                    }
                exit_create3:
                    break;

                case 2: // Вывести дерево
                    while (true) {
                        showPrintTreeMenu();
                        subChoice = getNumber();
                        switch (subChoice) {
                        case 1: tree.printTree(); goto exit_print3;
                        case 2: tree.saveTreeToFile(); goto exit_print3;
                        case 0: goto exit_print3;
                        default: cout << "Ошибкаааааа!\n";
                        }
                    }
                exit_print3:
                    break;

                case 3: // Вывести обход итератором
                    tree.printInorderIterator();
                    break;

                case 4: // Сохранить обход в файл
                    tree.saveInorderToFile();
                    break;

                case 0:
                    goto exit_fun3;

                default:
                    cout << "Фигню написал!\n";
                }
            }
        exit_fun3:
            break;
        }

        case 3: { 
            BinaryTree tree;
            while (true) {
                showTreeFun12Menu();
                actionChoice = getNumber();

                switch (actionChoice) {
                case 1: // Создать дерево
                    while (true) {
                        showCreateTreeMenu();
                        subChoice = getNumber();
                        switch (subChoice) {
                        case 1: tree.createBinaryTreeFromInput(); goto exit_create12;
                        case 2: tree.createRandomBinaryTree(); goto exit_create12;
                        case 3: tree.loadBinaryTreeFromFile(); goto exit_create12;
                        case 0: goto exit_create12;
                        default: cout << "Кто тебе только печатать позволил! Ошибка!\n";
                        }
                    }
                exit_create12:
                    break;

                case 2: // Вывести дерево
                    while (true) {
                        showPrintTreeMenu();
                        subChoice = getNumber();
                        switch (subChoice) {
                        case 1: tree.printTree(); goto exit_print12;
                        case 2: tree.saveTreeToFile(); goto exit_print12;
                        case 0: goto exit_print12;
                        default: cout << "Прекратите неверно вводить!\n";
                        }
                    }
                exit_print12:
                    break;

                case 3: // Найти пути с суммой S
                    tree.findPathsWithSum();
                    break;

                case 4: // Сохранить пути в файл
                    tree.savePathsToFile();
                    break;

                case 0:
                    goto exit_fun12;

                default:
                    cout << "Даже ноуту неприятно, что ты вводишь неверно!\n";
                }
            }
        exit_fun12:
            break;
        }

        case 0:
            cout << "еееее, наконец выход\n";
            return;

        default:
            cout << "Слышь, прекращай! Заново вводи.\n";
        }
        system("cls");
    }
}
