/*
** EPITECH PROJECT, 2021
** mutex exception
** File description:
** MutexException
*/

#include "MutexException.hpp"

plazza::MutexException::MutexException(const std::string &error_message):
    m_error_message(error_message)
{
}

const char *plazza::MutexException::what() const noexcept
{
    return m_error_message.c_str();
}