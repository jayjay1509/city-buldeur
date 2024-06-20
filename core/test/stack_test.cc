#include "maths/stack.h"

#include <gtest/gtest.h>


class stackFixture : public ::testing::TestWithParam<std::pair<core::FixedStack<int, 4>, std::vector<int>>> {};

// Test case for push and peek functions
TEST_P(stackFixture, PushAndPeek) {
    auto [stack, vector] = GetParam();
    for (auto value : vector) {
        stack.push(value);
    }

    // Ensure peek() throws an exception on an empty stack
    if (!vector.empty()) {
        EXPECT_EQ(stack.front(), vector.back());
    }
    else {
        EXPECT_THROW(stack.front(), std::underflow_error);
    }
}

// Test case for pop function
TEST_P(stackFixture, Pop) {
    auto [stack, vector] = GetParam();
    for (auto value : vector) {
        stack.push(value);
    }

    // Ensure pop() and peek() work correctly
    if (!vector.empty()) {
        for (size_t i = 0; i < vector.size(); ++i) {
            stack.pop();
            if (i < vector.size() - 1) {
                EXPECT_EQ(stack.front(), vector[vector.size() - i - 2]);
            }
            else {
                EXPECT_THROW(stack.front(), std::underflow_error);
            }
        }
    }
    else {
        EXPECT_THROW(stack.pop(), std::underflow_error);
    }
}

INSTANTIATE_TEST_SUITE_P(Numbers, stackFixture,
    testing::Values(
        std::make_pair(core::FixedStack<int, 4>(), std::vector<int>{1, 4, 5, 123}),
        std::make_pair(core::FixedStack<int, 4>(), std::vector<int>{5, 123, 3, -1}),
        std::make_pair(core::FixedStack<int, 4>(), std::vector<int>{})
    )
);

class StackDyn : public ::testing::TestWithParam<std::pair<core::DynamicStack<int>, std::vector<int>>> {};

// Test case for push and peek functions
TEST_P(StackDyn, PushAndPeek) {
    auto [stack, vector] = GetParam();
    for (auto value : vector) {
        stack.push(value);
    }

    // Ensure peek() throws an exception on an empty stack
    if (!vector.empty()) {
        EXPECT_EQ(stack.front(), vector.back());
    }
    else {
        EXPECT_THROW(stack.front(), std::underflow_error);
    }
}

// Test case for pop function
TEST_P(StackDyn, Pop) {
    auto [stack, vector] = GetParam();
    for (auto value : vector) {
        stack.push(value);
    }

    // Ensure pop() and peek() work correctly
    if (!vector.empty()) {
        for (size_t i = 0; i < vector.size(); ++i) {
            stack.pop();
            if (i < vector.size() - 1) {
                EXPECT_EQ(stack.front(), vector[vector.size() - i - 2]);
            }
            else {
                EXPECT_THROW(stack.front(), std::underflow_error);
            }
        }
    }
    else {
        EXPECT_THROW(stack.pop(), std::underflow_error);
    }
}

INSTANTIATE_TEST_SUITE_P(Numbers, StackDyn,
    ::testing::Values(
        std::make_pair(core::DynamicStack<int>(), std::vector<int>{1, 4, 5, 123}),
        std::make_pair(core::DynamicStack<int>(), std::vector<int>{5, 123, 3, -1}),
        std::make_pair(core::DynamicStack<int>(), std::vector<int>{})
    )
);
