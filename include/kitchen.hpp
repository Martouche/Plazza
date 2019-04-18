/*
** EPITECH PROJECT, 2018
** CCP_plazza_2018
** File description:
** Kitchens file
*/

#ifndef KITCHEN_H_
#define KITCHEN_H_

#include "plazza.hpp"

class Kitchen
{
public:
    Kitchen(int);
    ~Kitchen();
    int getNumber() const;
private:
    int cooks;
};

#endif