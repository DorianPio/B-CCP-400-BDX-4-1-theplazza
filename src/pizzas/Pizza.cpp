/*
** EPITECH PROJECT, 2021
** pizza
** File description:
** Pizza
*/

#include <iostream>
#include "Pizza.hpp"

plazza::Pizza::Pizza(std::string name, int time, std::vector<std::string> ingredients, PizzaSize size):
    m_name(name),
    m_time(time),
    m_ingredients(ingredients),
    m_size(size)
{
}

std::vector<std::string> plazza::Pizza::getIngredients() const noexcept
{
    return m_ingredients;
}

const std::string &plazza::Pizza::getName() const noexcept
{
    return m_name;
}

size_t plazza::Pizza::getTime() const noexcept
{
    return m_time;
}

plazza::PizzaSize plazza::Pizza::getSize() const noexcept
{
    return m_size;
}

std::string plazza::Pizza::getStringSize() const noexcept
{
    if (m_size == plazza::PizzaSize::S)
        return "S";
    else if (m_size == plazza::PizzaSize::M)
        return "M";
    else if (m_size == plazza::PizzaSize::L)
        return "L";
    else if (m_size == plazza::PizzaSize::XL)
        return "XL";
    else if (m_size == plazza::PizzaSize::XXL)
        return "XXL";
    return "NONE";
}
