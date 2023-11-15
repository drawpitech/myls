/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** float
*/

#include <stdarg.h>

#include "my.h"
#include "../my_printf.h"

int printf_float(printf_args_t *arg)
{
    int size = 0;
    double nbr = va_arg(arg->ap, double);
    int len = (
        my_nbr_len_base((int)nbr, BASE_DEC)
        + (arg->precision != 0) + arg->precision
    );

    size += left_pad(arg, len);
    if (arg->flags.sign)
        size += my_putnstr((nbr >= 0) ? "+" : "-", 1);
    else if (arg->flags.space && nbr >= 0)
        size += my_putnstr(" ", 1);
    size += my_put_double(nbr, arg->precision);
    size += right_pad(arg, len);
    return size;
}

int printf_rounded_float(printf_args_t *arg)
{
    int size = 0;
    double nbr = va_arg(arg->ap, double);
    int len = (
        my_nbr_len_base((int)nbr, BASE_DEC)
        + (arg->precision != 0) + arg->precision
        + 4
    );

    size += left_pad(arg, len);
    if (arg->flags.sign)
        size += my_putnstr((nbr >= 0) ? "+" : "-", 1);
    else if (arg->flags.space && nbr >= 0)
        size += my_putnstr(" ", 1);
    size += my_put_double(nbr, arg->precision) + my_putstr("e+00");
    size += right_pad(arg, len);
    return size;
}
