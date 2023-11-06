/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_printf
*/

#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>

#include "my.h"
#include "my_printf.h"

int my_printf(const char *restrict format, ...)
{
    char *ptr = format;
    printf_args_t arg;

    arg.size = 0;
    if (format == NULL)
        return my_putstr("(null)");
    va_start(arg.ap, format);
    for (; *ptr; ptr++) {
        if (*ptr != '%') {
            arg.size += my_putnstr(ptr, 1);
            continue;
        }
        arg.size += may_you_show_this_formatting(&ptr, &arg);
    }
    va_end(arg.ap);
    return arg.size;
}
