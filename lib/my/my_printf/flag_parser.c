/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** flag_parser
*/

#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>

#include "my.h"
#include "my_printf.h"

static
func_t *get_func(char c)
{
    for (int i = 0; i < FORMAT_N; i++)
        if (FORMAT_FUNCS[i].format == c)
            return FORMAT_FUNCS[i].func;
    return NULL;
}

static
int get_simple_flags(char const *format, int *i, printf_args_t *arg)
{
    if (format[*i] == '#') {
        arg->flags.alternative_form = true;
        *i += 1;
        return get_simple_flags(format, i, arg);
    }
    if (format[*i] == ' ') {
        arg->flags.space = true;
        *i += 1;
        return get_simple_flags(format, i, arg);
    }
    if (format[*i] == '+') {
        arg->flags.sign = true;
        *i += 1;
        return get_simple_flags(format, i, arg);
    }
    if (format[*i] == 'I' || format[*i] == '\'') {
        *i += 1;
        return get_simple_flags(format, i, arg);
    }
    return 0;
}

static
void get_flags(char const *format, int *i, printf_args_t *arg)
{
    arg->flags = (struct flags_s){ 0 };
    get_simple_flags(format, i, arg);
    if (IS_NUM(format[*i]) || format[*i] == '-') {
        arg->flags.padding = my_getnbr(format + *i);
        arg->flags.padded = true;
        *i += (
            (int)my_nbr_len_base(arg->flags.padding, BASE_DEC)
            + (format[*i] == '-' && arg->flags.padding == 0)
        );
    }
}

static
bool get_precision(char const *format, int *i, printf_args_t *arg)
{
    static const int default_precision = 6;
    int tmp;

    arg->precision = default_precision;
    if (format[*i] != '.')
        return true;
    tmp = my_getnbr(format + *i + 1);
    if (tmp <= 0 && format[*i + 1] == '-')
        return false;
    *i += 1;
    arg->precision = tmp;
    *i += (
        (int)my_nbr_len_base(tmp, BASE_DEC)
        + (format[*i] == '-' && tmp == 0)
    );
    return true;
}

int may_you_show_with_fmt(char const *format, int *i, printf_args_t *arg)
{
    func_t *func = NULL;
    int start = *i;

    *i += 1;
    get_flags(format, i, arg);
    if (!get_precision(format, i, arg))
        return (int)my_putstr("%.0");
    func = get_func(format[*i]);
    if (func != NULL)
        return func(arg);
    my_putchar('%');
    *i = start;
    return 1;
}
