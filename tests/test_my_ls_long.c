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

Test(my_ls_long, tty, .init=cr_redirect_stdout)
{
    int argc = 3;
    char *argv[] = {"./my_ls", "-ld", "/dev/tty", NULL};

    cr_assert_eq(my_ls(argc, argv), RET_VALID);
    cr_assert_stdout_eq_str(get_ls("env ls -ld /dev/tty"));
}

Test(my_ls_long, char_device, .init=cr_redirect_stdout)
{
    int argc = 3;
    char *argv[] = {"./my_ls", "-ld", "/tmp", NULL};

    cr_assert_eq(my_ls(argc, argv), RET_VALID);
    cr_assert_stdout_eq_str(get_ls("env ls -ld /tmp"));
}

Test(my_ls_long, more, .init=cr_redirect_stdout)
{
    int argc = 3;
    char *argv[] = {"./my_ls", "-l", "tests/examples", NULL};

    cr_assert_eq(my_ls(argc, argv), RET_VALID);
    cr_assert_stdout_eq_str(get_ls("env ls -l tests/examples"));
}

Test(my_ls_long, color, .init=cr_redirect_stdout)
{
    int argc = 3;
    char *argv[] = {"./my_ls", "-la", "--color", NULL};

    cr_assert_eq(my_ls(argc, argv), RET_VALID);
    cr_assert_stdout_eq_str(get_ls("env ls -la --color"));
}
