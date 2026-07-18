#ifndef LEETCODE_BINARYMAPSOLUTION_H
#define LEETCODE_BINARYMAPSOLUTION_H

#include "Solution.h"

class BinaryMapSolution final : public Solution {
public:
    ~BinaryMapSolution() override = default;

    int lengthOfLongestSubstring(std::string s) override;
};

#endif //LEETCODE_BINARYMAPSOLUTION_H
