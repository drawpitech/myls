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
uint8_t *get_pivot(
    uint8_t *ptr, size_t size,
    size_t nmemb, compar_func_t *compar
)
{
    uint8_t *pivot = ptr + (size * nmemb);

    for (uint8_t *j = ptr; j <= pivot - nmemb; j += nmemb) {
        if (!compar(j, pivot)) {
            swap(ptr, j, nmemb);
            ptr += nmemb;
        }
    }
    swap(ptr, pivot, nmemb);
    return ptr;
}

void my_qsort(void *arr, size_t size, size_t nmemb, compar_func_t *compar)
{
    uint8_t *ptr = arr;
    uint8_t *pi;

    if (ptr >= ptr + (size * nmemb))
        return;
    pi = get_pivot(ptr, size, nmemb, compar);
    my_qsort(arr, (pi - ptr) / nmemb - 1, nmemb, compar);
    my_qsort(pi + nmemb, size - ((pi - ptr) / nmemb + 1), nmemb, compar);
}
