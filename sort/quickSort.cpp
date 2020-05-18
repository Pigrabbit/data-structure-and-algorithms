#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

void quickSort(int arr[], int size);
void quickSortRecur(int arr[], int start, int end);
int partition(int arr[], int start, int pivotPos, int end);
int getPivotPos(int arr[], int start, int end);
void swap(int arr[], int idx1, int idx2);

void swap(int arr[], int idx1, int idx2)
{
    int tmp = arr[idx1];
    arr[idx1] = arr[idx2];
    arr[idx2] = tmp;
}

int getPivotPos(int arr[], int start, int end)
{
    if (end > start + 1)
    {
        int middle = start + (end - start) / 2;
        return (arr[start] < arr[middle]) ? ((arr[middle] < arr[end]) ? middle : (arr[end] < arr[start]) ? start : end)
                                          : ((arr[end] < arr[middle]) ? middle : ((arr[start] < arr[end]) ? start : end));
    }
    else if (end > start)
        return arr[start] < arr[end] ? start : end;
    else if (end == start)
        return start;
}

int partition(int arr[], int start, int pivotPos, int end)
{
    // Todo
    // 0. get pivot
    int pivot = arr[pivotPos];
    // 1. first move pivot to the end
    swap(arr, pivotPos, end);
    // 2. set left and right for iteration
    int left = start - 1, right = end;
    // 3. loop through start-end to separtate elements into two
    while (true)
    {
        while (arr[++left] < pivot);
        while (arr[--right] > pivot);
        if (left < right)
        {
            swap(arr, left, right);
        }
        else
            break;
    }
    // 4. restore pivot
    swap(arr, end, left);
    return left;
}

void quickSortRecur(int arr[], int start, int end) {
    if (start < end) {
        int pivotPos = getPivotPos(arr, start, end);
        pivotPos = partition(arr, start, pivotPos, end);
        quickSortRecur(arr, start, pivotPos -1);
        quickSortRecur(arr, pivotPos + 1, end);
    }
}

void quickSort(int arr[], int size) {
    quickSortRecur(arr, 0, size - 1);
}

SCENARIO("getPivotPos picks a pivot")
{
    GIVEN("an arry with integers")
    {
        WHEN("the array has more than 3 elements")
        {
            int arr[] = {10, 40, 60, 100, 20};
            int start = 0, end = sizeof(arr) / sizeof(*arr) - 1;
            int expectedPivotPos = 4;
            THEN("picks a median among element in the beginning, end and the middle.")
            {
                int pivotPos = getPivotPos(arr, start, end);
                REQUIRE(pivotPos == expectedPivotPos);
            }
        }
        WHEN("the array has 2 elements")
        {
            int arr[] = {10, 20};
            int start = 0, end = sizeof(arr) / sizeof(*arr) - 1;
            int expectedPivotPos = 0;
            THEN("picks a smaller elements")
            {
                int pivotPos = getPivotPos(arr, start, end);
                REQUIRE(pivotPos == expectedPivotPos);
            }
        }
        WHEN("the array has single element")
        {
            int arr[] = {10};
            int start = 0, end = sizeof(arr) / sizeof(*arr) - 1;
            int expectedPivotPos = 0;
            THEN("picks the element")
            {
                int pivotPos = getPivotPos(arr, start, end);
                REQUIRE(pivotPos == expectedPivotPos);
            }
        }
    }
}

SCENARIO("parttion separtes array into elements which are smaller than pivot and elements which are larger than pivot")
{
    GIVEN("an unsorted array")
    {
        int arr[]{30, 90, 20};
        int start = 0, end = sizeof(arr) / sizeof(*arr) - 1;

        WHEN("array has more than 1 element")
        {
            int pivotPos = getPivotPos(arr, start, end);
            int expLeft[]{20};
            int expRight[]{90};

            THEN("separates array into two")
            {
                pivotPos = partition(arr, start, pivotPos, end);
                for (int i = start; i < pivotPos; i++)
                {
                    REQUIRE(arr[i] == expLeft[i]);
                }

                for (int i = pivotPos + 1; i <= end; i++)
                {
                    REQUIRE(arr[i] == expRight[i - pivotPos - 1]);
                }
            }
        }
    }
}

SCENARIO("swap")
{
    GIVEN("two integer pointers")
    {
        int arr[]{10, 20};
        int exp[]{20, 10};
        WHEN("those are not identical")
        {
            THEN("swap them")
            {
                swap(arr, 0, 1);
                for (int i = 0; i < 2; i++)
                {
                    REQUIRE(arr[i] == exp[i]);
                }
            }
        }
    }
}

SCENARIO("quickSort") {
    GIVEN("an unsorted array") {
        int arr[]{100, 20, 80, 30, 60, 10, 70, 50};
        int size = sizeof(arr)/sizeof(*arr);
        int exp[]{10, 20, 30, 50, 60, 70, 80, 100};
        WHEN("array contains more than 1 element") {
            THEN("sort it in ascendding order") {
                quickSort(arr, size);
                for (int i = 0 ; i < size; i++) {
                    REQUIRE(arr[i] == exp[i]);
                }
            }
        }
    }
}