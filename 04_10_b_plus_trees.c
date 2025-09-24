#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ORDER 3

typedef struct BPTreeNode {
    bool isLeaf;
    int numKeys;
    int keys[ORDER - 1];
    struct BPTreeNode* children[ORDER]; 
    struct BPTreeNode* next;              
} BPTreeNode;

typedef struct BPTree {
    BPTreeNode* root;
} BPTree;

BPTreeNode* createNode(bool isLeaf) {
    BPTreeNode* node = (BPTreeNode*)malloc(sizeof(BPTreeNode));
    node->isLeaf = isLeaf;
    node->numKeys = 0;
    node->next = NULL;
    for (int i = 0; i < ORDER; i++) node->children[i] = NULL;
    return node;
}

BPTree* createTree() {
    BPTree* tree = (BPTree*)malloc(sizeof(BPTree));
    tree->root = createNode(true);
    return tree;
}

BPTreeNode* searchItem(BPTree* tree, int key) {
    BPTreeNode* current = tree->root;
    while (!current->isLeaf) {
        int i = 0;
        while (i < current->numKeys && key >= current->keys[i]) i++;
        current = current->children[i];
    }

    for (int i = 0; i < current->numKeys; i++) {
        if (current->keys[i] == key)
            return current;
    }
    return NULL;
}

void splitLeaf(BPTreeNode* parent, BPTreeNode* leaf, int insertIndex, int key, BPTreeNode** newLeafOut) {
    BPTreeNode* newLeaf = createNode(true);

    int tempKeys[ORDER];
    for (int i = 0, j = 0; i < leaf->numKeys; i++, j++) {
        if (j == insertIndex) j++;
        tempKeys[j] = leaf->keys[i];
    }
    tempKeys[insertIndex] = key;

    leaf->numKeys = (ORDER - 1) / 2;
    newLeaf->numKeys = ORDER - 1 - leaf->numKeys;

    for (int i = 0; i < leaf->numKeys; i++)
        leaf->keys[i] = tempKeys[i];
    for (int i = 0; i < newLeaf->numKeys; i++)
        newLeaf->keys[i] = tempKeys[i + leaf->numKeys];

    newLeaf->next = leaf->next;
    leaf->next = newLeaf;

    *newLeafOut = newLeaf;
}

void insertInternal(BPTreeNode* parent, BPTreeNode* child, int key, BPTreeNode* newChild) {
    int i;
    for (i = parent->numKeys - 1; i >= 0 && parent->keys[i] > key; i--) {
        parent->keys[i + 1] = parent->keys[i];
        parent->children[i + 2] = parent->children[i + 1];
    }

    parent->keys[i + 1] = key;
    parent->children[i + 2] = newChild;
    parent->numKeys++;
}

void splitInternal(BPTreeNode** root, BPTreeNode* node, int* promotedKey, BPTreeNode** newChildOut) {
    int mid = node->numKeys / 2;
    *promotedKey = node->keys[mid];

    BPTreeNode* newNode = createNode(false);
    newNode->numKeys = node->numKeys - mid - 1;

    for (int i = 0; i < newNode->numKeys; i++)
        newNode->keys[i] = node->keys[i + mid + 1];

    for (int i = 0; i <= newNode->numKeys; i++)
        newNode->children[i] = node->children[i + mid + 1];

    node->numKeys = mid;
    *newChildOut = newNode;
}

BPTreeNode* insertRecursive(BPTreeNode* node, int key, int* promotedKey, BPTreeNode** newChild) {
    if (node->isLeaf) {
        int i;
        for (i = 0; i < node->numKeys && key > node->keys[i]; i++);

        if (node->numKeys < ORDER - 1) {
            for (int j = node->numKeys; j > i; j--)
                node->keys[j] = node->keys[j - 1];
            node->keys[i] = key;
            node->numKeys++;
            return NULL;
        } else {
            BPTreeNode* newLeaf;
            splitLeaf(NULL, node, i, key, &newLeaf);
            *promotedKey = newLeaf->keys[0];
            *newChild = newLeaf;
            return node;
        }
    } else {
        int i;
        for (i = 0; i < node->numKeys && key >= node->keys[i]; i++);
        int tempKey;
        BPTreeNode* tempChild = NULL;
        BPTreeNode* result = insertRecursive(node->children[i], key, &tempKey, &tempChild);
        if (result == NULL) return NULL;

        if (node->numKeys < ORDER - 1) {
            insertInternal(node, result, tempKey, tempChild);
            return NULL;
        } else {
            BPTreeNode* newNode;
            int newPromotedKey;
            splitInternal(NULL, node, &newPromotedKey, &newNode);
            if (tempKey < newPromotedKey)
                insertInternal(node, result, tempKey, tempChild);
            else
                insertInternal(newNode, result, tempKey, tempChild);

            *promotedKey = newPromotedKey;
            *newChild = newNode;
            return node;
        }
    }
}

void insertItem(BPTree* tree, int key) {
    int promotedKey;
    BPTreeNode* newChild = NULL;
    BPTreeNode* result = insertRecursive(tree->root, key, &promotedKey, &newChild);

    if (result != NULL) {
        BPTreeNode* newRoot = createNode(false);
        newRoot->keys[0] = promotedKey;
        newRoot->children[0] = tree->root;
        newRoot->children[1] = newChild;
        newRoot->numKeys = 1;
        tree->root = newRoot;
    }
}

void deleteTree(BPTreeNode* node) {
    if (!node) return;
    if (!node->isLeaf) {
        for (int i = 0; i <= node->numKeys; i++) {
            deleteTree(node->children[i]);
        }
    }
    free(node);
}

void printLeaves(BPTree* tree) {
    BPTreeNode* current = tree->root;
    while (!current->isLeaf)
        current = current->children[0];

    printf("B+ Tree Leaf Level: ");
    while (current) {
        for (int i = 0; i < current->numKeys; i++)
            printf("%d ", current->keys[i]);
        current = current->next;
    }
    printf("\n");
}

int main() {
    BPTree* tree = createTree();

    int keys[] = {10, 20, 5, 6, 12, 30, 7, 17};
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++) {
        insertItem(tree, keys[i]);
    }

    printLeaves(tree);

    int searchKey = 12;
    BPTreeNode* result = searchItem(tree, searchKey);
    printf("Search %d: %s\n", searchKey, result ? "Found" : "Not Found");

    deleteTree(tree->root);
    free(tree);
    return 0;
}
