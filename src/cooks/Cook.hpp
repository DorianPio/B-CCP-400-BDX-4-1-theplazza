/*
** EPITECH PROJECT, 2021
** B-CCP-400-BDX-4-1-theplazza-camille.grandjean
** File description:
** Cook
*/

#pragma once

#include <iostream>
#include <thread>
#include <memory>
#include "SafeQueue.hpp"
#include "Ingredients.hpp"

namespace plazza
{
    class Cook {
        public:
            Cook(int multiplier, std::unique_ptr<Ingredients> &ingredients, std::unique_ptr<SafeQueue> &safequeue);
            Cook(const Cook &other) = delete;
            Cook(Cook &&b) noexcept = default;

            ~Cook();

            Cook &operator=(Cook const& rhs) noexcept = delete;
            Cook &operator=(Cook &&rhs) noexcept = default;

            bool getOccupied() const noexcept {return m_isOccupied;};
            void setOccupied() noexcept;
            void makePizza();
            Pizza getPizza() const noexcept;

        protected:
        private:
            bool m_isOccupied;
            Pizza m_pizza;
            int m_multiplier;
            std::thread m_thread;
            std::unique_ptr<Ingredients> &m_ingredients;
            std::unique_ptr<SafeQueue> &m_safequeue;
    };
}