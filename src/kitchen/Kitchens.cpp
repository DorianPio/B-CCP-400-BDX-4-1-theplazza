/*
** EPITECH PROJECT, 2021
** B-CCP-400-BDX-4-1-theplazza-camille.grandjean
** File description:
** Kitchens
*/

#include "Kitchens.hpp"
#include <iostream>
#include <thread>
#include <functional>
#include "PizzaRegina.hpp"
#include "PizzaFantasia.hpp"
#include "PizzaMargarita.hpp"
#include "PizzaAmericana.hpp"

plazza::Kitchens::Kitchens(int numberCook, int timerefill, int multiplier):
    m_nbcook(numberCook),
    m_timerefill(timerefill),
    m_multiplier(multiplier),
    m_safequeue(std::make_unique<SafeQueue>()),
    m_ingredients(std::make_unique<Ingredients>()),
    m_status(STOP),
    m_time_point_close(std::chrono::system_clock::now() + std::chrono::seconds(5)),
    m_time_point_refill(std::chrono::system_clock::now() + std::chrono::milliseconds(m_timerefill))
{
    for (int i = 0; i < numberCook; i++) {
        m_listOfCooks.emplace_back(m_multiplier, m_ingredients, m_safequeue);
    }
}

void plazza::Kitchens::addIngredients() noexcept
{
    m_ingredients->refill();
}

void plazza::Kitchens::addPizzaToQueue(std::string &string)
{
    m_status = START;
    std::string name = string.substr(0, string.find(" "));
    PizzaSize size = getEnumPizza(string.substr(string.find(" ") + 1, string.find("\n")));

    if (name.compare("regina") == 0) {
        m_safequeue->push(PizzaRegina(size));
    } else if (name.compare("americana") == 0) {
        m_safequeue->push(PizzaAmericana(size));
    } else if (name.compare("fantasia") == 0) {
        m_safequeue->push(PizzaFantasia(size));
    } else if (name.compare("margarita") == 0) {
        m_safequeue->push(PizzaMargarita(size));
    }
}

int plazza::Kitchens::getNbPlace() noexcept
{
    int nb_places = 0;

    for (plazza::Cook &cook : m_listOfCooks) {
        if (cook.getOccupied() == false)
            nb_places++;
    }
    nb_places += (m_nbcook - m_safequeue->size());
    return nb_places;
}

plazza::PizzaSize plazza::Kitchens::getEnumPizza(std::string size) const noexcept
{
    if (size == "S\n")
        return PizzaSize::S;
    else if (size == "M\n")
        return PizzaSize::M;
    else if (size == "L\n")
        return PizzaSize::L;
    else if (size == "XL\n")
        return PizzaSize::XL;
    else if (size == "XXL\n")
        return PizzaSize::XXL;
    return PizzaSize::NONE;
}

std::string plazza::Kitchens::prepareStatus() noexcept
{
    int cook_nb = 1;
    std::string status = "";

    status += "In creation :\n";
    for (plazza::Cook &cook : m_listOfCooks) {
        Pizza pizza = cook.getPizza();
        if (cook.getOccupied() == true) {
            status += "\tCook n°" + std::to_string(cook_nb) + " preparing : " + pizza.getName() + " " + pizza.getStringSize() + "\n";
        } else {
            status += "\tCook n°" + std::to_string(cook_nb) + " waiting order\n";
        }
        cook_nb += 1;
    }
    status += "In queue :\n";
    status += m_safequeue->getStatusQueue();
    status += "Ingredients :\n";
    status += m_ingredients->getStatusIngredients();
    return status;
}

void plazza::Kitchens::setStatus() noexcept
{
    if (m_status == STOP) {
        m_status = START;
    } else {
        m_status = STOP;
    }
}

plazza::Kitchens::status plazza::Kitchens::getStatus() const noexcept
{
    return m_status;
}

bool plazza::Kitchens::canClose() noexcept
{
    if (m_status == START) {
        if (getNbPlace() == m_nbcook * 2) {
            m_status = STOP;
            m_time_point_close = std::chrono::system_clock::now() + std::chrono::seconds(5);
        }
    } else if (m_status == STOP) {
        if (std::chrono::system_clock::now() > m_time_point_close)
            return true;
    }
    return false;
}

void plazza::Kitchens::refill() noexcept
{
    if (std::chrono::system_clock::now() > m_time_point_refill) {
        m_ingredients->refill();
        m_time_point_refill = std::chrono::system_clock::now() + std::chrono::milliseconds(m_timerefill);
    }
}