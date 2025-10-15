#include <iostream>
using namespace std;

struct Node {
    int val;
    Node* next;
    Node(int v) : val(v), next(nullptr) {}
};

// 创建循环链表，返回头指针
Node* createCircularList(int n) {
    if (n <= 0) return nullptr;
    Node* head = new Node(1);
    Node* tail = head;
    for (int i = 2; i <= n; ++i) {
        tail->next = new Node(i);
        tail = tail->next;
    }
    tail->next = head; // 成环
    return head;
}

// 循环打印链表k次
void printCircularList(Node* head, int n, int k) {
    if (!head || n <= 0 || k <= 0) return;
    Node* p = head;
    int total = n * k;
    for (int i = 0; i < total; ++i) {
        cout << p->val;
        if (i != total - 1) cout << ",";
        p = p->next;
    }
    cout << endl;
}

// 释放链表内存
void freeCircularList(Node* head, int n) {
    if (!head || n <= 0) return;
    Node* p = head->next;
    for (int i = 1; i < n; ++i) {
        Node* tmp = p;
        p = p->next;
        delete tmp;
    }
    delete head;
}

int main() {
    int n = 4;
    Node* head = createCircularList(n);
    printCircularList(head, n, 2);
    freeCircularList(head, n);
    return 0;
}