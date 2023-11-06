/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_strncpy
*/

#include "my.h"

char *my_strncpy(char *dest, char const *src, int n)
{
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
    return dest;
}
