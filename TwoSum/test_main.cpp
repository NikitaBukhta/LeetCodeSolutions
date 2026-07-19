#include <gtest/gtest.h>

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <memory>
#include <ostream>
#include <string>
#include <tuple>
#include <typeinfo>
#include <vector>

#if defined(__GNUC__) || defined(__clang__)
#include <cxxabi.h>
#endif

#include "Solution.h"
#include "HashTableSolution.h"
#include "BinaryTableSolution.h"

// Human-readable, gtest-safe class name derived automatically from the
// runtime type, so the solution list stays a plain list of instances.
// Lives in the global namespace so the PrintTo below (found via ADL on
// std::shared_ptr<Solution>) can reuse it.
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
    // MSVC's typeid().name() is like "class HashTableSolution" - drop the
    // leading "class "/"struct " tag so the name reads cleanly.
    for (const char* tag : {"class ", "struct "}) {
        const std::string prefix = tag;
        if (name.rfind(prefix, 0) == 0) {
            name.erase(0, prefix.size());
            break;
        }
    }
    return name;
}

// Teach gtest to print a solution as its class name instead of a raw byte
// dump. Must be in the global namespace (an associated namespace of
// std::shared_ptr<Solution>) for ADL to find it.
inline void PrintTo(const std::shared_ptr<Solution>& s, std::ostream* os) {
    *os << (s ? SolutionName(*s) : std::string("nullptr"));
}

namespace {

// Replace anything that isn't [A-Za-z0-9_], since gtest param names are
// restricted to that set.
std::string Sanitize(std::string s) {
    for (char& c : s) {
        if (!std::isalnum(static_cast<unsigned char>(c))) {
            c = '_';
        }
    }
    return s;
}

// One test case: the input array, the target, and the (order-independent)
// pair of indices that forms the unique valid answer, stored sorted so the
// test can compare against a sorted result.
struct Case {
    std::string name;
    std::vector<int> nums;
    int target;
    std::vector<int> expectedSorted;  // ascending, exactly two indices
};

// Pretty-print a Case in gtest diagnostics instead of a raw byte dump.
void PrintTo(const Case& c, std::ostream* os) {
    *os << c.name << " (nums=[";
    for (size_t i = 0; i < c.nums.size(); ++i) {
        if (i != 0) {
            *os << ",";
        }
        *os << c.nums[i];
    }
    *os << "], target=" << c.target << ")";
}

// Param = (solution under test) x (test case). ::testing::Combine below builds
// the full cross product, so every case runs against every solution.
using Param = std::tuple<std::shared_ptr<Solution>, Case>;

class TwoSumTest : public ::testing::TestWithParam<Param> {};

TEST_P(TwoSumTest, ReturnsIndicesThatSumToTarget) {
    const std::shared_ptr<Solution>& solution = std::get<0>(GetParam());
    const Case& c = std::get<1>(GetParam());

    // twoSum takes nums by non-const reference; give each run its own copy.
    std::vector<int> nums = c.nums;
    std::vector<int> result = solution->twoSum(nums, c.target);

    // The answer must be a pair of indices.
    ASSERT_EQ(result.size(), 2u);

    // Both indices must be in range and refer to two different elements.
    ASSERT_GE(result[0], 0);
    ASSERT_GE(result[1], 0);
    ASSERT_LT(static_cast<size_t>(result[0]), c.nums.size());
    ASSERT_LT(static_cast<size_t>(result[1]), c.nums.size());
    EXPECT_NE(result[0], result[1]) << "must not use the same element twice";

    // The two referenced values must add up to the target.
    EXPECT_EQ(static_cast<long long>(c.nums[result[0]]) +
                  static_cast<long long>(c.nums[result[1]]),
              static_cast<long long>(c.target));

    // Exactly one valid answer exists, so it must be the expected index pair
    // (order-independent: compare sorted).
    std::vector<int> sorted = result;
    std::sort(sorted.begin(), sorted.end());
    EXPECT_EQ(sorted, c.expectedSorted);
}

// --- Solutions under test --------------------------------------------------
// Add new implementations here; every case below runs against each of them.
const auto kSolutions = ::testing::Values(
    std::make_shared<HashTableSolution>(),
    std::make_shared<BinaryTableSolution>()
);

// --- Cases: (nums, target) -> the unique pair of answer indices ------------
const auto kCases = ::testing::Values(
    // LeetCode examples.
    Case{"Leetcode_1", {2, 7, 11, 15}, 9, {0, 1}},
    Case{"Leetcode_2", {3, 2, 4}, 6, {1, 2}},
    Case{"Leetcode_3_DuplicateInputs", {3, 3}, 6, {0, 1}},
    // Minimum-size input.
    Case{"TwoElements", {1, 2}, 3, {0, 1}},
    // Negative numbers.
    Case{"AllNegative", {-1, -2, -3, -4, -5}, -8, {2, 4}},
    Case{"MixedSigns", {-3, 4, 3, 90}, 0, {0, 2}},
    // Zero handling.
    Case{"ZeroTargetWithZeros", {0, 4, 3, 0}, 0, {0, 3}},
    Case{"NegativeTarget", {5, -2, 7, -8}, -10, {1, 3}},
    // A repeated value that is NOT the answer (distractor).
    Case{"DuplicateValueDistractor", {3, 2, 3}, 6, {0, 2}},
    // Answer sits at the very end / spans the ends of the array.
    Case{"AnswerAtEnd", {1, 5, 2, 7, 3}, 10, {3, 4}},
    Case{"AnswerSpansFirstAndLast", {5, 1, 1, 1, 5}, 10, {0, 4}},
    // Values at the magnitude limits from the constraints (1e9).
    Case{"LargeMagnitude", {1000000000, -999999993}, 7, {0, 1}},
    Case{"LargeNegativeSum", {-1000000000, -1, -999999999}, -1999999999, {0, 2}});

INSTANTIATE_TEST_SUITE_P(
    Solutions,
    TwoSumTest,
    ::testing::Combine(kSolutions, kCases),
    [](const ::testing::TestParamInfo<Param>& info) {
        return Sanitize(SolutionName(*std::get<0>(info.param)) + "_" +
                        std::get<1>(info.param).name);
    });

}  // namespace
