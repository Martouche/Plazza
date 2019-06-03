/*
** EPITECH PROJECT, 2018
** CCP_plazza_2018
** File description:
** plazza.cpp
*/

#include "../include/plazza.hpp"
#include "../include/error.hpp"
#include "../include/reception.hpp"

Plazza::Plazza(PizzaType typ, PizzaSize siz) : type(typ), size(siz)
{
}

PizzaType Plazza::getType() const noexcept
{
    return this->type;
}

void Plazza::setType(PizzaType type) noexcept
{
    this->type = type;
}

PizzaSize Plazza::getSize() const noexcept
{
    return this->size;
}

void Plazza::setSize(PizzaSize size) noexcept
{
    this->size = size;
}

int main(int ac, char **av)
{
    try {
        if (ac != 4)
            throw Error("USAGE: ./plazza [multiplier] [cooks_per_kitchen] [replace_ingredients_time]");
        if (std::atoi(av[1]) < 0 || std::atoi(av[2]) < 0 || std::atoi(av[3]) < 0)
            throw Error("All parameters must be positive values");
        std::unique_ptr<Reception> reception = std::make_unique<Reception>(std::atoi(av[1]), std::atoi(av[2]), std::atoi(av[3]));
        reception->launchShell();
        return 0;
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
