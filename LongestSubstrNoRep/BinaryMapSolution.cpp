#include "BinaryMapSolution.h"

#include <algorithm>
#include <map>
#include <ostream>
#include <iostream>

int BinaryMapSolution::lengthOfLongestSubstring(std::string s) {
    auto first = s.begin();
    std::map<char, std::string::iterator> cache;
    int maxLength = 0;

    for (auto current = first; current != s.end(); ++current) {
        auto cacheIt = cache.find(*current);

        if (cacheIt != cache.end() && cacheIt->second >= first) {
            std::cout << "Found rep: " << cacheIt->first << std::endl;
            maxLength = std::max(maxLength, static_cast<int>(std::distance(first, current)));
            first = cacheIt->second + 1;
        }

        cache.insert_or_assign(*current, current);
    }

    return std::max(maxLength, static_cast<int>(std::distance(first, s.end())));
}
