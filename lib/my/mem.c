/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** mem
*/

#include <stdint.h>
#include <stdlib.h>

#include "my.h"

void *my_memset(void *s, int c, size_t n)
{
    uint8_t *p = s;

    for (size_t i = 0; i != n; ++i) {
        p[i] = c;
    }
    return s;
}

void *my_memcpy(void *restrict dest, const void *restrict src, size_t n)
{
    uint8_t *ptrd = dest;
    const uint8_t *ptrs = src;

    for (size_t i = 0; i < n; i++)
        ptrd[i] = ptrs[i];
    return dest;
}
