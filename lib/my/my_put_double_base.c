/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_put_double_base
*/

#include "my.h"

static
int get_leftover(double n, int len, int precision)
{
    n -= (long)n;
    n *= len;
    if (!precision)
        return (n >= len / 2);
    return (get_leftover(n, len, precision - 1) + n >= len);
}

static
int get_after_point(double n, const char *base, int precision, int len)
{
    for (int i = 0; i < precision; i++) {
        n -= (long)n;
        n *= len;
        n += get_leftover(n, len, precision);
        my_putchar(base[(int)n % len]);
    }
    return precision;
}

int my_put_double_base(double n, const char *base, int precision)
{
    int len = my_strlen(base);
    int size = my_putnbr_base((int)n + get_leftover(n, len, precision), base);

    if (precision > 0)
        size += my_putnstr(".", 1) + get_after_point(n, base, precision, len);
    return size;
}
