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
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr or head->next == nullptr) { //si es que esta vacia
            return head;
        }

        //se inicializan punteros para prev, current y newhead
        ListNode* prev = nullptr;
        ListNode* current = head;
        ListNode* newHead = head->next;

        while (current != nullptr and current->next != nullptr) { //recorre la lista
            //establece el primero y el segundo nodo como current y su siguiente
            ListNode* n1 = current;
            ListNode* n2 = current->next;

            n1->next = n2->next; //el siguiente del primero es el siguiente del segundo
            n2->next = n1; //el siguiente del segundo es el primero, ya que se cambio n1 para adelante

            //se debe conectar con el nodo previo a n2 que quedo en primera posicion, asi que:

            if (prev != nullptr) {
                prev->next = n2; //se actualiza su puntero para n2...
            }

            prev = n1; //... y para n1 (n1 se convierte en el prev para el par que sigue)

            current = n1->next; //se avanza el bucle
        }

        return newHead;
    }
};

void printLinkedList(ListNode* head) {
    ListNode* current = head;
    while (current != nullptr) {
        cout << current->val;
        if (current->next != nullptr) cout << " -> ";
        current = current->next;
    }
    cout << endl;
}

int main() {
    Solution solution;

    ListNode* head1 = new ListNode(1);
    head1->next = new ListNode(2);
    head1->next->next = new ListNode(3);
    head1->next->next->next = new ListNode(4);

    cout << "Lista original 1: ";
    printLinkedList(head1);

    head1 = solution.swapPairs(head1);
    cout << "Lista después de intercambiar 1: ";
    printLinkedList(head1);

    ListNode* head2 = nullptr;

    cout << "Lista original 2: ";
    printLinkedList(head2);

    head2 = solution.swapPairs(head2);
    cout << "Lista después de intercambiar 2: ";
    printLinkedList(head2);

    ListNode* head3 = new ListNode(1);

    cout << "Lista original 3: ";
    printLinkedList(head3);

    head3 = solution.swapPairs(head3);
    cout << "Lista después de intercambiar 3: ";
    printLinkedList(head3);


}
