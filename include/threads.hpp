//
// EPITECH PROJECT, 2019
// my thread include file
// File description:
// made by Martin Vantalon
//

#ifndef THREADS_HPP_
#define THREADS_HPP_

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <pthread.h>
#include <mutex>
#include "../include/plazza.hpp"

constexpr int MAX_KITCHENS = 100;

struct Plazzas {
    int status[MAX_KITCHENS][10];
    std::mutex mutex;
};

struct OrderPizza {
    PizzaType type;
    PizzaSize size;
};

struct OrderMsg {
    long mtype;
    OrderPizza pizza;
};

class Thread {
public:
  Thread();
  ~Thread();
  int getMsqid() const noexcept;
  void createSharedMemory();
private:
    Plazzas *_sharedMemory;
    int _shmid;
    int _msqid;
};

Plazzas *openSharedMemory();

#endif
