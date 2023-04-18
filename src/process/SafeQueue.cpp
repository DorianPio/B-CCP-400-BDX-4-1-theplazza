/*
** EPITECH PROJECT, 2021
** safequeue
** File description:
** SafeQueue
*/

#include "SafeQueue.hpp"
#include <iostream>

plazza::SafeQueue::SafeQueue():
    m_mutex(),
    m_cond()
{
}

bool plazza::SafeQueue::empty()
{
    return m_queue.empty();
}

void plazza::SafeQueue::pop()
{
    m_queue.pop();
}

void plazza::SafeQueue::push(plazza::Pizza pizza)
{
    std::unique_lock<std::mutex> mlock(m_mutex);
    m_queue.push(pizza);
    m_cond.notify_one();
}

size_t plazza::SafeQueue::size()
{
    std::unique_lock<std::mutex> mlock(m_mutex);
    return m_queue.size();
}

plazza::Pizza plazza::SafeQueue::front()
{
    std::unique_lock<std::mutex> mlock(m_mutex);
    while (m_queue.empty()) {
        m_cond.wait(mlock);
    }
    plazza::Pizza pizza = m_queue.front();
    pop();
    return pizza;
}

void plazza::SafeQueue::display() noexcept
{
    if (m_queue.size() == 0)
        std::cout << "safequeue empty" << std::endl;
    for (size_t i = 0; i < m_queue.size(); i++) {
        plazza::Pizza pizza = m_queue.front();
        m_queue.pop();
        std::cout << pizza.getName() << " " << pizza.getSize() << std::endl;
        m_queue.push(pizza);
    }
}

std::string plazza::SafeQueue::getStatusQueue() noexcept
{
    std::string status = "";

    if (m_queue.size() == 0)
        status += "\tSafequeue empty\n";
    for (size_t i = 0; i < m_queue.size(); i++) {
        plazza::Pizza pizza = m_queue.front();
        m_queue.pop();
        status += "\t" + pizza.getName() + " " + pizza.getStringSize() + "\n";
        m_queue.push(pizza);
    }
    return status;
}