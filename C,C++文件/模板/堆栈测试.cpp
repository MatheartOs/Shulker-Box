#include <bits/stdc++.h>
using namespace std;
#define ll long long

static int i = 1;

void test(){
    i++;
    cout<<"这是第 "<<i<<" 层栈"<<endl;
    test();
    cout<<"出栈"<<endl;
}

int main(){
    test();
    return 0;
}