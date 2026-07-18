#include "LiniarSolution.h"

#include <ostream>

int LiniarSolution::lengthOfLongestSubstring(std::string s) {
        int maxLength{0};
        std::string substring;

        for (const auto c : s) {
            size_t pos = substring.find(c);
            if (pos != std::string::npos) {
                const size_t substrSize = substring.size();
                maxLength = std::max(maxLength, static_cast<int>(substrSize));

                if (pos == substrSize - 1) {
                    substring = c;
                } else {
                    substring = substring.substr(pos + 1) + c;
                }

                continue;
            }

            substring.push_back(c);
        }

        return std::max(maxLength, static_cast<int>(substring.size()));
}
