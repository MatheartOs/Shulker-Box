#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Tree{
    int val;
    Tree *left;
    Tree *right;

    Tree(int x): val(x), left(nullptr), right(nullptr){};
};