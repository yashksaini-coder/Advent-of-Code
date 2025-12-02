#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

bool is_invalid_id(long long num)
{
    // Check if a number is invalid (made of a sequence repeated at least twice)
    // E.g., 55 (5 twice), 6464 (64 twice), 123123 (123 twice), 12341234 (1234 twice), etc.
    string s = to_string(num);
    int length = s.length();

    // Try all possible period lengths (1 to length/2)
    for (int period = 1; period <= length / 2; period++)
    {
        // Check if length is divisible by period
        if (length % period != 0)
        {
            continue;
        }

        // Check if the string is made of repeating pattern of this period
        string pattern = s.substr(0, period);
        int repeats = length / period;

        bool is_repeating = true;
        for (int i = 0; i < repeats; i++)
        {
            if (s.substr(i * period, period) != pattern)
            {
                is_repeating = false;
                break;
            }
        }

        if (is_repeating && repeats >= 2)
        {
            return true;
        }
    }

    return false;
}

int main(int argc, char *argv[])
{
    // Allow specifying input file via command line argument
    string filename = (argc > 1) ? argv[1] : "input.txt";

    ifstream input(filename);
    if (!input.is_open())
    {
        cerr << "Error: Could not open " << filename << endl;
        return 1;
    }

    vector<pair<long long, long long>> ranges;
    string line;

    while (getline(input, line))
    {
        stringstream ss(line);
        string range_str;

        while (getline(ss, range_str, ','))
        {
            // Trim whitespace
            size_t start = range_str.find_first_not_of(" \t\n\r");
            if (start == string::npos)
                continue;
            range_str = range_str.substr(start);

            size_t last_dash = range_str.rfind('-');
            if (last_dash == string::npos)
                continue;

            long long range_start = stoll(range_str.substr(0, last_dash));
            long long range_end = stoll(range_str.substr(last_dash + 1));

            pair<long long, long long> p;
            p.first = range_start;
            p.second = range_end;
            ranges.push_back(p);
        }
    }
    input.close();

    long long total = 0;
    int invalid_count = 0;

    // Check each range for invalid IDs
    for (int i = 0; i < ranges.size(); i++)
    {
        long long start = ranges[i].first;
        long long end = ranges[i].second;

        for (long long id = start; id <= end; id++)
        {
            if (is_invalid_id(id))
            {
                total += id;
                invalid_count++;
            }
        }
    }

    cout << "Sum of invalid IDs: " << total << endl;

    return 0;
}