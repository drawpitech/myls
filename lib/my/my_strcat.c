/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_strcat
*/

#include <stddef.h>

#include "my.h"

char *my_strcat(char *dest, char const *src)
{
    int len;

    if (!dest || !src)
        return NULL;
    len = my_strlen(dest);
    for (int i = 0; src[i]; i++)
        dest[len + i] = src[i];
    return dest;
}
