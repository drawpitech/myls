/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_swap
*/

#include <stdint.h>
#include <stdlib.h>

#include "my.h"

void swap(void *left, void *right, size_t size)
{
    uint8_t *l_ptr = left;
    uint8_t *r_ptr = right;
    uint8_t tmp;

    for (uint32_t i = 0; i < size; i++) {
        tmp = l_ptr[i];
        l_ptr[i] = r_ptr[i];
        r_ptr[i] = tmp;
    }
}

void my_swap(int *a, int *b)
{
    int tmp = *a;

    *a = *b;
    *b = tmp;
}

void char_swap(char *a, char *b)
{
    char tmp = *a;

    *a = *b;
    *b = tmp;
}

void str_swap(char **file1, char **file2)
{
    char *tmp = *file1;

    *file1 = *file2;
    *file2 = tmp;
}
