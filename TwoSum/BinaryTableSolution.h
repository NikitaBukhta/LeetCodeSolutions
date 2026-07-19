#ifndef LEETCODE_BINARYTABLESOLUTION_H
#define LEETCODE_BINARYTABLESOLUTION_H

#include "Solution.h"

#include <vector>

class BinaryTableSolution final : public Solution {
public:
    ~BinaryTableSolution() override = default;

    std::vector<int> twoSum(std::vector<int> &nums, int target) override;
};


#endif //LEETCODE_BINARYTABLESOLUTION_H
