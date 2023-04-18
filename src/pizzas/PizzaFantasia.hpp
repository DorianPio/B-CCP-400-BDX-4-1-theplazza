/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** PizzaFantasia
*/

#pragma once

#include "Pizza.hpp"
#include "PizzaSize.hpp"

namespace plazza {
    class PizzaFantasia : public Pizza {
        public:
            PizzaFantasia() = default;
            PizzaFantasia(const PizzaFantasia &other) = delete;
            PizzaFantasia(PizzaFantasia &&b) noexcept = default;
            PizzaFantasia(plazza::PizzaSize size);
            ~PizzaFantasia() = default;

            PizzaFantasia &operator=(PizzaFantasia const& rhs) noexcept = delete;
            PizzaFantasia &operator=(PizzaFantasia &&rhs) noexcept = default;

        protected:
        private:
    };
}