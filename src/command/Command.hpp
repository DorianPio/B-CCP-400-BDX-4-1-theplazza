/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** Command
*/

#pragma once

#include "IShell.hpp"
#include <iostream>
#include "PizzaSize.hpp"
#include "struct_command.hpp"
#include <vector>

namespace plazza {
    class Command: public IShell {
        public:
            Command();
            Command(const Command &other) = delete;
            Command(Command &&b) noexcept = default;

            ~Command() = default;

            Command &operator=(Command const& rhs) noexcept = delete;
            Command &operator=(Command &&rhs) noexcept = default;

            int shellLoop() override final;
            bool getStatus() { return m_status; };
            bool getStatusCmd() const noexcept;
            void setStatusCmd() noexcept;
            std::vector<command_t> getQueue();
            void deleteCommand() noexcept;
            void displayPrompt() const override final;
        protected:
            enum plazza::PizzaSize getSize(std::string size) const;
            int helpCommand() const;
            int quitCommand();
            int statusCommand();
            int parsePizza();
            int checkPizza(std::string input);
            void getInput() override final;
            int parseCommand() override final;

        private:
            bool m_status;
            bool m_status_cmd;
            std::string m_input;
            std::vector<command_t> m_queue;
    };
}
