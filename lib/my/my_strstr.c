/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_strstr
*/

#include <stddef.h>

#include "my.h"

char const *my_strstr(char const *str, char const *to_find)
{
    size_t len;

    if (str == NULL || to_find == NULL)
        return NULL;
    len = my_strlen(to_find);
    if (len == 0)
        return str;
    for (int i = 0; str[i]; i++)
        if (my_strncmp(str + i, to_find, len) == 0)
            return str + i;
    return NULL;
}
