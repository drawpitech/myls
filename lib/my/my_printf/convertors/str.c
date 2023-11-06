/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** str
*/

#include <stdarg.h>
#include <stdlib.h>

#include "my.h"
#include "my_printf.h"

int printf_str(printf_args_t *arg)
{
    int size = 0;
    char *str = va_arg(arg->ap, char *);
    int len = (str == NULL) ? 6 : my_strlen(str);

    size += left_pad(arg, len);
    size += my_putstr(str);
    size += right_pad(arg, len);
    return size;
}
