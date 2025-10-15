#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    int l,r;
    cin>>l>>r;
    int age = min(l,r);
    if(age > 0 && age <=20){
        cout<<age<<endl<<"XianHua";
    }else if(age <=40){
        cout<<age<<endl<<"XiangXun";
    }else if(age <=60){
        cout<<age<<endl<<"BaoWenBei";
    }else if(age <= 200){
        cout<<age<<endl<<"HunShaZhao";
    }
}