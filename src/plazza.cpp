/*
** EPITECH PROJECT, 2018
** CCP_plazza_2018
** File description:
** plazza.cpp
*/

#include "../include/plazza.hpp"

Plazza::Plazza() // Constructeur
{
}

Plazza::~Plazza() // Destructeur
{
}

void Plazza::shell(int multiplier, int number, int time)
{
    printf("plazza> ");
    fflush(stdout);

    while (42) {
        std::cout << this->input << std::endl;
    }
}

int main(int ac, char **av)
{
    if (ac == 3)
        Plazza *plazza = new shell(atoi(av[1]), atoi(av[2]), atoi(av[3]));
    else
        return (84);
    return (0);
}