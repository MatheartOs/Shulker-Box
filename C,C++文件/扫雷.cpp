#include <bits/stdc++.h>
using namespace std;

char boomb[50][50];
bool vis[50][50];

void get_rand() {
    int tot = 0;
    while (tot < 49)
    {
        int x = rand() % 10 + 1;
        int y = rand() % 26 + 1;
        if(!vis[x][y]){
            boomb[x][y] = '*';
            tot++;
            vis[x][y] = 1;
        }
    }
}

int dx[8] = {-1,-1,-1,0,1,1 ,1 ,0,};
int dy[8] = {-1,0 ,1 ,1,1,0,-1,-1};

int cnt(int x, int y){
    int tot = 0;
    for(int i = 0; i < 8; i++){
        if(boomb[x+dx[i]][y+dy[i]] == '*') tot++;
    }
    return tot;
}

int main(){
    get_rand();
    for(int i = 1; i <=10; i++){
        for(int j = 1; j <= 26; j++){
            if(boomb[i][j] == '*') cout<<'*'<<' ';
            else cout<<cnt(i,j)<<' ';
        }
        cout<<endl;
    }
}