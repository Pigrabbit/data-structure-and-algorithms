#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

void mergeSort(int arr[], int size);
void mergeSortRecur(int arr[], int left, int right);
void merge(int arr[], int leftPos, int rightPos, int rightEnd);

void mergeSort(int arr[], int size)
{
    mergeSortRecur(arr, 0, size - 1);
}

void mergeSortRecur(int arr[], int left, int right)
{
    if (left < right)
    {
        int middle = left + (right - left) / 2;
        mergeSortRecur(arr, left, middle);
        mergeSortRecur(arr, middle + 1, right);
        merge(arr, left, middle + 1, right);
    }
}

void merge(int arr[], int leftPos, int rightPos, int rightEnd)
{
    int leftEnd = rightPos - 1, leftPosSaved = leftPos;

    int numElements = rightEnd - leftPos + 1;
    int *tmp = new int[numElements]();
    int tmpPos = 0;

    while (leftPos <= leftEnd && rightPos <= rightEnd)
    {
        if (arr[leftPos] < arr[rightPos])
            tmp[tmpPos++] = arr[leftPos++];
        else
            tmp[tmpPos++] = arr[rightPos++];
    }

    while (leftPos <= leftEnd)
        tmp[tmpPos++] = arr[leftPos++];
    while (rightPos <= rightEnd)
        tmp[tmpPos++] = arr[rightPos++];

    // copy tmp to original array
    for (int i = 0; i < numElements; i++)
        arr[leftPosSaved + i] = tmp[i];

    delete[] tmp;
}

SCENARIO("merge can merge two different presorted array into one")
{
    GIVEN("Two presorted arrays with some elements")
    {
        int size = 4;
        int arr[]{5, 20, 7, 12};

        REQUIRE(sizeof(arr) / sizeof(*arr) == size);

        WHEN("merges two presorted different array")
        {
            THEN("it merges elements in ascending order")
            {
                int leftPos = 0, rightEnd = size - 1;
                int rightPos = (leftPos + rightEnd) / 2 + 1;
                int exp[]{5, 7, 12, 20};

                merge(arr, leftPos, rightPos, rightEnd);

                for (int i = 0; i < size; i++)
                {
                    REQUIRE(arr[i] == exp[i]);
                }
            }
        }
    }
}

SCENARIO("mergeSortRecur operates merge sort recursively")
{
    GIVEN("an unsorted array")
    {
        int arr[]{38, 27, 43, 3, 9, 82, 10};
        int size = sizeof(arr) / sizeof(*arr);

        WHEN("array has more than 1 elements")
        {
            THEN("divides the given array into two and recursively merge sort them")
            {
                int left = 0, right = size - 1;
                int exp[]{3, 9, 10, 27, 38, 43, 82};
                mergeSortRecur(arr, left, right);
                for (int i = 0; i < size; i++)
                {
                    REQUIRE(arr[i] == exp[i]);
                }
            }
        }
    }
}
