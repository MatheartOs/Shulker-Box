#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int countMatches(const string &a, const string &b) {
    int matches = 0;
    for (int i = 0; i < a.size(); ++i) {
        if (tolower(a[i]) == tolower(b[i])) {
            matches++;
        }
    }
    return matches;
}

bool canBeHowPay(string a, string b) {
    if (a.size() != b.size()) {
        return false;
    }
    
    int matches = countMatches(a, b);
    if (matches >= 4) {
        return true;
    }
    if(matches < 2){
        return false;
    }
    for (int i = 0; i < a.size(); ++i) {
        for (int j = i + 1; j < a.size(); ++j) {
            swap(b[i], b[j]);
            matches = countMatches(a, b);
            if (matches >= 4) {
                return true;
            }
            swap(b[i], b[j]);
        }
    }
    
    return false;
}

int main() {
    int n;
    cin >> n;
    cin.ignore();
    
    for (int i = 0; i < n; ++i) {
        string name1, name2;
        cin >> name1 >> name2;
        
        if (canBeHowPay(name1, name2)) {
            cout << "how pay" << endl;
        } else {
            cout << "bull pay" << endl;
        }
    }
    
    return 0;
}