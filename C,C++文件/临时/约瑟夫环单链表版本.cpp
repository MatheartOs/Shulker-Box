#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

// 单链表结点定义
struct Node {
    int val;
    Node* next;
    Node(int v) : val(v), next(nullptr) {}
};

// 创建长度为n的单链表，编号1~n
Node* createList(int n) {
    Node* head = new Node(1);
    Node* tail = head;
    for (int i = 2; i <= n; ++i) {
        tail->next = new Node(i);
        tail = tail->next;
    }
    return head;
}

// 约瑟夫环操作，返回新队列头指针
Node* josephus(Node* head, int n) {
    if (!head || !head->next) return head;
    // 先将单链表变为循环链表
    Node* tail = head;
    while (tail->next) tail = tail->next;
    tail->next = head;
    vector<int> outOrder;
    Node* prev = tail;
    Node* curr = head;
    int len = 0;
    Node* tmp = head;
    while (tmp) { ++len; tmp = tmp->next; if (tmp == head) break; }
    while (len) {
        for (int i = 1; i < n; ++i) {
            prev = curr;
            curr = curr->next;
        }
        outOrder.push_back(curr->val);
        prev->next = curr->next;
        Node* toDelete = curr;
        curr = curr->next;
        if (toDelete == prev) { // 最后一个
            delete toDelete;
            break;
        }
        delete toDelete;
        --len;
    }
    // 由出列顺序重建单链表
    Node* newHead = nullptr;
    Node* newTail = nullptr;
    for (int v : outOrder) {
        if (!newHead) newHead = newTail = new Node(v);
        else { newTail->next = new Node(v); newTail = newTail->next; }
    }
    return newHead;
}

// 释放链表内存
void freeList(Node* head) {
    while (head) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
}

int main() {
    vector<int> input;
    int x;
    while (cin >> x) input.push_back(x);
    if (input.empty()) return 0;
    int M = input[0];
    Node* head = createList(M);
    for (size_t i = 1; i < input.size(); ++i) {
        head = josephus(head, input[i]);
    }
    // 输出结果
    Node* p = head;
    while (p) {
        cout << setw(4) << p->val;
        p = p->next;
    }
    cout << endl;
    freeList(head);
    return 0;
}
