/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my
*/

#ifndef LIBMY
    #define LIBMY

    #include <stdbool.h>
    #include <stdint.h>
    #include <stdlib.h>

    #define IS_LOWERCASE(c) ((c) >= 'a' && (c) <= 'z')
    #define IS_UPPERCASE(c) ((c) >= 'A' && (c) <= 'Z')
    #define IS_ALPHA(c) (IS_LOWERCASE(c) || IS_UPPERCASE(c))
    #define IS_NUM(c) ((c) >= '0' && (c) <= '9')
    #define IS_ALPHANUM(c) (IS_NUM(c) || IS_ALPHA(c))
    #define IS_PRINTABLE(c) ((c) >= ' ' && (c) <= '~')

    #define CH_LOW(c) (IS_UPPERCASE(c) ? ((c) + 32) : (c))
    #define CH_UPP(c) (IS_LOWERCASE(c) ? ((c) - 32) : (c))

    #define MIN(x, y) (((x) < (y)) ? (x) : (y))
    #define MAX(x, y) (((x) > (y)) ? (x) : (y))
    #define ABS(n) (((n) > 0) ? (n) : -(n))

    #define BASE_BIN "01"
    #define BASE_OCT "01234567"
    #define BASE_DEC "0123456789"
    #define BASE_HEX "0123456789abcdef"
    #define BASE_HEX_MIN "0123456789abcdef"
    #define BASE_HEX_MAJ "0123456789ABCDEF"

    #define BOOL(arg) (!!(arg))
    #define CHR(n) ((n) + '0')

enum {
    RET_VALID = 0,
    RET_ERROR = 84,
};

typedef int (compar_func_t)(void const *, void const *);

char **my_str_to_word_array(char const *str);
char *concat_params(int argc, char **argv);
char *convert_base(char const *, char const *, char const *);
char *my_nbr_to_base(int nbr, char const *base);
char *my_revstr(char *src);
char *my_strcapitalize(char *str);
char *my_strcat(char *dest, char const *src);
char *my_strcpy(char *dest, char const *src);
char *my_strdup(char const *src);
char *my_strlowcase(char *str);
char *my_strncat(char *dest, char const *src, int nb);
char *my_strncpy(char *dest, char const *src, int n);
char *my_strndup(char const *src, int n);
char const *my_strstr(char const *str, char const *to_find);
char *my_strupcase(char *str);
char *get_fullpath(char const *directory, char const *filename, char *result);
int count_island(char **world);
int get_color(unsigned char red, unsigned char green, unsigned char blue);
int my_compute_power_rec(int nb, int power);
uint32_t my_pow(uint32_t x, uint32_t y);
int my_compute_square_root(int nb);
int my_find_prime_sup(int nb);
int my_getnbr(char const *str);
int my_getnbr_base(char const *str, char const *base);
int my_is_prime(int nb);
int my_isneg(int nb);
int my_put_nbr(int nb);
int my_putnbr_base(int nbr, char const *base);
size_t my_putnstr(char const *str, size_t n);
size_t my_putstr(const char *str);
int my_show_word_array(char *const *tab);
int my_showmem(char const *str, int size);
int my_showstr(char const *str);
int my_str_isalpha(char const *str);
int my_str_islower(char const *str);
int my_str_isnum(char const *str);
int my_str_isprintable(char const *str);
int my_str_isupper(char const *str);
int my_strcmp(char const *s1, char const *s2);
size_t my_strlen(char const *str);
int my_strncmp(char const *s1, char const *s2, size_t n);
size_t my_nbr_len_base(size_t n, const char *base);
size_t my_i64_len_base(int64_t n, const char *base);
size_t my_u64_len_base(uint64_t n, const char *base);
size_t my_i64_len(int64_t n);
size_t my_u64_len(uint64_t n);
void char_swap(char *a, char *b);
void swap(void *left, void *right, size_t size);
void my_putchar(char c);
void my_sort_int_array(int *tab, int size);
void my_swap(int *a, int *b);
void str_swap(char **file1, char **file2);
int my_put_unsigned_base(unsigned int, const char *);
int my_put_long_base(unsigned long, const char *);
int my_put_double(double n, int precison);
int my_put_double_base(double n, const char *base, int precision);
size_t my_putnchar(char c, size_t n);
int return_err(char const *str);
bool my_str_startswith(const char *big, const char *little);
void *reverse_arr(uint32_t size, void *arr, size_t memsize);
void *my_memset(void *s, int c, size_t n);
void *my_memcpy(void *restrict dest, const void *restrict src, size_t n);
void *my_calloc(size_t nmemb, size_t size);
void *my_realloc(void *ptr, size_t old, size_t size);
void *my_reallocarray(void *ptr, size_t nmemb, size_t nmemb_old, size_t size);
void my_qsort(void *arr, size_t nmemb, size_t size, compar_func_t *compar);
int my_printf(const char *restrict format, ...);

#endif /* LIBMY */
