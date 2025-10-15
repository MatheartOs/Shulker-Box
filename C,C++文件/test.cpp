#include <bits/stdc++.h>
using namespace std;
int seeds[5];
void print(int i){
    srand(seeds[i]);
    cout<<rand()%5<<endl;
    cout<<rand()%5<<endl;
    cout<<rand()%5<<endl;
    cout<<rand()%5<<endl;
    cout<<rand()%5<<endl;
    cout<<endl;
}
int main()
{
    time_t seed = time(NULL);
    for(int i = 0; i<5;i++){
        seeds[i] = seed + i*1000;
    }

    for(int i = 0; i < 5; i++){
        print(i);
    }
}
