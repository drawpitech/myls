/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_ls
*/

#ifndef MY_LS
    #define MY_LS

    #include <dirent.h>
    #include <grp.h>
    #include <pwd.h>
    #include <stdbool.h>
    #include <stdint.h>
    #include <sys/stat.h>

struct file_s {
    char filename[NAME_MAX];
    bool valid;
    struct stat stat;
    struct passwd *passwd;
    struct group *group;
};

struct directory_s {
    char path[PATH_MAX];
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

struct paths_s {
    char **paths;
    uint32_t n;
};

typedef struct {
    struct paths_s paths;
    struct paths_s alone_files;
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
 * Fetch all files in the dir->path directory and store them in the
 * directory_t structure.
 */
int get_files_in_dir(struct directory_s *dir, struct params_s *params);

/**
 * Fill the file struct with the file->filename.
 * If dir_path is NULL, the filename is considered already resolved.
 */
int set_file(char *dir_path, struct file_s *file);

/**
 * Sort all files in the directory_t structure according to the ls->params.
 *  - By default, the files are sorted alphabetically.
 *  - If ls->params.time_sorted is true, the files are sorted by time.
 *  - If ls->params.reversed is true, the files are then reversed.
 */
void sort_files(ls_t *ls);

/**
 * Sort all paths in the ls->paths array according to the ls->params, excluding
 * the '.' from the start of the paths.
 */
void sort_paths(struct paths_s *paths);

/**
 * Set the ls structure parameters according to the arguments passed to the
 * program. Get the paths ("." if none are provided), and the parameters.
 */
void get_params(ls_t *ls, uint32_t argc, char **argv);

/**
 * Print the files of the ls->dir structure with the long format.
 */
void ls_output_long(struct directory_s *dir, bool total);

/**
 * Print the files of the ls->dir structure with the normal format.
 */
void ls_output_normal(struct directory_s *dir);

#endif /* MY_LS */
