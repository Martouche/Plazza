/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018 my cook .h file
** File description:
** Made by Martin Vantalon
*/

#ifndef COOK_HPP_
#define COOK_HPP_

#include "../include/plazza.hpp"

class Cook {
	public:
		Cook() = default;
		~Cook() = default;
        bool getActiveOrder() const noexcept;
        void setActiveOrder(bool activeOrder) noexcept;
        Plazza *getPizza() const noexcept;
        void setPizza(Plazza *pizza) noexcept;
	private:
        bool _activeOrder;
        Plazza *_pizza;
};

#endif
