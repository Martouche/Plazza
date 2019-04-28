//
// EPITECH PROJECT, 2019
// my thread include file
// File description:
// made by Martin Vantalon
//

#ifndef THREADS_HPP_
#define THREADS_HPP_

#include <pthread.h>

class Thread
{
public:
  Thread();
  int launch(void *(*routine)(void *), void *);
  bool is_running() const;
  int waitThread();
  ~Thread();

private:
    pthread_t thread;
    bool running;
};

#endif
