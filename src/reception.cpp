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
    this->kitchen_number = 0;
}

Recept::~Recept()
{
}

int check_quantity(std::vector<std::string> tab)
{
    return -1;
}

int check_size(std::vector<std::string> tab)
{
    if (tab[1].compare("S") == 0 || tab[1].compare("M") == 0)
        check_quantity(tab);
    else if (tab[1].compare("L") == 0 || tab[1].compare("XL") == 0)
        check_quantity(tab);
    else if (tab[1].compare("XXL") == 0)
        check_quantity(tab);
    else
        return -1;
    return -1;
}

int check_command(std::string str)
{
    std::vector<std::string> argument = split_arg(str);

    if (argument[0].compare("status") == 0)
        std::cout << "hello" << std::endl;
    else if (argument[0].compare("Margaritana") == 0 || argument[0].compare("Regina") == 0)
        check_size(argument);
    else if (argument[0].compare("Americana") == 0 || argument[0].compare("Fantasia") == 0)
        check_size(argument);
    else
        return -1;
    return -1;
}

void Recept::loop(int cook)
{
    std::cout << "Welcome to loop" << std::endl;

    while (42) {
        printf("plazza> ");
        fflush(stdout);
        getline(std::cin, this->input);
        check_command(this->input);
        std::cout << this->input << std::endl;
        create_kitchen(cook);
    }
}