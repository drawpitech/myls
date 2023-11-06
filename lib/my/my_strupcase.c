/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_strupcase
*/

#include "my.h"

char *my_strupcase(char *str)
{
    for (int i = 0; str[i]; i++)
        if (IS_LOWERCASE(str[i]))
            str[i] -= 32;
    return str;
}
