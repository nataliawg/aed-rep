//
// Created by NATALIA WATSON on 11/09/2024.
//

#include <iostream>
using namespace std;

//implementando listas enlazadas
class MinStack {
private:

    struct Node{
        int value;
        Node* next;

        Node (int val, Node* nxt = nullptr): value(val), next(nxt){}
    };

    Node* head;
    Node* minHead;

public:
    MinStack(): head(nullptr), minHead(nullptr){}

    void push(int val) {

        //se hace el push al stack original independientemente de si es el menor o no
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;

        if (minHead == nullptr){
            minHead = new Node(val);
        }
        else if (val <= minHead->value or minHead == nullptr){
            Node* newMin = new Node(val);
            newMin->next = minHead;
            minHead = newMin;
        }


    }

        void pop() {

            if (head == nullptr) {
                return;
            }

            //por si es que el valor a popear es el minimo hasta ahora, se elimina de la pila de min
            if (head->value == minHead->value){
                Node* tempMin = minHead;
                minHead = minHead->next;
                delete tempMin;

            }

            Node* temp = head;
            head = head->next;
            delete temp;


        }

    int top() {

        if(head == nullptr){
            return -1;
        }

        return head->value;
    }

    int getMin() {

        if (minHead == nullptr){
            return -1;
        }

        return minHead->value;
    }
};

int main(){

}