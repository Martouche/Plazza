/*
** EPITECH PROJECT, 2018
** CCP_plazza_2018
** File description:
** Reception file
*/

#include "../include/plazza.hpp"

Recept::Recept()
{
    this->input = "";
}

Recept::~Recept()
{
}

void Recept::loop(int cook)
{
    std::cout << "Welcome to loop" << std::endl;

    while (42) {
        printf("plazza> ");
        fflush(stdout);
        getline(std::cin, this->input);
        std::cout << this->input << std::endl;
        create_kitchen(cook);
    }
}