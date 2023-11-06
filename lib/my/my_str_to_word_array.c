/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_str_to_word_array
*/

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include "my.h"

static
const char *get_next_word(const char *str)
{
    for (int i = 0; str[i]; i++)
        if (IS_ALPHANUM(str[i]))
            return str + i;
    return NULL;
}

static
int get_word_len(const char *str)
{
    int len = 0;

    for (; str[len]; len++)
        if (!IS_ALPHANUM(str[len]))
            return len;
    return len;
}

static
int count_words(const char *str)
{
    int len = 0;
    const char *ptr = str;

    do {
        ptr = get_next_word(ptr);
        if (ptr == NULL)
            break;
        len++;
        ptr += get_word_len(ptr);
    } while (ptr != NULL);
    return len;
}

char **my_str_to_word_array(char const *str)
{
    char **arr;
    const char *ptr = str;
    int tmp;
    int i = 0;

    if (!str)
        return NULL;
    arr = malloc((count_words(str) + 1) * sizeof(char *));
    do {
        ptr = get_next_word(ptr);
        if (ptr == NULL)
            break;
        tmp = get_word_len(ptr);
        arr[i] = my_strndup(ptr, tmp);
        arr[i][tmp] = '\0';
        ptr += tmp;
        i++;
    } while (ptr != NULL);
    arr[i] = NULL;
    return arr;
}
