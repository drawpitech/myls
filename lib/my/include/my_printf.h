/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_printf
*/

#ifndef MY_PRINTF
    #define MY_PRINTF

    #include <stdarg.h>
    #include <stdbool.h>

    #define FORMAT_N 17

typedef struct {
    va_list ap;
    struct flags_s {
        bool alternative_form;
        int padding;
        bool padded;
        bool space;
        bool sign;
    } flags;
    int precision;
    int size;
} printf_args_t;

typedef int (func_t)(printf_args_t *);

typedef struct {
    char format;
    func_t *func;
} format_t;

int my_printf(const char *restrict format, ...);
int may_you_show_with_fmt(char const *format, int *i, printf_args_t *arg);
int left_pad(printf_args_t *arg, int written);
int right_pad(printf_args_t *arg, int written);
int printf_int(printf_args_t *);
int printf_char(printf_args_t *);
int printf_purcent(printf_args_t *);
int printf_str(printf_args_t *);
int printf_octal(printf_args_t *);
int printf_decimal(printf_args_t *);
int printf_hexadecimal(printf_args_t *);
int printf_hexadecimal2(printf_args_t *);
int printf_pointer(printf_args_t *);
int printf_float(printf_args_t *);
int printf_rounded_float(printf_args_t *arg);
int printf_len(printf_args_t *);
int printf_bool_min(printf_args_t *arg);
int printf_bool_maj(printf_args_t *arg);

static
const format_t FORMAT_FUNCS[FORMAT_N] = {
    {'d', &printf_int},
    {'i', &printf_int},
    {'%', &printf_purcent},
    {'c', &printf_char},
    {'s', &printf_str},
    {'o', &printf_octal},
    {'u', &printf_decimal},
    {'x', &printf_hexadecimal},
    {'X', &printf_hexadecimal2},
    {'p', &printf_pointer},
    {'f', &printf_float},
    {'F', &printf_float},
    {'n', &printf_len},
    {'b', &printf_bool_min},
    {'B', &printf_bool_maj},
    {'e', &printf_rounded_float},
    {'E', &printf_rounded_float},
};

#endif /* MY_PRINTF */
