/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** PizzaRegina
*/

#pragma once

#include "Pizza.hpp"
#include "PizzaSize.hpp"
namespace plazza {
    class PizzaRegina : public Pizza {
        public:
            PizzaRegina() = default;
            PizzaRegina(plazza::PizzaSize size);
            PizzaRegina(const PizzaRegina &other) = delete;
            PizzaRegina(plazza::PizzaRegina &&b) noexcept = default;
            ~PizzaRegina() = default;

            PizzaRegina &operator=(PizzaRegina const& rhs) noexcept = delete;
            PizzaRegina &operator=(PizzaRegina &&rhs) noexcept = default;
        protected:
        private:
    };
}
