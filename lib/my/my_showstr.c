/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_showstr
*/

#include "my.h"

int my_showstr(char const *str)
{
    if (!str)
        return 0;
    for (int i = 0; str[i]; i++) {
        if (IS_PRINTABLE(str[i])) {
            my_putchar(str[i]);
            continue;
        }
        my_putchar('\\');
        if (str[i] < 16)
            my_putchar('0');
        my_putnbr_base(str[i], "0123456789abcdef");
    }
    return 0;
}
