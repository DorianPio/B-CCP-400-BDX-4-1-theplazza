/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** PizzaMargarita
*/

#pragma once

#include "Pizza.hpp"
#include "PizzaSize.hpp"

namespace plazza {
    class PizzaMargarita : public Pizza {
        public:
            PizzaMargarita() = default;
            PizzaMargarita(const PizzaMargarita &other) = delete;
            PizzaMargarita(PizzaMargarita &&b) noexcept = default;
            PizzaMargarita(plazza::PizzaSize size);
            ~PizzaMargarita() = default;

            PizzaMargarita &operator=(PizzaMargarita const& rhs) noexcept = delete;
            PizzaMargarita &operator=(PizzaMargarita &&rhs) noexcept = default;

        protected:
        private:
    };
}