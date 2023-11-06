/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_strdup
*/

#include <stdlib.h>

#include "my.h"

char *my_strdup(char const *src)
{
    char *dest;

    if (!src)
        return NULL;
    dest = malloc((my_strlen(src) + 1) * sizeof(char));
    if (!dest)
        return NULL;
    my_strcpy(dest, src);
    return dest;
}
