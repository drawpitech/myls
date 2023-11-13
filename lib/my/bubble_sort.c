/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** bubble_sort
*/

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "my.h"

void bubble_sort(
    uint32_t n, void *arr, size_t size,
    bool (*compar)(void *, void *)
)
{
    uint8_t *ptr = arr;
    uint32_t x;

    if (n == 0)
        return;
    n -= 1;
    for (uint32_t i = 0; i < (n * n); i++) {
        x = (i % n) * size;
        if (compar(ptr + x, ptr + x + size))
            swap(ptr + x, ptr + x + size, size);
    }
}
