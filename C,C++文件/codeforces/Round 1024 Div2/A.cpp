#include <bits/stdc++.h>
using namespace std;
#define ll long long

void solve(){
    int t;
    cin>>t;
    while (t--)
    {
        ll n,m,p,q;
        cin >> n >> m >> p >> q;
        if(n%p==0){
            ll tmp = n/p;
            if(m == tmp * q) cout<<"YES"<<endl;
            else cout<<"NO"<<endl;
            continue;
        }else{
            cout<<"YES"<<endl;
            continue;
        }
    }
    
}

int main(){
    solve();
}