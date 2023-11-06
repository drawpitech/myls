/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** ptr
*/

#include <stdarg.h>

#include "my.h"
#include "my_printf.h"

int printf_pointer(printf_args_t *arg)
{
    int size = 0;
    unsigned long ptr = (unsigned long)va_arg(arg->ap, void *);
    int len = my_nbr_len(ptr, BASE_HEX) + 2;

    size += left_pad(arg, len);
    size += my_putstr("0x") + my_put_long_base(ptr, BASE_HEX);
    size += right_pad(arg, len);
    return size;
}
