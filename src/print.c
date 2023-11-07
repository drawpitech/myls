/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** print
*/

#include <stdlib.h>

#include "my.h"
#include "my_ls.h"

static
void ouput_files(ls_t *ls)
{
    directory_t *dir = &ls->directories;

    for (uint32_t i = 0; i < dir->n_files; i++)
        my_printf("%s\n", dir->files[i].d_name);
}

int print_dir(ls_t *ls, bool print_path, uint32_t index)
{
    directory_t *dir;

    if (ls == NULL)
        return return_ls_error("invalid ptr");
    dir = &ls->directories;
    my_strcpy(dir->path, ls->paths[index]);
    if (get_files_in_dir(ls) == ERR_RETURN) {
        clear_dir(dir);
        return ERR_RETURN;
    }
    sort_files(dir);
    if (print_path)
        my_printf("%s%s:\n", (index != 0) ? "\n" : "", dir->path);
    ouput_files(ls);
    clear_dir(dir);
    return 0;
}
