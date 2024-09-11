#include <iostream>
#include <cmath>
#define MAX_STACK_SIZE 100
using namespace std;

template <typename T>
class Stack {

private:

    T list[MAX_STACK_SIZE]; // Aloco memoria para el array
    int top;

public:

    // Constructor
    Stack() : top(-1) {}

    bool isfull (){
        if (top >= MAX_STACK_SIZE - 1) // si top tiene mas que 99 es que esta lleno (va de 0 a 99)
            return true;
        return false;
    }

    bool isempty ()
    {
        if (top == -1) // Si top es -1 esta vacio
            return true;
        return false;
    }

    T gtop()
    {
        return list[top]; // Obtengo el ultimo valor de la lista de elementos
    }

    void push(T e )
    {
        (top)++; // Aumento el valor de top
        list[top] = e; //Agrego el elemento a la lista
    }

    void pop()
    {
        (top)--;// A top le bajo el valor por lo que se reescribira la lista cuando se vuelva a usar
        // Nota: basicamente se baja el valor de la lista
    }

};


int depth(string cadena) {

    Stack<char> stack1;
    int counter = 0;
    int maxcounter = 0;

    for (size_t i = 0; i < cadena.size(); ++i) {
        if (cadena[i] == '(') {
            stack1.push(cadena[i]);
            counter++;
            if (counter >= maxcounter) {
                maxcounter = counter;


            }
        }
        else if (cadena[i]==')'){
            stack1.pop();
            counter--;
        }
    }


    if (stack1.isempty()) {
            return maxcounter;
        }
        else {
            return 0;
        }
    }


int main(){
    string texto = "((()(())()))";
    cout << "Profundidad: " << depth(texto) << endl;
}