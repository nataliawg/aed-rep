#include <iostream>
#include <cmath>
using namespace std;

// Definir TreeNode fuera de la clase BSTree
struct TreeNode {
    int data;
    TreeNode *left;
    TreeNode *right;
    int Fb;

    TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

template<typename T>
class BSTree {

    TreeNode *root;

    template<typename U>
    class Queue {
        struct QueueNode {
            U data;
            QueueNode *next;
        };
        QueueNode *front;
        QueueNode *rear;

    public:
        Queue() : front(nullptr), rear(nullptr) {}

        void enqueue(U value) {
            QueueNode *newNode = new QueueNode();
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
            QueueNode *temp = front;
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
            StackNode *next;
        };
        StackNode *top;

    public:
        Stack() : top(nullptr) {}

        void push(U value) {
            StackNode *newNode = new StackNode();
            newNode->data = value;
            newNode->next = top;
            top = newNode;
        }

        U pop() {
            StackNode *temp = top;
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

        Queue<TreeNode *> queue;
        queue.enqueue(root);

        while (!queue.isEmpty()) {
            TreeNode *current = queue.dequeue();
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
        if (root == nullptr) {
            return;
        }

        Stack<TreeNode *> stack;
        stack.push(root);

        while (!stack.isEmpty()) {
            TreeNode *current = stack.pop();
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

    TreeNode *insertRec(TreeNode *node, T value) {
        if (node == nullptr) {
            return new TreeNode(value);  // Crear un nuevo nodo si el actual es nulo
        }

        if (value < node->data) {
            node->left = insertRec(node->left, value);
        } else if (value > node->data) {
            node->right = insertRec(node->right, value);
        }

        return node;
    }

    bool findRec(TreeNode *node, T value) {
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

    void inorder(TreeNode *node) {
        if (node != nullptr) {
            inorder(node->left);
            cout << node->data << " ";
            inorder(node->right);
        }
    }

    void preorder(TreeNode *node) {
        if (node != nullptr) {
            cout << node->data << " ";
            preorder(node->left);
            preorder(node->right);
        }
    }

    void postorder(TreeNode *node) {
        if (node != nullptr) {
            postorder(node->left);
            postorder(node->right);
            cout << node->data << " ";
        }
    }

    TreeNode *removeRec(TreeNode *node, T value) {
        if (node == nullptr) {
            return node;
        }

        if (value < node->data) {
            node->left = removeRec(node->left, value);
        } else if (value > node->data) {
            node->right = removeRec(node->right, value);
        } else {
            // Nodo encontrado
            if (node->left == nullptr) {
                TreeNode *temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                TreeNode *temp = node->left;
                delete node;
                return temp;
            }

            // Nodo con dos hijos
            TreeNode *temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = removeRec(node->right, temp->data);
        }
        return node;
    }

    TreeNode *minValueNode(TreeNode *node) {
        TreeNode *current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }
};


class Solution {
public:
    TreeNode* lcaDeepestLeaves(TreeNode* root) {

        int maxDepth = getMaxDepth(root);
        return findLCA(root, 0, maxDepth);
    }

private:
    int getMaxDepth(TreeNode* node) {

        if (node == nullptr) {
            return 0;
        }

        int leftDepth = getMaxDepth(node->left);
        int rightDepth = getMaxDepth(node->right);

        return 1 + max(leftDepth, rightDepth);
    }

    TreeNode* findLCA(TreeNode* node, int currentDepth, int maxDepth) {

        //caso donde el arbol es vacio
        if (node == nullptr) {
            return nullptr;
        }

        //caso donde ambos nodos que le siguen son de maxima profundidad
        if (currentDepth == maxDepth - 1 and node->left == nullptr and node->right == nullptr) {
            return node;
        }

        TreeNode* leftLCA = findLCA(node->left, currentDepth + 1, maxDepth);
        TreeNode* rightLCA = findLCA(node->right, currentDepth + 1, maxDepth);

        //caso donde ambos subarboles que le siguen tienen hojas mas profundas
        if (leftLCA != nullptr and rightLCA != nullptr) {
            return node;
        }

        //caso donde solo un subarbol tiene hojas mas profundas
        if (leftLCA != nullptr) {
            return leftLCA;
        }
        else {
            return rightLCA;
        }
    }


};


int main() {

    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);

    Solution solution;
    TreeNode* lca = solution.lcaDeepestLeaves(root);

    cout << "el ancestro comun mas bajo de las hojas mas profundas es: " << lca->data << endl;

}

