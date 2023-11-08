/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_nbr_len
*/

#include "my.h"

int my_nbr_len(int n)
{
    return my_nbr_len_base(n, BASE_DEC);
}

int my_nbr_len_base(int n, const char *base)
{
    int i = (n <= 0);
    int len = my_strlen(base);

    for (; n; n /= len)
        i++;
    return i;
}
