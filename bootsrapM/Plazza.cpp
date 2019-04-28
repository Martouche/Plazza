//
// EPITECH PROJECT, 2019
// my Plazza functions
// File description:
// made by Martin Vantalon
//

#include "Plazza.hpp"

Plazza::Plazzza(int argc, char **argv) : _logs("PlazzaLogs", std::ios::out | std::ios::app)

{
    std::stringstream ss;
    if (argc < 4)
        std::cout << "soucis dans les arguments" << std::endl;
    ss << argv[1] << " " << argv[2] " " << argv[3];
    ss >> this->cooking_time >> this->cooks_per_kitchen >> this->replacing_time;
    std::cout << this->cooking_time << this->cooks_per_kitchen << this->replacing_time << std::endl;
    pipe_number = 1;
}

Plazza::~Plazza()
{
    this->logs.close();
}

int main(int ac, char **av)
{
    Plazza plazza(ac, av);
/*    try {
        plazza.work();
    }
    catch(std::exception &e) {
        std::cerr << "there is an exception : " << e.what() << std::endl;
    }
*/    return 0;
}
