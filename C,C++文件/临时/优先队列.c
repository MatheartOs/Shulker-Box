//优先队列的纯c实现
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    int priority;
    struct Node* next;
} Node;

typedef struct PriorityQueue {
    Node* head;
} PriorityQueue;

PriorityQueue* createPriorityQueue() {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->head = NULL;
    return pq;
}

int isEmpty(PriorityQueue* pq) {
    return pq->head == NULL;
}

void enqueue(PriorityQueue* pq, int value, int priority) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->priority = priority;
    newNode->next = NULL;

    if (isEmpty(pq) || pq->head->priority < priority) {
        newNode->next = pq->head;
        pq->head = newNode;
    } else {
        Node* current = pq->head;
        while (current->next != NULL && current->next->priority >= priority) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

int dequeue(PriorityQueue* pq) {
    if (isEmpty(pq)) {
        printf("Priority Queue is empty\n");
        return -1;  // 表示队列空
    }
    Node* temp = pq->head;
    int dequeuedValue = temp->data;
    pq->head = pq->head->next;
    free(temp);
    return dequeuedValue;
}

int peek(PriorityQueue* pq) {
    if (isEmpty(pq)) {
        printf("Priority Queue is empty\n");
        return -1;  // 表示队列空
    }
    return pq->head->data;
}

void freePriorityQueue(PriorityQueue* pq) {
    while (!isEmpty(pq)) {
        dequeue(pq);
    }
    free(pq);
}

int main() {
    PriorityQueue* pq = createPriorityQueue();
    enqueue(pq, 10, 2);
    enqueue(pq, 20, 1);
    enqueue(pq, 30, 3);
    printf("Front element is %d\n", peek(pq));
    printf("Dequeued element is %d\n", dequeue(pq));
    printf("Front element is %d\n", peek(pq));
    freePriorityQueue(pq);
    return 0;
}
