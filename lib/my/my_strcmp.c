/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_strcmp
*/

#include "my.h"

int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;

    while (s1[i] && s2[i]) {
        if (s1[i] != s2[i])
            return s1[i] - s2[i];
        i++;
    }
    if (s1[i] != s2[i])
        return s1[i] - s2[i];
    return 0;
}
