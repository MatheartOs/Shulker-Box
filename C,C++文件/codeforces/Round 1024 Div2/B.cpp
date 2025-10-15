#include <bits/stdc++.h>
using namespace std;
#define ll long long

void solve(){
    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        vector<long long> a(n+1);
        for(int i = 0; i < n; i++){
            cin>>a[i];
        }
        int flag = abs(a[0]);
        ll cnt = 0;
        for(int i = 1; i < n; i++){
            if(abs(a[i]) > flag) cnt++;
        }
        if(cnt >= (n-1)/2){
            cout<<"YES"<<endl;
        }else{
            cout<<"NO"<<endl;
        }
    }
}

int main(){
    solve();
    return 0;
}