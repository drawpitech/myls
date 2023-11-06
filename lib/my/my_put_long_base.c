/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_put_long_base
*/

#include "my.h"

static
int print_digits(unsigned long n, char const *base, int len)
{
    int size;

    if (n == 0)
        return 0;
    size = print_digits(n / len, base, len);
    my_putchar(base[n % len]);
    return size + 1;
}

int my_put_long_base(unsigned long nbr, char const *base)
{
    int len = my_strlen(base);

    if (len == 0)
        return 0;
    if (nbr == 0) {
        my_putchar(base[0]);
        return 1;
    }
    return print_digits(nbr, base, len);
}
