//
// Created by NATALIA WATSON on 9/09/2024.
//

#include <iostream>
#define MAX_Q_SIZE 100
using namespace std;

typedef struct {

    int key;

} element;

typedef struct {

    element list[MAX_Q_SIZE];
    int front, rear;

} queue;

int isfull(queue* q){

    if (q->front == ((q->rear+1) % MAX_Q_SIZE)){ //la siguiente posición de rear debe coincidir con front (no debe haber residuo con maxqsize)
        return 1;
    }

    return 0;
}

int isempty(queue* q){

    if (q->front == q->rear){
        return 1;
    }

    return 0;
}

element front(queue* q){

    return q->list[(q->front+1) % MAX_Q_SIZE]; //recordar que front esta justo antes del primer elemento
}

void enqueue(queue* q, element e){

    q->rear = (q->rear+1) % MAX_Q_SIZE; //rear avanza una poisición, se aumenta un elemento
    q->list[q->rear] = e; //el nuevo elemento se vuele rear
}

void dequeue(queue* q){

    q->front = (q->front+1) % MAX_Q_SIZE; //front avanza otra posición, significa que el primer elemento del queue ya no se considera
}


int main(){

    queue Q;
    Q.front = 0;
    Q.rear = 0;

}