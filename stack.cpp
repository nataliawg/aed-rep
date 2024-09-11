//
// Created by NATALIA WATSON on 9/09/2024.
//

#include <iostream>
#define MAX_STACK_SIZE 100
using namespace std;

typedef struct{
    int key;

} element;

typedef struct {
    element list[MAX_STACK_SIZE];
    int top;

} stack;

int isfull(stack* s){

    if (s->top >= MAX_STACK_SIZE-1){
        return 1;
    }
    return 0;
}

int isempty(stack* s){

    if (s->top == -1){
        return 1;
    }

    return 0;
}

element top(stack* s){

    return s->list[s->top];
}

void push (stack* s, element e){

    (s->top)++;
    s->list[s->top] = e;
}

void pop(stack* s){

    s->list[s->top] = (element){0};
    (s->top)--;
}




int main(){

    stack Z;
    Z.top = -1;

}
