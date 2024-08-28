#include <iostream>
using namespace std;

struct ListNode {

    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        while (head != nullptr && head->val == val) { //bucle para el caso de eliminiar el head
            ListNode* temp = head; //se asigna el temporal al head a eliminar
            head = head->next; //se le asigna head al siguiente
            delete temp; //se elimina
        }

        ListNode* current = head; //current para manejar el valor actual al recorrer (comienza con el head)
        while (current != nullptr && current->next != nullptr) { //el bucle se delimita mientras el current y su respectivo next no sea nulo
            if (current->next->val == val) { //se verifica si el siguiente valor al current es val
                ListNode* temp = current->next; //se crea un temp para eliminarlo
                current->next = current->next->next; //se le asigna el siguiente current a que sea el siguiente siguiente
                delete temp; //se elimina pues existe redundancia
            } else {
                current = current->next; //si no se encuentra la coincidencia, solo se avanza el bucle
            }
        }

        return head;
    }
};

void printList(ListNode* head) {
    if (head == nullptr) {
        cout << "[]" << endl;
        return;
    }

    cout << "[";
    ListNode* current = head;
    while (current != nullptr) {
        cout << current->val;
        if (current->next != nullptr) {
            cout << ",";
        }
        current = current->next;
    }
    cout << "]" << endl;
}

int main() {
    Solution solution; //crear el objeto

    //crear nodos
    ListNode* node1 = new ListNode(1);
    ListNode* node2 = new ListNode(2);
    ListNode* node3 = new ListNode(6);
    ListNode* node4 = new ListNode(3);
    ListNode* node5 = new ListNode(4);
    ListNode* node6 = new ListNode(5);
    ListNode* node7 = new ListNode(6);

    //definir los punteros
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;
    node5->next = node6;
    node6->next = node7;

    ListNode* head1 = node1; //asignar el primer nodo a head
    int val1 = 6; //valor a eliminar

    ListNode* result1 = solution.removeElements(head1, val1); //aplicar fucncion
    cout << "Resultado para [1,2,6,3,4,5,6], val = 6: ";
    printList(result1);

    //eliminar memoria
    while (result1 != nullptr) {
        ListNode* temp = result1;
        result1 = result1->next;
        delete temp;
    }

    ListNode* head2 = nullptr;
    int val2 = 1;

    ListNode* result2 = solution.removeElements(head2, val2);
    cout << "Resultado para [], val = 1: ";
    printList(result2);

    ListNode* node8 = new ListNode(7);
    ListNode* node9 = new ListNode(7);
    ListNode* node10 = new ListNode(7);
    ListNode* node11 = new ListNode(7);

    node8->next = node9;
    node9->next = node10;
    node10->next = node11;

    ListNode* head3 = node8;
    int val3 = 7;

    ListNode* result3 = solution.removeElements(head3, val3);
    cout << "Resultado para [7,7,7,7], val = 7: ";
    printList(result3);

    while (result3 != nullptr) {
        ListNode* temp = result3;
        result3 = result3->next;
        delete temp;
    }
}
