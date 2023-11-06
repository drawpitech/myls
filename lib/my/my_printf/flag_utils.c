/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** flag_utils
*/

#include "my.h"
#include "my_printf.h"

int left_pad(printf_args_t *arg, int written)
{
    struct flags_s *flags = &(arg->flags);

    if (flags->padded && flags->padding > 0)
        return my_putnchar(' ', flags->padding - written);
    return 0;
}

int right_pad(printf_args_t *arg, int written)
{
    struct flags_s *flags = &(arg->flags);

    if (flags->padded && flags->padding < 0)
        return my_putnchar(' ', -flags->padding - written);
    return 0;
}
