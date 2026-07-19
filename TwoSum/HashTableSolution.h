#ifndef LEETCODE_HASHTABLESOLUTION_H
#define LEETCODE_HASHTABLESOLUTION_H

#include "Solution.h"

class HashTableSolution final : public Solution {
public:
    ~HashTableSolution() override = default;

    std::vector<int> twoSum(std::vector<int> &nums, int target) override;
};


#endif //LEETCODE_HASHTABLESOLUTION_H
