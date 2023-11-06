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
    write(1, &c, 1);
}

int my_putnchar(char c, int n)
{
    for (int i = 0; i < n; i++)
        my_putchar(c);
    return n;
}
