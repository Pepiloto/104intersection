/*
** EPITECH PROJECT, 2020
** 104intersection
** File description:
** main.c
*/

#include "intersection.h"

static int is_number(char *str)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] == '-' || str[i] >= '0' && str[i] <= '9')
            continue;
        else
            return 84;
    }
    return 0;
}
static int error_handling(char **av)
{
    for (int i = 1; av[i]; i++)
        if (is_number(av[i]) == 84)
            return 84;
    if (av[1][0] == '3' && atof(av[8]) < 0 || av[1][0] == '3' && atof(av[8]) > 90)
        return 84;
    else if (atof(av[8]) < 0)
        return 84;
    return 0;
}

int main(int ac, char **av)
{
    if (ac == 9 && error_handling(av) == 0)
        return intersection(ac, av);
    return 84;
}
