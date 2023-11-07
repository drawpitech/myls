/*
** EPITECH PROJECT, 2023
** bspushswap
** File description:
** test
*/

#include <criterion/criterion.h>

#include "my.h"
#include "my_ls.h"
#include "tests.h"

Test(clear, basic)
{
    uint32_t argc = 2;
    char *argv[] = { "./my_ls", "-al", "src", "." };
    ls_t ls = { 0 };
    ls_t expected = { 0 };

    ls.paths = (char *[2]){ 0 };
    get_params(&ls, argc, argv);
    clear_ls(&ls);
    assert_ls(&ls, &expected);
}

Test(clear, null)
{
    clear_ls(NULL);
}

Test(clear, dirp)
{
    ls_t ls = { 0 };
    ls_t expected = { 0 };

    my_strcpy(ls.directories.path, ".");
    get_files_in_dir(&ls);
    clear_dir(&ls.directories);
    assert_ls(&ls, &expected);
}

Test(clear, null_dir)
{
    clear_dir(NULL);
}
