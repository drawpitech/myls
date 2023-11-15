/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** bool
*/

#include <stdarg.h>
#include <stdbool.h>

#include "my.h"
#include "../my_printf.h"

static
int printf_bool_helper(printf_args_t *arg, char *str_true, char *str_false)
{
    int size = 0;
    bool val = (bool)va_arg(arg->ap, int);
    char str[16] = { 0 };
    int len;

    my_strcpy(str, (val) ? str_true : str_false);
    len = my_strlen(str);
    size += left_pad(arg, len);
    size += my_putstr(str);
    size += right_pad(arg, len);
    return size;
}

int printf_bool_min(printf_args_t *arg)
{
    return printf_bool_helper(arg, "true", "false");
}

int printf_bool_maj(printf_args_t *arg)
{
    return printf_bool_helper(arg, "True", "False");
}
