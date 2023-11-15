/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** print
*/

#include <grp.h>
#include <pwd.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "my.h"
#include "my_ls.h"

static
void get_max_size(struct directory_s const *dir, size_t arr[4])
{
    struct file_s *file;

    for (uint32_t i = 0; i < dir->n_files; i++) {
        file = dir->files + i;
        if (!file->valid)
            continue;
        arr[0] = MAX(arr[0], my_u64_len((uint32_t)file->stat.st_nlink));
        arr[1] = MAX(arr[1], my_strlen(file->passwd->pw_name));
        arr[2] = MAX(arr[2], my_strlen(file->group->gr_name));
        arr[3] = MAX(arr[3], (S_ISCHR(file->stat.st_mode))
                ? 4 : my_u64_len((uint32_t)file->stat.st_size));
    }
}

static
void put_total(struct directory_s const *dir)
{
    uint32_t sum = 0;

    for (uint32_t i = 0; i < dir->n_files; i++)
        sum += dir->files[i].stat.st_blocks / 2;
    my_printf("total %u\n", sum);
}

static
void put_date(struct file_s const *file, options_t options)
{
    struct timespec timestamp = (options & OPT_ACCESS_TIME)
        ? file->stat.st_atim
        : file->stat.st_mtim;
    char *time = ctime(&timestamp.tv_sec);

    time[my_strlen(time) - 9] = '\0';
    my_printf("%s ", time + 4);
}

static
void put_perms(struct file_s const *file)
{
    static char const perms[] = "-rwx";
    static char buf[PERMS_SIZE + 1];
    mode_t mode = file->stat.st_mode;

    for (int i = 0; i < PERMS_SIZE; i += 3) {
        buf[i + 0] = perms[(ptrdiff_t)(1 * !!(mode & (S_IRUSR >> i)))];
        buf[i + 1] = perms[(ptrdiff_t)(2 * !!(mode & (S_IWUSR >> i)))];
        buf[i + 2] = perms[(ptrdiff_t)(3 * !!(mode & (S_IXUSR >> i)))];
    }
    if (mode & S_ISVTX)
        buf[PERMS_SIZE - 1] = 't';
    buf[PERMS_SIZE] = ' ';
    my_putnstr(buf, PERMS_SIZE + 1);
}

static
void put_link(struct directory_s const *dir, struct file_s const *file)
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
void put_size(size_t const max_size[4], struct file_s const *file)
{
    if (!S_ISCHR(file->stat.st_mode)) {
        my_putnchar(' ', max_size[3] - my_u64_len(file->stat.st_size));
        my_printf("%u ", file->stat.st_size);
        return;
    }
    my_printf(
        "%u, %u ",
        (uintmax_t)minor(file->stat.st_dev),
        (uintmax_t)major(file->stat.st_dev)
    );
}

static
void put_file(
    size_t const max_size[4],
    struct directory_s const *dir,
    struct file_s *file,
    options_t options
)
{
    if (!file->valid)
        return;
    put_perms(file);
    my_putnchar(' ', max_size[0] - my_u64_len(file->stat.st_nlink));
    my_printf("%u ", file->stat.st_nlink);
    if ((options & OPT_LONG_NO_OWN) != OPT_LONG_NO_OWN) {
        my_putnchar(' ', max_size[1] - my_strlen(file->passwd->pw_name));
        my_printf("%s ", file->passwd->pw_name);
    }
    my_putnchar(' ', max_size[2] - my_strlen(file->group->gr_name));
    my_printf("%s ", file->group->gr_name);
    put_size(max_size, file);
    put_date(file, options);
    print_filename(file, options);
    put_link(dir, file);
    my_putchar('\n');
}

void ls_output_long(
    struct directory_s const *dir,
    bool total, options_t options)
{
    size_t max_size[4] = {0};

    if (dir == NULL || dir->files == NULL)
        return;
    if (total)
        put_total(dir);
    get_max_size(dir, max_size);
    for (uint32_t i = 0; i < dir->n_files; i++)
        put_file(max_size, dir, dir->files + i, options);
}
