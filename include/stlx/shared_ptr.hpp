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

protected:
    T* _ptr;

    inline void _cleanup() {
        if (_ptr != nullptr) {
            (_ptr->_strong_reference_count)--;
            if (_ptr->_strong_reference_count == 0) {
                delete _ptr;
                _ptr = nullptr;
            }
        }
    }

public:
    shared_ptr() : _ptr(nullptr) {}

    shared_ptr(T* ptr) : _ptr(ptr) {}

    // copy constructor
    template<typename T2>
    shared_ptr(const shared_ptr<T2>& other) {
//        static_assert(std::is_base_of<T, T2>::value, "Will not copy pointer of different types, unless from derived type to base type.");

        _ptr = other._ptr;
        if (other._ptr != nullptr)
            (_ptr->_strong_reference_count)++;
    }

    // copy assignment
    template<typename T2>
    shared_ptr& operator=(const shared_ptr<T2>& other) {
//        static_assert(std::is_base_of<T, T2>::value, "Will not copy-assign pointer of different types, unless from derived type to base type.");

        _cleanup();
        _ptr = other._ptr;
        if (other._ptr != nullptr)
            (other._ptr->_strong_reference_count)++;
        return *this;
    }

    // move constructor
    template<typename T2>
    shared_ptr(shared_ptr<T2>&& dying_other) {
//        static_assert(std::is_base_of<T, T2>::value, "Will not move pointer of different types, unless from derived type to base type.");

        _ptr = dying_other._ptr;
        dying_other._ptr = nullptr;
    }

    // move assignement
    template<typename T2>
    shared_ptr& operator=(shared_ptr<T2>&& dying_other) {
//        static_assert(std::is_base_of<T, T2>::value, "Will not move-assign pointer of different types, unless from derived type to base type.");

        _cleanup();
        _ptr = dying_other._ptr;
        dying_other._ptr = nullptr;
        return *this;
    }

    // destructor
    ~shared_ptr() {
        _cleanup();
    }

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
        return _ptr->_strong_reference_count;
    }
};


template<typename T, typename U>
bool operator==(const share_ptr<T>& lhs, const share_ptr<U>& rhs) noexcept {
    return lhs.get() == rhs.get();
}

template<class T>
bool operator==(const std::shared_ptr<T>& lhs, std::nullptr_t) noexcept {
    return lhs.get() == nullptr;
}


template<typename T, typename ... Args>
inline shared_ptr<T> make_shared(Args&& ... args) {
    return new T(std::forward<Args>(args)...);
}

}  // namespace tlex