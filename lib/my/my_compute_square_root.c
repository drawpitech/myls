/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_compute_square_root
*/

#include "my.h"

int my_compute_square_root(int nb)
{
    int tmp;

    for (int i = 1; i <= nb; i++) {
        tmp = my_compute_power_rec(i, 2);
        if (tmp == 0)
            return 0;
        if (tmp == nb)
            return i;
        if (tmp > nb)
            return 0;
    }
    return 0;
}
