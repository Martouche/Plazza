/*
** EPITECH PROJECT, 2018
** CCP_plazza_2018
** File description:
** plazza.hpp
*/

#ifndef PLAZZA_HPP
#define PLAZZA_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <cstring>
#include <vector>
#include <sstream>

enum PizzaType
{
    Regina = 1, // Contains doe, tomato, gruyere, ham, mushrooms. Baked in 2 secs * multiplier
    Margarita = 2, // Contains doe, tomato and gruyere. Baked in 1 sec * multiplier
    Americana = 4, // Contains doe, tomato, gruyere, steak. Baked in 2 secs * multiplier
    Fantasia = 8 // Contains doe, tomato, eggplant, goat cheese and chief love. Baked in 4 secs * multiplier
};

enum PizzaSize
{
    S = 1,
    M = 2,
    L = 4,
    XL = 8,
    XXL = 16
};

class Plazza {
public:
    Plazza(PizzaType type, PizzaSize size);
    ~Plazza() = default;
    PizzaType getType() const noexcept;
    void setType(PizzaType type) noexcept;
    PizzaSize getSize() const noexcept;
    void setSize(PizzaSize size) noexcept;
private:
    PizzaType type;
    PizzaSize size;
};

#endif
