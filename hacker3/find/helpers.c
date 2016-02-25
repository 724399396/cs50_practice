/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <string.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int array[], int n)
{
    if (n == 0) {
        return false;
    }
    if (n == 1) {
        return value == array[0];
    }
    int middle = n/2;
    int middle_ele = array[middle];
    if (value == middle_ele) {
        return true;
    } else if (value < middle_ele) {
        int left_size = middle;
        int left[left_size];
        memcpy(left, array, left_size * sizeof(int));
        return search(value, left, middle);
    } else {
        int right_size = n - middle;
        int right[right_size];
        memcpy(right, &array[middle], right_size * sizeof(int));
        return search(value, right, right_size);
    }
}

void merge(int left[], int left_size, int right[], int right_size, int values[])
{
    int i = 0, j = 0, k = 0;
    while(i < left_size && j < right_size) {
        int x = left[i], y = right[j];
        if (x < y) {
            values[k++] = x;
            i++;
        } else {
            values[k++] = y;
            j++;
        }
    }
    for(; i < left_size; i++) {
        values[k++] = left[i];
    }
    for(; j < right_size; j++) {
        values[k++] = right[j];
    }
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    if (n <= 1) {
        return;
    }
    int middle = n / 2;
    int left_size = middle, right_size = n - middle;
    int left[left_size], right[right_size];
    memcpy(left, values, left_size * sizeof(int));
    memcpy(right, &values[left_size], right_size * sizeof(int));
    sort(left,left_size);
    sort(right,right_size);
    merge(left, left_size, right, right_size, values);
}