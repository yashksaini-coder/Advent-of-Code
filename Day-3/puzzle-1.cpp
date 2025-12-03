#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

int solve(const string& s) {
    int maxJoltage = 0;
    
    // For each position i, find the max digit after position i
    for (int i = 0; i < s.length() - 1; i++) {
        int tens = s[i] - '0';
        int ones = 0;
        
        // Find max digit after position i
        for (int j = i + 1; j < s.length(); j++) {
            ones = max(ones, s[j] - '0');
        }
        
        int joltage = tens * 10 + ones;
        maxJoltage = max(maxJoltage, joltage);
    }
    
    return maxJoltage;
}

int main() {
    ifstream file("input.txt");
    string line;
    int totalJoltage = 0;
    
    while (getline(file, line)) {
        totalJoltage += solve(line);
    }
    
    cout << totalJoltage << endl;
    
    file.close();
    return 0;
}
