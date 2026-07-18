#ifndef LEETCODE_CHARTABLESOLUTION_H
#define LEETCODE_CHARTABLESOLUTION_H

#include "Solution.h"

class CharTableSolution final : public Solution {
public:
    ~CharTableSolution() override = default;

    int lengthOfLongestSubstring(std::string s) override;
};


#endif //LEETCODE_CHARTABLESOLUTION_H
