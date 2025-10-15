#include <stdio.h>
#include <stdlib.h>
//约瑟夫环纯链表实现
typedef struct Node {
    int data;
    struct Node* next;
} Node;
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    Node* head = (Node*)malloc(sizeof(Node));
    head->data = 1;
    Node* prev = head;
    for (int i = 2; i <= n; i++) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = i;
        prev->next = newNode;
        prev = newNode;
    }
    prev->next = head; // 形成环
    Node* curr = head;
    while (curr->next != curr) {
        for (int count = 1; count < m; count++) {
            curr = curr->next;
        }
        Node* toDelete = curr->next;
        curr->next = toDelete->next;
        free(toDelete);
        curr = curr->next;
    }
    printf("%d\n", curr->data);
    free(curr);
    return 0;
}