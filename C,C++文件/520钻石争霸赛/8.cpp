#include <iostream>
#include <unordered_set>
#include <string>

using namespace std;

int main() {
    int n;
    cin >> n;
    unordered_set<string> couples;
    
    for (int i = 0; i < n; ++i) {
        string a, b;
        cin >> a >> b;
        couples.insert(a + b);
        couples.insert(b + a);
    }
    
    int m;
    cin >> m;
    
    for (int i = 0; i < m; ++i) {
        string x, y;
        cin >> x >> y;
        
        if (couples.find(x + y) != couples.end() || couples.find(y + x) != couples.end()) {
            cout << "(~_~)" << endl;
        } else {
            cout << "o(@O@)o" << endl;
        }
    }
    
    return 0;
}