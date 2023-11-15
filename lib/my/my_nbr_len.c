/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_nbr_len
*/

#include <stdint.h>

#include "my.h"

size_t my_i64_len_base(int64_t n, const char *base)
{
    size_t i = (n <= 0);
    int64_t len = my_strlen(base);

    for (; n; n /= len)
        i++;
    return i;
}

size_t my_i64_len(int64_t n)
{
    return my_i64_len_base(n, BASE_DEC);
}

size_t my_u64_len_base(uint64_t n, const char *base)
{
    size_t i = 0;
    uint64_t len = my_strlen(base);

    for (; n; n /= len)
        i++;
    return i;
}

size_t my_u64_len(uint64_t n)
{
    size_t i = (n == 0);

    for (; n; n /= 10) {
        i++;
    }
    return i;
}

size_t my_nbr_len_base(size_t n, const char *base)
{
    return my_i64_len_base((int)n, base);
}
