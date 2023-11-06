/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_sort_int_array
*/

#include "my.h"

void my_sort_int_array(int *array, int size)
{
    if (!array || size < 0)
        return;
    for (int i = 0; i < size * size; i++)
        if (array[i % size] > array[i / size])
            my_swap(array + (i % size), array + (i / size));
}
