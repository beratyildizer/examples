#include <vector>

void max_heapify(std::vector<int>& input, size_t size, size_t current)
{
    size_t left = (current * 2) + 1;
    size_t right = (current * 2) + 2;

    int largest = current;

    if (left < size && input[left] > input[largest])
        largest = left;

    if (right < size && input[right] > input[largest])
        largest = right;

    if (largest != current)
    {
        std::swap(input[current], input[largest]);
        max_heapify(input, size, largest);
    }
}

void heapsort(std::vector<int>& input)
{
    // Normally we could simply use std::make_heap and std::sort_heap.

    for (size_t i = input.size() / 2; i > 0; --i)
    {
        max_heapify(input, input.size(), i - 1);
    }

    for (size_t i = input.size(); i > 0; -- i)
    {
        std::swap(input[0], input[i - 1]);
        max_heapify(input, i - 1, 0);
    }
}

void sort_and_print(std::vector<int>& data)
{
    printf("Before: [");

    for (size_t i = 0; i < data.size(); i++)
    {
        printf("%d,", data[i]);
    }

    printf("]\n");

    heapsort(data);

    printf("After: [");

    for (size_t i = 0; i < data.size(); i++)
    {
        printf("%d,", data[i]);
    }

    printf("]\n\n");
}

int main()
{
    std::vector<int> testcase_a = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9 };
    std::vector<int> testcase_b = { -1, -2, -3, -4, -5, -6, -7 };
    std::vector<int> testcase_c = { -10, 9, -8, 7, -6, 5, -4, 3, -2, 1, 0 };
    std::vector<int> testcase_d = { -10 };
    std::vector<int> testcase_e = { 10, -10 };

    sort_and_print(testcase_a);
    sort_and_print(testcase_b);
    sort_and_print(testcase_c);
    sort_and_print(testcase_d);
    sort_and_print(testcase_e);

    return 0;
}