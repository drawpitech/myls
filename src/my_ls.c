/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_ls
*/

#include <stdlib.h>
#include <dirent.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "my.h"
#include "my_ls.h"

int return_ls_error(char *str)
{
    if (str == NULL) {
        perror("my_ls");
    } else {
        return_err("my_ls: ");
        return_err(str);
        return_err("\n");
    }
    return ERR_RETURN;
}

int my_ls(int argc, char **argv)
{
    uint32_t uargc = (uint32_t)argc;
    char *paths[uargc + 1];
    ls_t ls = {
        .directories = { .path = { 0 }, 0 },
        .paths = paths,
        .nbr_paths = 0,
        .params = { 0 },
    };
    bool success = true;

    if (argc < 1 || argv == NULL)
        return return_ls_error("invalid args\n");
    get_params(&ls, uargc, argv);
    if (ls.nbr_paths == 1)
        success = (print_dir(&ls, false, 0) == 0) && success;
    else
        for (uint32_t i = 0; i < ls.nbr_paths; i++)
            success = (print_dir(&ls, true, i) == 0) && success;
    clear_ls(&ls);
    return (success) ? 0 : ERR_RETURN;
}
