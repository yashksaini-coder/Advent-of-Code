#include <bits/stdc++.h>
using namespace std;

/* ---------- 8-direction offsets ---------- */
const int dx[8] = {-1,-1,-1, 0,0, 1,1,1};
const int dy[8] = {-1, 0, 1,-1,1,-1,0,1};

/* ---------- single sweep: remove every reachable roll ---------- */
int solve(vector<vector<bool>>& grid) {
    int rows = grid.size();
    if (rows == 0) return 0;
    int cols = grid[0].size();

    int removedInThisSweep = 0;

    /* we need to know the state **before** any removals in this sweep,
       so we pre-compute who gets removed */
    vector<pair<int,int>> toRemove;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!grid[i][j]) continue;          // not a roll

            int neigh = 0;
            for (int d = 0; d < 8; ++d) {
                int ni = i + dx[d];
                int nj = j + dy[d];
                if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && grid[ni][nj])
                    ++neigh;
            }
            if (neigh < 4) toRemove.emplace_back(i, j);
        }
    }

    /* actually remove them */
    for (auto [i, j] : toRemove) {
        grid[i][j] = false;
        ++removedInThisSweep;
    }
    return removedInThisSweep;
}

/* -------------------- main -------------------- */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    /* read whole file */
    ifstream file("input.txt");
    if (!file) {
        cerr << "Cannot open input.txt\n";
        return 1;
    }
    stringstream buffer;
    buffer << file.rdbuf();
    string content = buffer.str();

    /* split into lines */
    vector<string> data;
    string line;
    istringstream iss(content);
    while (getline(iss, line))
        if (!line.empty()) data.push_back(line);

    int rows = data.size();
    int cols = data[0].size();

    /* build boolean grid */
    vector<vector<bool>> grid(rows, vector<bool>(cols, false));
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            grid[i][j] = (data[i][j] == '@');

    /* repeatedly sweep until nothing is removed */
    int totalRemoved = 0;
    while (true) {
        int curr = solve(grid);
        if (curr == 0) break;
        totalRemoved += curr;
    }

    cout << totalRemoved << '\n';
    return 0;
}

/* -------------- Algorithm summary ----------------
 * Data:  vector<vector<bool>> grid – true = present roll
 * Step:  while true
 *            scan whole grid
 *            collect positions with < 4 live neighbours
 *            set those positions to false
 *            add count to total
 *        until count == 0
 * Complexity:
 *        Time:  O(R * C * S)  – S = number of sweeps (≤ R*C)
 *        Memory: O(R * C)
 * ------------------------------------------------- */
