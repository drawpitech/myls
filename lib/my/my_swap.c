/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_swap
*/

#include "my.h"

void my_swap(int *a, int *b)
{
    int tmp = *a;

    *a = *b;
    *b = tmp;
}

void char_swap(char *a, char *b)
{
    char tmp = *a;

    *a = *b;
    *b = tmp;
}

void str_swap(char **file1, char **file2)
{
    char *tmp = *file1;

    *file1 = *file2;
    *file2 = tmp;
}
