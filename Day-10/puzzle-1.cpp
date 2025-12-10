#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <climits>
#include <sstream>

using namespace std;

vector<string> split(string s, string delim) {
    vector<string> tokens; 
    size_t start = 0; 
    size_t end;
    while ((end = s.find(delim, start)) != string::npos) {
        tokens.push_back(s.substr(start, end - start));
        start = end + delim.length();
    } 
    if (start < s.length()) {
        tokens.push_back(s.substr(start));
    }
    return tokens; 
}

long long solveSingle(int curr, vector<vector<int>>& buttons, vector<long long>& dp, int target) {
    // Already computed
    if (dp[curr] >= 0) {
        return dp[curr];
    }
    
    // Mark as visiting to detect cycles
    if (dp[curr] == -1) {
        return LLONG_MAX; 
    }
    dp[curr] = -1; 
    
    // Base case: reached target configuration
    if (curr == target) {
        dp[curr] = 0; 
        return 0; 
    }
    
    long long minPresses = LLONG_MAX; 
    
    // Try pressing each button
    for (const auto& button : buttons) {
        int nextState = curr; 
        
        // Toggle the lights specified by this button
        for (int lightIndex : button) {
            nextState ^= (1 << lightIndex); 
        }
        
        long long result = solveSingle(nextState, buttons, dp, target); 
        
        if (result != LLONG_MAX) {
            minPresses = min(minPresses, 1 + result);
        }
    }
    
    dp[curr] = (minPresses == LLONG_MAX) ? LLONG_MAX : minPresses; 
    return dp[curr]; 
}

long long solve(vector<vector<vector<int>>>& allButtons, vector<int>& targets, vector<int>& maxStates) {
    long long totalPresses = 0;
    
    for (size_t i = 0; i < allButtons.size(); i++) {
        // DP array: -2 = unvisited, -1 = visiting, >= 0 = computed
        vector<long long> dp(maxStates[i], -2);
        long long result = solveSingle(0, allButtons[i], dp, targets[i]);
        totalPresses += result;
    }
    
    return totalPresses; 
} 

int main() {
    ifstream inputFile("input.txt");
    string line;
    
    vector<vector<vector<int>>> allButtons;
    vector<int> targets;
    vector<int> maxStates; 
    
    while (getline(inputFile, line)) {
        vector<string> parts = split(line, " ");
        
        // Parse indicator light diagram [.##.]
        string lightDiagram = parts[0].substr(1, parts[0].length() - 2);
        int targetState = 0;
        int maxState = 0; 
        
        for (size_t i = 0; i < lightDiagram.length(); i++) {
            if (lightDiagram[i] == '#') {
                targetState |= (1 << i); 
            }
            maxState |= (1 << i);
        }
        
        targets.push_back(targetState); 
        maxStates.push_back(maxState + 1);
        
        // Parse button schematics (0,1,2)
        vector<vector<int>> buttons; 
        for (size_t i = 1; i < parts.size() - 1; i++) {
            string buttonStr = parts[i].substr(1, parts[i].length() - 2);
            vector<string> indices = split(buttonStr, ",");
            
            vector<int> button; 
            for (const string& indexStr : indices) {
                button.push_back(stoi(indexStr));
            }
            buttons.push_back(button);
        }
        allButtons.push_back(buttons);
    }
    
    cout << solve(allButtons, targets, maxStates) << endl; 
    
    return 0;
}
