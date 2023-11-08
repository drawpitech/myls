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
    #include <sys/stat.h>

struct file_s {
    struct dirent *dirent;
    struct stat stat;
};

struct directory_s {
    char path[256];
    DIR *dirp;
    uint32_t n_files;
    struct file_s *files;
};

struct params_s {
    bool all;
    bool recursive;
    bool time_sorted;
    bool long_format;
    bool directories;
    bool reverse;
};

typedef struct {
    char **paths;
    uint32_t nbr_paths;
    struct directory_s dir;
    struct params_s params;
} ls_t;

typedef struct {
    char c;
    bool *b;
} arg_t;

/**
 * Main function of the program. Mimic the ls command in the shell.
 */
int my_ls(int argc, char **argv);

/**
 * Return 84 and print an error message. If the error message is NULL,
 * perror() is called.
 */
int return_ls_error(char *str);

/**
 * Clear all the allocated memory in the ls_t structure.
 */
void clear_ls(ls_t *ls);

/**
 * Clear all the allocated memory in the directory_t structure.
 */
void clear_dir(struct directory_s *dir);

/**
 * Fetch all files in the ls->dir.path directory and store them in the
 * directory_t structure.
 */
int get_files_in_dir(ls_t *ls);

/**
 * Sort all files in the directory_t structure according to the ls->params.
 *  - By default, the files are sorted alphabetically.
 *  - If ls->params.time_sorted is true, the files are sorted by time.
 */
void sort_files(struct directory_s *dir);

/**
 * Sort all paths in the ls->paths array according to the ls->params, excluding
 * the '.' from the start of the paths.
 */
void sort_paths(char **paths, uint32_t n);

/**
 * Set the ls structure parameters according to the arguments passed to the
 * program. Get the paths ("." if none are provided), and the parameters.
 */
void get_params(ls_t *ls, uint32_t argc, char **argv);

/**
 * Print the files of the ls->dir structure with the long format.
 */
void ls_output_long(ls_t *ls);

/**
 * Print the files of the ls->dir structure with the normal format.
 */
void ls_output_normal(ls_t *ls);

#endif /* MY_LS */
