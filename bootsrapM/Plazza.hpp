//
// EPITECH PROJECT, 2019
// my Plazza include file
// File description:
// made by Martin Vantalon
//

#ifndef PLAZZA_HPP_
#define PLAZZA_HPP_

#include <iostream>
#include <fstream>
#include <vector>
#include <exception>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <unistd.h>

class Plazza
{
public:
    Plazza(int, char **);
    ~Plazza();

private:
    float cooking_time;
    int cooks_per_kitchen;
    int replacing_time;
//    std::vector<KitchenEntry> kitchens;
    int	pipe_number;
    std::ofstream logs;
;}

#endif
