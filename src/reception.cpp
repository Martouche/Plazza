/*
** EPITECH PROJECT, 2018
** CCP_plazza_2018
** File description:
** Reception file
*/

#include "../include/plazza.hpp"
#include "../include/reception.hpp"
#include "../include/error.hpp"
#include "../include/threads.hpp"
#include <iostream>
#include <regex>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>

Reception::Reception(int multiplier, int numberOfCooks, int replaceTime)
: _multiplier(multiplier), _numberOfCooks(numberOfCooks), _replaceTime(replaceTime)
{
}

Reception::~Reception()
{
    delete _shm;
}

void Reception::launchShell()
{
    _shm = new Thread();
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

void Reception::extractOrders(std::string &input)
{
    size_t pos = 0;
    std::smatch match;
    static std::regex const regex("^([a-zA-Z]+)\\s{1}(S|M|L|XL|XXL)\\s{1}x(\\d+)$");
    std::string order;
    std::string separator = "; ";

    try {
        while ((pos = input.find(separator)) != std::string::npos) {
            order = input.substr(0, pos);
            if (std::regex_search(order, match, regex))
                addOrder(match[1], match[2], stoi(match[3]));
            else
                throw Error("'" + order + "' : " + "Bad order syntax!");
            input.erase(0, pos + separator.length());
        }
        if (std::regex_search(input, match, regex))
            addOrder(match[1], match[2], stoi(match[3]));
        else
            throw Error("'" + input + "' : " + "Bad order syntax!");
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

void Reception::addOrder(std::string type, std::string size, int number)
{
    PizzaType newType;
    PizzaSize newSize;

    if (number == 0)
        throw Error(std::to_string(number) + " : " + "Invalid pizzas number!");
    for (int i = 0; i < number; i++) {

        if (type == "regina")
            newType = Regina;
        else if (type == "margarita")
            newType = Margarita;
        else if (type == "americana")
            newType = Americana;
        else if (type == "fantasia")
            newType = Fantasia;
        else
            throw Error("'" + type + "' : " + "Bad pizza name!");

        if (size == "S")
            newSize = S;
        else if (size == "M")
            newSize = M;
        else if (size == "L")
            newSize = L;
        else if (size == "XL")
            newSize = XL;
        else
            newSize = XXL;

        Plazza *pizza = new Plazza(newType, newSize);
        _orders.push_back(pizza);
    }
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
void Reception::sendOrders() noexcept
{
    int kitchen;
    pid_t pid;
    int stack = 0;

    while (_orders.size()) {
        std::this_thread::sleep_for (std::chrono::milliseconds(10));
        for (int i = _numberOfCooks; i > 0; i--){
            kitchen = findFreeKitchen(i);
            if (kitchen != -1)
                break;
        }
        if (kitchen != -1) {
            sendOrder(kitchen, _orders.back());
            _orders.pop_back();
        } else {
            if ((pid = fork()) == -1)
                perror("fork");
            waitpid(pid, &stack, WNOHANG);
            if (pid == 0) {
                kitchen = findNewKitchen();
                if (kitchen != -1) {
                    Kitchen k(kitchen, _multiplier, _numberOfCooks, _replaceTime);
                    k.launchKitchen();
                }
            }
        }
    }
}

void Reception::sendOrder(int kitchen, Plazza *pizza)
{
    _sendBuffer.pizza.type = pizza->getType();
    _sendBuffer.pizza.size = pizza->getSize();
    _sendBuffer.mtype = kitchen + 1;
    if (msgsnd(_shm->getMsqid(), &_sendBuffer, sizeof(Plazza), IPC_NOWAIT) < 0)
        throw Error("msgsnd failed");
}

int Reception::findFreeKitchen(int numberOfCooks) const noexcept
{
    for (int i = 0; i < MAX_KITCHENS; i++) {
        std::unique_lock<std::mutex> lock(_sharedMemory->mutex);
        if (_sharedMemory->status[i][0] == numberOfCooks)
            return i;
        lock.unlock();
    }
    return -1;
}

int Reception::findNewKitchen() const noexcept
{
    for (int i = 0; i < MAX_KITCHENS; i++) {
        std::unique_lock<std::mutex> lock(_sharedMemory->mutex);
        if (_sharedMemory->status[i][0] == -1)
            return i;
        lock.unlock();
    }
    return -1;
}
