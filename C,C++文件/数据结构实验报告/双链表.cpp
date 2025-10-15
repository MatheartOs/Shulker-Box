//创建2个双链表，a: [0,1,2,3,4], b: [0,1,2,3,4],将对应元素相加结果保存到新的双链表c
#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}
Node* addTwoLists(Node* a, Node* b) {
    Node* dummy = createNode(0);
    Node* tail = dummy;
    while (a || b) {
        int sum = (a ? a->data : 0) + (b ? b->data : 0);
        Node* newNode = createNode(sum);
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
        if (a) a = a->next;
        if (b) b = b->next;
    }
    return dummy->next;
}
void printList(Node* head) {
    Node* current = head;
    while (current) {
        printf("%d <-> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}
void freeList(Node* head) {
    Node* current = head;
    Node* next;
    while (current) {
        next = current->next;
        free(current);
        current = next;
    }
}
int main() {
    Node* a = createNode(0);
    a->next = createNode(1);
    a->next->prev = a;
    a->next->next = createNode(2);
    a->next->next->prev = a->next;
    a->next->next->next = createNode(3);
    a->next->next->next->prev = a->next->next;
    a->next->next->next->next = createNode(4);
    a->next->next->next->next->prev = a->next->next->next;
    Node* b = createNode(0);
    b->next = createNode(1);
    b->next->prev = b;
    b->next->next = createNode(2);
    b->next->next->prev = b->next;
    b->next->next->next = createNode(3);
    b->next->next->next->prev = b->next->next;
    b->next->next->next->next = createNode(4);
    b->next->next->next->next->prev = b->next->next->next;
    printf("List A: ");
    printList(a);
    printf("List B: ");
    printList(b);
    Node* result = addTwoLists(a, b);
    printf("相加链表: ");
    printList(result);
    freeList(a);
    freeList(b);
    freeList(result);
    return 0;
}