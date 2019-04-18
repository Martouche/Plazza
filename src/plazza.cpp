/*
** EPITECH PROJECT, 2018
** CCP_plazza_2018
** File description:
** plazza.cpp
*/

#include "../include/plazza.hpp"

<<<<<<< HEAD
/*Plazza::Plazza() // Constructeur
=======
Plazza::Plazza(int multiplier, int number, int time) // Constructeur
>>>>>>> 53c72d525e179d19914c5a3154a72eecf2b11958
{
    shell(multiplier, number, time);
}

Plazza::~Plazza() // Destructeur
{
}

void Plazza::shell(int multiplier, int number, int time)
{
    while (42) {
        printf("plazza> ");
        fflush(stdout);
        getline(std::cin, this->input);
        std::cout << this->input << std::endl;
    }
<<<<<<< HEAD
}*/

int main(int ac, char **av)
{
    if (ac == 4) {
        Recept *reception = new Recept;
        reception->loop();
        //Plazza *plazza = new Plazza;
        //plazza->shell(atoi(av[1]), atoi(av[2]), atoi(av[3]))
    } else
        return (84);
    return (0);
=======
>>>>>>> 53c72d525e179d19914c5a3154a72eecf2b11958
}