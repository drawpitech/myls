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

    #include "my_ls.h"

static inline
void assert_ls(ls_t *ls, ls_t *expected)
{
    cr_assert_eq(ls->nbr_paths, expected->nbr_paths);
    cr_assert_eq(ls->params.all, expected->params.all);
    cr_assert_eq(ls->params.directories, expected->params.directories);
    cr_assert_eq(ls->params.long_format, expected->params.long_format);
    cr_assert_eq(ls->params.recursive, expected->params.recursive);
    cr_assert_eq(ls->params.reverse, expected->params.reverse);
    cr_assert_eq(ls->params.time_sorted, expected->params.time_sorted);
    cr_assert_eq(ls->dir.n_files, expected->dir.n_files);
    cr_assert_str_eq(ls->dir.path, expected->dir.path);
    cr_assert_eq(ls->dir.dirp, expected->dir.dirp);
    cr_assert_arr_eq(ls->dir.files, expected->dir.files, ls->dir.n_files);
    cr_assert_eq(ls->nbr_paths, expected->nbr_paths);
    cr_assert_arr_eq(ls->paths, expected->paths, ls->nbr_paths);
}

static inline
void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

#endif /* TEST_LS */
