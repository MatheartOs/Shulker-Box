#include <iostream>
using namespace std;

// 结点结构体
struct Node {
    int data;
    Node *next;
};

// 约瑟夫环结构体
struct CJosephRing {
    Node *m_pLast;
};

// 函数声明
void CJR_Init(CJosephRing *ring);
void CJR_Display(const CJosephRing *ring);
void CJR_Clear(CJosephRing *ring);
void CJR_Append(CJosephRing *ring, int x);
void CJR_RunGame(CJosephRing *ring, int N, CJosephRing *result);

// 初始化环
void CJR_Init(CJosephRing *ring) {
    ring->m_pLast = NULL;
}

// 显示环
void CJR_Display(const CJosephRing *ring) {
    if (ring->m_pLast == NULL)
        return;
        
    Node *p = ring->m_pLast->next;
    while (true) {
        cout.width(4);
        cout << p->data;
        if (p == ring->m_pLast)
            break;
        p = p->next;
    }
    cout << endl;
}

// 清空环
void CJR_Clear(CJosephRing *ring) {
    if (ring->m_pLast == NULL)
        return;
        
    while (ring->m_pLast->next != ring->m_pLast) {
        Node *p = ring->m_pLast->next;
        ring->m_pLast->next = p->next;
        delete p;
    }
    delete ring->m_pLast;
    ring->m_pLast = NULL;
}

// 向环中添加元素
void CJR_Append(CJosephRing *ring, int x) {
    Node *p = new Node;
    p->data = x;
    
    if (ring->m_pLast == NULL) {
        p->next = p;
        ring->m_pLast = p;
        return;
    }
    
    p->next = ring->m_pLast->next;
    ring->m_pLast->next = p;
    ring->m_pLast = p;
}

// 进行约瑟夫游戏
void CJR_RunGame(CJosephRing *ring, int N, CJosephRing *result) {
    if (ring->m_pLast == NULL)
        return;
        
    while (ring->m_pLast->next != ring->m_pLast) {
        for (int i = 1; i < N; i++)
            ring->m_pLast = ring->m_pLast->next;
            
        Node *p = ring->m_pLast->next;
        ring->m_pLast->next = p->next;
        CJR_Append(result, p->data);
        delete p;
    }
    
    CJR_Append(result, ring->m_pLast->data);
    delete ring->m_pLast;
    ring->m_pLast = NULL;
}

int main() {
    int M, N;
    int times = 0;

    cin >> M;
    CJosephRing firstRing, secondRing;
    
    // 初始化环
    CJR_Init(&firstRing);
    CJR_Init(&secondRing);

    // 构建初始环
    for (int i = 1; i <= M; i++) {
        CJR_Append(&firstRing, i);
    }
    
    // 处理游戏过程
    while (cin >> N) {
        if (times % 2 == 0)
            CJR_RunGame(&firstRing, N, &secondRing);
        else
            CJR_RunGame(&secondRing, N, &firstRing);
        ++times;
    }
    
    // 显示结果
    if (times % 2 == 0)
        CJR_Display(&firstRing);
    else
        CJR_Display(&secondRing);
        
    // 清理内存
    CJR_Clear(&firstRing);
    CJR_Clear(&secondRing);
    
    return 0;
}
