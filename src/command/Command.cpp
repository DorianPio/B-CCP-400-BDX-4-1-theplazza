/*
** EPITECH PROJECT, 2021
** COmmand
** File description:
** Command
*/

#include <fstream>
#include <iostream>
#include "Command.hpp"
#include <algorithm>
#include "Kitchens.hpp"
#define HELP "Help:\n\tstatus\n\tquit\n\t<pizza> <size> <quantity>\n\thelp"

plazza::Command::Command():
    m_status(true),
    m_status_cmd(false)
{
}

void plazza::Command::getInput()
{
    std::cin.sync_with_stdio(false);
    if (std::cin.rdbuf()->in_avail() == 0) {
        m_input = "";
    } else if (std::cin.rdbuf()->in_avail() > 0)
        std::getline(std::cin, m_input);
}

void plazza::Command::displayPrompt() const
{
    std::cout << "$> " << std::flush;
}

int plazza::Command::helpCommand() const
{
    std::cout << HELP << std::endl;
    return 200;
}

std::vector<command_t> plazza::Command::getQueue()
{
    return m_queue;
}

enum plazza::PizzaSize plazza::Command::getSize(std::string size) const
{
    try {
        if (size == "s")
            return S;
        else if (size == "m")
            return M;
        else if (size == "l")
            return L;
        else if (size == "xl")
            return XL;
        else if (size == "xxl")
            return XXL;
        throw std::runtime_error("Error size pizza must be S, M, L, XL or XXL");
    } catch(const std::runtime_error& e) {
            std::cerr << e.what() << "\n";
    }
    return NONE;
}

int plazza::Command::checkPizza(std::string input)
{
    std::string save = input;
    std::string type;
    std::string size;
    std::string tmp;
    enum plazza::PizzaSize sizePizza;
    int multiplier = 0;
    int nb_spaces = 0;

    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    save = input;
    for (long unsigned int i = 0; i < input.length(); i++) {
        if (input[i] == ' ' && input[i - 1] != ' ') {
            nb_spaces++;
        }
    }
    if (nb_spaces < 2) {
        std::cout << "Invalid command\n";
            return 84;
    }
    if (input.find(";") == std::string::npos) {
        if (save.find("regina") != std::string::npos) {
            type = "regina";
            save = &save[7];
        } else if (save.find("margarita") != std::string::npos) {
            save = &save[10];
            type = "margarita";
        } else if (save.find("americana") != std::string::npos) {
            save = &save[10];
            type = "americana";
        } else if (save.find("fantasia") != std::string::npos) {
            save = &save[9];
            type = "fantasia";
        } else {
            std::cout << "Invalid command\n";
            return 84;
        }
        tmp = save;
        size = tmp.erase(save.find(" "));
        sizePizza = getSize(size);
        multiplier = atoi(&save[tmp.size() + 2]);
        if (sizePizza == NONE)
            return 84;
        if (multiplier == 0) {
            std::cout << "Invalid number of pizza\n";
            return 84;
        }
        while (multiplier > 0) {
            command_t result;
            result.m_size = sizePizza;
            result.m_type = type;
            m_queue.push_back(result);
            multiplier--;
        }
    }
    return 0;
}

int plazza::Command::quitCommand()
{
    std::cout << "Bye bye bro :)\n";
    m_status = false;
    return 200;
}

int plazza::Command::statusCommand()
{
    m_status_cmd = true;
    return 200;
}

int plazza::Command::parsePizza()
{
    std::string pizza;
    size_t findP = 0;
    bool quit = false;

    if (m_input.find(";") != std::string::npos) {
        while (m_input.size() > 0) {
            pizza = m_input;
            findP = pizza.find(";");
            if (findP != std::string::npos) {
                pizza = pizza.erase(findP);
                if (pizza[pizza.size() - 1] == ' ') {
                    pizza.erase(pizza.size() - 1);
                }
                m_input = &m_input[findP + 1];
            }
            return checkPizza(pizza);
            while (m_input[0] == ' ') {
                m_input = &m_input[1];
            }
            if (quit)
                break;
            if (m_input.find(";") == std::string::npos)
                quit = true;
        }
    } else {
       return checkPizza(m_input);
    }
    return 0;
}

int plazza::Command::parseCommand()
{
    if (m_input.find("help") != std::string::npos) {
        return helpCommand();
    } else if (m_input.find("status") != std::string::npos) {
        return statusCommand();
    } else if (m_input.find("quit") != std::string::npos) {
        return quitCommand();
    } else {
        return parsePizza();
    }
    return 0;
}

int plazza::Command::shellLoop()
{
    getInput();
    if (m_input.compare("") == 0)
        return 111;
    displayPrompt();
    return parseCommand();
}

void plazza::Command::deleteCommand() noexcept
{
    if (m_queue.size() <= 0)
        return;
    auto i = m_queue.begin();
    m_queue.erase(i);
}

bool plazza::Command::getStatusCmd() const noexcept
{
    return m_status_cmd;
}

void plazza::Command::setStatusCmd() noexcept
{
    m_status_cmd = !m_status_cmd;
}