/*
** EPITECH PROJECT, 2021
** B-CCP-400-BDX-4-1-theplazza-camille.grandjean
** File description:
** Kitchens
*/

#pragma once

#include <unistd.h>
#include <list>
#include <memory>
#include <chrono>
#include "Ingredients.hpp"
#include "Cook.hpp"
#include "SafeQueue.hpp"

namespace plazza
{
    class Kitchens {
        public:

            enum status {
                START = 0,
                STOP
            };

            Kitchens() = default;
            Kitchens(const Kitchens &other) = delete;
            Kitchens(Kitchens &&b) noexcept = default;
            Kitchens(int numberCook, int timerefill, int multiplier);

            ~Kitchens() = default;

            Kitchens &operator=(Kitchens const& rhs) noexcept = delete;
            Kitchens &operator=(Kitchens &&rhs) noexcept = default;

            void addIngredients() noexcept;
            void createCook() noexcept;
            int getTimeRefill() const { return m_timerefill; };
            int getNbCook() const { return m_nbcook; };
            void addPizzaToQueue(std::string &string);
            PizzaSize getEnumPizza(std::string size) const noexcept;
            int getNbPlace() noexcept;
            std::string prepareStatus() noexcept;
            void setStatus() noexcept;
            status getStatus() const noexcept;
            bool canClose() noexcept;
            void refill() noexcept;

        protected:
        private:
            int m_nbcook;
            int m_timerefill;
            int m_multiplier;
            std::unique_ptr<SafeQueue> m_safequeue;
            std::unique_ptr<Ingredients> m_ingredients;
            std::list<plazza::Cook> m_listOfCooks;
            std::string m_TypeOfPizza;
            status m_status;
            std::chrono::system_clock::time_point m_time_point_close;
            std::chrono::system_clock::time_point m_time_point_refill;
    };
}