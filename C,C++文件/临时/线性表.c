#include <stdio.h>
#define MAXSIZE 20
typedef int ElemType;
typedef struct {
    ElemType data[MAXSIZE];
    int length;
} SqList;
int main() {
    SqList list;
    list.length = 0;
        for (int i = 0; i < 10; i++) {
            list.data[i] = i + 1;
            list.length++;
        }
    for (int i = 0; i < list.length; i++) {
        printf("%d ", list.data[i]);
    }
    printf("\n");
    return 0;
}