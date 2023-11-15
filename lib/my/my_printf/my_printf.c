/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_printf
*/

#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>

#include "my.h"
#include "my_printf.h"

int my_printf(const char *restrict format, ...)
{
    printf_args_t arg;

    arg.size = 0;
    if (format == NULL)
        return (int)my_putstr("(null)");
    va_start(arg.ap, format);
    for (int i = 0; format[i]; i++) {
        if (format[i] != '%') {
            arg.size += (int)my_putnstr(format + i, 1);
            continue;
        }
        arg.size += may_you_show_with_fmt(format, &i, &arg);
    }
    va_end(arg.ap);
    return arg.size;
}
