/*
** EPITECH PROJECT, 2021
** Mutex exception
** File description:
** MutexException
*/

#ifndef MUTEXEXCEPTION_HPP_
#define MUTEXEXCEPTION_HPP_

#include <string>

namespace plazza {
    class MutexException : public std::exception {
        public:
            MutexException() = default;
            MutexException(const MutexException &other) = delete;
            MutexException(MutexException &&b) noexcept = default;
            MutexException(const std::string &error_message);

            ~MutexException() = default;

            MutexException &operator=(MutexException const& rhs) noexcept = delete;
            MutexException &operator=(MutexException &&rhs) noexcept = default;

            const char *what() const noexcept;

        protected:
        private:
            std::string m_error_message;
    };
}

#endif /* !MUTEXEXCEPTION_HPP_ */
