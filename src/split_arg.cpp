/*
** EPITECH PROJECT, 2018
** CCP_plazza_2018
** File description:
** Split arguments
*/

#include "../include/plazza.hpp"

std::vector<std::string> split_arg(std::string str)
{
    std::vector<std::string> result;
    std::istringstream stm(str);
    std::string token;

    while (stm >> token)
        result.push_back(token);
    return result;
}
