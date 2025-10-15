#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int N=1e5+5;
ll a[N];
ll s[N<<2];
ll t1[N<<2];
ll t2[N<<2];

#define ls (p<<1)
#define rs (p<<1|1)
#define mid ((l+r)>>1)
#define len (r-l+1)

ll n,q,mod;

void pushUp(ll p){
    s[p] = (s[ls]%mod+s[rs]%mod)%mod;
}
void build(ll p, ll l, ll r){
    t1[p] = 0;
    t2[p] = 1;
    if(l==r){
        s[p] = a[l]%mod;
        return;
    }
    build(ls, l, mid);
    build(rs, mid+1, r);
    pushUp(p);
}
void add(ll p, ll l, ll r, ll k){
    s[p] = (s[p]%mod+(1ll*len*k)%mod)%mod;
    t1[p] = (t1[p]%mod+k%mod)%mod;
}
void mul(ll p, ll k){
    s[p] = ((s[p]%mod)*(k%mod))%mod;
    t1[p] = ((t1[p]%mod)*(k%mod))%mod;
    t2[p] = ((t2[p]%mod)*(k%mod))%mod;
}
void pushDown(ll p, ll l, ll r){
    if(!t1[p]&&t2[p]==1) return;
    mul(ls,t2[p]);
    mul(rs,t2[p]);
    add(ls,l,mid,t1[p]);
    add(rs,mid+1,r,t1[p]);
    t1[p]=0;
    t2[p]=1;
}
void add(ll p, ll l, ll r, ll L, ll R, ll k){
    if(r<L||R<l) return;
    if(L<=l&&r<=R) return add(p,l,r,k);
    pushDown(p,l,r);
    add(ls,l,mid,L,R,k);
    add(rs,mid+1,r,L,R,k);
    pushUp(p);
}
void mul(ll p, ll l, ll r, ll L, ll R, ll k){
    if(r<L||R<l) return;
    if(L<=l&&r<=R) return mul(p,k);
    pushDown(p,l,r);
    mul(ls,l,mid,L,R,k);
    mul(rs,mid+1,r,L,R,k);
    pushUp(p);
}
ll ask(ll p, ll l, ll r, ll L, ll R){
    if(r<L||R<l) return 0;
    if(L<=l&&r<=R) return s[p]%mod;
    pushDown(p,l,r);
    return (ask(ls,l,mid,L,R)%mod+ask(rs,mid+1,r,L,R)%mod)%mod;
}

int main(){
    cin>>n>>q>>mod;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    build(1,1,n);
    ll op,x,y,k;
    for(int i=1;i<=q;i++){
        cin>>op;
        if(op==1){
            cin>>x>>y>>k;
            mul(1,1,n,x,y,k);
        }else if(op==2){
            cin>>x>>y>>k;
            add(1,1,n,x,y,k);
        }else{
            cin>>x>>y;
            cout<<ask(1,1,n,x,y)<<endl;
        }
    }
    return 0;
}
