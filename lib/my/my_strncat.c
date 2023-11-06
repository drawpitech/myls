/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_strncat
*/

#include <stddef.h>

#include "my.h"

char *my_strncat(char *dest, char const *src, int n)
{
    int len;
    int i;

    if (!dest || !src)
        return NULL;
    len = my_strlen(dest);
    for (i = 0; src[i] && i < n; i++)
        dest[len + i] = src[i];
    dest[len + i] = '\0';
    return dest;
}
