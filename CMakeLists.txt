cmake_minimum_required(VERSION 3.14)

project(LeetCode LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

# ---------------------------------------------------------------------------
# GoogleTest: use a system/prebuilt install if present, otherwise download it.
# ---------------------------------------------------------------------------
find_package(GTest QUIET)

if(NOT GTest_FOUND)
    message(STATUS "GTest not found locally - fetching it via FetchContent")

    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.15.2
        GIT_SHALLOW    TRUE
    )

    # Keep GoogleTest from clobbering our compiler/runtime settings on Windows.
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    FetchContent_MakeAvailable(googletest)
endif()

# ---------------------------------------------------------------------------
# Helper so every subdir stays a one-liner:
#   add_leetcode_test(<target_name> <source1> [<source2> ...])
# Creates the executable, links GTest, and registers it with CTest.
# ---------------------------------------------------------------------------
include(GoogleTest)

function(add_leetcode_test target_name)
    add_executable(${target_name} ${ARGN})
    target_link_libraries(${target_name} PRIVATE GTest::gtest_main)
    gtest_discover_tests(${target_name})
endfunction()

# ---------------------------------------------------------------------------
# Auto-include every immediate subdirectory that ships its own CMakeLists.txt,
# so new problem folders are picked up without editing this file.
# ---------------------------------------------------------------------------
file(GLOB children RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)
foreach(child ${children})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${child}
       AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${child}/CMakeLists.txt)
        add_subdirectory(${child})
    endif()
endforeach()
