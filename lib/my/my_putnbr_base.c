/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_putnbr_base
*/

#include "my.h"

static
int print_digits(int n, char const *base, int len)
{
    int size;

    if (n == 0)
        return 0;
    size = print_digits(n / len, base, len);
    my_putchar(base[-(n % len)]);
    return size + 1;
}

int my_putnbr_base(int nbr, char const *base)
{
    int len = my_strlen(base);
    int is_neg = (nbr < 0);

    if (len == 0)
        return 0;
    if (nbr == 0) {
        my_putchar(base[0]);
        return 1;
    }
    if (is_neg)
        my_putchar('-');
    else
        nbr = -nbr;
    return is_neg + print_digits(nbr, base, len);
}
