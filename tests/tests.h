/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_ls
*/

#ifndef TEST_LS
    #define TEST_LS

    #include <criterion/criterion.h>
    #include <criterion/redirect.h>

    #include "../src/my_ls.h"

static inline
void assert_paths(struct paths_s *paths, struct paths_s *expected)
{
    cr_assert_eq(paths->n, expected->n);
    cr_assert_arr_eq(paths->paths, expected->paths, expected->n);
}

static inline
void assert_ls(ls_t *ls, ls_t *expected)
{
    cr_assert_eq(ls->options, expected->options);
    cr_assert_eq(ls->dir.n_files, expected->dir.n_files);
    cr_assert_str_eq(ls->dir.path, expected->dir.path);
    cr_assert_eq(ls->dir.dirp, expected->dir.dirp);
    cr_assert_arr_eq(ls->dir.files, expected->dir.files, ls->dir.n_files);
    assert_paths(&ls->paths, &expected->paths);
    assert_paths(&ls->alone_files, &expected->alone_files);
}

static inline
void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

static inline
char *get_ls(char const *command)
{
    static char buf[16384];
    char *ptr = buf;
    FILE *ls = popen(command, "r");

    while (fgets(ptr, 256, ls) != 0)
        ptr += strlen(ptr);
    pclose(ls);
    return buf;
}

#endif /* TEST_LS */
