/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_find_prime_sup
*/

#include "my.h"

int my_find_prime_sup(int nb)
{
    if (nb < 0)
        return my_find_prime_sup(0);
    while (nb >= 0) {
        if (my_is_prime(nb))
            return nb - 1;
        nb += 1;
    }
    return 0;
}
