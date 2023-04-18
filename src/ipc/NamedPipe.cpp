/*
** EPITECH PROJECT, 2021
** B-CCP-400-BDX-4-1-theplazza-camille.grandjean
** File description:
** NamedPipe
*/

#include "NamedPipe.hpp"
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <mqueue.h>
#include <unistd.h>

plazza::NamedPipe::NamedPipe(int file):
    m_fd(-1)
{
    m_name = std::to_string(file);
    std::string path = "./" + m_name;
    int test = mkfifo(path.c_str(), 0666);
    int fd = open(path.c_str(), O_RDWR, O_NONBLOCK, O_NDELAY);

    if (test == -1 || fd == -1)
        throw std::runtime_error("NamedPipe failed\n");
    m_fd = fd;
}

void plazza::NamedPipe::closeFd()
{
    close(m_fd);
}

std::string &operator<<(std::string &string, plazza::NamedPipe &other)
{
    usleep(100000);
    int m = 0;

    string.resize(4096);
    m = read(other.get_fd() , &string[0], 4096);
    if (m > 0)
        string.resize(m);
    else
        string = "";
    return string;
}

void operator>>(std::string &to_send, plazza::NamedPipe &other)
{
    usleep(100000);
    int result = write(other.get_fd(), to_send.c_str(), to_send.length());

    if (result == -1)
        throw std::runtime_error("Write failed\n");
}

int plazza::NamedPipe::get_fd() const noexcept
{
    return m_fd;
}

std::string plazza::NamedPipe::getNameNP() const noexcept
{
    return m_name;
}