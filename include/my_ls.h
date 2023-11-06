/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_ls
*/

#ifndef MY_LS
    #define MY_LS

    #include <dirent.h>
    #include <stdbool.h>
    #include <stdint.h>

typedef struct {
    const char *path;
    DIR *dirp;
    bool show_hidden;
    struct dirent *files;
    uint32_t n_files;
} ls_t;

int my_ls(int argc, char **argv);
int return_ls_error(char *str);
void clear_ls(ls_t *ls);
int get_files_in_dir(ls_t *ls);

#endif /* MY_LS */
