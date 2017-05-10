#ifndef _TIME_RATIO_
#define _TIME_RATIO_

#include "time_details.h"
#include "date_time.h"

namespace temporal
{

enum class since
{
    epoch,
    julian // add to std::duration seconds since julian year 0 to 1970
};

namespace details
{

template< time_type tick_cnt, time_type sec_period >
class time_ratio final
{
    using curr_std_duration_type = std::chrono::duration<
    typename std::conditional< ( sec_period > tick_cnt ), int, int64_t >::type,
    std::ratio< sec_period, tick_cnt > >;

    using curr_time_ratio = time_ratio< tick_cnt, sec_period >;
    template< time_type, time_type > friend class time_ratio;

    template< time_type ltk, time_type lp, time_type rtk, time_type rp >
    constexpr time_ratio< ltk, lp >
    friend operator+( const time_ratio< ltk, lp >& l, const time_ratio< rtk, rp >& r ) noexcept;

    template< time_type ltk, time_type lp, time_type rtk, time_type rp >
    constexpr time_ratio< ltk, lp >
    friend operator-( const time_ratio< ltk, lp >& l, const time_ratio< rtk, rp >& r ) noexcept;

public:
    // ctors
    constexpr time_ratio() = default;
    constexpr explicit time_ratio( time_type count ) noexcept;
    constexpr explicit time_ratio( const time_moment& tm ) noexcept;
    constexpr explicit time_ratio( const date_time& dt ) noexcept;

    constexpr explicit time_ratio( const timeval& tv ) noexcept;
    constexpr explicit time_ratio( const timespec& ts ) noexcept;

    template< typename std_duration_type, typename = enable_if_std_duration< std_duration_type > >
    constexpr explicit time_ratio( const std_duration_type& duration, const since& start_point ) noexcept;

    template< time_type other_tick_cnt, time_type other_sec_period >
    constexpr time_ratio( const time_ratio< other_tick_cnt, other_sec_period >& other ) noexcept;

    template< time_type other_tick_cnt, time_type other_sec_period >
    constexpr time_ratio( time_ratio< other_tick_cnt, other_sec_period >&& other ) noexcept;

    // assignment
    time_ratio& operator=( time_type count ) noexcept;
    time_ratio& operator=( const time_moment& tm ) noexcept;
    time_ratio& operator=( const date_time& dt ) noexcept;

    template< time_type other_tick_cnt, time_type other_sec_period >
    time_ratio& operator=( const time_ratio< other_tick_cnt, other_sec_period >& other ) noexcept;

    template< time_type other_tick_cnt, time_type other_sec_period >
    time_ratio& operator=( time_ratio< other_tick_cnt, other_sec_period >&& other ) noexcept;

    // conversions from
    void from_time_t( time_t time ) noexcept;
    void from_timeval( const timeval& time ) noexcept;
    void from_timespec( const timespec& time ) noexcept;

    template< typename std_duration_type, typename = enable_if_std_duration< std_duration_type > >
    void from_std_duration( const std_duration_type& duration, const since& start_point ) noexcept;

    // returns curr_time_ratio class initialized with the current time since julian day 0
    static curr_time_ratio now() noexcept;

    // conversions to
    constexpr time_t to_time_t() const noexcept;
    constexpr timeval to_timeval() const noexcept;
    constexpr timespec to_timespec() const noexcept;

    template< typename std_duration_type = curr_std_duration_type,
              typename = enable_if_std_duration< std_duration_type > >
    constexpr std_duration_type to_std_duration() const noexcept; // since julian
    constexpr operator curr_std_duration_type() const noexcept;

    constexpr time_type count() const noexcept; // count of units(msec, sec etc)
    constexpr time_type count_since_epoch() const noexcept; // count of units since epoch
    constexpr date_time to_date_time() const noexcept; // convert to date_time

    // limits
    static constexpr curr_time_ratio max() noexcept; // max possible value for the current tick count and period

    // operators
    template< time_type other_tick_cnt, time_type other_sec_period >
    constexpr bool operator==( const time_ratio< other_tick_cnt, other_sec_period >& other ) const noexcept;

    template< time_type other_tick_cnt, time_type other_sec_period >
    constexpr bool operator!=( const time_ratio< other_tick_cnt, other_sec_period >& other ) const noexcept;

    time_ratio& operator+=( time_type count ) noexcept;
    time_ratio& operator-=( time_type count ) noexcept;

    template< time_type other_tick_cnt, time_type other_sec_period >
    time_ratio& operator+=( const time_ratio< other_tick_cnt, other_sec_period >& other ) noexcept;

    template< time_type other_tick_cnt, time_type other_sec_period >
    time_ratio& operator-=( const time_ratio< other_tick_cnt, other_sec_period >& other ) noexcept;

private:
    time_moment m_time;
    time_type m_count{ 0 }; // count of units for the current tick count and period
    static constexpr curr_time_ratio m_max{ std::numeric_limits< time_type >::max() };
};

template< time_type ltk, time_type lp, time_type rtk, time_type rp >
constexpr time_ratio< ltk, lp >
operator+( const time_ratio< ltk, lp >& l, const time_ratio< rtk, rp >& r ) noexcept;

template< time_type ltk, time_type lp, time_type rtk, time_type rp >
constexpr time_ratio< ltk, lp >
operator-( const time_ratio< ltk, lp >& l, const time_ratio< rtk, rp >& r ) noexcept;

}// details


}// temporal

#endif

#include "time_ratio_template.impl"
