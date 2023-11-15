/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** return_err
*/

#include <unistd.h>

#include "my.h"

int return_err(char const *str)
{
    write(STDERR_FILENO, str, my_strlen(str));
    return ERR_RETURN;
}
