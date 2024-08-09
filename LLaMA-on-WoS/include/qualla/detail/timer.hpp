// Copyright 2023 Qualcomm Technologies, Inc. All rights reserved.
// Confidential & Proprietary - Qualcomm Technologies, Inc. ("QTI")

#ifndef QUALLA_DETAIL_TIMER_HPP
#define QUALLA_DETAIL_TIMER_HPP

#include <chrono>
#include <string>
#include <atomic>

namespace qualla {

template <typename C = std::chrono::steady_clock, typename T = std::chrono::time_point<C>>
class Timer {
  public:
    Timer() { reset(); }

    void reset() { _t = C::now(); }

    T get() const { return _t; }

    uint64_t nsec() const {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(_t.time_since_epoch()).count();
    }

    uint64_t usec() const {
        return std::chrono::duration_cast<std::chrono::microseconds>(_t.time_since_epoch()).count();
    }

    uint64_t elapsed_nsec() const {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(C::now() - _t).count();
    }

    uint64_t elapsed_usec() const {
        return std::chrono::duration_cast<std::chrono::microseconds>(C::now() - _t).count();
    }

    float elapsed_msec() const { return elapsed_usec() / 1000.0; }

  private:
    T _t;
};

} // namespace qualla

#endif // QUALLA_DETAIL_TIMER_HPP
