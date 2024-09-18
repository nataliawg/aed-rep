//
// Created by NATALIA WATSON on 17/09/2024.
//
#include <iostream>
#include <cmath>
#include <random>
#include <set>
#include <string>
#include <type_traits>
#include <vector>
#include <unordered_set>

using namespace std;

#define MAX_SIZE 50

template <typename T, typename V>
struct Node {
    T key;
    V value;
    Node* next;
};

template <typename T, typename V>
class LinkedList {
    Node<T, V>* head;

public:
    LinkedList() : head(NULL) {}

    int push_front(T key, V valor) {
        Node<T, V>* temp = head;
        bool found = false;
        while (temp != NULL && !found) {
            if (temp->key == key) {
                temp->value = valor;
                found = true;
            } else {
                temp = temp->next;
            }
        }

        if (found) {
            return 0;
        } else {
            Node<T, V>* nodo = new Node<T, V>;
            nodo->key = key;
            nodo->value = valor;
            nodo->next = head;
            head = nodo;
            return 1;
        }
    }

    V findKey(T key){
        Node<T,V>*  temp = head;
        bool flag = false;
        int i = 0;
        while(!flag && temp!=NULL){
            if(temp->key==key){
                flag=true;
            }else{
                temp = temp->next;
                i++;
            }
        }

        if(flag==true){
            return temp->value;
        }
        else{
            return V();
        }

    }

    void deleteKey(T key) {
        Node<T, V>* temp = head;
        Node<T, V>* prev = NULL;
        while (temp != NULL) {
            if (temp->key == key) {
                if (temp == head) {
                    head = head->next;
                } else {
                    prev->next = temp->next;
                }
                delete temp;
                return;
            }
            prev = temp;
            temp = temp->next;
        }
    }

    bool empty() {
        return head == NULL;
    }

    int size() {
        int s = 0;
        Node<T, V>* temp = head;
        while (temp != NULL) {
            s++;
            temp = temp->next;
        }
        return s;
    }

    void clear() {
        while (head != NULL) {
            Node<T, V>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    Node<T, V>* gethead() {
        return head;
    }
};

template <typename T, typename V>
class TablaHash {
    int m = MAX_SIZE;
    LinkedList<T, V>* LlistArray; //cambiar a puntero dinamico
    int nelements;
    int P = 97;
    int maxCol = 3;
    float fillfactor;
    int a;
    int b;

public:
    TablaHash() : nelements(0) {
        LlistArray = new LinkedList<T, V>[m];
        a = getRandomNumber(1, P - 1);
        b = getRandomNumber(0, P - 1);
    }

    ~TablaHash() {
        delete[] LlistArray;
    }

    int getRandomNumber(int lower, int P) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(lower, P - 1);
        return distrib(gen);
    }

    int newkey(T key) {
        int nkey = 0;
        if constexpr (std::is_same_v<T, std::string>) {

            nkey = 0;
            int size=0;
            for (char c : key) {
                size++;
            }

            for (char c:key)
            {
                nkey+=(static_cast<int>(c))*static_cast<int>(pow(2,size-1));
                size--;
            }
            return nkey;

        } else if constexpr (std::is_same_v<T, char>) {

            nkey=static_cast<int>(key);
            return nkey;
        } else if constexpr (std::is_same_v<T, float>) {
            nkey = static_cast<int>(key * 1000);
        } else {
            throw invalid_argument("esta variable no esta siendo manejada");
        }
        return nkey;
    }

    int hashingfunction(T key) {
        int nkey = newkey(key);
        return ((a * nkey + b) % P) % m;
    }

    void insert(T key, V value) {
        int index = hashingfunction(key);
        if (LlistArray[index].size() >= maxCol) {
            reHash();
            index = hashingfunction(key);
        }

        int i = LlistArray[index].push_front(key, value);
        nelements += i;

        fillfactor = static_cast<float>(nelements) / (maxCol * m);
        if (fillfactor > 0.5) {
            reHash();
        }
    }

    V search(T key) {
        int index = hashingfunction(key);
        return LlistArray[index].findKey(key);
    }

    void Delete(T key) {
        int index = hashingfunction(key);
        LlistArray[index].deleteKey(key);
    }

    void reHash() {
        int new_size = m * 2;
        LinkedList<T, V>* new_list_array = new LinkedList<T, V>[new_size];

        LinkedList<T, V>* old_list_array = LlistArray;
        int old_size = m;

        m = new_size;
        LlistArray = new_list_array;

        a = getRandomNumber(1, P - 1);
        b = getRandomNumber(0, P - 1);

        for (int i = 0; i < old_size; ++i) {
            Node<T, V>* temp = old_list_array[i].gethead();
            while (temp != NULL) {
                int new_index = hashingfunction(temp->key);
                LlistArray[new_index].push_front(temp->key, temp->value);
                temp = temp->next;
            }
        }

        delete[] old_list_array;
    }
};

int morseCount(vector<string> v_input, TablaHash<char, string>& hash_input) {
    unordered_set<string> uniqueTransformations;

    for (const auto& word : v_input) {
        string morseCode;

        for (const auto& letter : word) {
            morseCode += hash_input.search(letter);
        }

        uniqueTransformations.insert(morseCode);
    }

    return uniqueTransformations.size();
}

int main() {


    TablaHash<char, string> tablita;
    tablita.insert('a', ".-");
    tablita.insert('b', "-...");
    tablita.insert('c', "-.-.");
    tablita.insert('d', "-..");
    tablita.insert('e', ".");
    tablita.insert('f', "..-.");
    tablita.insert('g', "--.");
    tablita.insert('h', "....");
    tablita.insert('i', "..");
    tablita.insert('j', ".---");
    tablita.insert('k', "-.-");
    tablita.insert('l', ".-..");
    tablita.insert('m', "--");
    tablita.insert('n', "-.");
    tablita.insert('o', "---");
    tablita.insert('p', ".--.");
    tablita.insert('q', "--.-");
    tablita.insert('r', ".-.");
    tablita.insert('s', "...");
    tablita.insert('t', "-");
    tablita.insert('u', "..-");
    tablita.insert('v', "...-");
    tablita.insert('w', ".--");
    tablita.insert('x', "-..-");
    tablita.insert('y', "-.--");
    tablita.insert('z', "--..");

    // Ejemplo de entrada: Vector de palabras
    vector<string> vector1 = {"gin", "zen", "gig", "msg"};

    // Llamar a la función y mostrar el resultado
    cout << "Número de transformaciones Morse únicas: " << morseCount(vector1, tablita) << endl;


}
