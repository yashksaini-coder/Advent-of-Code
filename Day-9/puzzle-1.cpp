#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <limits>

using namespace std;

void solve(const string& filename) {
    ifstream input(filename);
    if (!input) {
        cerr << "Error: Cannot open file '" << filename << "'" << endl;
        exit(1);
    }
    
    vector<pair<long long, long long>> pts;
    string line;
    
    // Read coordinates from file
    while (getline(input, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        long long x, y;
        char comma;
        
        if (ss >> x >> comma >> y) {
            pts.push_back({x, y});
        }
    }
    input.close();
    
    if (pts.empty()) {
        cerr << "Error: No valid points found in file" << endl;
        exit(1);
    }
    
    long long max_area = numeric_limits<long long>::min();
    
    // Calculate maximum rectangular area between all pairs of points
    for (size_t i = 0; i < pts.size(); i++) {
        for (size_t j = i + 1; j < pts.size(); j++) {
            long long len = abs(pts[i].first - pts[j].first) + 1;
            long long breadth = abs(pts[i].second - pts[j].second) + 1;
            long long area = len * breadth;
            max_area = max(max_area, area);
        }
    }
    
    cout << max_area << endl;
}

int main(int argc, char* argv[]) {
    // Check if filename argument is provided
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        cerr << "Example: " << argv[0] << " input.txt" << endl;
        return 1;
    }
    
    string filename = argv[1];
    solve(filename);
    
    return 0;
}
