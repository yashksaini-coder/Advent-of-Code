#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <cstdint>
#include <numeric>
#include <algorithm>

using namespace std;

uint64_t solve() {
    ifstream input("input.txt");
    vector<string> grid;
    string line;
    
    // Read the grid
    while (getline(input, line)) {
        grid.push_back(line);
    }
    input.close();
    
    if (grid.empty()) {
        cerr << "Error: Empty grid" << endl;
        return 0;
    }
    
    int rows = grid.size();
    int cols = grid[0].size();
    
    // Pre-process: store splitter positions for each row
    vector<set<int>> splitters(rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == '^') {
                splitters[i].insert(j);
            }
        }
    }
    
    // Find starting beam column
    int startCol = -1;
    for (int j = 0; j < cols; j++) {
        if (grid[0][j] == 'S') {
            startCol = j;
            break;
        }
    }
    
    if (startCol == -1) {
        cerr << "Error: Starting position 'S' not found" << endl;
        return 0;
    }
    
    // Dynamic programming: track beam count at each column for each level
    vector<uint64_t> curr(cols, 0);
    vector<uint64_t> next(cols, 0);
    
    // Initialize: starting beam
    curr[startCol] = 1;
    
    // Process each row
    for (int i = 0; i < rows; i++) {
        fill(next.begin(), next.end(), 0);
        
        for (int col = 0; col < cols; col++) {
            if (curr[col] > 0) {
                // Check if there's a splitter at this position
                if (splitters[i].count(col)) {
                    // Beam hits splitter: split into left and right
                    if (col - 1 >= 0) next[col - 1] += curr[col];
                    if (col + 1 < cols) next[col + 1] += curr[col];
                } else {
                    // Beam continues straight down
                    next[col] += curr[col];
                }
            }
        }
        
        swap(curr, next);
    }
    
    // Sum all beams that made it through
    return accumulate(curr.begin(), curr.end(), 0ULL);
}

int main() {
    uint64_t result = solve();
    cout << result << endl;
    return 0;
}
