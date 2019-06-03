/*
** EPITECH PROJECT, 2018
** CCP_plazza_2018
** File description:
** Reception file
*/

#include "../include/plazza.hpp"
#include "../include/reception.hpp"
#include "../include/error.hpp"

Reception::Reception(int multiplier, int numberOfCooks, int replaceTime)
: _multiplier(multiplier), _numberOfCooks(numberOfCooks), _replaceTime(replaceTime)
{
}

Reception::~Reception()
{
    delete _shm;
}

int check_quantity(std::vector<std::string> tab)
{
    return -1;
}

void Reception::launchShell()
{
    _shm = new SharedMemory();
    _sharedMemory = openSharedMemory();
    std::string input;
    while (true) {
        if (!std::getline(std::cin, input))
            throw Error("You entered an invalid input");
        if (input == "status")
            displayStatus();
        else {
            extractOrders(input);
            sendOrders();
        }
        input.erase();
    }
}

int check_command(std::string str)
{
    std::vector<std::string> argument = split_arg(str);

    if (argument[0].compare("status") == 0)
        std::cout << "hello" << std::endl;
    else if (argument[0].compare("Margaritana") == 0 || argument[0].compare("Regina") == 0)
        check_size(argument);
    else if (argument[0].compare("Americana") == 0 || argument[0].compare("Fantasia") == 0)
        check_size(argument);
    else
        return -1;
    return -1;
}

void Reception::displayStatus() const noexcept
{
    std::cout << std::endl << "==========" << std::endl;
    std::cout << "Kitchens status" << std::endl;
    for (int i = 0; i < MAX_KITCHENS; i++) {
        std::unique_lock<std::mutex> lock(_sharedMemory->mutex);
        if (_sharedMemory->status[i][0] != -1) {
            std::cout << "Kitchen n°" << i + 1 << " : " << std::endl;
            std::cout << "Working [" << _numberOfCooks - _sharedMemory->status[i][0] << "/" << _numberOfCooks << "]" << std::endl;
            std::cout << "Doe [" << _sharedMemory->status[i][1] << "/" << 5 << "]" << std::endl;
            std::cout << "Tomato [" << _sharedMemory->status[i][2] << "/" << 5 << "]" << std::endl;
            std::cout << "Gruyere [" << _sharedMemory->status[i][3] << "/" << 5 << "]" << std::endl;
            std::cout << "Ham [" << _sharedMemory->status[i][4] << "/" << 5 << "]" << std::endl;
            std::cout << "Mushrooms [" << _sharedMemory->status[i][5] << "/" << 5 << "]" << std::endl;
            std::cout << "Steak [" << _sharedMemory->status[i][6] << "/" << 5 << "]" << std::endl;
            std::cout << "Eggplant [" << _sharedMemory->status[i][7] << "/" << 5 << "]" << std::endl;
            std::cout << "Goat cheese [" << _sharedMemory->status[i][8] << "/" << 5 << "]" << std::endl;
            std::cout << "Chief love [" << _sharedMemory->status[i][9] << "/" << 5 << "]" << std::endl;
            std::cout << "----------" << std::endl;
        }
        lock.unlock();
    }
    std::cout << std::endl << "==========" << std::endl;
}
