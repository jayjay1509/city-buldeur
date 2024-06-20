#include "maths/BasicVector.h"
#include <gtest/gtest.h>


class BasicVectorFixture : public ::testing::TestWithParam<std::vector<int>> {};

TEST_P(BasicVectorFixture, CombinedOperations) {
    core::BasicVector<int, 6> vector;
    auto values = GetParam();

    
    for (auto value : values) {
        vector.push_back(value);
    }

    
    ASSERT_EQ(vector.size(), values.size());
    for (size_t i = 0; i < values.size(); ++i) {
        EXPECT_EQ(vector.at(i), values[i]);
    }

    
    size_t originalSize = vector.size();
    for (size_t i = 0; i < originalSize / 2; ++i) {
        vector.pop_back();
    }

    
    ASSERT_EQ(vector.size(), originalSize / 2);

    
    for (size_t i = 0; i < originalSize / 2; ++i) {
        vector.push_back(values[i]);
    }

    
    ASSERT_EQ(vector.size(), originalSize);
    for (size_t i = 0; i < originalSize; ++i) {
        EXPECT_EQ(vector.at(i), values[i % (originalSize / 2)]);
    }
}

INSTANTIATE_TEST_SUITE_P(Values, BasicVectorFixture,
    ::testing::Values(
        std::vector<int>{1, 4, 5, 123},
        std::vector<int>{5, 123, 3, -1},
        std::vector<int>{10, 20, 30, 40, 50, 60}
    )
);