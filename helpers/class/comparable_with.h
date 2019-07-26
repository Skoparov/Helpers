#ifndef _HELPERS_COMPARABLE_WITH_H_
#define _HELPERS_COMPARABLE_WITH_H_

namespace helpers{
namespace classes{

// A C++11-14 wanabe replacement for the C++17 spaceship operator

template<typename T>
class ComparableWith
{
    friend T;

public:
    constexpr bool operator==(const T& other) const noexcept
    {
        return Derived().Members() == other.Members();
    }

    constexpr bool operator!=(const T& other) const noexcept
    {
        return Derived().Members() != other.Members();
    }

    constexpr bool operator<(const T& other) const noexcept
    {
        return Derived().Members() < other.Members();
    }

    constexpr bool operator>(const T& other) const noexcept
    {
        return Derived().Members() > other.Members();
    }

    constexpr bool operator>=(const T& other) const noexcept
    {
        return Derived().Members() >= other.Members();
    }

    constexpr bool operator<=(const T& other) const noexcept
    {
        return Derived().Members() <= other.Members();
    }

private:
    ComparableWith() = default;
    ComparableWith(const ComparableWith&) = default;
    ComparableWith(ComparableWith&&) = default;
    ComparableWith& operator=(const ComparableWith&) = default;
    ComparableWith& operator=(ComparableWith&&) = default;
    ~ComparableWith() = default;

    constexpr const T& Derived() const noexcept
    {
        return static_cast<const T&>(*this);
    }
};

namespace details
{

template<typename T>
struct MemberType
{
    using type = typename std::conditional<std::is_trivially_copyable<T>::value, T, const T&>::type;
};

template<typename T>
using MemberType_t = typename MemberType<T>::type;

}

template<typename... Args>
using Members = std::tuple <details::MemberType_t<Args>...>;

/* 
All classes that inherit ComparableWith should implement Members<class member types...> Members() function
For example:

struct Test : ComparableWith<Test>
{
    int i;
    std::string s;

    Members<int, std::string> Members() const noexcept{ 
        return std::tie(i, s); 
    }
};

*/


}// classes
}// helpers
