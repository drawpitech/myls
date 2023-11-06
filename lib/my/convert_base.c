/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** convert_base
*/

#include <stdlib.h>
#include <stddef.h>

#include "my.h"

char *convert_base(char const *nbr, char const *base_from, char const *base_to)
{
    return my_nbr_to_base(my_getnbr_base(nbr, base_from), base_to);
}
