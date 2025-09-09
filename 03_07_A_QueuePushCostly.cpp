#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

struct Stack {
    int arr[SIZE];
    int top;
};

void init(struct Stack* s) { s->top = -1; }
int isEmpty(struct Stack* s) { return s->top == -1; }
void push(struct Stack* s, int val) { s->arr[++s->top] = val; }
int pop(struct Stack* s) { return s->arr[s->top--]; }
int peek(struct Stack* s) { return s->arr[s->top]; }

// Queue using two stacks
struct Queue {
    struct Stack s1, s2;
};

void initQueue(struct Queue* q) {
    init(&q->s1);
    init(&q->s2);
}

void enqueue(struct Queue* q, int x) {
    // Move everything from s1 to s2
    while (!isEmpty(&q->s1)) {
        push(&q->s2, pop(&q->s1));
    }
    // Push new element into s1
    push(&q->s1, x);
    // Move everything back
    while (!isEmpty(&q->s2)) {
        push(&q->s1, pop(&q->s2));
    }
    printf("%d enqueued\n", x);
}

int dequeue(struct Queue* q) {
    if (isEmpty(&q->s1)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return pop(&q->s1);
}

int main() {
    struct Queue q;
    initQueue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);

    printf("%d dequeued\n", dequeue(&q));
    printf("%d dequeued\n", dequeue(&q));

    enqueue(&q, 40);
    printf("%d dequeued\n", dequeue(&q));

    return 0;
}

