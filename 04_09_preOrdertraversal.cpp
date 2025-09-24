#include <stdio.h>
#include <stdlib.h>

#define STACK_MAX 100
#define QUEUE_MAX 100

typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct {
    TreeNode* data[STACK_MAX];
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
}

void push(Stack* s, TreeNode* node) {
    if (s->top < STACK_MAX - 1) {
        s->data[++(s->top)] = node;
    }
}

TreeNode* pop(Stack* s) {
    if (s->top >= 0) {
        return s->data[(s->top)--];
    }
    return NULL;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

typedef struct {
    TreeNode* data[QUEUE_MAX];
    int front, rear;
} Queue;

void initQueue(Queue* q) {
    q->front = q->rear = 0;
}

void enqueue(Queue* q, TreeNode* node) {
    if ((q->rear + 1) % QUEUE_MAX != q->front) {
        q->data[q->rear] = node;
        q->rear = (q->rear + 1) % QUEUE_MAX;
    }
}

TreeNode* dequeue(Queue* q) {
    if (q->front == q->rear) return NULL;
    TreeNode* node = q->data[q->front];
    q->front = (q->front + 1) % QUEUE_MAX;
    return node;
}

int isQueueEmpty(Queue* q) {
    return q->front == q->rear;
}

TreeNode* createNode(int val) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->val = val;
    node->left = node->right = NULL;
    return node;
}

TreeNode* buildTreeFromInput() {
    int val;
    printf("Enter value for root: ");
    scanf("%d", &val);
    if (val == -1) return NULL;

    TreeNode* root = createNode(val);
    Queue q;
    initQueue(&q);
    enqueue(&q, root);

    while (!isQueueEmpty(&q)) {
        TreeNode* current = dequeue(&q);

        printf("Enter left child of %d (-1 for NULL): ", current->val);
        scanf("%d", &val);
        if (val != -1) {
            current->left = createNode(val);
            enqueue(&q, current->left);
        }

        printf("Enter right child of %d (-1 for NULL): ", current->val);
        scanf("%d", &val);
        if (val != -1) {
            current->right = createNode(val);
            enqueue(&q, current->right);
        }
    }

    return root;
}

void preorderTraversal(TreeNode* root) {
    if (root == NULL) return;

    Stack stack;
    initStack(&stack);
    push(&stack, root);

    while (!isEmpty(&stack)) {
        TreeNode* node = pop(&stack);
        printf("%d ", node->val); 

        if (node->right) push(&stack, node->right);
        if (node->left) push(&stack, node->left);
    }
}

int main() {
    TreeNode* root = buildTreeFromInput();

    printf("\nPreorder Traversal: ");
    preorderTraversal(root);
    printf("\n");

    return 0;
}
