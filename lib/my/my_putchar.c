/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_putchar
*/

#include <unistd.h>

#include "my.h"

void my_putchar(char c)
{
    write(STDOUT_FILENO, &c, 1);
}

size_t my_putnchar(char c, size_t n)
{
    char buf[n + 1];

    for (size_t i = 0; i < n; i++)
        buf[i] = c;
    my_putstr(buf);
    return n;
}
