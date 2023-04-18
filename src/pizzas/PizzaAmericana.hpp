/*
** EPITECH PROJECT, 2021
** americana
** File description:
** PizzaAmericana
*/

#pragma once

#include "Pizza.hpp"
#include "PizzaSize.hpp"

namespace plazza {
    class PizzaAmericana : public Pizza {
        public:
            PizzaAmericana() = default;
            PizzaAmericana(const PizzaAmericana &other) = delete;
            PizzaAmericana(PizzaAmericana &&b) noexcept = default;
            PizzaAmericana(plazza::PizzaSize size);
            ~PizzaAmericana() = default;

            PizzaAmericana &operator=(PizzaAmericana const& rhs) noexcept = delete;
            PizzaAmericana &operator=(PizzaAmericana &&rhs) noexcept = default;

        protected:
        private:
    };
}
