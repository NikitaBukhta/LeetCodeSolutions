#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <tuple>
#include <typeinfo>

#if defined(__GNUC__) || defined(__clang__)
#include <cxxabi.h>
#endif

#include "Solution.h"
#include "BinaryMapSolution.h"
#include "LiniarSolution.h"
#include "CharTableSolution.h"

inline std::string SolutionName(const Solution& s) {
    const char* raw = typeid(s).name();
    std::string name = raw;
#if defined(__GNUC__) || defined(__clang__)
    int status = 0;
    char* demangled = abi::__cxa_demangle(raw, nullptr, nullptr, &status);
    if (status == 0 && demangled != nullptr) {
        name = demangled;
    }
    std::free(demangled);
#endif
    for (const char* tag : {"class ", "struct "}) {
        const std::string prefix = tag;
        if (name.rfind(prefix, 0) == 0) {
            name.erase(0, prefix.size());
            break;
        }
    }
    return name;
}

inline void PrintTo(const std::shared_ptr<Solution>& s, std::ostream* os) {
    *os << (s ? SolutionName(*s) : std::string("nullptr"));
}

namespace {

std::string Sanitize(std::string s) {
    for (char& c : s) {
        if (!std::isalnum(static_cast<unsigned char>(c))) {
            c = '_';
        }
    }
    return s;
}

struct Case {
    std::string name;
    std::string input;
    int expected;
};

void PrintTo(const Case& c, std::ostream* os) {
    *os << c.name << " (input=\"" << c.input << "\", expected=" << c.expected
        << ")";
}

using Param = std::tuple<std::shared_ptr<Solution>, Case>;

class LengthOfLongestSubstringTest
    : public ::testing::TestWithParam<Param> {};

TEST_P(LengthOfLongestSubstringTest, ReturnsLongestLength) {
    const std::shared_ptr<Solution>& solution = std::get<0>(GetParam());
    const Case& c = std::get<1>(GetParam());
    EXPECT_EQ(solution->lengthOfLongestSubstring(c.input), c.expected);
}

const auto kSolutions = ::testing::Values(
    std::make_shared<BinaryMapSolution>(),
    std::make_shared<LiniarSolution>(),
    std::make_shared<CharTableSolution>()
);

const auto kCases = ::testing::Values(
    // LeetCode examples.
    Case{"Leetcode_1", "abcabcbb", 3},
    Case{"Leetcode_2", "bbbbb", 1},
    Case{"Leetcode_3", "pwwkew", 3},
    Case{"Leetcode_4", "aabaab!bb", 3},
    // Edge cases.
    Case{"EmptyString", "", 0},
    Case{"SingleCharacter", "a", 1},
    Case{"SingleSpace", " ", 1},
    Case{"TwoDistinct", "au", 2},
    Case{"AllUnique", "abcdef", 6},
    // Off-by-one / window-reset traps.
    Case{"RepeatNotAtWindowStart_abba", "abba", 2},
    Case{"InteriorRepeat_dvdf", "dvdf", 3},
    Case{"TrailingLongWindow_tmmzuxt", "tmmzuxt", 5},
    Case{"BestWindowAtEnd_abcb", "abcb", 3},
    // Non-letter characters.
    Case{"DigitsAndSymbols", "1!2@3#3", 6},
    Case{"SpacesInside", "a b c a", 3},
    // Scale.
    Case{"AllSameCharacter", std::string(500, 'z'), 1});

INSTANTIATE_TEST_SUITE_P(
    Solutions,
    LengthOfLongestSubstringTest,
    ::testing::Combine(kSolutions, kCases),
    [](const ::testing::TestParamInfo<Param>& info) {
        return Sanitize(SolutionName(*std::get<0>(info.param)) + "_" +
                        std::get<1>(info.param).name);
    });

}  // namespace
