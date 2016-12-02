#ifndef TUPLE_FIND_HELPER
#define TUPLE_FIND_HELPER

#include "details/tuple_find.h"
#include "details/tuple_size.h"

namespace helpers
{

namespace tuple
{

template< size_t start_index = 0, typename Target, typename T >
constexpr size_t tuple_find( Target&& target, T&& t )
{
    return details::_tuple_find< Target,
                                first_of_type< Target, start_index >( t ),
                                details::tuple_size( t ) >
                                ( std::forward< Target >( target ), std::forward< T >( t ) );
}

}

}

#endif
