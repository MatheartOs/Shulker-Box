#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class OptimizedNonogramSolver {
private:
    int n;
    vector<int> colHints;
    vector<int> rowHints;
    vector<vector<int>> solution;
    
    bool backtrack(int row, vector<vector<int>>& board, 
                  vector<int>& rowCount, vector<int>& colCount) {
        if (row == n) {
            solution = board;
            return true;
        }
        
        // 计算当前行还能填充的最大格子数
        int remaining = rowHints[row] - rowCount[row];
        if (remaining < 0) return false;
        
        // 生成所有可能的填充组合
        vector<int> positions;
        for (int col = 0; col < n; col++) {
            if (board[row][col] == 0 && colCount[col] < colHints[col]) {
                positions.push_back(col);
            }
        }
        
        // 尝试所有可能的组合
        vector<bool> mask(positions.size(), false);
        fill(mask.end() - remaining, mask.end(), true);
        
        do {
            bool valid = true;
            // 尝试当前组合
            for (int i = 0; i < positions.size(); i++) {
                if (mask[i]) {
                    int col = positions[i];
                    board[row][col] = 1;
                    rowCount[row]++;
                    colCount[col]++;
                    if (colCount[col] > colHints[col]) {
                        valid = false;
                        // 回滚更改
                        for (int j = 0; j <= i; j++) {
                            if (mask[j]) {
                                int c = positions[j];
                                board[row][c] = 0;
                                rowCount[row]--;
                                colCount[c]--;
                            }
                        }
                        break;
                    }
                }
            }
            
            if (valid) {
                if (backtrack(row + 1, board, rowCount, colCount)) {
                    return true;
                }
                // 回滚更改
                for (int i = 0; i < positions.size(); i++) {
                    if (mask[i]) {
                        int col = positions[i];
                        board[row][col] = 0;
                        rowCount[row]--;
                        colCount[col]--;
                    }
                }
            }
        } while (next_permutation(mask.begin(), mask.end()));
        
        return false;
    }

public:
    OptimizedNonogramSolver(int size, const vector<int>& cols, const vector<int>& rows) 
        : n(size), colHints(cols), rowHints(rows) {}
    
    vector<vector<int>> solve() {
        vector<vector<int>> board(n, vector<int>(n, 0));
        vector<int> rowCount(n, 0);
        vector<int> colCount(n, 0);
        
        if (backtrack(0, board, rowCount, colCount)) {
            return solution;
        } else {
            return {};
        }
    }
};

// 主函数与之前相同
int main() {
    int n;
    cin >> n;
    
    vector<int> cols(n), rows(n);
    for (int i = 0; i < n; i++) cin >> cols[i];
    for (int i = 0; i < n; i++) cin >> rows[i];
    
    OptimizedNonogramSolver solver(n, cols, rows);
    auto solution = solver.solve();
    
    if (solution.empty()) {
        cout << "No solution exists" << endl;
    } else {
        for (const auto& row : solution) {
            for (int cell : row) {
                cout << cell << " ";
            }
            cout << endl;
        }
    }
    
    return 0;
}