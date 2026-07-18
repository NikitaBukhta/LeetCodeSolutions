#ifndef LEETCODE_SOLUTION_H
#define LEETCODE_SOLUTION_H

#include <string>

class Solution {
public:
    virtual ~Solution() = default;

    virtual int lengthOfLongestSubstring(std::string s) = 0;
};

#endif //LEETCODE_SOLUTION_H
