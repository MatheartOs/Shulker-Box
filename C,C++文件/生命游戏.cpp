#include <iostream>
#include <vector>
#include <unistd.h> // 用于usleep (Unix系统)

using namespace std;

const int WIDTH = 40;
const int HEIGHT = 20;

// 初始化网格
void initializeGrid(vector<vector<bool>>& grid) {
    grid.resize(HEIGHT, vector<bool>(WIDTH, false));
    
    // 可以在这里设置初始模式，或者随机初始化
    // 这里设置一个滑翔机(glider)模式
    grid[1][2] = true;
    grid[2][3] = true;
    grid[3][1] = true;
    grid[3][2] = true;
    grid[3][3] = true;
}

// 打印当前网格状态
void printGrid(const vector<vector<bool>>& grid) {
    system("clear"); // 清屏 (Unix系统), Windows用 "cls"
    
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            cout << (grid[i][j] ? "■" : " ");
        }
        cout << endl;
    }
    cout << endl;
}

// 计算某个细胞的邻居数量
int countNeighbors(const vector<vector<bool>>& grid, int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue; // 跳过自身
            
            int nx = x + i;
            int ny = y + j;
            
            // 处理边界条件（这里使用环形边界）
            if (nx < 0) nx = HEIGHT - 1;
            if (nx >= HEIGHT) nx = 0;
            if (ny < 0) ny = WIDTH - 1;
            if (ny >= WIDTH) ny = 0;
            
            if (grid[nx][ny]) count++;
        }
    }
    return count;
}

// 更新网格到下一代
void updateGrid(vector<vector<bool>>& grid) {
    vector<vector<bool>> newGrid = grid;
    
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            int neighbors = countNeighbors(grid, i, j);
            
            // 应用生命游戏规则
            if (grid[i][j]) {
                // 活细胞：2或3个邻居则存活，否则死亡
                newGrid[i][j] = (neighbors == 2 || neighbors == 3);
            } else {
                // 死细胞：恰好3个邻居则复活
                newGrid[i][j] = (neighbors == 3);
            }
        }
    }
    
    grid = newGrid;
}

int main() {
    vector<vector<bool>> grid;
    initializeGrid(grid);
    
    // 运行100代
    for (int generation = 0; generation < 100; ++generation) {
        printGrid(grid);
        updateGrid(grid);
        usleep(10000); // 暂停200毫秒 (Unix系统), Windows用 Sleep(200)
    }
    
    return 0;
}