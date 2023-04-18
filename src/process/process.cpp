/*
** EPITECH PROJECT, 2021
** B-CCP-400-BDX-4-1-theplazza-camille.grandjean
** File description:
** process
*/

#include "process.hpp"
#include <iostream>
#include <sys/types.h>

plazza::Process::Process(int numberCook, int timeCook, std::function<int(plazza::Kitchens &&toAdd, NamedPipe &pipe)> function, plazza::NamedPipe &pipe, int multiplier)
{
    m_pid = fork();

    if (m_pid == -1)
        throw std::runtime_error("Fork failed");
    else if (m_pid == 0) {
        function(plazza::Kitchens(numberCook, timeCook, multiplier), pipe);
        exit(0);
    }
}

pid_t plazza::Process::getPid()
{
    return m_pid;
}