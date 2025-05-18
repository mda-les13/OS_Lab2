#include <windows.h>
#include <iostream>
#include <vector>
#include <stdexcept>

struct ThreadData
{
    std::vector<int>* array;
    int* minElement;
    int* maxElement;
    double* averageValue;
};

DWORD WINAPI MinMaxThread(LPVOID lpParam)
{
    try
    {
        ThreadData* data = static_cast<ThreadData*>(lpParam);
        std::vector<int>& array = *data->array;
        int& minElement = *data->minElement;
        int& maxElement = *data->maxElement;

        for (size_t i = 0; i < array.size(); ++i)
        {
            if (array[i] < minElement)
            {
                minElement = array[i];
            }
            Sleep(7);
            if (array[i] > maxElement)
            {
                maxElement = array[i];
            }
            Sleep(7);
        }
        std::cout << "Minimum element: " << minElement << std::endl;
        std::cout << "Maximum element: " << maxElement << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error in MinMaxThread thread: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

DWORD WINAPI AverageThread(LPVOID lpParam)
{
    try {
        ThreadData* data = static_cast<ThreadData*>(lpParam);
        std::vector<int>& array = *data->array;
        double& averageValue = *data->averageValue;

        double sum = 0.0;
        for (size_t i = 0; i < array.size(); ++i)
        {
            sum += array[i];
            Sleep(12);
        }
        averageValue = sum / array.size();
        std::cout << "Average value: " << averageValue << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error in AverageThread: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

void replaceMinMaxWithAverage(std::vector<int>& array, int minElement, int maxElement, double averageValue)
{
    for (size_t i = 0; i < array.size(); ++i)
    {
        if (array[i] == minElement || array[i] == maxElement)
        {
            array[i] = static_cast<int>(averageValue);
        }
    }
}

int main()
{
    try
    {
        int n;
        std::cout << "Enter the number of array elements: ";
        std::cin >> n;

        if (n <= 0)
        {
            throw std::invalid_argument("The number of elements must be positive.");
        }

        std::vector<int> array(n);
        std::cout << "Enter Array Elements: ";
        for (int i = 0; i < n; ++i)
        {
            std::cin >> array[i];
        }

        int minElement = INT_MAX;
        int maxElement = INT_MIN;
        double averageValue = 0.0;

        ThreadData threadData = { &array, &minElement, &maxElement, &averageValue };

        HANDLE hMinMax = CreateThread(NULL, 0, MinMaxThread, &threadData, 0, NULL);
        if (hMinMax == NULL)
        {
            throw std::runtime_error("Failed to create MinMaxThread thread.");
        }

        HANDLE hAverage = CreateThread(NULL, 0, AverageThread, &threadData, 0, NULL);
        if (hAverage == NULL)
        {
            CloseHandle(hMinMax);
            throw std::runtime_error("Failed to create AverageThread.");
        }

        DWORD waitResultMinMax = WaitForSingleObject(hMinMax, INFINITE);
        DWORD waitResultAverage = WaitForSingleObject(hAverage, INFINITE);

        if (waitResultMinMax != WAIT_OBJECT_0)
        {
            throw std::runtime_error("Could not wait for MinMaxThread to complete.");
        }
        if (waitResultAverage != WAIT_OBJECT_0)
        {
            throw std::runtime_error("Could not wait for AverageThread to complete.");
        }

        replaceMinMaxWithAverage(array, minElement, maxElement, averageValue);

        std::cout << "Modified array: ";
        for (int num : array)
        {
            std::cout << num << " ";
        }
        std::cout << std::endl;

        CloseHandle(hMinMax);
        CloseHandle(hAverage);

        std::cin >> n;

    }
    catch (const std::exception& e)
    {
        std::cerr << "An error has occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}