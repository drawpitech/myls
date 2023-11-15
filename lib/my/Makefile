##
## EPITECH PROJECT, 2023
## Libmy
## File description:
## Makefile for libmy
##

# ↓ Basic variables
CC := gcc -std=gnu11
CFLAGS := -W -Wall -Wextra -Wunused -Wpedantic
CFLAGS += -Wundef -Wshadow -Wcast-align
CFLAGS += -Wstrict-prototypes
CFLAGS += -Waggregate-return -Wcast-qual
CFLAGS += -Wunreachable-code
CFLAGS += -U_FORTIFY_SOURCE
CFLAGS += -I./include

# ↓ Binaries
NAME := libmy.a

# Source files
VPATH := .
SRC := pow.c
SRC += my_compute_square_root.c
SRC += my_find_prime_sup.c
SRC += my_getnbr.c
SRC += my_isneg.c
SRC += my_is_prime.c
SRC += my_putchar.c
SRC += my_put_nbr.c
SRC += my_putstr.c
SRC += reverse.c
SRC += my_showmem.c
SRC += my_showstr.c
SRC += my_sort_int_array.c
SRC += my_strcapitalize.c
SRC += my_strcat.c
SRC += my_strcmp.c
SRC += my_strcpy.c
SRC += my_str_isalpha.c
SRC += my_str_islower.c
SRC += my_str_isnum.c
SRC += my_str_isprintable.c
SRC += my_str_isupper.c
SRC += my_strlen.c
SRC += my_strlowcase.c
SRC += my_strncat.c
SRC += my_strncmp.c
SRC += my_strncpy.c
SRC += my_strstr.c
SRC += my_strupcase.c
SRC += my_swap.c
SRC += my_putnbr_base.c
SRC += my_getnbr_base.c
SRC += my_nbr_to_base.c
SRC += my_strdup.c
SRC += concat_params.c
SRC += my_show_word_array.c
SRC += my_str_to_word_array.c
SRC += my_strndup.c
SRC += convert_base.c
SRC += get_color.c
SRC += my_put_unsigned_base.c
SRC += my_put_long_base.c
SRC += my_put_double.c
SRC += my_put_double_base.c
SRC += my_nbr_len.c
SRC += my_str_startswith.c
SRC += return_err.c
SRC += get_fullpath.c
SRC += mem.c
SRC += malloc.c
SRC += qsort.c
SRC += my_printf/my_printf.c
SRC += my_printf/flag_parser.c
SRC += my_printf/flag_utils.c
SRC += my_printf/convertors/char.c
SRC += my_printf/convertors/float.c
SRC += my_printf/convertors/int.c
SRC += my_printf/convertors/ptr.c
SRC += my_printf/convertors/str.c
SRC += my_printf/convertors/unsigned.c
SRC += my_printf/convertors/len.c
SRC += my_printf/convertors/bool.c

# ↓ Objects
BUILD_DIR := .build
OBJ := $(SRC:%.c=$(BUILD_DIR)/%.o)

# ↓ Dependencies for headers
DEPS_FLAGS := -MMD -MP
DEPS := $(OBJ:.o=.d)

DIE := exit 1
# ↓ Colors
ECHO := echo -e
C_RESET := \033[00m
C_BOLD := \e[1m
C_RED := \e[31m
C_GREEN := \e[32m
C_YELLOW := \e[33m
C_BLUE := \e[34m
C_PURPLE := \e[35m
C_CYAN := \e[36m

all: $(NAME)

.PHONY: all

# ↓ Compiling
$(BUILD_DIR)/%.o: %.c
	@ mkdir -p $(dir $@)
	@ $(ECHO) "[${C_BOLD}${C_RED}CC${C_RESET}] $^"
	@ $(CC) -o $@ -c $< $(CFLAGS) $(DEPS_FLAGS) || $(DIE)

$(NAME): $(HEADER) $(OBJ)
	@ $(ECHO) "[${C_BOLD}${C_YELLOW}AR${C_RESET}] ${C_RED}$@${C_RESET}"
	@ $(AR) rc $@ $(OBJ) || $(DIE)
	@ cp $@ ..
	@ mkdir -p ../../include
	@ cp include/*.h ../../include/

# ↓ Cleaning
clean:
	@ $(RM) -r $(BUILD_DIR)

fclean: clean
	@ $(RM) $(NAME) ../$(NAME)
	@ $(RM) ../../include/my.h ../../include/my_printf.h

.PHONY: clean fclean

re: fclean all

.PHONY: re

-include $(DEPS)
