/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_strlowcase
*/

#include "my.h"

char *my_strlowcase(char *str)
{
    for (int i = 0; str[i]; i++)
        if (IS_UPPERCASE(str[i]))
            str[i] += 32;
    return str;
}
