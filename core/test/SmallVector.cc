#include "maths/SmallVector.h"

#include <gtest/gtest.h>


class SmallVectorComplexFixture : public ::testing::TestWithParam<std::vector<int>> {};

TEST_P(SmallVectorComplexFixture, CombinedOperations) {
    core::SmallVector<int, 6> vector;
    auto values = GetParam();
    
    // Ajout initial de tous les éléments
    for (auto value : values) {
        vector.push_back(value);
    }

    // Vérification de la taille et des éléments
    ASSERT_EQ(vector.size(), values.size());
    for (size_t i = 0; i < values.size(); ++i) {
        EXPECT_EQ(vector.at(i), values[i]);
    }

    // Suppression de la moitié des éléments
    size_t originalSize = vector.size();
    for (size_t i = 0; i < originalSize / 2; ++i) {
        vector.pop_back();
    }
    
    // Vérification de la taille après suppression
    ASSERT_EQ(vector.size(), originalSize / 2);
    
    // Réinsertion d'éléments
    for (size_t i = 0; i < originalSize / 2; ++i) {
        vector.push_back(values[i]);
    }

    // Vérification finale de la taille et des éléments
    ASSERT_EQ(vector.size(), originalSize);
    for (size_t i = 0; i < originalSize; ++i) {
        EXPECT_EQ(vector.at(i), values[i % (originalSize / 2)]);
    }
}

INSTANTIATE_TEST_SUITE_P(Values, SmallVectorComplexFixture,
    ::testing::Values(
        std::vector<int>{1, 4, 5, 123},
        std::vector<int>{5, 123, 3, -1},
        std::vector<int>{10, 20, 30, 40, 50, 60}
    )
);