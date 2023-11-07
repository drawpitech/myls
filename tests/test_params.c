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

Test(params, basic)
{
    uint32_t argc = 2;
    char *argv[] = { "./my_ls", "." };
    ls_t ls = { 0 };
    ls_t expect = { 0 };

    ls.paths = (char *[1]){ 0 };
    expect.paths = (char *[]){ "." },
    expect.nbr_paths = 1;
    get_params(&ls, argc, argv);
    assert_ls(&ls, &expect);
}

Test(params, no_args)
{
    uint32_t argc = 1;
    char *argv[] = { "./my_ls" };
    ls_t ls = { 0 };
    ls_t expect = { 0 };

    ls.paths = (char *[1]){ 0 };
    expect.paths = (char *[]){ "." },
    expect.nbr_paths = 1;
    get_params(&ls, argc, argv);
    assert_ls(&ls, &expect);
}

Test(params, multiple_dirs)
{
    uint32_t argc = 3;
    char *argv[] = { "./my_ls", "src", "build" };
    ls_t ls = { 0 };
    ls_t expect = { 0 };

    ls.paths = (char *[2]){ 0 };
    expect.paths = (char *[]){ "build", "src" },
    expect.nbr_paths = 2;
    get_params(&ls, argc, argv);
    assert_ls(&ls, &expect);
}

Test(params, single_arg)
{
    uint32_t argc = 2;
    char *argv[] = { "./my_ls", "-a" };
    ls_t ls = { 0 };
    ls_t expect = { 0 };

    ls.paths = (char *[1]){ 0 };
    expect.paths = (char *[]){ "." },
    expect.nbr_paths = 1;
    expect.params.all = true;
    get_params(&ls, argc, argv);
    assert_ls(&ls, &expect);
}

Test(params, multi_arg)
{
    uint32_t argc = 3;
    char *argv[] = { "./my_ls", "-a", "-l" };
    ls_t ls = { 0 };
    ls_t expect = { 0 };

    ls.paths = (char *[1]){ 0 };
    expect.paths = (char *[]){ "." },
    expect.nbr_paths = 1;
    expect.params.all = true;
    expect.params.long_format = true;
    get_params(&ls, argc, argv);
    assert_ls(&ls, &expect);
}

Test(params, multi_arg_in_one)
{
    uint32_t argc = 3;
    char *argv[] = { "./my_ls", "-aRr", "-l" };
    ls_t ls = { 0 };
    ls_t expect = { 0 };

    ls.paths = (char *[1]){ 0 };
    expect.paths = (char *[]){ "." },
    expect.nbr_paths = 1;
    expect.params.all = true;
    expect.params.long_format = true;
    expect.params.recursive = true;
    expect.params.reverse = true;
    get_params(&ls, argc, argv);
    assert_ls(&ls, &expect);
}

Test(params, args_with_paths)
{
    uint32_t argc = 6;
    char *argv[] = { "./my_ls", "-dt", "src", "-l", "build", "-a" };
    ls_t ls = { 0 };
    ls_t expect = { 0 };

    expect.params.all = true;
    expect.params.long_format = true;
    expect.params.time_sorted = true;
    expect.params.directories = true;
    ls.paths = (char *[2]){ 0 };
    expect.paths = (char *[]){ "build", "src" },
    expect.nbr_paths = 2;
    get_params(&ls, argc, argv);
    assert_ls(&ls, &expect);
}

Test(params, invalid_flag, .exit_code=ERR_RETURN, .init=cr_redirect_stderr)
{
    uint32_t argc = 2;
    char *argv[] = { "./my_ls", "-g" };
    ls_t ls = { 0 };

    ls.paths = (char *[1]){ 0 };
    get_params(&ls, argc, argv);
}

Test(params, null_ls)
{
    uint32_t argc = 2;
    char *argv[] = { "./my_ls", "-g" };

    get_params(NULL, argc, argv);
}

Test(params, null_argv)
{
    uint32_t argc = 2;
    ls_t ls = { 0 };

    ls.paths = (char *[1]){ 0 };
    get_params(&ls, argc, NULL);
}

Test(params, null_paths)
{
    uint32_t argc = 2;
    char *argv[] = { "./my_ls", "-g" };
    ls_t ls = { 0 };

    get_params(&ls, argc, argv);
}

Test(params, null_in_arr)
{
    uint32_t argc = 2;
    char *argv[] = { "./my_ls", NULL };
    ls_t ls = { 0 };

    ls.paths = (char *[1]){ 0 };
    get_params(&ls, argc, argv);
}
