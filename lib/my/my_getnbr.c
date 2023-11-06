/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_getnbr
*/

#include "my.h"

static
int is_valid(char c, int has_started, int *is_neg)
{
    if (IS_NUM(c))
        return 1;
    if (c == '+')
        return !(has_started);
    if (c == '-') {
        if (has_started)
            return 0;
        *is_neg = !*is_neg;
        return 1;
    }
    return 0;
}

static
int true_val(int res, int is_neg)
{
    if (is_neg)
        return res;
    res = -res;
    if (res < 0)
        return 0;
    return res;
}

int my_getnbr(char const *str)
{
    int res = 0;
    int is_neg = 0;
    int has_started = 0;

    if (!str)
        return 0;
    for (int i = 0; str[i]; i++) {
        if (!is_valid(str[i], has_started, &is_neg))
            return true_val(res, is_neg);
        if (!IS_NUM(str[i]))
            continue;
        has_started = 1;
        res = res * 10 + -(str[i] - '0');
        if (res > 0)
            return 0;
    }
    return true_val(res, is_neg);
}
