/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** concat_params
*/

#include <stdlib.h>
#include <stddef.h>

#include "my.h"

static
int len_str_arr(char **arr, int size)
{
    int len = 0;

    while (size--)
        len += my_strlen(arr[size]);
    return len;
}

char *concat_params(int argc, char **argv)
{
    char *dest;

    if (!argv || argc < 1)
        return NULL;
    dest = malloc((len_str_arr(argv, argc) + argc) * sizeof(char));
    dest[0] = '\0';
    for (int i = 0; i < argc - 1; i++) {
        my_strcat(dest, argv[i]);
        my_strcat(dest, "\n");
    }
    my_strcat(dest, argv[argc - 1]);
    return dest;
}
