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
    char *path;
    DIR *dirp;
    uint32_t n_files;
    struct dirent *files;
    struct {
        bool all;
        bool recursive;
        bool time_sorted;
        bool long_format;
        bool directories;
        bool reverse;
    } params;
} ls_t;

typedef struct {
    char c;
    bool *b;
} arg_t;

int my_ls(int argc, char **argv);
int return_ls_error(char *str);
void clear_ls(ls_t *ls);
int get_files_in_dir(ls_t *ls);
void sort_files(ls_t *ls);
void get_params(ls_t *ls, int argc, char **argv);

#endif /* MY_LS */
