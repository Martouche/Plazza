/*
** EPITECH PROJECT, 2018
** CCP_plazza_2018
** File description:
** plazza.cpp
*/

#include "../include/plazza.hpp"

Plazza::Plazza(int multiplier, int number, int time) // Constructeur
{
    shell(multiplier, number, time);
}

Plazza::~Plazza() // Destructeur
{
}

void Plazza::shell(int multiplier, int number, int time)
{
    printf("plazza> ");
    fflush(stdout);

    while (getline(std::cin, this->input)) {
        std::cout << this->input << std::endl;
    }
}