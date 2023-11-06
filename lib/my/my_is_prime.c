/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_is_prime
*/

#include "my.h"

int my_is_prime(int nb)
{
    if (nb <= 1)
        return 0;
    for (int i = 2; i < nb; i++)
        if (nb % i == 0)
            return 0;
    return 1;
}
