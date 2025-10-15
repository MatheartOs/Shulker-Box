#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Tree{
    int val;
    Tree *left;
    Tree *right;

    Tree(int x): val(x), left(nullptr), right(nullptr){};
};

void preorder(Tree *root){
    if(root == nullptr) return;
    cout << root -> val << " ";
    preorder(root -> left);
    preorder(root -> right);
}

void inorder(Tree *root){
    if(root == nullptr) return;
    inorder(root -> left);
    cout << root -> val << " ";
    inorder(root -> right);
}

void postorder(Tree *root){
    if(root == nullptr) return;
    postorder(root -> left);
    postorder(root -> right);
    cout << root -> val << " ";
}

int main(){

    //        1
    //       / \
    //      2   3
    //     / \
    //    4   5

    Tree* root = new Tree(1);
    root->left = new Tree(2);
    root->right = new Tree(3);
    root->left->left = new Tree(4);
    root->left->right = new Tree(5);

    cout << "Preorder: ";
    preorder(root);
    cout << endl;

    cout << "Inorder: ";
    inorder(root);
    cout << endl;

    cout << "Postorder: ";
    postorder(root);
    cout << endl;
}