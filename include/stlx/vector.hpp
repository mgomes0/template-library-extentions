#pragma once

#include <cstddef>
#include <memory>
#include <type_traits>

namespace stlx {


namespace detail {

struct empty_t {};

}  // namespace detail


template <typename T, std::size_t stack_size = 0>
class vector {
protected:
    std::unique_ptr<T[]> _heap;
    std::size_t _size;
    std::size_t _alloc_size;
    T* _last;
    std::array<T, stack_size> _stack;

public:
    vector() : _size(0), _alloc_size(0), _last(nullptr) {}

    void push_back(T&& item) {
        if (stack_size == 0 || _size > stack_size) {
            if (_size)
            _heap[_size - stack_size] = item;
        }
        else {
            _stack[_size] = item;
        }
    }

    void pop_back() {
        if (stack_size == 0 || _size > stack_size) {
            delete _heap[_size - stack_size];
            _size--;
        }
    }

    std::size_t size() const { return _size; }
};


}  // namespace tlex
