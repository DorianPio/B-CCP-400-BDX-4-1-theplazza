/*
** EPITECH PROJECT, 2021
** B-CCP-400-BDX-4-1-theplazza-camille.grandjean
** File description:
** process
*/

#pragma once

#include <functional>
#include "Kitchens.hpp"
#include "NamedPipe.hpp"


namespace plazza
{
    class Process {
        public:
            Process() = default;
            Process(const Process &other) = delete;
            Process(Process &&b) noexcept = default;
            Process(int numberCook, int timeCook, std::function<int(plazza::Kitchens &&toAdd, NamedPipe &pipe)> function, NamedPipe &pipe, int multiplier);
            ~Process() = default;

            Process &operator=(Process const& rhs) noexcept = delete;
            Process &operator=(Process &&rhs) noexcept = default;

            pid_t getPid();
        protected:
        private:
            pid_t m_pid;
            int pid_comment;
    };
}