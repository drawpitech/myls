/*
** EPITECH PROJECT, 2023
** bspushswap
** File description:
** test
*/

#include <criterion/criterion.h>

#include "my.h"
#include "my_ls.h"

Test(sort_paths, basic)
{
    char *paths[] = { "src", "build" };
    char *expected[] = { "build", "src" };

    sort_paths(paths, 2);
    cr_assert_arr_eq(paths, expected, 2);
}

Test(sort_paths, dotfiles)
{
    char *paths[] = { "src", ".direnv", "build", ".asan", ".", ".." };
    char *expected[] = { ".", "..", ".asan", "build", ".direnv", "src" };

    sort_paths(paths, 6);
    cr_assert_arr_eq(paths, expected, 6);
}

Test(sort_paths, null_filename)
{
    char *paths[] = { "src", NULL, ".." };

    sort_paths(paths, 3);
}

Test(sort_paths, null)
{
    sort_paths(NULL, 0);
}
