/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_strcapitalize
*/

#include "my.h"

char *my_strcapitalize(char *str)
{
    int on_word = 0;

    for (int i = 0; str[i]; i++) {
        if (!IS_ALPHA(str[i]) && !IS_NUM(str[i])) {
            on_word = 0;
            continue;
        }
        if (IS_LOWERCASE(str[i]) && !on_word)
            str[i] -= 32;
        if (IS_UPPERCASE(str[i]) && on_word)
            str[i] += 32;
        on_word = 1;
    }
    return str;
}
