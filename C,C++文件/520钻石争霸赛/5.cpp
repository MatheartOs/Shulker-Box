#include <iostream>
#include <unordered_map>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    int n;
    cin >> n;
    int r, c;
    cin >> r >> c;
    
    unordered_map<int, pair<int, int>> student_pos;
    vector<vector<int>> grid(r, vector<int>(c));
    
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] != 0) {
                student_pos[grid[i][j]] = {i, j};
            }
        }
    }
    
    int k;
    cin >> k;
    
    while (k--) {
        int a, b;
        cin >> a >> b;
        
        if (student_pos.find(a) == student_pos.end() || student_pos.find(b) == student_pos.end()) {
            cout << "no" << endl;
            continue;
        }
        
        auto pos_a = student_pos[a];
        auto pos_b = student_pos[b];
        
        int row_a = pos_a.first, col_a = pos_a.second;
        int row_b = pos_b.first, col_b = pos_b.second;
        
        bool adjacent = false;
        
        if (row_a == row_b && abs(col_a - col_b) == 1) {
            adjacent = true;
        } else if (col_a == col_b && abs(row_a - row_b) == 1) {
            adjacent = true;
        }
        
        cout << (adjacent ? "yes" : "no") << endl;
    }
    
    return 0;
}