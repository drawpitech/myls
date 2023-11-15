/*
** EPITECH PROJECT, 2023
** bspushswap
** File description:
** test
*/

#include <criterion/criterion.h>

#include "my.h"
#include "../src/my_ls.h"

Test(sort_paths, basic)
{
    struct paths_s paths = {
        .paths = (char *[]){ "src", "build" },
        .n = 2,
    };
    char *expected[] = { "build", "src" };

    sort_paths(&paths);
    cr_assert_arr_eq(paths.paths, expected, paths.n);
}

Test(sort_paths, dotfiles)
{
    struct paths_s paths = {
        .paths = (char *[]){ "src", ".direnv", "build", ".asan", ".", ".." },
        .n = 6,
    };
    char *expected[] = { ".", "..", ".asan", "build", ".direnv", "src" };

    sort_paths(&paths);
    cr_assert_arr_eq(paths.paths, expected, paths.n);
}

Test(sort_paths, null)
{
    sort_paths(NULL);
}
