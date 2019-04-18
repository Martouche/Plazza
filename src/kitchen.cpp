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