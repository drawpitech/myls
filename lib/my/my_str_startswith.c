/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_str_startswith
*/

#include <stdbool.h>
#include <unistd.h>

#include "my.h"

bool my_str_startswith(const char *big, const char *little)
{
    return (
        big != NULL && little != NULL
        && !my_strncmp(big, little, my_strlen(little))
    );
}
