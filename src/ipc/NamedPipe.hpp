/*
** EPITECH PROJECT, 2021
** B-CCP-400-BDX-4-1-theplazza-camille.grandjean
** File description:
** NamedPipe
*/

#include <linux/limits.h>
#include <iostream>
#include <memory>
#include <string.h>
#include <sys/msg.h>

#ifndef NamedPipe_HPP_
#define NamedPipe_HPP_

#define KEY 1234

namespace plazza {
    class NamedPipe {
        public:
            typedef struct messageC
            {
                long type;
                char text[PATH_MAX];
            } msg;
            NamedPipe(int file);
            NamedPipe(const NamedPipe &other) = default;
            NamedPipe(NamedPipe &&b) noexcept = default;

            ~NamedPipe() = default;

            NamedPipe &operator=(NamedPipe const& rhs) noexcept = default;
            NamedPipe &operator=(NamedPipe &&rhs) = default;
            int get_fd() const noexcept;
            std::string getNameNP() const noexcept;

            void closeFd();
        protected:
        private:
            int m_fd;
            std::string m_name;
    };
}

std::string &operator<<(std::string &string, plazza::NamedPipe &rhs);
void operator>>(std::string &string, plazza::NamedPipe &rhs);

#endif /* !NamedPipe_HPP_ */

