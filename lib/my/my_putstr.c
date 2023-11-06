/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_putstr
*/

#include <stdlib.h>

#include "my.h"

int my_putstr(char const *str)
{
    unsigned int i = 0;

    if (str == NULL)
        return my_putstr("(null)");
    for (; str[i]; i++)
        my_putchar(str[i]);
    return i;
}

int my_putnstr(char const *str, unsigned int n)
{
    if (str == NULL)
        return my_putstr("(null)");
    for (unsigned int i = 0; i < n; i++)
        my_putchar(str[i]);
    return n;
}
