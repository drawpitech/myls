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
    int i = 0;

    if (!dest || !src)
        return NULL;
    len = my_strlen(dest);
    for (; src[i]; i++)
        dest[len + i] = src[i];
    dest[len + i] = '\0';
    return dest;
}
