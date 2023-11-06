/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_strncmp
*/

int my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;

    if (!s1 || !s2 || n == 0)
        return 0;
    while (i < n - 1 && s1[i]) {
        if (s1[i] != s2[i])
            return s1[i] - s2[i];
        i++;
    }
    return s1[i] - s2[i];
}
