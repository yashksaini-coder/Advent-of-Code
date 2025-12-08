 #include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

struct Point {
    int64_t x, y, z;
};

struct Dist {
    int64_t dist;
    size_t i, j;
};

bool dfs(size_t i, size_t j, const vector<vector<size_t>>& adj, vector<bool>& visited) {
    if (i == j) {
        return true;
    }
    for (size_t x : adj[i]) {
        if (!visited[x]) {
            visited[x] = true;
            if (dfs(x, j, adj, visited)) {
                return true;
            }
        }
    }
    return false;
}

int dfs_cnt(size_t i, const vector<vector<size_t>>& adj, vector<bool>& visited) {
    visited[i] = true;
    int res = 0;
    for (size_t x : adj[i]) {
        if (!visited[x]) {
            res += dfs_cnt(x, adj, visited);
        }
    }
    return res + 1;
}

int main() {
    ifstream input("input.txt");
    if (!input) {
        cerr << "Error: Cannot open input.txt" << endl;
        return 1;
    }
    
    vector<Point> coordinates;
    string line;
    
    // Read coordinates
    while (getline(input, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        Point pt;
        char comma;
        
        ss >> pt.x >> comma >> pt.y >> comma >> pt.z;
        coordinates.push_back(pt);
    }
    input.close();
    
    size_t n = coordinates.size();
    
    // Calculate all pairwise distances
    vector<Dist> dist;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            int64_t dx = coordinates[i].x - coordinates[j].x;
            int64_t dy = coordinates[i].y - coordinates[j].y;
            int64_t dz = coordinates[i].z - coordinates[j].z;
            int64_t d = dx * dx + dy * dy + dz * dz;
            
            dist.push_back({d, i, j});
        }
    }
    
    // Sort distances
    sort(dist.begin(), dist.end(), [](const Dist& a, const Dist& b) {
        return a.dist < b.dist;
    });
    
    // Build adjacency list using shortest edges (MST-like approach)
    vector<vector<size_t>> adj(n);
    int rem = 1000;
    
    for (const auto& d : dist) {
        vector<bool> visited(n, false);
        visited[d.i] = true;
        
        // Check if i and j are already connected
        if (!dfs(d.i, d.j, adj, visited)) {
            // If not connected, add edge
            adj[d.i].push_back(d.j);
            adj[d.j].push_back(d.i);
        }
        
        rem--;
        if (rem == 0) {
            break;
        }
    }
    
    // Count connected components
    vector<bool> visited(n, false);
    vector<int> component_sizes;
    
    for (size_t i = 0; i < n; i++) {
        if (!visited[i]) {
            int cnt = dfs_cnt(i, adj, visited);
            component_sizes.push_back(cnt);
        }
    }
    
    // Sort and get top 3 components
    sort(component_sizes.rbegin(), component_sizes.rend());
    
    int64_t result = (int64_t)component_sizes[0] * component_sizes[1] * component_sizes[2];
    cout << "Answer is " << result << endl;
    
    return 0;
}
