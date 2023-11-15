/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** get_fullpath
*/

#include <stdlib.h>

#include "my.h"

char *get_fullpath(char const *directory, char const *filename, char *result)
{
    if (directory == NULL || filename == NULL || result == NULL)
        return NULL;
    result[0] = '\0';
    if (filename[0] != '/' && filename[0] != '~') {
        my_strcpy(result, directory);
        if (directory[my_strlen(directory) - 1] != '/')
            my_strcat(result, "/");
    }
    my_strcat(result, filename);
    return result;
}
