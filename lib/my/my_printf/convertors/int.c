/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** int
*/

#include <stdarg.h>

#include "my.h"
#include "my_printf.h"

int printf_int(printf_args_t *arg)
{
    int size = 0;
    int nbr = va_arg(arg->ap, int);
    int len = my_nbr_len_base(nbr, BASE_DEC);

    size += left_pad(arg, len);
    if (arg->flags.sign)
        size += my_putnstr((nbr >= 0) ? "+" : "-", 1);
    else if (arg->flags.space && nbr >= 0)
        size += my_putnstr(" ", 1);
    size += my_put_nbr(nbr);
    size += right_pad(arg, len);
    return size;
}
