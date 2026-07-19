#ifndef LEETCODE_SOLUTION_H
#define LEETCODE_SOLUTION_H

#include <vector>

class Solution {
public:
    virtual ~Solution() = default;

    virtual std::vector<int> twoSum(std::vector<int>& nums, int target) = 0;
};

#endif //LEETCODE_SOLUTION_H
