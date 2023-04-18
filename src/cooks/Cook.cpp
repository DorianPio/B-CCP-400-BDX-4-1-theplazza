/*
** EPITECH PROJECT, 2021
** B-CCP-400-BDX-4-1-theplazza-camille.grandjean
** File description:
** Cook
*/

#include "Cook.hpp"
#include "Pizza.hpp"
#include "Reception.hpp"
#include <chrono>
#include <functional>

#include <fstream>


plazza::Cook::Cook(int multiplier, std::unique_ptr<Ingredients> &ingredients, std::unique_ptr<SafeQueue> &safequeue):
    m_isOccupied(false),
    m_pizza("Americana", 2, {"Doe", "Tomato", "Gruyere", "Steak"}, L),
    m_multiplier(multiplier),
    m_thread(std::thread(&plazza::Cook::makePizza, this)),
    m_ingredients(ingredients),
    m_safequeue(safequeue)
{
}

plazza::Cook::~Cook()
{
    if (m_thread.joinable())
        m_thread.join();
}

void plazza::Cook::setOccupied() noexcept
{
    if (m_isOccupied)
        m_isOccupied = false;
    else
        m_isOccupied = true;
}

plazza::Pizza plazza::Cook::getPizza() const noexcept
{
    return m_pizza;
}

void plazza::Cook::makePizza()
{
    int sec = 0;

    while (true) {
        m_pizza = m_safequeue->front();
        setOccupied();
        m_ingredients->removeMultipleIngredients(m_pizza.getIngredients());
        sec = m_pizza.getTime() * m_multiplier;
        std::this_thread::sleep_for(std::chrono::seconds(sec));
        std::cout << m_pizza.getName() + " " + m_pizza.getStringSize() + " est terminé\n$> " << std::flush;
        setOccupied();
    }
}