/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_nbr_len
*/

#include <stdint.h>

#include "my.h"

int my_i64_len_base(int64_t n, const char *base)
{
    int i = (n <= 0);
    int64_t len = my_strlen(base);

    for (; n; n /= len)
        i++;
    return i;
}

int my_i64_len(int64_t n)
{
    return my_i64_len_base(n, BASE_DEC);
}

int my_u64_len_base(uint64_t n, const char *base)
{
    int i = 0;
    uint64_t len = my_strlen(base);

    for (; n; n /= len)
        i++;
    return i;
}

int my_u64_len(uint64_t n)
{
    int i = (n == 0);

    for (; n; n /= 10) {
        i++;
    }
    return i;
}

int my_nbr_len_base(int n, const char *base)
{
    return my_i64_len_base((int)n, base);
}
