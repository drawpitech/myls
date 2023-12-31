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
    #include <stdlib.h>
    #include <sys/stat.h>

typedef uint16_t options_t;

enum {
    OPT_ALL_FILES = 1 << 0,
    OPT_DIRECTORY = 1 << 1,
    OPT_LONG_FORM = 1 << 2,
    OPT_RECURSIVE = 1 << 3,
    OPT_REV_ORDER = 1 << 4,
    OPT_TIME_SORT = 1 << 5,
    OPT_ACCS_TIME = 1 << 6,
    OPT_CLASS_CHR = 1 << 7,
    OPT_DIR_ORDER = 1 << 8 | OPT_ALL_FILES,
    OPT_LONG_NOWN = 1 << 9 | OPT_LONG_FORM,
    OPT_WTH_COLOR = 1 << 10,
};

static const struct {
    char c;
    char *word;
    options_t bit_mask;
} OPTIONS[sizeof(options_t) * 8] = {
    { 'a', "all", OPT_ALL_FILES },
    { 'd', "directory", OPT_DIRECTORY },
    { 'l', NULL, OPT_LONG_FORM },
    { 'R', "recursive", OPT_RECURSIVE },
    { 'r', "reverse", OPT_REV_ORDER },
    { 't', NULL, OPT_TIME_SORT },
    { 'u', NULL, OPT_ACCS_TIME },
    { 'F', "classify", OPT_CLASS_CHR },
    { 'f', NULL, OPT_DIR_ORDER },
    { 'g', NULL, OPT_LONG_NOWN },
    { '\0', "color", OPT_WTH_COLOR },
    { '\0', NULL, 0 },
};

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
    uint32_t allocated;
    struct file_s *files;
};

struct paths_s {
    char **paths;
    uint32_t n;
};

typedef struct {
    struct paths_s paths;
    struct paths_s alone_files;
    struct directory_s dir;
    options_t options;
} ls_t;

/**
 * Main function of the program. Mimic the ls command in the shell.
 */
int my_ls(int argc, char *const *argv);

/**
 * Return 84 and print an error message. If the error message is NULL,
 * perror() is called.
 */
int return_ls_error(char const *str);

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
int get_files_in_dir(struct directory_s *dir, options_t options);

/**
 * Fill the file struct with the file->filename.
 * If dir_path is NULL, the filename is considered already resolved.
 */
int set_file(char const *dir_path, char const *file_path, struct file_s *file);

/**
 * Sort all files in the directory_t structure according to the ls->params.
 *  - By default, the files are sorted alphabetically.
 *  - If ls->params.time_sorted is true, the files are sorted by time.
 *  - If ls->params.reversed is true, the files are then reversed.
 */
void sort_files(struct directory_s *dir, options_t options);

/**
 * Sort all paths in the ls->paths array according to the ls->params, excluding
 * the '.' from the start of the paths.
 */
void sort_paths(struct paths_s *paths);

/**
 * Set the ls structure parameters according to the arguments passed to the
 * program. Get the paths ("." if none are provided), and the parameters.
 */
void get_params(ls_t *ls, uint32_t argc, char *const *argv);

/**
 * Print the files of the ls->dir structure with the long format.
 */
void ls_output_long(
    struct directory_s const *dir,
    bool total, options_t options);

/**
 * Print the files of the ls->dir structure with the normal format.
 */
void ls_output_normal(struct directory_s const *dir, options_t options);

/**
 * Print a directory to the stdout following the ls->params formats.
 */
int print_dir(
    ls_t *ls,
    bool show_path,
    bool line_jmp,
    struct directory_s *dir
);

/**
 * Prints the 'alone files' following the ls->params format.
 * Alone files are:
 *  - Paths that are passed to the program but are not directories.
 *  - All the dirs when the -d is used.
 */
int print_alone_files(ls_t *ls);

#endif /* MY_LS */
