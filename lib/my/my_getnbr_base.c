/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_getnbr_base
*/

#include <stdio.h>

#include "my.h"

static
int index_in(char c, char const *base)
{
    for (int i = 0; base[i]; i++)
        if (base[i] == c)
            return i;
    return -1;
}

static
int is_valid(char c, int has_started, int *is_neg, const char *base)
{
    if (index_in(c, base) != -1)
        return 1;
    if (c == '+')
        return !(has_started);
    if (c == '-') {
        if (has_started)
            return 0;
        *is_neg = !*is_neg;
        return 1;
    }
    if (has_started)
        return 0;
    *is_neg = 0;
    return 1;
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

int my_getnbr_base(char const *str, char const *base)
{
    int res = 0;
    int is_neg = 0;
    int has_started = 0;
    int len = my_strlen(base);

    if (!str || !base)
        return 0;
    for (int i = 0; str[i]; i++) {
        if (is_valid(str[i], has_started, &is_neg, base) == 0)
            return true_val(res, is_neg);
        if (index_in(str[i], base) == -1)
            continue;
        has_started = 1;
        res = res * len + -index_in(str[i], base);
        if (res > 0)
            return 0;
    }
    return true_val(res, is_neg);
}
