/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Reception
*/

#ifndef RECEPTION_HPP_
#define RECEPTION_HPP_

#include <iostream>
#include <regex>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <vector>
#include "../include/plazza.hpp"
#include "../include/threads.hpp"

class Reception {
	public:
		Reception(int multiplier, int numberOfCooks, int replaceTime);
		~Reception();
        void sendOrders() noexcept;
        void sendOrder(int kitchen, Plazza *pizza);
        int findFreeKitchen(int numberOfCooks) const noexcept;
        int findNewKitchen() const noexcept;
        void launchShell();
        void displayStatus() const noexcept;
        void extractOrders(std::string &input);
        void addOrder(std::string type, std::string size, int number);
	private:
        std::vector<Plazza *> _orders;
        Thread *_shm;
        Plazzas *_sharedMemory;
        OrderMsg _sendBuffer;
        int _multiplier;
        int _numberOfCooks;
        int _replaceTime;
};

#endif
