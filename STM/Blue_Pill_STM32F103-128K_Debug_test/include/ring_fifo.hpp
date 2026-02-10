// Simple fixed-size ring FIFO (header-only)
#pragma once

#include <cstddef>
#include <cstdint>

template<typename T, std::size_t N>
class RingFIFO {
    static_assert(N > 0, "Ring size must be > 0");
public:
    constexpr RingFIFO(): head(0), tail(0), count(0) {}

    bool push(const T &item) {
        if (full()) return false;
        buf[head] = item;
        head = (head + 1) % N;
        ++count;
        return true;
    }

    bool pop(T &out) {
        if (empty()) return false;
        out = buf[tail];
        tail = (tail + 1) % N;
        --count;
        return true;
    }

    bool empty() const { return count == 0; }
    bool full() const { return count == N; }
    std::size_t size() const { return count; }
    constexpr std::size_t capacity() const { return N; }
    void clear() { head = tail = count = 0; }

private:
    T buf[N];
    std::size_t head;
    std::size_t tail;
    std::size_t count;
};
