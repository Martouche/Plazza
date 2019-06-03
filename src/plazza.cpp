/*
** EPITECH PROJECT, 2018
** CCP_plazza_2018
** File description:
** plazza.cpp
*/

#include "../include/plazza.hpp"
#include "../include/error.hpp"

int main(int ac, char **av)
{
    try {
        if (ac != 4)
            throw Error("USAGE: ./plazza [multiplier] [cooks_per_kitchen] [replace_ingredients_time]");
        if (std::atoi(av[1]) < 0 || std::atoi(av[2]) < 0 || std::atoi(av[3]) < 0)
            throw Error("All parameters must be positive values");
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
            return 84;
        }

/*    if (ac == 4) {
        Plazza *plazza = new Plazza;
        plazza->loop(atoi(av[2]));
        //Plazza *plazza = new Plazza;
        //plazza->shell(atoi(av[1]), atoi(av[2]), atoi(av[3]))
    } else
        return (84);
*/
    return (0);
}
