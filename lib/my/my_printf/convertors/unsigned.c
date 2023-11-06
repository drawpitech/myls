/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** unsigned
*/

#include <stdarg.h>

#include "my.h"
#include "my_printf.h"

int printf_octal(printf_args_t *arg)
{
    int size = 0;
    unsigned int nbr = va_arg(arg->ap, unsigned int);
    int len = my_nbr_len(nbr, BASE_OCT);
    bool alter = (nbr == 0 && arg->flags.alternative_form);

    size += left_pad(arg, len + 2 * alter);
    if (alter)
        size += my_putstr("0x");
    size += my_put_unsigned_base(nbr, BASE_OCT);
    size += right_pad(arg, len + 2 * alter);
    return size;
}

int printf_decimal(printf_args_t *arg)
{
    int size = 0;
    unsigned int nbr = va_arg(arg->ap, unsigned int);
    int len = my_nbr_len(nbr, BASE_DEC);

    size += left_pad(arg, len);
    size += my_put_unsigned_base(nbr, BASE_DEC);
    size += right_pad(arg, len);
    return size;
}

int printf_hexadecimal(printf_args_t *arg)
{
    int size = 0;
    unsigned int nbr = va_arg(arg->ap, unsigned int);
    int len = my_nbr_len(nbr, BASE_HEX_MIN);
    bool alter = (nbr != 0 && arg->flags.alternative_form);

    size += left_pad(arg, len + 2 * alter);
    if (alter)
        size += my_putstr("0x");
    size += my_put_unsigned_base(nbr, BASE_HEX_MIN);
    size += right_pad(arg, len + 2 * alter);
    return size;
}

int printf_hexadecimal2(printf_args_t *arg)
{
    int size = 0;
    unsigned int nbr = va_arg(arg->ap, unsigned int);
    int len = my_nbr_len(nbr, BASE_HEX_MAJ);
    bool alter = (nbr != 0 && arg->flags.alternative_form);

    size += left_pad(arg, len + 2 * alter);
    if (alter)
        size += my_putstr("0X");
    size += my_put_unsigned_base(nbr, BASE_HEX_MAJ);
    size += right_pad(arg, len + 2 * alter);
    return size;
}
