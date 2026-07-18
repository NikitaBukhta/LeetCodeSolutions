#include "CharTableSolution.h"

#include <algorithm>
#include <array>
#include <climits>
#include <cstdint>

int CharTableSolution::lengthOfLongestSubstring(std::string s) {
    // Index range is 0..UCHAR_MAX, so the table needs UCHAR_MAX + 1 slots.
    std::array<size_t, UCHAR_MAX + 1> charTable{};
    size_t leftIndex{0};
    size_t maxLength{0};

    for (size_t rightIndex{0}; rightIndex < s.size(); ++rightIndex) {
        // charTable stores (last position + 1); 0 means "never seen".
        auto& currentCharNextPos = charTable[static_cast<uint8_t>(s[rightIndex])];

        // check for reps;
        if (leftIndex < currentCharNextPos) {
            leftIndex = currentCharNextPos;
        }

        currentCharNextPos = rightIndex + 1;
        maxLength = std::max(maxLength, rightIndex - leftIndex + 1);
    }

    return static_cast<int>(maxLength);
}
