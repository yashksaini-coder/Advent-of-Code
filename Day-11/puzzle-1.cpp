#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <sstream>
#include <cstdint>

using Dev = std::array<uint8_t, 3>;

// Hash function for Dev (array of 3 bytes)
struct DevHash {
    size_t operator()(const Dev& dev) const {
        return (size_t(dev[0]) << 16) | (size_t(dev[1]) << 8) | size_t(dev[2]);
    }
};

using DevMap = std::unordered_map<Dev, std::vector<Dev>, DevHash>;
using DevSetMap = std::unordered_map<Dev, std::unordered_set<Dev, DevHash>, DevHash>;

size_t paths(const DevMap& fwd, DevSetMap bwd, const Dev& from, const Dev& to) {
    std::unordered_map<Dev, size_t, DevHash> count;
    count[from] = 1;
    
    // Find all devices with no backward dependencies
    std::vector<Dev> pending;
    for (const auto& [dev, _] : fwd) {
        if (bwd.find(dev) == bwd.end()) {
            pending.push_back(dev);
        }
    }
    
    while (!pending.empty()) {
        Dev dev = pending.back();
        pending.pop_back();
        
        auto fwd_it = fwd.find(dev);
        if (fwd_it != fwd.end()) {
            size_t c = count[dev];
            
            for (const Dev& dep : fwd_it->second) {
                count[dep] += c;
                
                auto& revs = bwd[dep];
                revs.erase(dev);
                
                if (revs.empty()) {
                    pending.push_back(dep);
                }
            }
        }
    }
    
    return count[to];
}

int main() {
    std::ifstream file("input.txt");
    if (!file) {
        std::cerr << "Error: Could not open input.txt" << std::endl;
        return 1;
    }
    
    DevMap fwd;
    DevSetMap bwd;
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        // Parse device name (first 3 bytes)
        Dev dev = {(uint8_t)line[0], (uint8_t)line[1], (uint8_t)line[2]};
        
        // Parse outputs (after ": ")
        std::vector<Dev> outs;
        size_t pos = 5; // Skip "xxx: "
        while (pos + 2 < line.length()) {
            Dev out = {(uint8_t)line[pos], (uint8_t)line[pos+1], (uint8_t)line[pos+2]};
            outs.push_back(out);
            
            // Add to backward map
            bwd[out].insert(dev);
            
            pos += 4; // Move to next device (3 chars + 1 space)
        }
        
        fwd[dev] = outs;
    }
    
    Dev from = {'y', 'o', 'u'};
    Dev to = {'o', 'u', 't'};
    
    std::cout << paths(fwd, bwd, from, to) << std::endl;
    
    return 0;
}
