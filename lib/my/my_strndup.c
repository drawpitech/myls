/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_strndup
*/

#include <stdlib.h>

#include "my.h"

char *my_strndup(char const *src, int n)
{
    char *dest;

    if (!src)
        return NULL;
    dest = malloc((n + 1) * sizeof(char));
    if (!dest)
        return NULL;
    my_strncpy(dest, src, n);
    return dest;
}
