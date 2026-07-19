#include "BinaryTableSolution.h"

#include <map>

std::vector<int> BinaryTableSolution::twoSum(std::vector<int> &nums, int target) {
    std::multimap<int, int> hash;  // value; index;

    for (size_t i{0}; i < nums.size(); ++i) {
        hash.insert(std::make_pair(nums[i], i));
    }

    for (auto it{hash.begin()}; it != hash.end(); ++it) {
        const int searchNum = target - it->first;
        if (auto searchIt = std::find_if( std::next(it), hash.end(), [searchNum](const std::pair<int, int> &p) { return p.first == searchNum; }); searchIt != hash.end() && it != searchIt) {
            return {it->second, searchIt->second};
        }
    }

    return {};
}
