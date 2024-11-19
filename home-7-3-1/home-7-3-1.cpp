#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <future>


int find_min_element(const std::vector<int>& arr, int start_index, int end_index)
{
    if (start_index >= end_index) {
        return start_index;
    }

    int min_index = start_index;
    for (int i = start_index + 1; i <= end_index; ++i) {
        if (arr[i] < arr[min_index]) {
            min_index = i;
        }
    }
    return min_index;
}


void find_min(std::promise<int>&& promise, const std::vector<int>& arr, int start_index, int end_index)
{

    int min_index = find_min_element(arr, start_index, end_index);
    promise.set_value(min_index);
}


void selection_sort(std::vector<int>& arr)
{
    int n = static_cast<int>(arr.size());

    for (int i = 0; i < n - 1; ++i) {

        std::promise<int> promise;
        auto future = promise.get_future();

        std::thread(find_min, std::move(promise), std::ref(arr), i, n - 1).detach();

        int min_index = future.get();

        std::swap(arr[i], arr[min_index]);
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    std::vector<int> arr{ 64, 25, 12, 22, 11 };

    std::cout << "Массив: ";
    for (auto x : arr) {
        std::cout << x << ' ';
    }
    std::cout << '\n';

    selection_sort(arr);

    std::cout << "Отсортированный массив: ";
    for (auto x : arr) {
        std::cout << x << ' ';
    }
    std::cout << '\n';

    return 0;
}
