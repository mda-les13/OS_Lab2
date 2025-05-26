#include <vector>
#include <climits>
#include "mettle\include\mettle.hpp"
// Подключаем реализацию функций из основного файла
#include "main.cpp"

using namespace mettle;

// ----------------------------
// Тесты для replaceMinMaxWithAverage
// ----------------------------

suite<> replace_min_max_with_average("replaceMinMaxWithAverage", [](auto &_) {
    _.test("Replace single min and max", []() {
        std::vector<int> array = {1, 2, 3, 4, 5};
        replaceMinMaxWithAverage(array, 1, 5, 3.5);
        std::vector<int> expected = {3, 2, 3, 4, 3};
        expect(array).equal(expected);
    });

    _.test("Replace multiple min and max", []() {
        std::vector<int> array = {1, 1, 3, 5, 5};
        replaceMinMaxWithAverage(array, 1, 5, 2.8);
        std::vector<int> expected = {2, 2, 3, 2, 2};
        expect(array).equal(expected);
    });

    _.test("All elements are the same", []() {
        std::vector<int> array = {4, 4, 4, 4};
        replaceMinMaxWithAverage(array, 4, 4, 4.0);
        std::vector<int> expected = {4, 4, 4, 4};
        expect(array).equal(expected);
    });
});

// ----------------------------
// Тесты для MinMaxThread
// ----------------------------

suite<> minmax_thread("MinMaxThread", [](auto &_) {
    _.test("Find min and max in simple array", []() {
        std::vector<int> array = {5, 3, 8, 1, 9, 2};
        int minElement = INT_MAX;
        int maxElement = INT_MIN;
        double averageValue = 0.0;

        ThreadData data = {&array, &minElement, &maxElement, &averageValue};
        DWORD result = MinMaxThread(&data);

        expect(minElement).equal(1);
        expect(maxElement).equal(9);
        expect(result).equal(static_cast<DWORD>(0));
    });

    _.test("Single element array", []() {
        std::vector<int> array = {7};
        int minElement = INT_MAX;
        int maxElement = INT_MIN;
        double averageValue = 0.0;

        ThreadData data = {&array, &minElement, &maxElement, &averageValue};
        DWORD result = MinMaxThread(&data);

        expect(minElement).equal(7);
        expect(maxElement).equal(7);
        expect(result).equal(static_cast<DWORD>(0));
    });

    _.test("Null pointer handling", []() {
        ThreadData data = {nullptr, nullptr, nullptr, nullptr};
        DWORD result = MinMaxThread(&data);
        expect(result).equal(static_cast<DWORD>(1));
    });
});

// ----------------------------
// Тесты для AverageThread
// ----------------------------

suite<> average_thread("AverageThread", [](auto &_) {
    _.test("Compute average of simple array", []() {
        std::vector<int> array = {1, 2, 3, 4, 5};
        double averageValue = 0.0;

        ThreadData data = {&array, nullptr, nullptr, &averageValue};
        DWORD result = AverageThread(&data);

        expect(averageValue).approximately(3.0, 1e-6);
        expect(result).equal(static_cast<DWORD>(0));
    });

    _.test("Compute average of negative numbers", []() {
        std::vector<int> array = {-1, -2, -3, -4, -5};
        double averageValue = 0.0;

        ThreadData data = {&array, nullptr, nullptr, &averageValue};
        DWORD result = AverageThread(&data);

        expect(averageValue).approximately(-3.0, 1e-6);
        expect(result).equal(static_cast<DWORD>(0));
    });

    _.test("Null pointer handling", []() {
        ThreadData data = {nullptr, nullptr, nullptr, nullptr};
        DWORD result = AverageThread(&data);
        expect(result).equal(static_cast<DWORD>(1));
    });
});

// ----------------------------
// Точка входа для тестов
// ----------------------------

int main(int argc, char* argv[]) {
    mettle::log::console logger;
    return mettle::run_all_tests(argc, argv);
}