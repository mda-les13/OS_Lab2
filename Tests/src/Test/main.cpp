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