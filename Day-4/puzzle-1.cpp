#include <bits/stdc++.h>
using namespace std;

/*  Approach
 *  ---------
 *  1. Read the entire grid from input.txt
 *  2. Convert it into a 2-D boolean table: true = ‘@’, false = anything else
 *  3. For every true cell, look at its 8 neighbors
 *  4. If the neighbor count is < 4, that roll is forklift-reachable → increment answer
 *  5. Print the total reachable rolls
 */

/*  Algorithm
 *  ----------
 *  Data structures:
 *      vector<string> data        – original lines
 *      vector<vector<bool>> grid  – fast lookup for ‘@’
 *
 *  Directions:
 *      8 offset pairs (dx, dy) covering the 3×3 square minus the center
 *
 *  Walk:
 *      for each cell (i, j)
 *          if grid[i][j] == true
 *              neighbors = 0
 *              for d in 0…7
 *                  ni = i + dx[d],  nj = j + dy[d]
 *                  if inside bounds and grid[ni][nj] == true → ++neighbors
 *              if neighbors < 4 → ++answer
 *
 *  Complexity:
 *      Time:  O(R * C)  – one pass over the grid
 *      Memory: O(R * C) – for the boolean grid
 */

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    /* ---------- 1. read whole file ---------- */
    ifstream file("input.txt");
    if (!file) {
        cerr << "Cannot open input.txt\n";
        return 1;
    }
    stringstream buffer;
    buffer << file.rdbuf();
    string content = buffer.str();

    /* ---------- 2. split into lines ---------- */
    vector<string> data;
    string line;
    istringstream iss(content);
    while (getline(iss, line))
        if (!line.empty()) data.push_back(line);

    int rows = data.size();
    if (rows == 0) {          // empty file guard
        cout << "0\n";
        return 0;
    }
    int cols = data[0].size();

    /* ---------- 3. build boolean grid ---------- */
    vector<vector<bool>> grid(rows, vector<bool>(cols, false));
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            grid[i][j] = (data[i][j] == '@');

    /* ---------- 4. 8-direction offsets ---------- */
    const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    /* ---------- 5. count reachable rolls ---------- */
    int answer = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!grid[i][j]) continue;          // not a paper roll

            int neighbors = 0;
            for (int d = 0; d < 8; ++d) {
                int ni = i + dx[d];
                int nj = j + dy[d];
                if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && grid[ni][nj])
                    ++neighbors;
            }
            if (neighbors < 4) ++answer;        // forklift can reach this roll
        }
    }

    /* ---------- 6. output result ---------- */
    cout << answer << '\n';
    return 0;
}

/*  Solution points
 *  -----------------
 *  – A roll is reachable when it is NOT too crowded (neighbor count < 4)
 *  – We simply tally how many rolls satisfy that condition
 *  – No BFS/DFS needed; pure neighbor counting is enough
 */
