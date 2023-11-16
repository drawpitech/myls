/*
** EPITECH PROJECT, 2023
** bspushswap
** File description:
** test
*/

#include <stdio.h>
#include <string.h>

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "my.h"
#include "../src/my_ls.h"
#include "tests.h"

Test(my_ls_long, normal, .init=cr_redirect_stdout)
{
    int argc = 2;
    char *argv[] = {"./my_ls", "-la", NULL};

    cr_assert_eq(my_ls(argc, argv), RET_VALID);
    cr_assert_stdout_eq_str(get_ls("env ls -la"));
}

Test(my_ls_long, tests, .init=cr_redirect_stdout)
{
    int argc = 3;
    char *argv[] = {"./my_ls", "-la", "tests", NULL};

    cr_assert_eq(my_ls(argc, argv), RET_VALID);
    cr_assert_stdout_eq_str(get_ls("env ls -la tests"));
}

Test(my_ls_long, recursive, .init=cr_redirect_stdout)
{
    int argc = 2;
    char *argv[] = {"./my_ls", "-lR", NULL};

    cr_assert_eq(my_ls(argc, argv), RET_VALID);
    cr_assert_stdout_eq_str(get_ls("env ls -lR"));
}
