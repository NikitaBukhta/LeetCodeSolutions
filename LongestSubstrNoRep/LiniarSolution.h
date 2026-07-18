#ifndef LEETCODE_LINIARSOLUTION_H
#define LEETCODE_LINIARSOLUTION_H

#include "Solution.h"

class LiniarSolution final : public Solution {
public:
    ~LiniarSolution() override = default;

    int lengthOfLongestSubstring(std::string s) override;
};

#endif //LEETCODE_LINIARSOLUTION_H
