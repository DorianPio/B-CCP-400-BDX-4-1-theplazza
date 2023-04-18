/*
** EPITECH PROJECT, 2021
** shell
** File description:
** Shell
*/

#ifndef SHELL_HPP_
#define SHELL_HPP_

namespace plazza {
    class IShell {
        public:
            ~IShell() = default;

            virtual int shellLoop() = 0;

        protected:
            virtual void getInput() = 0;
            virtual void displayPrompt() const = 0;
            virtual int parseCommand() = 0;
        private:
    };
}

#endif /* !SHELL_HPP_ */