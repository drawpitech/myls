##
## EPITECH PROJECT, 2023
## my_ls
## File description:
## Makefile for my_ls
##

# ↓ Basic variables
CC := gcc -std=gnu11
CFLAGS := -W -Wall -Wextra -Wunused -Wpedantic
CFLAGS += -Wundef -Wshadow -Wcast-align
CFLAGS += -Wstrict-prototypes -Wmissing-prototypes
CFLAGS += -Waggregate-return -Wcast-qual
CFLAGS += -Wunreachable-code
CFLAGS += -U_FORTIFY_SOURCE
CFLAGS += -iquote ./include

# ↓ Tests flags
ifeq ($(NO_COV), 1)
COVERAGE_FLAGS :=
else
COVERAGE_FLAGS := -g3 --coverage
endif
TEST_FLAGS := $(COVERAGE_FLAGS) -lcriterion

# ↓ Asan
ASAN_FLAGS := -fsanitize=address,leak,undefined -g3

# ↓ Binaries
NAME := my_ls
TEST_NAME := unit_tests
ASAN_NAME := asan

# Libmy
LIBMY := lib/libmy.a
CFLAGS += -L./$(dir $(LIBMY)) -lmy

# Source files
VPATH := src
SRC := my_ls.c
SRC += get_files.c
SRC += sort_files.c
SRC += params.c
SRC += clear.c
SRC += print_format/long.c
SRC += print_format/normal.c

# Tests files
VPATH += tests
TEST_SRC := $(SRC)

SRC += main.c

# ↓ Objects
BUILD_DIR := .build
OBJ := $(SRC:%.c=$(BUILD_DIR)/source/%.o)
TEST_OBJ := $(TEST_SRC:%.c=$(BUILD_DIR)/tests/%.o)
ASAN_OBJ := $(SRC:%.c=$(BUILD_DIR)/asan/%.o)

# ↓ Dependencies for headers
DEPS_FLAGS := -MMD -MP
DEPS := $(OBJ:.o=.d)
TEST_DEPS := $(TEST_OBJ:.o=.d)
ASAN_DEPS := $(ASAN_OBJ:.o=.d)

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

# ↓ Compiling libmy
$(LIBMY):
	@ $(MAKE) -s -C $(dir $(LIBMY))/my

libmy: $(LIBMY)

.PHONY: libmy

# ↓ Compiling
$(BUILD_DIR)/source/%.o: %.c
	@ mkdir -p $(dir $@)
	@ $(ECHO) "[${C_BOLD}${C_RED}CC${C_RESET}] $^"
	@ $(CC) -o $@ -c $< $(CFLAGS) $(DEPS_FLAGS) || $(DIE)

$(NAME): $(LIBMY) $(OBJ)
	@ $(ECHO) "[${C_BOLD}${C_YELLOW}CC${C_RESET}] ${C_GREEN}$@${C_RESET}"
	@ $(CC) -o $@ $(OBJ) $(CFLAGS) || $(DIE)

.PHONY: $(NAME)

# ↓ Unit tests
$(BUILD_DIR)/tests/%.o: %.c
	@ mkdir -p $(dir $@)
	@ $(ECHO) "[${C_BOLD}${C_RED}CC${C_RESET}] $^"
	@ $(CC) -o $@ -c $< $(CFLAGS) $(DEPS_FLAGS) || $(DIE)

$(TEST_NAME): CFLAGS += $(TEST_FLAGS)
$(TEST_NAME): $(LIBMY) $(TEST_OBJ)
	@ $(ECHO) "[${C_BOLD}${C_YELLOW}CC${C_RESET}] ${C_GREEN}$@${C_RESET}"
	@ $(CC) -o $@ $(TEST_OBJ) $(CFLAGS) || $(DIE)

tests_run: fclean $(TEST_NAME)
	@ ./$(TEST_NAME)

.PHONY: $(TEST_NAME) tests_run

# ↓ Asan
$(BUILD_DIR)/asan/%.o: %.c
	@ mkdir -p $(dir $@)
	@ $(ECHO) "[${C_BOLD}${C_RED}CC${C_RESET}] $^"
	@ $(CC) -o $@ -c $< $(CFLAGS) $(DEPS_FLAGS) || $(DIE)

$(ASAN_NAME): CFLAGS += $(ASAN_FLAGS)
$(ASAN_NAME): $(LIBMY) $(ASAN_OBJ)
	@ $(ECHO) "[${C_BOLD}${C_YELLOW}CC${C_RESET}] ${C_GREEN}$@${C_RESET}"
	@ $(CC) -o $@ $(ASAN_OBJ) $(CFLAGS) || $(DIE)

tests_asan: fclean $(ASAN_NAME)
	@ ./$(ASAN_NAME)

.PHONY: tests_asan

# ↓ Cleaning
clean:
	@ $(RM) $(OBJ) $(TEST_OBJ)

fclean: clean
	@ $(RM) $(NAME) $(TEST_NAME) $(ASAN_NAME)
	@ $(RM) -r $(BUILD_DIR)
	@ $(MAKE) -s -C $(dir $(LIBMY))/my fclean

.PHONY: clean fclean

re: fclean all

.PHONY: re

-include $(DEPS)
-include $(TEST_DEPS)
-include $(ASAN_DEPS)
