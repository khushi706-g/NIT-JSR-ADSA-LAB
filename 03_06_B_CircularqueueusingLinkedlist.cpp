#include <stdio.h>
#include <stdlib.h>

// Node 
struct Node {
    int data;
    struct Node* next;
};

struct Node *front = NULL, *rear = NULL;

// Enqueue operation
void enqueue(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    if (front == NULL) {
        front = rear = newNode;
        rear->next = front;  // circular link
    } else {
        rear->next = newNode;
        rear = newNode;
        rear->next = front;  // maintain circular link
    }
    printf("%d enqueued to queue\n", value);
}

// Dequeue operation
void dequeue() {
    if (front == NULL) {
        printf("Queue is Empty!\n");
        return;
    }
    if (front == rear) {
        printf("%d dequeued from queue\n", front->data);
        free(front);
        front = rear = NULL;
    } else {
        struct Node* temp = front;
        printf("%d dequeued from queue\n", temp->data);
        front = front->next;
        rear->next = front;
        free(temp);
    }
}

// Display operation
void display() {
    if (front == NULL) {
        printf("Queue is Empty!\n");
        return;
    }
    struct Node* temp = front;
    printf("Queue: ");
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != front);
    printf("\n");
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    display();

    dequeue();
    dequeue();
    display();

    enqueue(50);
    enqueue(60);
    display();

    return 0;
}

