/*
** EPITECH PROJECT, 2021
** safequeue
** File description:
** SafeQueue
*/

#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include "Pizza.hpp"

namespace plazza
{
    class SafeQueue {
        public:
            SafeQueue();
            SafeQueue(SafeQueue &&b) noexcept = default;
            SafeQueue(const SafeQueue &other) = delete;

            ~SafeQueue() = default;

            SafeQueue &operator=(SafeQueue const& rhs) noexcept = delete;
            SafeQueue &operator=(SafeQueue &&rhs) noexcept = default;

            bool empty();
            void push(plazza::Pizza pizza);
            size_t size();
            plazza::Pizza front();
            void display() noexcept;
            std::string getStatusQueue() noexcept;
        protected:
            void pop();
        private:
            std::queue<plazza::Pizza> m_queue;
            std::mutex m_mutex;
            std::condition_variable m_cond;
    };
}
