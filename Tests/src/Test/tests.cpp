#include <gtest/gtest.h>
#include <vector>
#include <climits>
#include "main.cpp"

// ----------------------------
// Тесты для replaceMinMaxWithAverage
// ----------------------------

TEST(ReplaceMinMaxWithAverageTest, ReplaceSingleMinAndMax) {
    std::vector<int> array = {1, 2, 3, 4, 5};
    replaceMinMaxWithAverage(array, 1, 5, 3.5);
    std::vector<int> expected = {3, 2, 3, 4, 3};
    EXPECT_EQ(array, expected);
}

TEST(ReplaceMinMaxWithAverageTest, ReplaceMultipleMinAndMax) {
    std::vector<int> array = {1, 1, 3, 5, 5};
    replaceMinMaxWithAverage(array, 1, 5, 2.8);
    std::vector<int> expected = {2, 2, 3, 2, 2};
    EXPECT_EQ(array, expected);
}

TEST(ReplaceMinMaxWithAverageTest, AllElementsSame) {
    std::vector<int> array = {4, 4, 4, 4};
    replaceMinMaxWithAverage(array, 4, 4, 4.0);
    std::vector<int> expected = {4, 4, 4, 4};
    EXPECT_EQ(array, expected);
}

// ----------------------------
// Тесты для MinMaxThread
// ----------------------------

TEST(MinMaxThreadTest, FindMinMaxInSimpleArray) {
    std::vector<int> array = {5, 3, 8, 1, 9, 2};
    int minElement = INT_MAX;
    int maxElement = INT_MIN;
    double averageValue = 0.0;

    ThreadData data = {&array, &minElement, &maxElement, &averageValue};
    DWORD result = MinMaxThread(&data);

    EXPECT_EQ(minElement, 1);
    EXPECT_EQ(maxElement, 9);
    EXPECT_EQ(result, 0u);
}

TEST(MinMaxThreadTest, SingleElementArray) {
    std::vector<int> array = {7};
    int minElement = INT_MAX;
    int maxElement = INT_MIN;
    double averageValue = 0.0;

    ThreadData data = {&array, &minElement, &maxElement, &averageValue};
    DWORD result = MinMaxThread(&data);

    EXPECT_EQ(minElement, 7);
    EXPECT_EQ(maxElement, 7);
    EXPECT_EQ(result, 0u);
}

// ----------------------------
// Тесты для AverageThread
// ----------------------------

TEST(AverageThreadTest, ComputeAverageOfSimpleArray) {
    std::vector<int> array = {1, 2, 3, 4, 5};
    double averageValue = 0.0;

    ThreadData data = {&array, nullptr, nullptr, &averageValue};
    DWORD result = AverageThread(&data);

    EXPECT_DOUBLE_EQ(averageValue, 3.0);
    EXPECT_EQ(result, 0u);
}

TEST(AverageThreadTest, ComputeAverageOfNegativeNumbers) {
    std::vector<int> array = {-1, -2, -3, -4, -5};
    double averageValue = 0.0;

    ThreadData data = {&array, nullptr, nullptr, &averageValue};
    DWORD result = AverageThread(&data);

    EXPECT_DOUBLE_EQ(averageValue, -3.0);
    EXPECT_EQ(result, 0u);
}

// ----------------------------
// Точка входа для тестов
// ----------------------------

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}