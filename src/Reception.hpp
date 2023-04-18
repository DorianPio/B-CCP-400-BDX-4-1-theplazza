/*
** EPITECH PROJECT, 2021
** B-CCP-400-BDX-4-1-theplazza-camille.grandjean
** File description:
** Reception
*/

#pragma once

#include <vector>
#include <list>
#include "process.hpp"
#include "struct_command.hpp"
#include "NamedPipe.hpp"
#include "Command.hpp"
#include <map>

namespace plazza
{
    class Reception {
        public:
            Reception() noexcept = default;
            Reception(const Reception &other) = delete;
            Reception(Reception &&b) noexcept = default;
            Reception(int numberCook, int timeCook, int multiplier) noexcept;

            ~Reception() = default;

            Reception &operator=(Reception const& rhs) noexcept = delete;
            Reception &operator=(Reception &&rhs) noexcept = default;

            void createProcess(int numberCook) noexcept;
            size_t getSize(std::vector<command_t> command) noexcept;
            void initAll();
            void processDispatch(plazza::Command &shell);
            int getAllFreeSpace() noexcept;
            void display_status() noexcept;
            void removeProcessInfo(int i);
            void forceKill();

        protected:
        private:
            int m_nb_kitchen_created;
            std::list<plazza::Process> m_proccess;
            int m_numberCook;
            int m_maxNumberCook;
            int m_multiplier;
            int m_timeCook;
            std::vector<NamedPipe> m_fd;
            std::vector<int> m_nbCook;
            bool m_sendCook;
            std::map<int, int> nb_places;
    };
}

int makeChildProcess(plazza::Kitchens &&toAdd, plazza::NamedPipe &pipe);
std::string getSizePizza(plazza::PizzaSize size);