/*
** EPITECH PROJECT, 2021
** B-CCP-400-BDX-4-1-theplazza-camille.grandjean
** File description:
** Reception
*/

#include "Reception.hpp"
#include "Command.hpp"
#include <functional>
#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/wait.h>

plazza::Reception::Reception(int numberCook, int timeCook, int multiplier) noexcept :
    m_nb_kitchen_created(0),
    m_numberCook(numberCook),
    m_maxNumberCook(numberCook),
    m_multiplier(multiplier),
    m_timeCook(timeCook),
    m_sendCook(true)
{
}

void plazza::Reception::createProcess(int number_kitchen) noexcept
{
    std::function<int(plazza::Kitchens &&toAdd, NamedPipe &pipe)> function = makeChildProcess;

    try {
        for (int i = 0; i < number_kitchen; i++) {
            m_fd.emplace_back(m_nb_kitchen_created);
            m_proccess.emplace_back(m_maxNumberCook, m_timeCook, function, m_fd.back(), m_multiplier);
            m_nb_kitchen_created += 1;
        }
    } catch (std::exception &e) {
        std::cerr << "error " << e.what() << std::endl;
    }
}

void plazza::Reception::processDispatch(plazza::Command &shell)
{
    std::string receive = "";
    std::string nb_cook = "nb_cook";
    std::string none = "none";
    std::string send_command = "";
    for (size_t i = 0; i < m_fd.size(); i++) {
        nb_cook >> m_fd[i];
        receive << m_fd[i];
        int nb_places = atoi(receive.c_str());
        for (int j = 0; j < nb_places; j++) {
            if (shell.getQueue().empty()) {
                if (j > 0) {
                    none >> m_fd[i];
                }
                break;
            }
            send_command = shell.getQueue()[0].m_type + " " + getSizePizza(shell.getQueue()[0].m_size);
            send_command >> m_fd[i];
            shell.deleteCommand();
        }
    }
}

void plazza::Reception::initAll()
{
    std::string finish = "finish";
    std::string finished = "";
    plazza::Command shell;
    std::vector<command_t> command;
    size_t size = 0;
    int nb_cuisine = 0;
    int result = 0;
    size_t cooksfree = 0;

    shell.displayPrompt();
    while (shell.getStatus()) {
        result = shell.shellLoop();
        if (result != 111) {
            if (shell.getStatusCmd()) {
                display_status();
                shell.displayPrompt();
                shell.setStatusCmd();
            } else {
                command = shell.getQueue();
                cooksfree = getAllFreeSpace();
                size = getSize(command);
                if (cooksfree > size) {
                    if (result == 0) {
                        processDispatch(shell);
                    }
                } else {
                    size = size - cooksfree;
                    nb_cuisine = size / (m_maxNumberCook * 2);
                    if (size % (m_maxNumberCook * 2) != 0)
                        nb_cuisine += 1;
                    if (result == 0) {
                        createProcess(nb_cuisine);
                        processDispatch(shell);
                    }
                }
            }
        }
        for (size_t i = 0; i < m_fd.size();) {
            finish >> m_fd[i];
            finished << m_fd[i];
            if (finished.compare("yes") == 0) {
                removeProcessInfo(i);
            } else {
                i++;
            }
        }
    }
    forceKill();
}

void plazza::Reception::forceKill()
{
    std::string command = "rm ";
    std::string name = "";

    for (auto it = m_fd.begin(); it != m_fd.end();) {
        name = it->getNameNP();
        std::cout << "Kitchen n°" <<it->getNameNP() << " closed" << std::endl;
        it->closeFd();
        command += name;
        system(command.c_str());
        command = "rm ";
        it = m_fd.erase(it);
    }
    while (!m_proccess.empty()) {
        kill(m_proccess.begin()->getPid(), SIGKILL);
        waitpid(m_proccess.begin()->getPid(), 0, WNOHANG);
        m_proccess.erase(m_proccess.begin());
    }
}

void plazza::Reception::removeProcessInfo(int index)
{
    std::string command = "rm ";
    std::string name = "";
    int i = 0;

    for (auto it = m_fd.begin(); it != m_fd.end(); it++) {
        if (i == index) {
            name = it->getNameNP();
            std::cout << "Kitchen n°" << name << " closed\n$> " << std::flush;
            it->closeFd();
            command += name;
            system(command.c_str());
            m_fd.erase(it);
            break;
        } else {
            i++;
        }
    }
    i = 0;
    for (auto it = m_proccess.begin(); it != m_proccess.end(); it++) {
        if (i == index) {
            kill(it->getPid(), SIGKILL);
            waitpid(it->getPid(), 0, WNOHANG);
            m_proccess.erase(it);
            break;
        } else {
            i++;
        }
    }
}

size_t plazza::Reception::getSize(std::vector<command_t> command) noexcept
{
    return command.size();
}

std::string getSizePizza(plazza::PizzaSize size)
{
    if (size == plazza::PizzaSize::S)
        return "S\n";
    else if (size == plazza::PizzaSize::M)
        return "M\n";
    else if (size == plazza::PizzaSize::L)
        return "L\n";
    else if (size == plazza::PizzaSize::XL)
        return "XL\n";
    else if (size == plazza::PizzaSize::XXL)
        return "XXL\n";
    return "NONE\n";
}

int plazza::Reception::getAllFreeSpace() noexcept
{
    int total = 0;
    std::string receive = "";
    std::string to_send = "nb_cook";

    for (size_t i = 0; i < m_fd.size(); i++) {
        to_send >> m_fd[i];
        receive << m_fd[i];
        total += atoi(receive.c_str());
    }
    return total;
}

void plazza::Reception::display_status() noexcept
{
    std::string receive = "";
    std::string status_final = "";
    std::string to_send = "status";

    if (m_fd.size() == 0) {
        std::cout << "0 kitchen started" << std::endl;
    } else {
        for (size_t i = 0; i < m_fd.size(); i++) {
            status_final += "Kitchen n°" + std::to_string(i + 1) + "\n";
            to_send >> m_fd[i];
            receive << m_fd[i];
            status_final += receive + "\n";
        }
        std::cout << status_final << std::flush;
    }
}