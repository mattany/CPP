#include <iostream>
#include <algorithm>
#include <random>
#include <stdlib.h>
//
// Created by mattan on 9/1/19.
//

// Returns true if arr1[0..n-1] and arr2[0..m-1]
// contain same elements.
bool areEqual(int arr1[], int arr2[], int n, int m)
{
    // If lengths of array are not equal means
    // array are not equal
    if (n != m)
        return false;

    // Sort both arrays
    std::sort(arr1, arr1 + n);
    std::sort(arr2, arr2 + m);

    // Linearly compare elements
    for (int i = 0; i < n; i++)
        if (arr1[i] != arr2[i])
            return false;

    // If all elements were same.
    return true;
}

long rng(long n)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distribution(1,n - 1);
    return distribution(rng);
}

