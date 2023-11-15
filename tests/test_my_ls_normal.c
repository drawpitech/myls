/*
** EPITECH PROJECT, 2023
** bspushswap
** File description:
** test
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "my.h"
#include "my_ls.h"
#include "tests.h"

Test(my_ls_normal, no_args, .init=cr_redirect_stdout)
{
    int argc = 1;
    char *argv[] = {"./my_ls", NULL};
    char expected[] =
        "assignement.pdf  compile_commands.json  ecsls.toml  flake.lock  "
        "flake.nix  include  lib  Makefile  README.md  src  tests  "
        "unit_tests\n";

    cr_assert_eq(my_ls(argc, argv), RET_VALID);
    cr_assert_stdout_eq_str(expected);
}

Test(my_ls_normal, directory, .init=cr_redirect_stdout)
{
    int argc = 2;
    char *argv[] = {"./my_ls", "src/../src/print_format", NULL };
    char expected[] = "long.c  normal.c  print.c\n";

    cr_assert_eq(my_ls(argc, argv), RET_VALID);
    cr_assert_stdout_eq_str(expected);
}

Test(my_ls_normal, multiple_dirs, .init=cr_redirect_stdout)
{
    int argc = 3;
    char *argv[] = {"./my_ls", ".", "src/../src/print_format", NULL };
    char expected[] =
        ".:\n"
        "assignement.pdf  compile_commands.json  ecsls.toml  flake.lock  "
        "flake.nix  include  lib  Makefile  README.md  src  tests  "
        "unit_tests\n"
        "\n"
        "src/../src/print_format:\n"
        "long.c  normal.c  print.c\n";

    cr_assert_eq(my_ls(argc, argv), RET_VALID);
    cr_assert_stdout_eq_str(expected);
}

Test(my_ls_normal, hidden_files, .init=cr_redirect_stdout)
{
    int argc = 3;
    char *argv[] = {"./my_ls", "src/../src/print_format", "-a", NULL };
    char expected[] = ".  ..  long.c  normal.c  print.c\n";

    cr_assert_eq(my_ls(argc, argv), RET_VALID);
    cr_assert_stdout_eq_str(expected);
}

Test(my_ls_normal, invalid_dir, .init=cr_redirect_stderr)
{
    int argc = 2;
    char *argv[] = {"./my_ls", "eh", NULL };
    char expected[] = "my_ls: no such file or directory\n";

    cr_assert_eq(my_ls(argc, argv), RET_ERROR);
    cr_assert_stderr_eq_str(expected);
}

Test(my_ls_normal, null_argv, .init=cr_redirect_stderr)
{
    uint32_t argc = 2;
    char expected[] = "my_ls: invalid args\n";

    cr_assert_eq(my_ls(argc, NULL), RET_ERROR);
    cr_assert_stderr_eq_str(expected);
}

Test(my_ls_normal, valid_and_invalid_dirs, .init=redirect_all_stdout)
{
    int argc = 3;
    char *argv[] = {"./my_ls", "eh", "src/../src/print_format", NULL };
    char expected_stderr[] = "my_ls: no such file or directory\n";
    char expected_stdout[] =
        "\n"
        "src/../src/print_format:\n"
        "long.c  normal.c  print.c\n";

    cr_assert_eq(my_ls(argc, argv), RET_ERROR);
    cr_assert_stderr_eq_str(expected_stderr);
    cr_assert_stdout_eq_str(expected_stdout);
}

Test(my_ls_normal, empty_dir, .init=cr_redirect_stdout)
{
    int argc = 3;
    char *argv[] = {"./my_ls", "tests/empty", "src/print_format", NULL };
    char expected_stdout[] =
        "src/print_format:\n"
        "long.c  normal.c  print.c\n"
        "\n"
        "tests/empty:\n";

    cr_assert_eq(my_ls(argc, argv), RET_VALID);
    cr_assert_stdout_eq_str(expected_stdout);
}
