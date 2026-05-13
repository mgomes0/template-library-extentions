#pragma once

#include <cstddef>

namespace tlex {

template <typename T>
class vector {
public:
    using value_type      = T;
    using size_type       = std::size_t;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using pointer         = value_type*;
    using const_pointer   = const value_type*;

    // ── Construction / destruction ──────────────────────────────────────────
    vector();
    explicit vector(size_type count);
    vector(size_type count, const T& value);
    vector(const vector& other);
    vector(vector&& other) noexcept;
    ~vector();

    // ── Assignment ──────────────────────────────────────────────────────────
    vector& operator=(const vector& other);
    vector& operator=(vector&& other) noexcept;

    // ── Element access ──────────────────────────────────────────────────────
    reference       operator[](size_type pos);
    const_reference operator[](size_type pos) const;
    reference       at(size_type pos);
    const_reference at(size_type pos) const;
    reference       front();
    const_reference front() const;
    reference       back();
    const_reference back() const;
    pointer         data() noexcept;
    const_pointer   data() const noexcept;

    // ── Capacity ────────────────────────────────────────────────────────────
    bool      empty()    const noexcept;
    size_type size()     const noexcept;
    size_type capacity() const noexcept;
    void      reserve(size_type new_cap);
    void      shrink_to_fit();

    // ── Modifiers ───────────────────────────────────────────────────────────
    void clear() noexcept;
    void push_back(const T& value);
    void push_back(T&& value);
    template <typename... Args>
    reference emplace_back(Args&&... args);
    void pop_back();
    void resize(size_type count);
    void resize(size_type count, const T& value);

private:
    pointer   data_     = nullptr;
    size_type size_     = 0;
    size_type capacity_ = 0;
};

} // namespace tlex
