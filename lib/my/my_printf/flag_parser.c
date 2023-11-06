/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** flag_parser
*/

#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>

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
int get_simple_flags(char **ptr, printf_args_t *arg)
{
    if (**ptr == '#') {
        arg->flags.alternative_form = true;
        *ptr += 1;
        return get_simple_flags(ptr, arg);
    }
    if (**ptr == ' ') {
        arg->flags.space = true;
        *ptr += 1;
        return get_simple_flags(ptr, arg);
    }
    if (**ptr == '+') {
        arg->flags.sign = true;
        *ptr += 1;
        return get_simple_flags(ptr, arg);
    }
    if (**ptr == 'I' || **ptr == '\'') {
        *ptr += 1;
        return get_simple_flags(ptr, arg);
    }
    return 0;
}

static
void get_flags(char **ptr, printf_args_t *arg)
{
    arg->flags = (struct flags_s){ 0 };
    get_simple_flags(ptr, arg);
    if (IS_NUM(**ptr) || **ptr == '-') {
        arg->flags.padding = my_getnbr(*ptr);
        arg->flags.padded = true;
        *ptr += (
            my_nbr_len(arg->flags.padding, BASE_DEC)
            + (**ptr == '-' && arg->flags.padding == 0)
        );
    }
}

static
bool get_precision(char **ptr, printf_args_t *arg)
{
    int tmp;

    arg->precision = 6;
    if (**ptr != '.')
        return true;
    tmp = my_getnbr(*ptr + 1);
    if (tmp <= 0 && (*ptr)[1] == '-')
        return false;
    (*ptr)++;
    arg->precision = tmp;
    *ptr += (
        my_nbr_len(tmp, BASE_DEC)
        + (**ptr == '-' && tmp == 0)
    );
    return true;
}

int may_you_show_this_formatting(char **ptr, printf_args_t *arg)
{
    func_t *func = NULL;
    char *start = *ptr;

    (*ptr)++;
    get_flags(ptr, arg);
    if (!get_precision(ptr, arg))
        return my_putstr("%.0");
    func = get_func(**ptr);
    if (func != NULL)
        return func(arg);
    my_putchar('%');
    *ptr = start;
    return 1;
}
