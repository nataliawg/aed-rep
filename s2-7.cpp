//
// Created by NATALIA WATSON on 28/08/2024.
//

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
    ListNode* insertGreatestCommonDivisors(ListNode* head) {

        ListNode* current = head; //se dirige el current a head para empezar

        while (current != nullptr and current->next != nullptr){ //bucle para recorrer
            int max_div = get_mcd(current->val, current->next->val); //se obiene el mcd del current y su siguiente

            ListNode* node = new ListNode(max_div); //se crea un nodo con el valor obtenido

            node->next = current->next; //se hace que el nodo apunte al mismo que apunta current
            current->next = node; //se hace que el siguiente a current sea node

            current = node->next; //se establece el current como el siguiente al nodo

        }

        return head;
    }

    int get_mcd(int a, int b){
        while (b != 0){
            int temp = b; //temp es b
            b = a%b; //b es modulo de a y b
            a = temp; //a es temp y asi sucesivamente
        }
        return a;

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

    ListNode* head1 = new ListNode(18);
    head1->next = new ListNode(6);
    head1->next->next = new ListNode(10);
    head1->next->next->next = new ListNode(3);

    cout << "Lista original 1: ";
    printLinkedList(head1);

    head1 = solution.insertGreatestCommonDivisors(head1);
    cout << "Lista después de la inserción 1: ";
    printLinkedList(head1);

    ListNode* head2 = new ListNode(7);

    cout << "Lista original 2: ";
    printLinkedList(head2);

    head2 = solution.insertGreatestCommonDivisors(head2);
    cout << "Lista después de la inserción 2: ";
    printLinkedList(head2);


}

