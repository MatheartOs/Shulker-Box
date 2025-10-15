#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    
    int husband = 0, wife = 0;
    vector<int> chores(7, 0);
    
    for (int i = 0; i < n; ++i) {
        int face, person;
        cin >> face >> person;
        
        if (face == 4 || face == 6) {
            continue;
        }
        
        if (person == 1) {
            husband++;
        } else {
            wife++;
        }
        
        chores[face]++;
    }
    if (husband > wife) {
        cout << "1 " << husband << endl;
    } else if (wife > husband) {
        cout << "0 " << wife << endl;
    } else {
        cout << "LOVE " << husband << endl;
    }
    
    int max_count = 0;
    vector<int> max_chores;
    
    for (int i = 1; i <= 6; ++i) {
        if (i == 4 || i == 6) {
            continue;
        }
        
        if (chores[i] > max_count) {
            max_count = chores[i];
            max_chores.clear();
            max_chores.push_back(i);
        } else if (chores[i] == max_count) {
            max_chores.push_back(i);
        }
    }
    
    sort(max_chores.begin(), max_chores.end());
    
    cout << max_count;
    for (int chore : max_chores) {
        cout << " " << chore;
    }
    cout << endl;
    
    return 0;
}