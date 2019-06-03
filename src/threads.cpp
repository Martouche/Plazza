//
// EPITECH PROJECT, 2019
// my thread functions
// File description:
// made by Martin Vantalon
//

#include "../include/threads.hpp"
#include <pthread.h>
#include <iostream>
#include <thread>

Thread::Thread() : running(false)
{
}

int	Thread::launch(void *(*routine)(void *), void *args)
{
    this->running = true;
    if (pthread_create(&this->thread, NULL, *routine, args) != 0) {
        this->running = false;
        return (-1);
    }
    return (0);
}

int	Thread::waitThread()
{
    int ret = pthread_join(this->thread, NULL);
    this->running = false;
    return (ret);
}

bool Thread::is_running() const
{
    return (this->running);
}

Thread::~Thread()
{
}
