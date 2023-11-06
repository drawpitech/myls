/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** len
*/

#include <stdarg.h>

#include "my.h"
#include "my_printf.h"

int printf_len(printf_args_t *arg)
{
    int *size = va_arg(arg->ap, int *);

    *size = arg->size;
    return 0;
}
