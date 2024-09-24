#include <iostream>
using namespace std;

template<typename T>
class BSTree {

    struct NodeBT {
        T data;
        NodeBT *left;
        NodeBT *right;

        NodeBT(T value) : data(value), left(nullptr), right(nullptr) {}
    };

    NodeBT *root;

    template<typename U>
    class Queue {
        struct QueueNode {
            U data;
            QueueNode* next;
        };
        QueueNode* front;
        QueueNode* rear;

    public:
        Queue() : front(nullptr), rear(nullptr) {}

        void enqueue(U value) {
            QueueNode* newNode = new QueueNode();
            newNode->data = value;
            newNode->next = nullptr;
            if (rear == nullptr) {
                front = rear = newNode;
            } else {
                rear->next = newNode;
                rear = newNode;
            }
        }

        U dequeue() {

            QueueNode* temp = front;
            U dequeuedValue = front->data;
            front = front->next;
            if (front == nullptr) {
                rear = nullptr;
            }
            delete temp;
            return dequeuedValue;
        }

        bool isEmpty() {
            return front == nullptr;
        }
    };

    template<typename U>
    class Stack {
        struct StackNode {
            U data;
            StackNode* next;
        };
        StackNode* top;

    public:
        Stack() : top(nullptr) {}

        void push(U value) {
            StackNode* newNode = new StackNode();
            newNode->data = value;
            newNode->next = top;
            top = newNode;
        }

        U pop() {

            StackNode* temp = top;
            U poppedValue = top->data;
            top = top->next;
            delete temp;
            return poppedValue;
        }

        bool isEmpty() {
            return top == nullptr;
        }
    };

public:

    BSTree() : root(nullptr) {}

    void insert(T value) {
        root = insertRec(root, value);
    }

    bool find(T value) {
        return findRec(root, value);
    }

    void inorder() {
        inorder(root);
        cout << endl;
    }

    void preorder() {
        preorder(root);
        cout << endl;
    }

    void postorder() {
        postorder(root);
        cout << endl;
    }

    void BFS() {
        if (root == nullptr) {
            return;
        }

        Queue<NodeBT*> queue;
        queue.enqueue(root);

        while (!queue.isEmpty()) {
            NodeBT* current = queue.dequeue();
            cout << current->data << " ";

            if (current->left != nullptr) {
                queue.enqueue(current->left);
            }
            if (current->right != nullptr) {
                queue.enqueue(current->right);
            }
        }

        cout << endl;
    }

    void DFS() {
        if (root == nullptr){
            return;
        }

        Stack<NodeBT*> stack;
        stack.push(root);

        while (!stack.isEmpty()) {
            NodeBT* current = stack.pop();
            cout << current->data << " ";

            if (current->right != nullptr) {
                stack.push(current->right);
            }
            if (current->left != nullptr) {
                stack.push(current->left);
            }
        }
        cout << endl;
    }

    void remove(T value) {
        root = removeRec(root, value);
    }

private:

    NodeBT* insertRec(NodeBT* node, T value) {
        if (node == nullptr) {
            return new NodeBT(value);  //crear un nuevo nodo si el actual es nulo
        }

        if (value < node->data) {
            node->left = insertRec(node->left, value);
        } else if (value > node->data) {
            node->right = insertRec(node->right, value);
        }

        return node;
    }

    bool findRec(NodeBT* node, T value) {
        if (node == nullptr) {
            return false;
        } else if (value < node->data) {
            return findRec(node->left, value);
        } else if (value > node->data) {
            return findRec(node->right, value);
        } else {
            return true;
        }
    }

    void inorder(NodeBT* node) {
        if (node != nullptr) {
            inorder(node->left);
            cout << node->data << " ";
            inorder(node->right);
        }
    }

    void preorder(NodeBT* node) {
        if (node != nullptr) {
            cout << node->data << " ";
            preorder(node->left);
            preorder(node->right);
        }
    }

    void postorder(NodeBT* node) {
        if (node != nullptr) {
            postorder(node->left);
            postorder(node->right);
            cout << node->data << " ";
        }
    }

    NodeBT* removeRec(NodeBT* node, T value) {
        if (node == nullptr) {
            return node;
        }

        if (value < node->data) {
            node->left = removeRec(node->left, value);
        } else if (value > node->data) {
            node->right = removeRec(node->right, value);
        } else {
            //nodo encontrado
            if (node->left == nullptr) {
                NodeBT* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                NodeBT* temp = node->left;
                delete node;
                return temp;
            }

            //nodo con dos hijos
            NodeBT* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = removeRec(node->right, temp->data);
        }
        return node;
    }

    NodeBT* minValueNode(NodeBT* node) {
        NodeBT* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }
};

int main() {
    BSTree<int> tree;

    tree.insert(12);
    tree.insert(8);
    tree.insert(20);
    tree.insert(5);
    tree.insert(1);
    tree.insert(15);
    tree.insert(25);
    tree.insert(7);
    tree.insert(11);
    tree.insert(9);
    tree.insert(13);
    tree.insert(22);
    tree.insert(18);
    tree.insert(26);


    cout << "\nrecorrido inorder: ";
    tree.inorder();

    cout << "recorrido preorder: ";
    tree.preorder();

    cout << "recorrido postorder: ";
    tree.postorder();

    cout << "\nrecorrido BFS: ";
    tree.BFS();

    cout << "recorrido DFS (esperado: 10 5 3 7 15 12 18): ";
    tree.DFS();

    if (tree.find(7)) {
        cout << "encontrado" << endl;
    } else {
        cout << "no encontrado" << endl;
    }

    tree.remove(3);
    tree.inorder();



}
