#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

// Queue structure
struct Queue {
    int arr[SIZE];
    int front, rear;
};

void init(struct Queue* q) {
    q->front = q->rear = -1;
}

int isEmpty(struct Queue* q) {
    return (q->front == -1);
}

void enqueue(struct Queue* q, int x) {
    if (q->rear == SIZE - 1) {
        printf("Queue Overflow!\n");
        return;
    }
    if (q->front == -1) q->front = 0;
    q->arr[++q->rear] = x;
}

int dequeue(struct Queue* q) {
    if (isEmpty(q)) return -1;
    int val = q->arr[q->front];
    if (q->front == q->rear) q->front = q->rear = -1;
    else q->front++;
    return val;
}

// Stack using two queues
struct Stack {
    struct Queue q1, q2;
};

void initStack(struct Stack* s) {
    init(&s->q1);
    init(&s->q2);
}

void push(struct Stack* s, int x) {
    enqueue(&s->q1, x);
    printf("%d pushed\n", x);
}

int pop(struct Stack* s) {
    if (isEmpty(&s->q1)) {
        printf("Stack is Empty!\n");
        return -1;
    }

    // Move all but last element to q2
    while (s->q1.front != s->q1.rear) {
        enqueue(&s->q2, dequeue(&s->q1));
    }

    // Last element is stack top
    int val = dequeue(&s->q1);

    // Swap q1 and q2
    struct Queue temp = s->q1;
    s->q1 = s->q2;
    s->q2 = temp;

    return val;
}

int main() {
    struct Stack s;
    initStack(&s);

    push(&s, 10);
    push(&s, 20);
    push(&s, 30);

    printf("%d popped\n", pop(&s));
    printf("%d popped\n", pop(&s));

    push(&s, 40);
    printf("%d popped\n", pop(&s));

    return 0;
}

