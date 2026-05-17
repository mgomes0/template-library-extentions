#pragma once

#include <atomic>
#include <cstdint>
#include <type_traits>
#include <utility>


namespace stlx {

/// forward declarations
class instrument_for_shared_ptr;
template<typename T> class shared_ptr;


/// declarations
class instrument_for_shared_ptr {
template<typename T> friend class shared_ptr;

protected:
    std::atomic<std::uint64_t> _strong_reference_count;
//    std::atomic<std::uint64_t> _weak_reference_count;

public:
    instrument_for_shared_ptr() : _strong_reference_count(1) {}

//    std::uint64_t use_count() const noexcept {
//        return _strong_reference_count.load();
//    }
};


template<typename T>
class shared_ptr {

static_assert(
    std::is_base_of<instrument_for_shared_ptr, T>::value,
    "Cannot use `stlx::shared_ptr<T>` unless `T` inherits from `stlx::instrument_for_shared_ptr`"
);

template<typename U>
friend class shared_ptr;

protected:
    T* _ptr;

    void _cleanup() {
        if (_ptr != nullptr) {
            (_ptr->_strong_reference_count)--;
            if (_ptr->_strong_reference_count == 0) {
                delete _ptr;
                _ptr = nullptr;
            }
        }
    }

public:
    shared_ptr() : _ptr(nullptr) { std::cout << "DEFAULT CONSTRUCTOR\n"; }

    shared_ptr(T* ptr) : _ptr(ptr) { std::cout << "RAW CONSTRUCTOR\n"; }

    // -------- COPY CONSTRUCTORS ----------------
    shared_ptr(const shared_ptr& other) {
        std::cout << "COPY CONSTRUCTOR\n";
        _ptr = other._ptr;
        if (other._ptr != nullptr)
            (_ptr->_strong_reference_count)++;
    }

    template<typename U>
    shared_ptr(const shared_ptr<U>& other) {
        std::cout << "COPY TEMPLATE CONSTRUCTOR\n";
        _ptr = other._ptr;
        if (other._ptr != nullptr)
            (_ptr->_strong_reference_count)++;
    }

    // -------- COPY ASSIGNMENT ----------------
    shared_ptr& operator=(const shared_ptr& other) {
        std::cout << "COPY ASSIGNMENT\n";
        if (_ptr == other._ptr)
            return *this;

        _cleanup();
        _ptr = other._ptr;
        if (other._ptr != nullptr)
            (other._ptr->_strong_reference_count)++;
        return *this;
    }

    template<typename U>
    shared_ptr& operator=(const shared_ptr<U>& other) {
        std::cout << "COPY TEMPLATE ASSIGNMENT\n";
        _cleanup();
        _ptr = other._ptr;
        if (other._ptr != nullptr)
            (other._ptr->_strong_reference_count)++;
        return *this;
    }

    // -------- MOVE CONSTRUCTOR ----------------
    shared_ptr(shared_ptr&& dying_other) {
        std::cout << "MOVE CONSTRUCTOR\n";
        _ptr = dying_other._ptr;
        dying_other._ptr = nullptr;
    }

    template<typename U>
    shared_ptr(shared_ptr<U>&& dying_other) {
        std::cout << "MOVE TEMPLATE CONSTRUCTOR\n";
        _ptr = dying_other._ptr;
        dying_other._ptr = nullptr;
    }

    // -------- MOVE ASSIGNMENT ----------------
    template<typename U>
    shared_ptr& operator=(shared_ptr<U>&& dying_other) {
        std::cout << "MOVE ASSIGNMENT\n";
        _cleanup();
        _ptr = dying_other._ptr;
        dying_other._ptr = nullptr;
        return *this;
    }

    // -------- DESTRUCTOR ----------------
    ~shared_ptr() {
        std::cout << "DESTRUCTOR\n";
        _cleanup();
    }

//    template<typename U>
//    operator shared_ptr<U>() const {
//        return _ptr;
//    }

    T* operator->() const {
        return _ptr;
    }

    T& operator*() const {
        return *_ptr;
    }

    T* get() const {
        return _ptr;
    }

    std::uint64_t use_count() const noexcept {
        if (_ptr)
            return _ptr->_strong_reference_count.load();
        else
            return 0;
    }
};


template<typename T, typename ... Args>
shared_ptr<T> make_shared(Args&& ... args) {
    return new T(std::forward<Args>(args)...);
}


#define BINARY_OPERATOR(op)\
    template<typename T>\
    bool operator op(const shared_ptr<T>& lhs, const shared_ptr<T>& rhs) noexcept {\
        return lhs.get() op rhs.get();\
    }\
    \
    template<typename T>\
    bool operator op(const shared_ptr<T>& lhs, std::nullptr_t) noexcept {\
        return lhs.get() op nullptr;\
    }\
    \
    template<typename T>\
    bool operator op(std::nullptr_t, const shared_ptr<T>& rhs) noexcept {\
        return nullptr op rhs.get();\
    }

BINARY_OPERATOR(==)
BINARY_OPERATOR(!=)
BINARY_OPERATOR(<=)
BINARY_OPERATOR(< )
BINARY_OPERATOR(>=)
BINARY_OPERATOR(> )



}  // namespace stlx