#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// Check if a number is invalid (made of a pattern repeated twice)
bool isInvalidID(long long num) {
    string s = to_string(num);
    int len = s.length();
    
    // Must have even length to be repeated twice
    if (len % 2 != 0) return false;
    
    int halfLen = len / 2;
    
    // Check if first half equals second half
    string firstHalf = s.substr(0, halfLen);
    string secondHalf = s.substr(halfLen, halfLen);
    
    return firstHalf == secondHalf;
}

int main() {
    string input = "749639-858415,65630137-65704528,10662-29791,1-17,9897536-10087630,1239-2285,1380136-1595466,8238934-8372812,211440-256482,623-1205,102561-122442,91871983-91968838,62364163-62554867,3737324037-3737408513,9494926669-9494965937,9939271919-9939349036,83764103-83929201,24784655-24849904,166-605,991665-1015125,262373-399735,557161-618450,937905586-937994967,71647091-71771804,8882706-9059390,2546-10476,4955694516-4955781763,47437-99032,645402-707561,27-86,97-157,894084-989884,421072-462151";
    
    // Parse the input
    vector<pair<long long, long long>> ranges;
    stringstream ss(input);
    string range;
    
    while (getline(ss, range, ',')) {
        size_t dashPos = range.find('-');
        long long start = stoll(range.substr(0, dashPos));
        long long end = stoll(range.substr(dashPos + 1));
        ranges.push_back({start, end});
    }
    
    long long totalSum = 0;
    int totalInvalidCount = 0;
    
    // Process each range
    for (const auto& r : ranges) {
        long long start = r.first;
        long long end = r.second;
        
        vector<long long> invalidIDs;
        
        // Check each number in the range
        for (long long num = start; num <= end; num++) {
            if (isInvalidID(num)) {
                invalidIDs.push_back(num);
                totalSum += num;
                totalInvalidCount++;
            }
        }
        
        // Print details for this range
        if (!invalidIDs.empty()) {
            cout << start << "-" << end << " has " << invalidIDs.size() << " invalid ID(s): ";
            for (size_t i = 0; i < invalidIDs.size(); i++) {
                cout << invalidIDs[i];
                if (i < invalidIDs.size() - 1) cout << ", ";
            }
            cout << endl;
        }
    }
    
    cout << "\n==================================" << endl;
    cout << "Total invalid IDs found: " << totalInvalidCount << endl;
    cout << "Sum of all invalid IDs: " << totalSum << endl;
    
    return 0;
}