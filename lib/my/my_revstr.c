/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_revstr
*/

#include "my.h"

char *my_revstr(char *src)
{
    int len = my_strlen(src);

    for (int i = 0; i < len / 2; i++)
        char_swap(src + i, src + len - i - 1);
    return src;
}
