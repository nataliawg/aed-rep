#include <iostream>
using namespace std;

template <typename T>
struct Node {
    T data;      
    Node* next;
};

template <typename T>
class LinkedList {
    Node<T>* head;

    public:
    LinkedList() : head(NULL) {}

    T front() {
        if(head == NULL) {
            cout << "La lista esta vacia" << endl;
            return T();
        }
        return head->data;
    }

    T back() {
        if(head == NULL) {
            cout << "Lista vacia" << endl;
            return T();
        }
        Node<T>* temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        return temp->data;
    } 

    void push_front(T valor) {
        Node<T>* nodo = new Node<T>;
        nodo->data = valor;
        nodo->next = head;
        head = nodo;
    }

    void push_back(T valor) {
        Node<T>* nodo = new Node<T>;
        nodo->data = valor;
        nodo->next = NULL;
        if(head == NULL){
            head = nodo;
        } else {
            Node<T>* temp = head;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = nodo;
        }
    }

    T pop_front() {
        if(head == NULL) {
            cout << "Lista vacia" << endl;
            return T();
        }
        Node<T>* temp = head;
        T valor = temp->data;
        head = head->next;
        delete temp;
        return valor;
    }

    T pop_back() {
        if(head == NULL) {
            cout << "Lista vacia" << endl;
            return T();
        } else if (head->next == NULL) {
            T valor = head->data;
            delete head;
            head = NULL;
            return valor;
        } else {
            Node<T>* temp = head;
            while (temp->next->next != NULL)
                temp = temp->next;
            T valor = temp->next->data;
            delete temp->next;
            temp->next = NULL;
            return valor;
        }
    }

    T operator[](int index) {
        Node<T>* temp = head;
        for(int i = 0; i < index; i++) {
            if(temp == NULL) return T(); // En caso de índice fuera de rango
            temp = temp->next;
        }
        return temp->data;
    }

    bool empty() {
        return head == NULL;
    }

    int size() {
        int s = 0;
        Node<T>* temp = head;
        while (temp != NULL) {
            temp = temp->next;
            s++;
        }
        return s;
    } 

    void clear() {
        while(head != NULL) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void reverse() {
        Node<T>* previo = NULL;
        Node<T>* actual = head;
        Node<T>* siguiente;
        while (actual != NULL) {
            siguiente = actual->next;
            actual->next = previo;
            previo = actual;
            actual = siguiente;
        }
        head = previo;
    } 

    void sort() {
        if(head != NULL) {
            bool swapped;
            Node<T>* temp;
            Node<T>* ultimo = NULL;

            do {
                swapped = false;
                temp = head;
                while (temp->next != ultimo) {
                    if (temp->data > temp->next->data) {
                        T swap = temp->data;
                        temp->data = temp->next->data;
                        temp->next->data = swap;
                        swapped = true;
                    }
                    temp = temp->next;
                }
                ultimo = temp;
            } while (swapped);
        }
    }

    bool remove(T valor) {
        if(head == NULL) return false;
        if(head->data == valor) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            return true;
        }
        Node<T>* temp = head;
        while (temp->next != NULL && temp->next->data != valor)
            temp = temp->next;
        if(temp->next == NULL) return false;
        Node<T>* toDelete = temp->next;
        temp->next = toDelete->next;
        delete toDelete;
        return true;
    }

    bool contains(T valor) {
        Node<T>* temp = head;
        while (temp != NULL) {
            if(temp->data == valor) return true;
            temp = temp->next;
        }
        return false;
    }

    void print() {
        Node<T>* actual = head;
        while(actual != NULL) {
            cout << actual->data << " ";
            actual = actual->next;
        }
    }    
};

template <typename T>
class Queue {
    LinkedList<T> list;
    
    public:
    void enqueue(T valor) {
        list.push_back(valor);
    }
    
    T dequeue() {
        return list.pop_front();
    }
    
    bool isEmpty() {
        return list.empty();
    }
};

template <typename T>
class Stack {
    LinkedList<T> list;

    public:
    void push(T valor) {
        list.push_front(valor);
    }

    T pop() {
        return list.pop_front();
    }

    bool isEmpty() {
        return list.empty();
    }
};

template <typename T>
class Graph {
    const int size = 20;
    LinkedList<T> grafo[20];

    public:
    Graph(){}

    void add_edge(T a, T b) {
        grafo[a].push_back(b);
        grafo[b].push_back(a);
    }

    void remove_edge(T a, T b) {
        grafo[a].remove(b);
        grafo[b].remove(a);
    }

    bool edge_exists(T a, T b) {
        return grafo[a].contains(b);
    }

    void print(){
        for (int i = 0; i < size; i++) {
            cout << i << ": ";
            grafo[i].print();
            cout << endl;
        }  
    }

    void bfs(T start) {
        bool visited[size] = {false};
        Queue<T> queue;
        queue.enqueue(start);
        visited[start] = true;

        while (!queue.isEmpty()) {
            T node = queue.dequeue();
            cout << node << " ";
            Node<T>* temp = grafo[node].head;

            while (temp != NULL) {
                if (!visited[temp->data]) {
                    queue.enqueue(temp->data);
                    visited[temp->data] = true;
                }
                temp = temp->next;
            }
        }
        cout << endl;
    }

    void dfs(T start) {
        bool visited[size] = {false};
        Stack<T> stack;
        stack.push(start);

        while (!stack.isEmpty()) {
            T node = stack.pop();
            if (!visited[node]) {
                cout << node << " ";
                visited[node] = true;
            }
            Node<T>* temp = grafo[node].head;
            while (temp != NULL) {
                if (!visited[temp->data]) {
                    stack.push(temp->data);
                }
                temp = temp->next;
            }
        }
        cout << endl;
    }
};

int main() {
    Graph<int> grafo;
    grafo.add_edge(0, 1);
    grafo.add_edge(0, 2);
    grafo.add_edge(1, 3);
    grafo.add_edge(2, 3);
    grafo.add_edge(3, 4);

    cout << "Grafo inicial:" << endl;
    grafo.print();

    cout << "BFS desde el nodo 0:" << endl;
    grafo.bfs(0);

    cout << "DFS desde el nodo 0:" << endl;
    grafo.dfs(0);

    return 0;
}
