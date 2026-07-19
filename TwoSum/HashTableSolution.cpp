#include "HashTableSolution.h"

#include <algorithm>
#include <iterator>
#include <unordered_map>

std::vector<int> HashTableSolution::twoSum(std::vector<int> &nums, int target) {
    std::pmr::unordered_multimap<int, int> hash;  // value; index;
    hash.reserve(nums.size());

    for (size_t i{0}; i < nums.size(); ++i) {
        hash.insert(std::make_pair(nums[i], i));
    }

    for (auto it{hash.begin()}; it != hash.end(); ++it) {
        const int searchNum = target - it->first;
        auto searchIt = std::find_if( std::next(it), hash.end(), [searchNum](std::pair<int, int> p) { return p.first == searchNum; });
        if (searchIt != hash.end() && it != searchIt) {
            return {it->second, searchIt->second};
        }
    }

     return {};
}
