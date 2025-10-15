#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    int a = 5;
    int b = 2;
    int c = 0;
    int n;
    cin>>n;
    if(n == 1){
        cout<<5;
        return 0;
    }
    if(n == 2){
        cout<<52;
        return 0;
    }
    if(n == 3){
        cout<<520;
        return 0;
    }
    cout<<a<<b<<c;
    for(int i = 4; i<=n;i++){
        int tmp = (a+b+c)%10;
        a = b;
        b = c;
        c = tmp;
        cout<<c;
    }
}