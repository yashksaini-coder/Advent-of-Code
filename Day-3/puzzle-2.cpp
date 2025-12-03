#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;

long long solve12(const string& s) {
    int start = 0;
    long long res = 0;
    
    // We need to select 12 digits
    for (int i = 11; i >= 0; i--) {
        int curr = 0;
        
        // Find the maximum digit from start to (s.length - i)
        // We need at least 'i' digits remaining after this position
        for (int j = start; j < s.length() - i; j++) {
            curr = max(curr, s[j] - '0');
        }
        
        // Find the first occurrence of that maximum digit
        for (int j = start; j < s.length(); j++) {
            if (s[j] - '0' == curr) {
                start = j + 1;
                break;
            }
        }
        
        // Add this digit to result at position i
        res += curr * pow(10, i);
    }
    
    return res;
}

int main() {
    ifstream file("input.txt");
    string line;
    long long totalJoltage = 0;
    
    while (getline(file, line)) {
        totalJoltage += solve12(line);
    }
    
    cout << totalJoltage << endl;
    
    file.close();
    return 0;
}
