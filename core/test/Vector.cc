#include "maths/Vector.h"
#include <gtest/gtest.h>

// Définir un test fixture pour les opérations complexes sur Vector
class VectorComplexFixture : public ::testing::TestWithParam<std::vector<int>> {};


TEST_P(VectorComplexFixture, CombinedOperations) {
   
    constexpr int GrowthDividend = 3;
    constexpr int GrowthDivisor = 2;

    core::Vector<int, std::allocator<int>, GrowthDividend, GrowthDivisor> vector;
    auto& values = GetParam();

    
    for (auto value : values) {
        vector.push_back(value);
    }

    
    ASSERT_EQ(vector.size(), values.size());
    for (size_t i = 0; i < values.size(); ++i) {
        EXPECT_EQ(vector.at(i), values[i]);
    }

    
    ASSERT_GE(vector.capacity(), vector.size());

    
    std::size_t initial_capacity = vector.capacity();

    
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

    
    ASSERT_GE(vector.capacity(), initial_capacity);


    std::size_t before_realloc = vector.capacity();

    //si trop haut sa refais une realocation suplementaire en le test nest pas juste 
    for (int i = 0; i < 4; ++i) {
        vector.push_back(i);
    }

    
    ASSERT_EQ(vector.capacity(), before_realloc * GrowthDividend / GrowthDivisor);
}


INSTANTIATE_TEST_SUITE_P(Values, VectorComplexFixture,
    ::testing::Values(
        std::vector<int>{1, 4, 5, 123,4,5,6,3},
        std::vector<int>{5, 123, 3, -1},
        std::vector<int>{10, 20, 30, 40, 50, 60}
    )
);