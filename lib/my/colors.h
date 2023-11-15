/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** colors
*/

#ifndef COLORS_H_
    #define COLORS_H_

    #include "my.h"

    #define C_BG(color) ((color) + 10)

    #define C_RESET "\x1b[0m"

enum {
    C_BLK = 30,
    C_RED = 31,
    C_GRN = 32,
    C_YEL = 33,
    C_BLU = 34,
    C_MAG = 35,
    C_CYN = 36,
    C_WHT = 37,
};

enum {
    C_NORM = 0,
    C_BOLD = 1,
    C_UNDR = 2,
};

static inline __attribute__((__used__))
void put_color(char color, char style, char bg)
{
    static char buf[] = "\x1b[0;30;00m";

    buf[2] = CHR(style);
    buf[4] = CHR(color / 10);
    buf[5] = CHR(color % 10);
    buf[7] = CHR(C_BG(bg) / 10);
    buf[8] = CHR(C_BG(bg) % 10);
    my_putstr(buf);
}

#endif /* COLORS_H_ */
