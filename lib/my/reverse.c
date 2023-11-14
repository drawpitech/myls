/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_revstr
*/

#include "my.h"

void *reverse_arr(uint32_t size, void *arr, size_t memsize)
{
    uint8_t *ptr = arr;

    for (uint32_t i = 0; i < size / 2; i++)
        swap(ptr + i * memsize, ptr + (size - i - 1) * memsize, memsize);
    return arr;
}

char *my_revstr(char *src)
{
    return (char *)reverse_arr(my_strlen(src), src, sizeof(char));
}
