/*
** EPITECH PROJECT, 2021
** B-CCP-400-BDX-4-1-theplazza-camille.grandjean
** File description:
** Ingredients
*/

#include <iostream>
#include "Ingredients.hpp"

plazza::Ingredients::Ingredients():
    m_ingredients({
        { "Doe", 5 },
        { "Ham", 5 },
        { "Steak", 5 },
        { "Tomato", 5 },
        { "Gruyere", 5 },
        { "Eggplant", 5 },
        { "Mushrooms", 5 },
        { "Chief love", 5 },
        { "Goat cheese", 5 }
    }),
    m_mutex(),
    m_cond()
{
}

std::unordered_map<std::string, int> plazza::Ingredients::getIngredients() const noexcept
{
    return m_ingredients;
}

void plazza::Ingredients::removeOneIngredient(std::string &name) noexcept
{
    for (auto &i : m_ingredients) {
        if (i.first == name)
            i.second -= 1;
    }
}

void plazza::Ingredients::removeMultipleIngredients(std::vector<std::string> ingred) noexcept
{
    std::unique_lock<std::mutex> mlock(m_mutex);

    while (check_ingredients(ingred) == false) {
        m_cond.wait(mlock);
    }
    for (auto &it : ingred) {
        removeOneIngredient(it);
    }
}

void plazza::Ingredients::display_ingredients() const noexcept
{
    for (auto i : m_ingredients) {
        std::cout << "name = " << i.first << " quantité = " << i.second << std::endl;
    }
}

void plazza::Ingredients::refill() noexcept
{
    std::unique_lock<std::mutex> mlock(m_mutex);

    for (auto &i : m_ingredients) {
        i.second += 1;
    }
    m_cond.notify_one();
}

bool plazza::Ingredients::check_ingredients(std::vector<std::string> ing) noexcept
{
    std::unordered_map<std::string, int>::const_iterator got;

    for (size_t i = 0; i < ing.size(); i++) {
        got = m_ingredients.find(ing[i]);
        if (got != m_ingredients.end()) {
            if (got->second <= 0) {
                return false;
            }
        } else {
            return false;
        }
    }
    return true;
}

std::string plazza::Ingredients::getStatusIngredients() noexcept
{
    std::string status = "";

    std::unique_lock<std::mutex> mlock(m_mutex);
    for (auto &i : m_ingredients) {
        status += "\tname = " + i.first + " quantity = " + std::to_string(i.second) + "\n";
    }
    return status;
}