/*
** EPITECH PROJECT, 2018
** CCP_plazza_2018
** File description:
** plazza.cpp
*/

#include "../include/plazza.hpp"

/*Plazza::Plazza() // Constructeur
Plazza::Plazza(int multiplier, int number, int time) // Constructeur
{
    shell(multiplier, number, time);
}

Plazza::~Plazza() // Destructeur
{
}

void Plazza::shell(int multiplier, int number, int time)
{

}*/

int main(int ac, char **av)
{
    if (ac == 4) {
        Recept *reception = new Recept;
        reception->loop(atoi(av[2]));
        //Plazza *plazza = new Plazza;
        //plazza->shell(atoi(av[1]), atoi(av[2]), atoi(av[3]))
    } else
        return (84);
    return (0);
}