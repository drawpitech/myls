/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** char
*/

#include <stdarg.h>

#include "my.h"
#include "../my_printf.h"

int printf_char(printf_args_t *arg)
{
    int size = 0;
    char c = (char)va_arg(arg->ap, int);

    size += left_pad(arg, 1);
    size += my_putnchar(c, 1);
    size += right_pad(arg, 1);
    return 1;
}

int printf_purcent(printf_args_t *arg)
{
    int size = 0;

    size += left_pad(arg, 1);
    size += my_putnchar('%', 1);
    size += right_pad(arg, 1);
    return 1;
}
