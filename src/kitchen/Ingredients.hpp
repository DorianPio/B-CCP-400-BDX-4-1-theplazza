/*
** EPITECH PROJECT, 2021
** B-CCP-400-BDX-4-1-theplazza-camille.grandjean
** File description:
** Ingredients
*/

#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <mutex>
#include <condition_variable>

namespace plazza
{
    class Ingredients {
        public:
            Ingredients();
            Ingredients(Ingredients &&b) noexcept = default;
            Ingredients(const Ingredients &other) = delete;

            ~Ingredients() = default;

            Ingredients &operator=(Ingredients const& rhs) noexcept = delete;
            Ingredients &operator=(Ingredients &&rhs) noexcept = default;

            std::unordered_map<std::string, int> getIngredients() const noexcept;
            void removeMultipleIngredients(std::vector<std::string> ingred) noexcept;
            void display_ingredients() const noexcept;
            void refill() noexcept;
            std::string getStatusIngredients() noexcept;

        protected:
            bool check_ingredients(std::vector<std::string> ingred) noexcept;
            void removeOneIngredient(std::string &) noexcept;
        private:
            std::unordered_map<std::string, int> m_ingredients;
            std::mutex m_mutex;
            std::condition_variable m_cond;
    };
}