#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <limits>

using namespace std;

class Edge {
public:
    pair<long long, long long> u;
    pair<long long, long long> v;
    
    Edge(pair<long long, long long> u, pair<long long, long long> v) : u(u), v(v) {}
    
    bool isVertical() const {
        return u.first == v.first;
    }
};

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
    
    // Create edges connecting consecutive points (forming a polygon)
    vector<Edge> edges;
    size_t n = pts.size();
    for (size_t i = 0; i < n; i++) {
        size_t next = (i + 1) % n;
        edges.emplace_back(pts[i], pts[next]);
    }
    
    long long max_area = numeric_limits<long long>::min();
    
    // Find maximum valid rectangular area between all pairs of points
    for (size_t i = 0; i < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            long long x1 = min(pts[i].first, pts[j].first);
            long long x2 = max(pts[i].first, pts[j].first);
            long long y1 = min(pts[i].second, pts[j].second);
            long long y2 = max(pts[i].second, pts[j].second);
            
            long long area = (x2 - x1 + 1) * (y2 - y1 + 1);
            
            // Skip if area is not better than current maximum
            if (area <= max_area) continue;
            
            bool valid = true;
            
            // Check if any polygon edge intersects the rectangle interior
            for (const auto& edge : edges) {
                if (edge.isVertical()) {
                    // Vertical edge
                    long long ex = edge.u.first;
                    if (ex > x1 && ex < x2) {
                        long long Ymin = min(edge.u.second, edge.v.second);
                        long long Ymax = max(edge.u.second, edge.v.second);
                        
                        // Check if vertical edge overlaps with rectangle's y-range
                        if (max(y1, Ymin) < min(y2, Ymax)) {
                            valid = false;
                            break;
                        }
                    }
                } else {
                    // Horizontal edge
                    long long ey = edge.u.second;
                    if (ey > y1 && ey < y2) {
                        long long Xmin = min(edge.u.first, edge.v.first);
                        long long Xmax = max(edge.u.first, edge.v.first);
                        
                        // Check if horizontal edge overlaps with rectangle's x-range
                        if (max(x1, Xmin) < min(x2, Xmax)) {
                            valid = false;
                            break;
                        }
                    }
                }
            }
            
            if (valid) {
                max_area = max(max_area, area);
            }
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
