#include <iostream>
#include <vector>
using namespace std;

const int MAX_NODES = 100;


class Queue {
    struct Node {
        int data;
        Node* next;
        Node(int data) : data(data), next(nullptr) {}
    };
    Node* frontNode = nullptr;
    Node* rearNode = nullptr;

public:
    bool isEmpty() { return frontNode == nullptr; }

    void enqueue(int data) {
        Node* newNode = new Node(data);
        if (rearNode != nullptr) {
            rearNode->next = newNode;
        }
        rearNode = newNode;
        if (frontNode == nullptr) {
            frontNode = newNode;
        }
    }

    int dequeue() {
        if (isEmpty()) return -1;
        int data = frontNode->data;
        Node* temp = frontNode;
        frontNode = frontNode->next;
        if (frontNode == nullptr) rearNode = nullptr;
        delete temp;
        return data;
    }
};

vector<int> graph[MAX_NODES];
bool visited[MAX_NODES];

void BFS(int start_node) {
    Queue queue;
    visited[start_node] = true;
    queue.enqueue(start_node);

    while (!queue.isEmpty()) {
        int current_node = queue.dequeue();
        cout << current_node << " "; 

        for (int neighbor : graph[current_node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                queue.enqueue(neighbor);
            }
        }
    }
}


void DFS(int node) {
    visited[node] = true;
    cout << node << " "; 

    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            DFS(neighbor);
        }
    }
}
