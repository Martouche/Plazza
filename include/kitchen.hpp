/*
** EPITECH PROJECT, 2018
** CCP_plazza_2018
** File description:
** Kitchens file
*/

#ifndef KITCHEN_H_
#define KITCHEN_H_

#include <vector>
#include <thread>
#include <iostream>
#include <fstream>
#include <chrono>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>
#include <signal.h>
#include "threads.hpp"
#include "Cook.hpp"

struct ThreadParams {
    Cook *cook;
    Plazzas *sharedMemory;
    int number;
    int kitchenNumber;
    int multiplier;
    int replaceTime;
};

class Kitchen {
	public:
		Kitchen(int number, int multiplier, int numberOfCooks, int replaceTime);
		~Kitchen() = default;
        void createCooks() noexcept;
        void launchKitchen() noexcept;
        void assignOrder() noexcept;
	private:
        std::vector<Cook *> _cooks;
        pthread_t *_threads;
        Plazzas *_sharedMemory;
        OrderMsg _receiveBuffer;
        int _msqid;
        int _number;
        int _multiplier;
        int _numberOfCooks;
        int _replaceTime;
};

void *launchThread(void *number);
void executeOrder(ThreadParams *readParams) noexcept;
void displayAndLog(ThreadParams *readParams, const std::string &type) noexcept;

#endif
