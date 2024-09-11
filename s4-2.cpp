#include <iostream>
using namespace std;

class MyCircularDeque{

private:
    int front, rear, size, capacity;
    int* deque;

public:

    MyCircularDeque(int k): front(0), rear(0), size(0), capacity(k){
        deque = new int[k];
    }

    bool insertFront(int value) {

        if (isFull()){
            return false;
        }

        front = (front-1 + capacity) % capacity; //mantiene a front dentro del rango segun la proporcion de la capacidad
        deque[front] = value;
        size++;

        return true;

    }


    bool insertLast(int value) {

        if (isFull()){
            return false;
        }

        deque[rear] = value;
        rear = (rear+1) % capacity;
        size++;

        return true;

    }

    bool deleteFront() {

        if (isEmpty()){
            return false;
        }

        front = (front+1) % capacity;
        size--;

        return true;
    }


    bool deleteLast() {

        if (isEmpty()){
            return false;
        }

        rear = (rear-1 + capacity) % capacity;
        size--;

        return true;
    }


    int getFront() {
        if (isEmpty()) {
            return -1;
        }

        return deque[front];
    }

    int getRear() {
        if (isEmpty()) {
            return -1;
        }

        return deque[(rear - 1 + capacity) % capacity];
    }

    bool isEmpty() {

        if (size == 0){
            return true;
        }
        else{
            return false;
        }

    }

    bool isFull() {

        if (size == capacity){
            return true;
        }
        else{
            return false;
        }
    }

    ~MyCircularDeque(){
        delete[] deque;
    }
};

int main(){

}