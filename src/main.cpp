/*
** EPITECH PROJECT, 2018
** CCP_plazza_2018
** File description:
** main.cpp
*/

#include "../include/plazza.hpp"

int main(int ac, char **av)
{
    if (ac == 4)
        Plazza *plazza = new Plazza(atoi(av[1]), atoi(av[2]), atoi(av[3]));
    else
        printf("You entered %d arguments instead of 4\n", ac);
        return (84);
    return (0);
}