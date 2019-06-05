/*
** EPITECH PROJECT, 2018
** CCP_plazza_2018
** File description:
** Kitchens file
*/

#include "../include/kitchen.hpp"
#include "../include/error.hpp"

bool isThreadAlive;

Kitchen::Kitchen(int number, int multiplier, int numberOfCooks, int replaceTime)
: _number(number), _multiplier(multiplier), _numberOfCooks(numberOfCooks), _replaceTime(replaceTime)
{
    std::cout << "Created kitchen : " << _number << std::endl;
    _sharedMemory = openSharedMemory();
    std::unique_lock<std::mutex> lock(_sharedMemory->mutex);
    _sharedMemory->status[_number][0] = _numberOfCooks;
    lock.unlock();
    isThreadAlive = true;
    key_t key = ftok("/etc/bashrc", 'B');
    if ((_msqid = msgget(key, 0666)) < 0)
        throw Error("msgget failed");
}



void Kitchen::createCooks() noexcept
{
    _threads = new pthread_t[_numberOfCooks];
    for (int i = 0; i < _numberOfCooks; i++) {
        Cook *cook = new Cook;
        cook->setActiveOrder(false);
        _cooks.push_back(cook);
        ThreadParams *params = new ThreadParams;
        params->cook = _cooks[i];
        params->sharedMemory = _sharedMemory;
        params->number = i;
        params->kitchenNumber = _number;
        params->multiplier = _multiplier;
        params->replaceTime = _replaceTime;
        pthread_create(&_threads[i], NULL, launchThread, (void*)params);
    }
}

void Kitchen::launchKitchen() noexcept
{
    createCooks();
    auto replaceTimer = std::chrono::steady_clock::now();
    auto killTimer = std::chrono::steady_clock::now();
    while (true) {
        if (std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - replaceTimer).count() > _replaceTime / 1000) {
            for (int i = 1; i <= 9; i++) {
                std::unique_lock<std::mutex> lock(_sharedMemory->mutex);
                if (_sharedMemory->status[_number][i] < 5)
                    _sharedMemory->status[_number][i] += 1;
                lock.unlock();
            }
            replaceTimer = std::chrono::steady_clock::now();
        }
        if (std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - killTimer).count() > 5) {
            std::unique_lock<std::mutex> lock(_sharedMemory->mutex);
            if (_sharedMemory->status[_number][0] == _numberOfCooks) {
                _sharedMemory->status[_number][0] = -1;
                _sharedMemory->status[_number][1] = 5;
                _sharedMemory->status[_number][2] = 5;
                _sharedMemory->status[_number][3] = 5;
                _sharedMemory->status[_number][4] = 5;
                _sharedMemory->status[_number][5] = 5;
                _sharedMemory->status[_number][6] = 5;
                _sharedMemory->status[_number][7] = 5;
                _sharedMemory->status[_number][8] = 5;
                _sharedMemory->status[_number][9] = 5;
                lock.unlock();
                std::cout << "Killed kitchen : " << _number << std::endl;
                isThreadAlive = false;
                for (int i = 0; i < _numberOfCooks; i++)
                    pthread_join(_threads[i],NULL);
                raise(SIGTERM);
            }
            lock.unlock();
            killTimer = std::chrono::steady_clock::now();
        }
        if (msgrcv(_msqid, &_receiveBuffer, sizeof(Plazza), _number + 1, MSG_NOERROR | IPC_NOWAIT) > 0)
            assignOrder();
    }
}

void Kitchen::assignOrder() noexcept
{
    for (int i = 0; i < _numberOfCooks; i++) {
        if (!_cooks[i]->getActiveOrder()) {
            std::unique_lock<std::mutex> lock(_sharedMemory->mutex);
            if (_sharedMemory->status[_number][0] > 0) {
                std::cout << "Kitchen n°" << _number << " : " << "1 cook busy" << std::endl;
                _sharedMemory->status[_number][0] -= 1;
                Plazza *pizza = new Plazza(_receiveBuffer.pizza.type, _receiveBuffer.pizza.size);
                _cooks[i]->setPizza(pizza);
                _cooks[i]->setActiveOrder(true);
            }
            lock.unlock();
            break;
        }
    }
}

void *launchThread(void *params)
{
    ThreadParams *readParams = (ThreadParams*)params;
    while (isThreadAlive == true) {
        if (readParams->cook->getActiveOrder()) {
            executeOrder(readParams);
        } else
            std::this_thread::yield();
    }
    std::cout << "Killed 1 cook" << std::endl;
    return (NULL);
}

void displayAndLog(ThreadParams *readParams, const std::string &type) noexcept
{
    time_t tt;
    struct tm *ti;
    time(&tt);
    ti = localtime(&tt);

    std::ofstream logFile;
    logFile.open("log.txt", std::ios::app);

    readParams->cook->setActiveOrder(false);
    switch (readParams->cook->getPizza()->getSize()) {
        case S:
            std::cout << "=> Cooked 1 " << type << " with size S" << std::endl;
            logFile << asctime(ti) << "Cooked 1 " << type << " with size S" << std::endl << std::endl;
            break;
        case M:
            std::cout << "=> Cooked 1 " << type << " with size M" << std::endl;
            logFile << asctime(ti) << "Cooked 1 " << type << " with size M" << std::endl << std::endl;
            break;
        case L:
            std::cout << "=> Cooked 1 " << type << " with size L" << std::endl;
            logFile << asctime(ti) << "Cooked 1 " << type << " with size L" << std::endl << std::endl;
            break;
        case XL:
            std::cout << "=> Cooked 1 " << type << " with size XL" << std::endl;
            logFile << asctime(ti) << "Cooked 1 " << type << " with size XL" << std::endl << std::endl;
            break;
        case XXL:
            std::cout << "=> Cooked 1 " << type << " with size XXL" << std::endl;
            logFile << asctime(ti) << "Cooked 1 " << type << " with size XXL" << std::endl << std::endl;
            break;
    }
    logFile.close();
    std::cout << "Kitchen n°" << readParams->kitchenNumber << " : " << "1 cook available" << std::endl;
}

void executeOrder(ThreadParams *readParams) noexcept
{
    switch (readParams->cook->getPizza()->getType()) {
        case Margarita:
            if (readParams->sharedMemory->status[readParams->kitchenNumber][1] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][2] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][3] > 0) {
                std::this_thread::sleep_for(std::chrono::seconds(1 * readParams->multiplier));
                readParams->sharedMemory->status[readParams->kitchenNumber][1] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][2] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][3] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][0] += 1;
                displayAndLog(readParams, "Margarita");
            }
            break;
        case Regina:
            if (readParams->sharedMemory->status[readParams->kitchenNumber][1] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][2] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][3] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][4] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][5] > 0) {
                std::this_thread::sleep_for(std::chrono::seconds(2 * readParams->multiplier));
                readParams->sharedMemory->status[readParams->kitchenNumber][1] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][2] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][3] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][4] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][5] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][0] += 1;
                displayAndLog(readParams, "Regina");
            }
            break;
        case Americana:
            if (readParams->sharedMemory->status[readParams->kitchenNumber][1] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][2] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][3] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][6] > 0) {
                std::this_thread::sleep_for(std::chrono::seconds(2 * readParams->multiplier));
                readParams->sharedMemory->status[readParams->kitchenNumber][1] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][2] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][3] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][6] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][0] += 1;
                displayAndLog(readParams, "Americana");
            }
            break;
        case Fantasia:
            if (readParams->sharedMemory->status[readParams->kitchenNumber][1] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][2] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][7] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][8] > 0
            && readParams->sharedMemory->status[readParams->kitchenNumber][9] > 0) {
                std::this_thread::sleep_for(std::chrono::seconds(4 * readParams->multiplier));
                readParams->sharedMemory->status[readParams->kitchenNumber][1] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][2] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][7] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][8] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][9] -= 1;
                readParams->sharedMemory->status[readParams->kitchenNumber][0] += 1;
                displayAndLog(readParams, "Fantasia");
            }
            break;
        default:
            break;
    }
}
