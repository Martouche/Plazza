/*
** EPITECH PROJECT, 2018
** CCP_plazza_2018
** File description:
** Kitchens file
*/

#include "../include/kitchen.hpp"

Kitchen::Kitchen(int number)
{
    this->cooks = number;
}

Kitchen::~Kitchen()
{
}

int Kitchen::getNumber() const
{
    return this->cooks;
}

void Recept::create_kitchen(int cook)
{
    Kitchen *kitchen1 = new Kitchen(cook);
    std::cout << "kitchen 1 has "<< kitchen1->getNumber() << " cookers" << std::endl;
}