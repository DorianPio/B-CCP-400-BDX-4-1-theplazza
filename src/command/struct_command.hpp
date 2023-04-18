/*
** EPITECH PROJECT, 2021
** B-CCP-400-BDX-4-1-theplazza-camille.grandjean
** File description:
** struct_command
*/

#include <iostream>
#include "PizzaSize.hpp"

#ifndef STRUCT_COMMAND_HPP_
#define STRUCT_COMMAND_HPP_

typedef struct struct_command
{
    std::string m_type;
    enum plazza::PizzaSize m_size;
} command_t;

#endif /* !STRUCT_COMMAND_HPP_ */
