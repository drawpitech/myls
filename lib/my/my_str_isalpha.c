/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_str_isalpha
*/

#include "my.h"

int my_str_isalpha(char const *str)
{
    for (int i = 0; str[i]; i++)
        if (!IS_ALPHA(str[i]))
            return 0;
    return 1;
}
