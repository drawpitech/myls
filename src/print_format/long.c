/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** print
*/

#include <grp.h>
#include <pwd.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "my.h"
#include "my_ls.h"

static
void get_max_size(struct directory_s *dir, int arr[4])
{
    struct file_s *file;

    for (uint32_t i = 0; i < dir->n_files; i++) {
        file = dir->files + i;
        if (!file->valid)
            continue;
        arr[0] = MAX(arr[0], my_u64_len(file->stat.st_nlink));
        arr[1] = MAX(arr[1], my_strlen(file->passwd->pw_name));
        arr[2] = MAX(arr[2], my_strlen(file->group->gr_name));
        arr[3] = MAX(arr[3], my_u64_len(file->stat.st_size));
    }
}

static
void put_total(struct directory_s *dir)
{
    uint32_t sum = 0;

    for (uint32_t i = 0; i < dir->n_files; i++)
        sum += dir->files[i].stat.st_blocks / 2;
    my_printf("total %u\n", sum);
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
    mode_t mode = file->stat.st_mode;

    my_putchar(get_file_type(file->stat.st_mode));
    my_putchar((mode & S_IRUSR) ? 'r' : '-');
    my_putchar((mode & S_IWUSR) ? 'w' : '-');
    my_putchar((mode & S_IXUSR) ? 'x' : '-');
    my_putchar((mode & S_IRGRP) ? 'r' : '-');
    my_putchar((mode & S_IWGRP) ? 'w' : '-');
    my_putchar((mode & S_IXGRP) ? 'x' : '-');
    my_putchar((mode & S_IROTH) ? 'r' : '-');
    my_putchar((mode & S_IWOTH) ? 'w' : '-');
    if (mode & S_ISVTX)
        my_putchar('t');
    else
        my_putchar((mode & S_IXOTH) ? 'x' : '-');
    my_putchar(' ');
}

static
void put_link(struct directory_s *dir, struct file_s *file)
{
    static char linkpath[PATH_MAX];
    static char fullpath[PATH_MAX];
    ssize_t size;

    if (!S_ISLNK(file->stat.st_mode))
        return;
    if (get_fullpath(dir->path, file->filename, fullpath) == NULL)
        return;
    size = readlink(fullpath, linkpath, PATH_MAX);
    linkpath[MIN(size, PATH_MAX - 1)] = '\0';
    my_printf(" -> %s", linkpath);
}

static
void put_file(int max_size[4], struct directory_s *dir, struct file_s *file)
{
    if (!file->valid)
        return;
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
    if (my_strstr(file->filename, " ") == NULL)
        my_printf("%s", file->filename);
    else
        my_printf("'%s'", file->filename);
    put_link(dir, file);
    my_putchar('\n');
}

void ls_output_long(struct directory_s *dir, bool total)
{
    int max_size[4] = {0};

    if (dir == NULL || dir->files == NULL)
        return;
    if (total)
        put_total(dir);
    get_max_size(dir, max_size);
    for (uint32_t i = 0; i < dir->n_files; i++)
        put_file(max_size, dir, dir->files + i);
}
