/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018 my cook .h file
** File description:
** Made by Martin Vantalon
*/

#include "../include/cook.hpp"

bool Cook::getActiveOrder() const noexcept
{
    return _activeOrder;
}

void Cook::setActiveOrder(bool activeOrder) noexcept
{
    _activeOrder = activeOrder;
}

Plazza *Cook::getPizza() const noexcept
{
    return _pizza;
}

void Cook::setPizza(Plazza *pizza) noexcept
{
    _pizza = pizza;
}
