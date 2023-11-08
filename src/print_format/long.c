/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** print
*/

#include <pwd.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>

#include "my.h"
#include "my_ls.h"

static
void get_max_size(ls_t *ls, int arr[4])
{
    struct file_s *file;

    for (uint32_t i = 0; i < ls->dir.n_files; i++) {
        file = ls->dir.files + i;
        arr[0] = MAX(arr[0], my_u64_len(file->stat.st_nlink));
        arr[1] = MAX(arr[1], my_strlen(file->passwd->pw_name));
        arr[2] = MAX(arr[2], my_strlen(file->group->gr_name));
        arr[3] = MAX(arr[3], my_u64_len(file->stat.st_size));
    }
}

static
void put_date(struct file_s *file)
{
    char *time = ctime(&file->stat.st_mtim.tv_sec);

    time[my_strlen(time) - 9] = '\0';
    my_printf("%s ", time + 4);
}

static
char get_file_type(mode_t mode)
{
    switch (mode & S_IFMT) {
        case S_IFBLK:
            return 'b';
        case S_IFCHR:
            return 'c';
        case S_IFDIR:
            return 'd';
        case S_IFIFO:
            return 'i';
        case S_IFLNK:
            return 'l';
        case S_IFREG:
            return '-';
        case S_IFSOCK:
            return 's';
    }
    return '?';
}

static
void put_perms(struct file_s *file)
{
    mode_t owner = file->stat.st_mode & S_IRWXU;
    mode_t group = file->stat.st_mode & S_IRWXG;
    mode_t other = file->stat.st_mode & S_IRWXO;

    my_putchar(get_file_type(file->stat.st_mode));
    my_putchar((owner & S_IRUSR) ? 'r' : '-');
    my_putchar((owner & S_IWUSR) ? 'w' : '-');
    my_putchar((owner & S_IXUSR) ? 'x' : '-');
    my_putchar((group & S_IRGRP) ? 'r' : '-');
    my_putchar((group & S_IWGRP) ? 'w' : '-');
    my_putchar((group & S_IXGRP) ? 'x' : '-');
    my_putchar((other & S_IROTH) ? 'r' : '-');
    my_putchar((other & S_IWOTH) ? 'w' : '-');
    my_putchar((other & S_IXOTH) ? 'x' : '-');
    my_putchar(' ');
}

static
void put_link(struct file_s *file)
{
    static char buf[PATH_MAX];
    ssize_t size;

    if ((file->stat.st_mode & S_IFMT) != S_IFLNK)
        return;
    size = readlink(file->fullpath, buf, PATH_MAX);
    buf[MIN(size, PATH_MAX - 1)] = '\0';
    my_printf(" -> %s", buf);
}

static
void show_long_formatting(ls_t *ls)
{
    struct file_s *file;
    int max_size[4] = {0};

    get_max_size(ls, max_size);
    for (uint32_t i = 0; i < ls->dir.n_files; i++) {
        file = ls->dir.files + i;
        put_perms(file);
        my_putnchar(' ', max_size[0] - my_u64_len(file->stat.st_nlink));
        my_printf("%u ", file->stat.st_nlink);
        my_putnchar(' ', max_size[1] - my_strlen(file->passwd->pw_name));
        my_printf("%s ", file->passwd->pw_name);
        my_putnchar(' ', max_size[2] - my_strlen(file->group->gr_name));
        my_printf("%s ", file->group->gr_name);
        my_putnchar(' ', max_size[3] - my_u64_len(file->stat.st_size));
        my_printf("%u ", file->stat.st_size);
        put_date(file);
        my_printf("%s", file->dirent->d_name);
        put_link(file);
        my_putchar('\n');
    }
}

void ls_output_long(ls_t *ls)
{
    if (ls == NULL || ls->dir.files == NULL || ls->dir.n_files == 0)
        return;
    show_long_formatting(ls);
}
