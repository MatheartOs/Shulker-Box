#include <bits/stdc++.h>
using namespace std;

const int INF = INT_MAX;
const int N = 1e5+10;

struct Edge{
    int to;
    int weight;
};
vector<Edge> adj[N];
int dist[N];
bool inQueue[N];
int cnt[N];

bool SPFA(int start, int n){
    fill(dist,dist+n+1,INF);
    memset(inQueue,false,sizeof(inQueue));
    memset(cnt,0,sizeof(cnt));

    queue<int> q;
    dist[start] = 0;
    q.push(start);
    inQueue[start] = true;
    cnt[start]++;

    while(!q.empty()){
        int u = q.front();
        q.pop();
        inQueue[u] = false;
        for(const Edge &e : adj[u]){
            int v = e.to; int w = e.weight;
            if(dist[v] > dist[u] + w){
                dist[v] = dist[u] + w;
                if(!inQueue[v]) {
                    q.push(v);
                    inQueue[v] = true;
                    cnt[v]++;
                    if(cnt[v] > n){
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

int main(){
    int n,m;
    cin>>n>>m;
    for(int i = 1; i <= m; i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,-1*w});
    }
    SPFA(1,n);
    if(dist[n] == INF) cout<<-1<<endl;
    else cout<<-1*dist[n]<<endl;
    return 0;
}