#pragma once

#include <utility>

namespace stlx {

template <typename T>
class unique_ptr {
public:
    using element_type = T;
    using pointer      = T*;

    // ── Construction / destruction ──────────────────────────────────────────
    constexpr unique_ptr() noexcept;
    constexpr explicit unique_ptr(pointer p) noexcept;
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr(unique_ptr&& other) noexcept;
    ~unique_ptr();

    // ── Assignment ──────────────────────────────────────────────────────────
    unique_ptr& operator=(const unique_ptr&) = delete;
    unique_ptr& operator=(unique_ptr&& other) noexcept;
    unique_ptr& operator=(std::nullptr_t) noexcept;

    // ── Observers ───────────────────────────────────────────────────────────
    pointer   get()              const noexcept;
    explicit  operator bool()    const noexcept;
    element_type& operator*()    const noexcept;
    pointer       operator->()   const noexcept;

    // ── Modifiers ───────────────────────────────────────────────────────────
    pointer release()            noexcept;
    void    reset(pointer p = nullptr) noexcept;
    void    swap(unique_ptr& other)    noexcept;

private:
    pointer ptr_ = nullptr;
};

// ── Non-member utilities ─────────────────────────────────────────────────────
template <typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args);

template <typename T>
void swap(unique_ptr<T>& lhs, unique_ptr<T>& rhs) noexcept;

template <typename T>
bool operator==(const unique_ptr<T>& lhs, std::nullptr_t) noexcept;

template <typename T>
bool operator==(std::nullptr_t, const unique_ptr<T>& rhs) noexcept;

template <typename T>
bool operator!=(const unique_ptr<T>& lhs, std::nullptr_t) noexcept;

template <typename T>
bool operator!=(std::nullptr_t, const unique_ptr<T>& rhs) noexcept;

} // namespace tlex
