#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <cctype>

using namespace std;

// 检查字符串是否只包含数字
bool isDigits(const string &s) {
    for (char c : s) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return !s.empty();
}

// 将字符串按分隔符拆分成向量
vector<string> split(const string &s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// 将时间字符串转换为总秒数
double parseTime(const string &timeStr) {
    vector<string> parts = split(timeStr, ':');
    double totalSeconds = 0.0;
    
    // 验证所有部分都是数字
    for (const auto &part : parts) {
        if (!isDigits(part)) {
            cerr << "错误: 时间部分包含非数字字符: " << part << endl;
            exit(1);
        }
    }
    
    if (parts.size() == 1) {
        // 格式1: 只有秒数 (如 "08" 表示8秒)
        totalSeconds = stod(parts[0]);
    } else if (parts.size() == 2) {
        // 格式2: 分:秒 (如 "02:48" 表示2分48秒)
        totalSeconds = stod(parts[0]) * 60 + stod(parts[1]);
    } else if (parts.size() == 3) {
        // 格式3: 时:分:秒 (如 "01:59:08" 表示1小时59分8秒)
        totalSeconds = stod(parts[0]) * 3600 + stod(parts[1]) * 60 + stod(parts[2]);
    } else {
        cerr << "错误: 无效的时间格式" << endl;
        exit(1);
    }
    
    // 验证时间部分的值合理性
    if (parts.size() >= 2 && stod(parts.back()) >= 60) {
        cerr << "错误: 秒数不能超过59" << endl;
        exit(1);
    }
    if (parts.size() >= 2 && stod(parts[parts.size()-2]) >= 60) {
        cerr << "错误: 分钟数不能超过59" << endl;
        exit(1);
    }
    
    return totalSeconds;
}

// 将秒数转换为配速格式 (min:sec/km)
string formatPace(double secondsPerKm) {
    int minutes = static_cast<int>(secondsPerKm) / 60;
    int seconds = static_cast<int>(secondsPerKm) % 60;
    
    ostringstream oss;
    oss << minutes << ":" << setw(2) << setfill('0') << seconds;
    return oss.str();
}

int main() {
    double distance;
    string timeInput;
    
    // 输入跑步距离
    cout << "请输入跑步距离(公里): ";
    cin >> distance;
    
    if (distance <= 0) {
        cerr << "错误: 距离必须大于0" << endl;
        return 1;
    }
    
    // 输入时间
    cout << "请输入用时(格式可以是: 秒数、分:秒、时:分:秒)\n";
    cin >> timeInput;
    
    // 解析时间并计算总秒数
    double totalSeconds = parseTime(timeInput);
    if (totalSeconds <= 0) {
        cerr << "错误: 时间必须大于0" << endl;
        return 1;
    }
    
    // 计算配速 (秒/公里)
    double paceSecondsPerKm = totalSeconds / distance;
    
    // 输出结果
    cout << "\n跑步数据统计:" << endl;
    cout << fixed << setprecision(2);
    cout << "距离: " << distance << " 公里" << endl;
    cout << "用时: " << formatPace(totalSeconds) << " (总秒数: " << totalSeconds << "秒)" << endl;
    cout << "平均配速: " << formatPace(paceSecondsPerKm) << "/公里" << endl;
    
    return 0;
}