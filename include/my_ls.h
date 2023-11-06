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

typedef struct {
    const char *path;
    DIR *dirp;
    bool show_hidden;
} ls_t;

int my_ls(int argc, char **argv);
int return_ls_error(void);

#endif /* MY_LS */
