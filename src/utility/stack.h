#ifndef STACK_H
#define STACK_H

#include <utility>

template<class T, size_t SIZE>
class Stack
{
public:
    Stack() noexcept(std::is_pod_v<T>) = default;

    T &operator[] (size_t idx) noexcept
    {
        return _stack[idx];
    }

    const T &operator[] (size_t idx) const noexcept
    {
        return _stack[idx];
    }

    T *begin() noexcept
    {
        return empty() ? nullptr : _stack;
    }

    T *end() noexcept
    {
        return empty() ? nullptr : &_stack[_next];
    }

    void push(const T &value) noexcept(std::is_pod_v<T>)    // you must check haveSpace() every time
    {
        _stack[_next++] = value;
    }

    void push(T &&value) noexcept(std::is_pod_v<T>)         // you must check haveSpace() every time
    {
        _stack[_next++] = std::forward<T>(value);
    }

    T &take() noexcept                                      // you must check empty() every time
    {
        return _stack[--_next];
    }

    void pop() noexcept                                     // you must check empty() every time
    {
        --_next;
    }

    T &top() noexcept                                       // you must check empty() every time
    {
        return _stack[_next - 1];
    }

    bool haveSpace() const noexcept
    {
        return _next < SIZE;
    }

    bool empty() const noexcept
    {
        return not _next;
    }

    size_t size() const noexcept
    {
        return _next;
    }

private:
    T _stack[SIZE];
    size_t _next = 0;
};

#endif // STACK_H
