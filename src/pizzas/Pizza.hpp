/*
** EPITECH PROJECT, 2021
** pizza
** File description:
** Pizza
*/

#pragma once

#include <vector>
#include <string>
#include "PizzaSize.hpp"

namespace plazza
{
    class Pizza {
        public:
            Pizza(const Pizza &other) = default;
            Pizza(Pizza &&b) noexcept = default;
            Pizza(std::string name, int time, std::vector<std::string> ingredients, PizzaSize size);
            ~Pizza() = default;

            Pizza &operator=(Pizza const& rhs) noexcept;
            Pizza &operator=(Pizza &&rhs) noexcept = default;

            std::vector<std::string> getIngredients() const noexcept;
            const std::string &getName() const noexcept;
            size_t getTime() const noexcept;
            PizzaSize getSize() const noexcept;
            std::string getStringSize() const noexcept;
        protected:
        private:
            std::string m_name;
            size_t m_time;
            std::vector<std::string> m_ingredients;
            PizzaSize m_size;
    };
}
