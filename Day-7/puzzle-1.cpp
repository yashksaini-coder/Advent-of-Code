#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>

using namespace std;

int main() {
    ifstream input("input.txt");
    vector<string> grid;
    string line;
    
    // Read the grid
    while (getline(input, line)) {
        grid.push_back(line);
    }
    input.close();
    
    if (grid.empty()) {
        cout << "Error: Empty grid" << endl;
        return 1;
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
    
    // Find starting beam column(s)
    set<int> beams;
    for (int j = 0; j < cols; j++) {
        if (grid[0][j] == 'S') {
            beams.insert(j);
            break;
        }
    }
    
    int res = 0;
    
    // Process each row
    for (int i = 0; i < rows; i++) {
        if (splitters[i].size() > 0) {
            // Find which beams hit splitters in this row
            set<int> toDelete;
            for (int beam : beams) {
                if (splitters[i].count(beam)) {
                    toDelete.insert(beam);
                    res++;
                }
            }
            
            // Remove beams that hit splitters
            for (int d : toDelete) {
                beams.erase(d);
            }
            
            // Add new beams from splitters (left and right)
            for (int d : toDelete) {
                beams.insert(d + 1);
                beams.insert(d - 1);
            }
        }
    }
    
    cout << "Answer is " << res << endl;
    
    return 0;
}
