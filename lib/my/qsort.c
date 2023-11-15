/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** qsort
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "my.h"

static
size_t get_pivot(uint8_t *ptr, size_t size, size_t nmemb, compar_func_t *cmp)
{
    uint8_t *pivot = ptr + (size - 1) * nmemb;
    size_t i = 0;

    for (uint8_t *j = ptr; j <= pivot - nmemb; j += nmemb) {
        if (!cmp(j, pivot)) {
            swap(ptr, j, nmemb);
            i += 1;
        }
    }
    swap(ptr + (i * nmemb), pivot, nmemb);
    return i;
}

void my_qsort(void *arr, size_t size, size_t nmemb, compar_func_t *compar)
{
    uint8_t *ptr = arr;
    size_t pi;

    if (ptr >= ptr + (size * nmemb))
        return;
    pi = get_pivot(ptr, size, nmemb, compar);
    my_qsort(arr, pi - 1, nmemb, compar);
    my_qsort(ptr + (pi + 1) * nmemb, size - (pi + 1), nmemb, compar);
}
